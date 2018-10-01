/*
(c) Copyright, Real-Time Innovations, 2016-2017.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission. Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

 */

#ifndef RTI_QUEUING_DETAIL_CONSUMERIMPL_HPP_
#define RTI_QUEUING_DETAIL_CONSUMERIMPL_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rti/core/detail/SelfReference.hpp>
#include <rti/core/EntityLock.hpp>
#include <dds/core/QosProvider.hpp>
#include <dds/sub/LoanedSamples.hpp>
#include <dds/pub/DataWriter.hpp>
#include <dds/sub/DataReader.hpp>
#include <dds/sub/discovery.hpp>

#include <rti/request/detail/GenericReceiver.hpp>
#include <rti/request/detail/Common.hpp>
#include <rti/queuing/QueueParams.hpp>
#include <rti/queuing/QueueConsumerListener.hpp>
#include <rti/queuing/detail/QueueSupportImpl.hpp>
#include <rti/queuing/QueueSupport.hpp>
#include <sstream>

#include <dds/core/xtypes/DynamicData.hpp>
#include <dds/core/xtypes/DynamicType.hpp>
#include <dds/core/xtypes/StructType.hpp>


namespace rti { namespace queuing { namespace detail {

typedef dds::pub::DataWriter<dds::core::xtypes::DynamicData> AvailiabilityWriter;

XMQCPP2DllExport
dds::sub::qos::DataReaderQos get_consumer_datareader_qos(
    const rti::queuing::QueueConsumerParams& params,
    const std::string& topic_name);

XMQCPP2DllExport
AvailiabilityWriter create_availability_writer(
    const rti::queuing::QueueConsumerParams& parameters,
    const std::string& consumer_topic_name);
    
template <typename T>
dds::topic::Topic<T> get_queue_consumer_topic(
    const rti::queuing::QueueConsumerParams& params);

template <typename T>
dds::topic::ContentFilteredTopic<T> create_consumer_cft(
    dds::domain::DomainParticipant participant,
    dds::topic::Topic<T> topic,
    const rti::core::Guid& consumer_guid);  

XMQCPP2DllExport
std::string create_consumer_filter_expression(
    const rti::core::Guid& consumer_guid); 

template <typename T>
void set_content_filter_for_receiver(
        rti::request::detail::GenericReceiver<T>& receiver,
        const rti::core::Guid& consumer_guid);

template <typename T>
rti::core::Guid get_data_reader_virtual_guid(const dds::sub::DataReader<T> reader) 
{
    dds::sub::qos::DataReaderQos reader_qos = reader.qos();
    return reader_qos.policy<rti::core::policy::DataReaderProtocol>().virtual_guid();
}

template <typename T>
dds::topic::Topic<T> get_queue_consumer_topic(
    const rti::queuing::QueueConsumerParams& params)
{
    std::string reader_topic_name = 
        get_consumer_reader_topic_name(
            params.request_topic_name(), 
            params.shared_subscriber_name());
    
    dds::topic::TopicDescription<T> topic_desc = 
        rti::request::detail::get_or_create_topic<T>(
            params.participant(),
            reader_topic_name,
            dds::core::optional<dds::core::xtypes::DynamicType>(), // TODO: support DynamicData
            false); 

    return dds::core::polymorphic_cast<dds::topic::Topic<T> >(topic_desc); 
}


template <typename T>
void set_content_filter_for_receiver(
        rti::request::detail::GenericReceiver<T>& receiver,
        const rti::core::Guid& consumer_guid)         
{
    std::string cft_expression =
        create_consumer_filter_expression(
            (consumer_guid != rti::core::Guid::unknown())?
                consumer_guid : get_data_reader_virtual_guid(receiver.reader()));
    dds::topic::TopicDescription<T> topicDesc = 
        receiver.reader().topic_description();
    dds::topic::ContentFilteredTopic<T> cft = 
        dds::core::polymorphic_cast<dds::topic::ContentFilteredTopic<T> >(topicDesc);

    cft->filter(dds::topic::Filter(cft_expression, cft.filter_parameters()));  
}


template <typename T>
class QueueConsumerImpl
    : public rti::core::detail::RetainableType<QueueConsumerImpl<T> > {
public:
    typedef rti::queuing::QueueConsumerListener<T> Listener;
    typedef std::map<
                dds::core::InstanceHandle, 
                QueuingServiceMatchedInfo, 
                InstanceHandleComparator> ServiceInstanceMap;
    
    explicit QueueConsumerImpl(
        const rti::queuing::QueueConsumerParams& parameters,      
        const rti::core::Guid& consumer_guid)
            : listener_(NULL), 
              internal_data_reader_listener_(NULL),
              consumer_topic_(get_queue_consumer_topic<T>(parameters)),
              receiver_(create_disabled_reader(parameters)),
              consumer_guid_(
                    ensure_valid_guid(
                        consumer_guid, 
                        parameters.participant(), 
                        parameters.entity_name(),
                        parameters.request_topic_name())),
              availability_writer_(
                    create_availability_writer(parameters, consumer_topic_.name())),
              is_closed_(false)
    {    
       /* Crate reader always disabled to:
        * - avoid race condition on the listener and 
        * - be able to use the reader virtual GUID that is computed after reader
        * creation. Since this requires creating the CFT first, to avoid the discovery
        * of the reader with a different filter, we create it disabled and wait 
        * to enable it until the filter expression is set. */  
        
        /* The content filter expression cannot be set at the time the receiver 
         * is created because the expression includes the data reader virtual guid
         * when the consumer_guid is provided as unknown. */  
        set_content_filter_for_receiver(receiver_, consumer_guid_);
    }
    
    
    void initialize(
        dds::sub::DataReaderListener<T>* data_reader_listener,    
        Listener* consumer_listener,
        bool is_enabled) 
    {
        internal_data_reader_listener_ = data_reader_listener;
        receiver_.reader().listener(
            internal_data_reader_listener_,
            dds::core::status::StatusMask::all());
        
        if (consumer_listener) {
            listener(consumer_listener, dds::core::status::StatusMask::all());
        }
        
        if (is_enabled) {  
            enable(); 
        }
    }

    
    Listener* listener() {
        return listener_; 
    }
    
    /* event_mask is required by listener binder and has no effect */
    void listener(
        Listener* the_listener,
        const dds::core::status::StatusMask&)
    {
        listener_ = the_listener;
        if (listener_ == NULL) {
            this->unretain();
        } else {
            this->retain();
        }
    }
    
    
    bool closed() {
        return is_closed_;
    }
    
    void enable() 
    {
        receiver_.reader().enable();
    }
    
    
    void acknowledge_sample(
        const dds::sub::SampleInfo& sample_info, 
        bool is_positive_acknowledgment) 
    { 
        dds::core::ByteSeq response_data;
        if (is_positive_acknowledgment) {
            response_data.push_back(1);
        } else {
            response_data.push_back(0); 
        } 
        rti::sub::AckResponseData response(response_data);
        /* response.value(response_data.begin(), response_data.end()); */
        receiver_.reader()->acknowledge_sample(sample_info, response);
    }
    
    void acknowledge_all(
        bool is_positive_acknowledgment) 
    { 
        dds::core::ByteSeq response_data;
        if (is_positive_acknowledgment) {
            response_data.push_back(1);
        } else {
            response_data.push_back(0); 
        } 
        rti::sub::AckResponseData response(response_data);
       /*  response.value(response_data.begin(), response_data.end()); */
        receiver_.reader()->acknowledge_all(response);
    }
    
    dds::sub::DataReader<T> reader() const
    {
        return receiver_.reader();
    }
    
    rti::request::detail::GenericReceiver<T> receiver() const
    {
        return receiver_;
    }
    
    rti::core::Guid guid() 
    {
        return consumer_guid_;
    }
    
    dds::sub::LoanedSamples<T> receive_samples(const dds::core::Duration& max_wait) 
    {
        return receive_samples(1, dds::core::LENGTH_UNLIMITED, max_wait);
    }
    
    dds::sub::LoanedSamples<T> receive_samples(
            int min_count, 
            int max_count,
            const dds::core::Duration& max_wait) 
    {
        return receiver_.receive_samples(min_count, max_count, max_wait, true);
    }
    
    dds::sub::LoanedSamples<T> take_samples()
    {
        return receiver_.read_or_take(dds::core::LENGTH_UNLIMITED, true);
    }
    
    dds::sub::LoanedSamples<T> take_samples(int max_count)
    {
        return receiver_.read_or_take(max_count, true);
    }
    
    dds::sub::LoanedSamples<T> read_samples()
    {
        return receiver_.read_or_take(dds::core::LENGTH_UNLIMITED, false);
    }
    
    dds::sub::LoanedSamples<T> read_samples(int max_count)
    {
        return receiver_.read_or_take(max_count, false);
    }
   
    bool wait_for_samples(const dds::core::Duration& max_wait)
    {
        return receiver_.wait_for_any_sample(1, max_wait);
    }
    
    bool wait_for_samples(int min_count, const dds::core::Duration& max_wait)
    {
        return receiver_.wait_for_any_sample(min_count, max_wait);
    }
    
    void send_availability(
            ConsumerAvailabilityParams availability_params) 
    {
        using namespace dds::core::xtypes;
        if (availability_writer_ == dds::core::null) {
            throw dds::core::PreconditionNotMetError(
                    "availabilty not enabled in this Consumer"); 
        }
        DynamicData availability_sample(
            ConsumerAvailabilitySupport::get_availability_type_code());
        ConsumerAvailabilitySupport::initialize_availability_sample(
            availability_sample, consumer_guid_);
        ConsumerAvailabilitySupport::set_availability_params(
            availability_sample, availability_params);

        availability_writer_.write(availability_sample);  
    }
    
    bool has_matching_reader_queue()
    {
        rti::core::EntityLock lock_(receiver_.reader());
        return !queuing_service_instances_.empty();
    }
    
    bool process_on_subscription_matched(
        const dds::core::status::SubscriptionMatchedStatus& status) 
    {
        rti::core::EntityLock lock_(receiver_.reader());
        unsigned long instances_count = queuing_service_instances_.size();
        
        if (status.current_count_change() > 0) {            
            dds::topic::PublicationBuiltinTopicData publication_data = 
                dds::sub::matched_publication_data(
                    receiver_.reader(), 
                    status.last_publication_handle());
            
            if (publication_data->service().kind() ==
                rti::core::policy::ServiceKind::QUEUING) 
            {
                QueuingServiceMatchedInfo info;
                info.epoch_ = 0;
                queuing_service_instances_[status.last_publication_handle()] = info;
            }
        } else {
            queuing_service_instances_.erase(status.last_publication_handle());      
        }
        return (instances_count != (unsigned long) queuing_service_instances_.size());
    }
    
    void close() {
        if (internal_data_reader_listener_ != NULL) {
            if (!receiver_.reader()->closed()) {
                receiver_.reader().listener(
                    NULL, dds::core::status::StatusMask::none());
            }
            delete internal_data_reader_listener_;
            internal_data_reader_listener_ = NULL;
        }
        is_closed_ = true;
    }
    
    ~QueueConsumerImpl() 
    {
        close();
    }        
private:
    
    /* This class makes sure the subscriber creates disabled entities.
     * The participant is locked in order to avoid race condition with other
     * threads using the subscriber. */
    class EnforceSubscriberDisabledEntitiyCreation { 
    public:
        EnforceSubscriberDisabledEntitiyCreation(
            dds::domain::DomainParticipant& participant,
            dds::sub::Subscriber& subscriber) 
            : subscriber_(subscriber),
              lock_(participant),
              subscriber_initial_qos_(subscriber_.qos())
        {    
            /* lock the participant so there is no race condition with other
             * threads using the subscriber.
             * This operation takes the entity lock that is the participant tableEA,
             * taken in all the operations that require access the reader group */
            dds::sub::qos::SubscriberQos subscriber_qos = subscriber_.qos(); 
            subscriber_qos.policy<dds::core::policy::EntityFactory>().autoenable_created_entities(false);  
            subscriber_.qos(subscriber_qos); 
        }
        
        ~EnforceSubscriberDisabledEntitiyCreation() {
            /* Leave subscriber unaltered  */ 
            subscriber_.qos(subscriber_initial_qos_); 
        }
    private:
        dds::sub::Subscriber subscriber_;
        rti::core::EntityLock lock_;
        dds::sub::qos::SubscriberQos subscriber_initial_qos_;
    };
    
    
    rti::request::detail::GenericReceiver<T> create_disabled_reader(
        const rti::queuing::QueueConsumerParams& params) 
    { 
        rti::queuing::QueueConsumerParams parameters = params;
        dds::domain::DomainParticipant participant = parameters.participant();
        dds::sub::Subscriber subscriber = parameters.subscriber();
        
        if (participant == dds::core::null) {
            throw dds::core::InvalidArgumentError("participant is null");
        }

        if (subscriber == dds::core::null) {
            subscriber = rti::sub::implicit_subscriber(participant);
        }
        
        /* Prepare participant and subscriber to create data reader disabled */
        EnforceSubscriberDisabledEntitiyCreation disabler(participant, subscriber);

        dds::sub::qos::DataReaderQos reader_qos = 
            get_consumer_datareader_qos(parameters, consumer_topic_.name());
        
        return rti::request::detail::GenericReceiver<T>(
            parameters.datareader_qos(reader_qos),     
            create_empty_consumer_cft(consumer_topic_),
            "QueueConsumer");
    }
    
    dds::topic::ContentFilteredTopic<T> create_empty_consumer_cft(
        dds::topic::Topic<T> topic)
    {
        std::stringstream pointer_as_string;
        pointer_as_string << static_cast<const void*>(this);
        
        std::string cft_name = 
                "queue consumer filter on " +
                topic.name() + " " +
                pointer_as_string.str(); 
        std::string cft_expression =  "1 = 1"; 

        return dds::topic::ContentFilteredTopic<T>(
            topic,
            cft_name,
            dds::topic::Filter(cft_expression));
    }
    
    
    /* ------------------------------------------------------------ */
    /* ------------------------------------------------------------ */
    /* -------------------- Private variables --------------------- */
    /* ------------------------------------------------------------ */
    /* ------------------------------------------------------------ */
    
    Listener* listener_;
    ServiceInstanceMap queuing_service_instances_;
    dds::sub::DataReaderListener<T>* internal_data_reader_listener_;
    dds::topic::Topic<T> consumer_topic_;
    rti::request::detail::GenericReceiver<T> receiver_;
    rti::core::Guid consumer_guid_;
    AvailiabilityWriter availability_writer_;
    bool is_closed_;
};



} } } // namespace rti::request::detail

#endif // RTI_QUEUING_DETAIL_CONSUMERIMPL_HPP_

