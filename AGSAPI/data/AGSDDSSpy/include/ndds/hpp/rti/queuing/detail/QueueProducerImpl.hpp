/*
(c) Copyright, Real-Time Innovations, 2016-2017.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission. Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

 */


#ifndef RTI_QUEUING_DETAIL_PRODUCERIMPL_HPP_
#define RTI_QUEUING_DETAIL_PRODUCERIMPL_HPP_

//#define SINGLE_ACK_POLICY_FOR_REPLICATED_QS /* this is disabled by deffault.  */

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>
#include <rti/core/detail/SelfReference.hpp>
#include <rti/core/EntityLock.hpp>
#include <dds/core/QosProvider.hpp>
#include <dds/core/detail/InstanceHandle.hpp>
#include <dds/pub/DataWriter.hpp>
#include <dds/sub/DataReader.hpp>
#include <dds/pub/discovery.hpp>

#include <rti/core/InstanceHandle.hpp>
#include <rti/core/Semaphore.hpp>
#include <rti/request/detail/GenericSender.hpp>
#include <rti/request/detail/Common.hpp>
#include <rti/queuing/QueueParams.hpp>
#include <rti/queuing/QueueProducerListener.hpp>
#include <rti/queuing/detail/QueueSupportImpl.hpp>
#include <rti/queuing/QueueSupport.hpp>
#include <map>

namespace rti { namespace queuing {

template <typename T>
class QueueProducer;

}}



namespace rti { namespace queuing { namespace detail {
 
XMQCPP2DllExport
dds::pub::qos::DataWriterQos get_producer_datawriter_qos(
    const rti::queuing::QueueProducerParams& params,
    const std::string& topic_name);

XMQCPP2DllExport
rti::core::SampleFlag set_sample_flag(
    const rti::queuing::QueueProducerParams& params);
    
    
template <typename T>
dds::topic::Topic<T> get_queue_producer_topic(
    const rti::queuing::QueueProducerParams& params);

template <typename T>
dds::topic::Topic<T> get_queue_producer_topic(
    const rti::queuing::QueueProducerParams& params)
{
    dds::topic::TopicDescription<T> topic_desc = 
            rti::request::detail::get_or_create_topic<T>(
                params.participant(),
                params.request_topic_name(),
                dds::core::optional<dds::core::xtypes::DynamicType>(), // TODO: support DynamicType
                false); 

    return dds::core::polymorphic_cast<dds::topic::Topic<T> >(topic_desc); 
}
 
template <typename T>
rti::core::SampleIdentity initialize_sample_identity(
    const rti::request::detail::GenericSender<T>& sender)
{
    dds::pub::DataWriter<T> writer = sender.writer(); 
    dds::pub::qos::DataWriterQos writer_qos = writer.qos();
    
    rti::core::Guid writer_guid =
        writer_qos.policy<rti::core::policy::DataWriterProtocol>().virtual_guid();
    rti::core::SequenceNumber sequence_number(0, 0);
    
    return rti::core::SampleIdentity(writer_guid, sequence_number);
}


/* Information stored per sample identity
 *  when wait for acknowledgments is set*/
struct SampleWaitForAckInfo {
    rti::pub::AcknowledgmentInfo info;
    int mathced_instances_;
    long long send_epoch_;
    bool already_waiting;
}; 

/**/
template <typename T>
class QueueProducerImpl
    : public rti::core::detail::RetainableType<QueueProducerImpl<T> > {
public:
    typedef rti::queuing::QueueProducerListener<T> Listener;
    typedef std::map<
            rti::core::SampleIdentity, 
            SampleWaitForAckInfo, 
            SampleIdentityComparator> SampleIdentityMap;
    typedef std::map<
            dds::core::InstanceHandle, 
            QueuingServiceMatchedInfo, 
            InstanceHandleComparator> ServiceInstanceMap;
    
    explicit QueueProducerImpl(
        const rti::queuing::QueueProducerParams& parameters,
        const rti::core::Guid& producer_guid)
            : listener_(NULL), 
              internal_data_writer_listener_(NULL),
              producer_topic_(get_queue_producer_topic<T>(parameters)),
              sender_(create_disabled_sender(parameters)),
              send_identity_(initialize_sample_identity(sender_)),
              producer_guid_(
                    ensure_valid_guid(
                        producer_guid, 
                        parameters.participant(), 
                        parameters.entity_name(),
                        parameters.request_topic_name())),
              sample_flag_(set_sample_flag(parameters)),
              concurrent_send_mutex_(RTI_OSAPI_SEMAPHORE_KIND_MUTEX),
              send_epoch_(0),
              wait_for_ack_enabled_(parameters.enable_wait_for_ack()),
              number_of_threads_waiting_for_any_sample_(false),
              is_waiting_for_all_acks_(false),
              is_closed_(false)
    {

    }
           
    void initialize(
        dds::pub::DataWriterListener<T>* data_writer_listener,
        Listener* producer_listener,
        bool is_enabled) 
    {
        internal_data_writer_listener_ = data_writer_listener;
        sender_.writer().listener(
            internal_data_writer_listener_,
            dds::core::status::StatusMask::all());
        
        if (producer_listener) {
            listener(producer_listener, dds::core::status::StatusMask::all());
        }
        
        if (is_enabled) {  
            enable(); 
        }
        
        
    }

    
    Listener* listener() 
    {
        return listener_; 
    }
    
    
    /* event_mask is required by listener binder and has no effect */
    void listener(
        Listener* the_listener,
        const dds::core::status::StatusMask&)
    {
        listener_ = the_listener;
        if (listener_ == NULL) {
            sender_.writer().listener(
                NULL,
                dds::core::status::StatusMask::all());
            this->unretain();
        } else {
            this->retain();
        }
    }
    
    bool closed() 
    {
        return is_closed_;
    }
    
    void enable() {
        sender_.writer().enable(); 
    }
    
    void send_sample(const T& data, rti::pub::WriteParams& write_params)
    {
        throw_if_no_matching_queues();
        
        write_params.replace_automatic_values(true); // to obtain the actual identity
        write_params.source_guid(producer_guid_);
        write_params.flag(sample_flag_ | write_params.flag());
        
        if (wait_for_ack_enabled_) {
            rti::core::LockGuard concurrent_send_lock(concurrent_send_mutex_);
            { 
                rti::core::EntityLock lock(sender_.writer());
                
                rti::core::SampleIdentity write_params_input_identity =
                        write_params.identity();

                if (write_params_input_identity.sequence_number() ==
                        rti::core::SequenceNumber::automatic()) 
                {
                    identity_plus_plus();
                    /* guid is set to writer's virtual guid */
                    write_params.identity(send_identity_);
                }
                
                if (write_params_input_identity.writer_guid() !=
                        rti::core::Guid::automatic()) 
                {
                    rti::core::SampleIdentity sample_identity(
                        write_params_input_identity.writer_guid(),
                        write_params.identity().sequence_number());
                    write_params.identity(sample_identity);
                } 

                SampleWaitForAckInfo info;
                info.send_epoch_ = send_epoch_;
                info.mathced_instances_ = queuing_service_instances_.size();
                info.already_waiting = false;
                samples_pending_ack_[write_params.identity()] = info;
            }
            sender_.write(data, write_params);
        } else {
          #ifdef SINGLE_ACK_POLICY_FOR_REPLICATED_QS
            throw dds::core::InvalidArgumentError("incompatible mode");
          #endif  
            sender_.write(data, write_params);
        }
    }
    
    void send_sample(const T& data)
    {
        rti::pub::WriteParams write_params;
        send_sample(data, write_params);
    }  
    
    bool wait_for_acknowledgments(const dds::core::Duration& max_wait) 
    {   
        if (!wait_for_ack_enabled_) {
            throw dds::core::PreconditionNotMetError("wait for acknowledgments is not enabled");
        }
        
        {
            rti::core::EntityLock lock(sender_.writer());
            
            if (is_waiting_for_all_acks_ || number_of_threads_waiting_for_any_sample_ > 0) {
                throw dds::core::IllegalOperationError("only one thread at a time can wait for acknowledgments");
            }
            is_waiting_for_all_acks_ = true;
            send_epoch_++; 
        }
  
        bool all_ack_positive = true;
        
        try {
            sender_.writer().wait_for_acknowledgments(max_wait);  
            throw_if_no_matching_queues();
            
            { /* if timed out this code is not read: */
                rti::core::EntityLock lock(sender_.writer());
                
                SampleIdentityMap::iterator it = samples_pending_ack_.begin();
                while (it != samples_pending_ack_.end()) 
                {
                    // Samples with equal epoch to the one observed when this 
                    // operation is called never got a positive ACK
                    if (it->second.send_epoch_ < send_epoch_) {
                        all_ack_positive = false;
                        samples_pending_ack_.erase(it);
                        /* for extra security if map re-sorts after erase */
                        it = samples_pending_ack_.begin(); 
                    } else {
                        ++it;
                    }
                }
                
                is_waiting_for_all_acks_ = false;
            }
        } 
        catch (const std::exception &exc) 
        {         
            rti::core::EntityLock lock(sender_.writer());
            is_waiting_for_all_acks_ = false;
            throw;
        }
        
        return all_ack_positive;
    }
    
    bool wait_for_acknowledgments(
        const rti::core::SampleIdentity& identity,
        const dds::core::Duration& max_wait) 
    {
        if (!wait_for_ack_enabled_) {
            throw dds::core::PreconditionNotMetError("wait for acknowledgments is not enabled");
        }
        
        {
            rti::core::EntityLock lock(sender_.writer());
            
            if (is_waiting_for_all_acks_) {
                throw dds::core::IllegalOperationError(
                        "another thread is waiting for acknowledgements of all the samples");
            }
            
            SampleIdentityMap::iterator it = samples_pending_ack_.find(identity); 
            if (it != samples_pending_ack_.end()) {
                if (it->second.already_waiting) {
                    throw dds::core::IllegalOperationError(
                            "only one thread at a time can wait for"
                            " acknowledgments of a particular sample");
                }
                it->second.already_waiting = true;
                number_of_threads_waiting_for_any_sample_++;
                send_epoch_++;
            } else {
                /* the sample is not in the list either because
                 * it was removed from the listener (positive ack)
                 * or because it is the second time we call the operation
                 * on the same sample (invalid) 
                 */
                return true;
            }
        }
            
        try { 
            sender_.writer()->wait_for_sample_acknowledgment(identity, max_wait);
            throw_if_no_matching_queues();

            {
                rti::core::EntityLock lock(sender_.writer());
                number_of_threads_waiting_for_any_sample_--;
                return (samples_pending_ack_.erase(identity) == 0);
            }
        } 
        catch (const std::exception& exc) 
        {  
            rti::core::EntityLock lock(sender_.writer());
            SampleIdentityMap::iterator it = samples_pending_ack_.find(identity); 
            if (it != samples_pending_ack_.end()) {
                it->second.already_waiting = false;
            }
            number_of_threads_waiting_for_any_sample_--;
            throw;
        } 
    }
    
     
    /* returns true if producer listener should be called  */
    bool process_received_acknowledgment(
        const rti::pub::AcknowledgmentInfo& info)
    { 
       /* Set to false to implement single ack/nack policy for 
        * replicated queuing services  */
      #ifdef SINGLE_ACK_POLICY_FOR_REPLICATED_QS
        bool call_user_callback = false;
      #else 
        if (!wait_for_ack_enabled_) {
            return true;
        }
        /* user is always called*/
        bool call_user_callback = true;
      #endif  
   
        {
            // This callback occurs within the write EA, so access to
            // the list of pending ACK is safe
            // rti::core::EntityLock lock(sender_.writer());
                        
            SampleIdentityMap::iterator it = 
                    samples_pending_ack_.find(info.sample_identity()); 
            if (it != samples_pending_ack_.end()) {
                if (rti::queuing::is_positive_ack(info.response_data())) {
                    
                    if (number_of_threads_waiting_for_any_sample_ >= 0) { 
                        if (it->second.already_waiting) {
                            struct DDS_SampleIdentity_t native_identity =
                                    info.sample_identity().native();
                            DDS_DataWriter * native_data_witer = sender_.writer()->native_writer();
                            DDS_DataWriter_unblock_wait_for_sample_acknowledgmentI(
                                    native_data_witer, 
                                    &native_identity);
                        } 
                    }  
                   
                    /* remove sample at first positive ack */
                    samples_pending_ack_.erase(info.sample_identity());
                  #ifdef SINGLE_ACK_POLICY_FOR_REPLICATED_QS
                    nack_all_prior_to(info.sample_identity().sequence_number(), producer); 
                  #endif  
                    call_user_callback = true;
                } else {
                  #ifdef SINGLE_ACK_POLICY_FOR_REPLICATED_QS  
                    /* remove negative when all have nacked */
                    SampleWaitForAckInfo  * wait_data = &samples_pending_ack_[info.sample_identity()];
                    wait_data->info = info;
                    if (--wait_data->mathced_instances_ == 0) {
                        samples_pending_ack_.erase(info.sample_identity());
                        call_user_callback = true;
                    } 
                  #endif  
                }
                
                if (is_waiting_for_all_acks_) {
                    if (samples_pending_ack_.empty()) {
                        DDS_DataWriter * native_data_witer = sender_.writer()->native_writer();
                        DDS_DataWriter_unblock_wait_for_acknowledgmentsI(native_data_witer);
                    } 
                }
            } 
        } 

        return call_user_callback;
    }
    
    bool has_matching_reader_queue()
    {
        return !queuing_service_instances_.empty();
    }
    
    /* returns true iff producer listener should be called  */
    bool process_on_publication_matched(
        const dds::core::status::PublicationMatchedStatus& status) 
    {
        rti::core::EntityLock lock(sender_.writer());
        unsigned long instances_count = queuing_service_instances_.size();
        
        if (status.current_count_change() > 0) {
            dds::topic::SubscriptionBuiltinTopicData subscription_data = 
                dds::pub::matched_subscription_data(
                    sender_.writer(), 
                    status.last_subscription_handle());
            
            if (subscription_data->service().kind() == rti::core::policy::ServiceKind::QUEUING) {
                QueuingServiceMatchedInfo info;
                info.epoch_ = 0;
                queuing_service_instances_[status.last_subscription_handle()] = info;
              #ifdef SINGLE_ACK_POLICY_FOR_REPLICATED_QS  
                add_one_pending_instance_to_all();
              #endif          
            }
        } else {
            queuing_service_instances_.erase(status.last_subscription_handle());      
        }
        return (instances_count != (unsigned long) queuing_service_instances_.size());
    }
    
    dds::pub::DataWriter<T> writer() const
    {
        return sender_.writer();
    }
    
    rti::core::Guid guid()
    {
        return producer_guid_;
    }

    void close() {
        if (internal_data_writer_listener_ != NULL) {
            if (!sender_.writer()->closed()) {
                sender_.writer().listener(
                    NULL, dds::core::status::StatusMask::none());
            }
            delete internal_data_writer_listener_;
            internal_data_writer_listener_ = NULL;
        }
        is_closed_ = true;
    }
    
    ~QueueProducerImpl() 
    {
        close();
    }  
private:
    
   /* This class makes sure the publisher creates disabled entities.
    * The participant is locked in order to avoid race condition with other
    * threads using the publisher. */
    class EnforcePublisherDisabledEntitiyCreation { 
    public:
        EnforcePublisherDisabledEntitiyCreation(
            dds::domain::DomainParticipant& participant,
            dds::pub::Publisher& publisher) 
            : publisher_(publisher),
              lock_(participant),
              publisher_initial_qos_(publisher_.qos())
        {    
            /* lock the participant so there is no race condition with other
             * threads using the subscriber.
             * This operation takes the entity lock that is the participant tableEA,
             * taken in all the operations that require access the reader group */
            dds::pub::qos::PublisherQos publisher_qos = publisher_.qos(); 
            publisher_qos.policy<dds::core::policy::EntityFactory>().autoenable_created_entities(false);  
            publisher_.qos(publisher_qos); 
        }
        
        ~EnforcePublisherDisabledEntitiyCreation() {
            /* Leave publisher unaltered  */ 
            publisher_.qos(publisher_initial_qos_); 
        }
    private:
        dds::pub::Publisher publisher_;
        rti::core::EntityLock lock_;
        dds::pub::qos::PublisherQos publisher_initial_qos_;
    };
    
    rti::request::detail::GenericSender<T> create_disabled_sender(
        const rti::queuing::QueueProducerParams& params) 
    { 
        rti::queuing::QueueProducerParams parameters = params;
        dds::domain::DomainParticipant participant = parameters.participant();
        dds::pub::Publisher publisher = parameters.publisher();
        
        if (participant == dds::core::null) {
            throw dds::core::InvalidArgumentError("participant is null");
        }

        if (publisher == dds::core::null) {
            publisher = rti::pub::implicit_publisher(participant);
        }
        
        /* Prepare participant and publisher to create data writer disabled */
        EnforcePublisherDisabledEntitiyCreation disabler(participant, publisher);
        
        dds::pub::qos::DataWriterQos writer_qos = 
                get_producer_datawriter_qos(parameters, producer_topic_.name());

        return rti::request::detail::GenericSender<T>(
            parameters.datawriter_qos(writer_qos), 
            producer_topic_,
            "QueueProducer");
    }

    void identity_plus_plus() 
    {
        rti::core::SequenceNumber sequence_number = send_identity_.sequence_number();
        rti::core::Guid writer_guid = send_identity_.writer_guid();
        sequence_number++;
        send_identity_ = rti::core::SampleIdentity(writer_guid, sequence_number);
    }
    
    void throw_if_no_matching_queues()
    {
        if (!has_matching_reader_queue())
        {
            throw NoMatchingQueueException(producer_guid_);
        }
    }
    
  #ifdef SINGLE_ACK_POLICY_FOR_REPLICATED_QS
    void nack_all_prior_to(
        rti::core::SequenceNumber& sequence_number, 
        QueueProducer<T>& producer) 
    {
        SampleIdentityMap::iterator it = samples_pending_ack_.begin();
        
        while (it != samples_pending_ack_.end()) {
            if (it->first.sequence_number() < sequence_number) {
                if (listener_) {
                    listener_->on_sample_acknowledged(producer, it->second.info);
                }
                samples_pending_ack_.erase(it++);
            } else { it++; }
        }
    }
     
    void add_one_pending_instance_to_all() {        
        rti::core::EntityLock lock(sender_.writer());
        for (SampleIdentityMap::iterator it = samples_pending_ack_.begin(); 
            it != samples_pending_ack_.end(); ++it) {
            it->second.mathced_instances_++;
        }
    }
  #endif 
    /* ------------------------------------------------------------ */
    /* ------------------------------------------------------------ */
    /* -------------------- Private variables --------------------- */
    /* ------------------------------------------------------------ */
    /* ------------------------------------------------------------ */
    
    SampleIdentityMap samples_pending_ack_;
    ServiceInstanceMap queuing_service_instances_;
    
    Listener* listener_;
    dds::pub::DataWriterListener<T>* internal_data_writer_listener_;
    dds::topic::Topic<T> producer_topic_;
    rti::request::detail::GenericSender<T> sender_;
    rti::core::SampleIdentity send_identity_;
    rti::core::Guid producer_guid_;
    rti::core::SampleFlag sample_flag_;
    rti::core::Semaphore concurrent_send_mutex_;
    long long send_epoch_;
    bool wait_for_ack_enabled_;
    int number_of_threads_waiting_for_any_sample_;
    bool is_waiting_for_all_acks_;
    bool is_closed_;
};

} } } // namespace rti::request::detail

#endif // RTI_QUEUING_DETAIL_PRODUCERIMPL_HPP_
