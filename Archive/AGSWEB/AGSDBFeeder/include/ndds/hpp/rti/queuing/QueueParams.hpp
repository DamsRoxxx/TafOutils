/*
(c) Copyright, Real-Time Innovations, 2016-2017.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission. Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

 */

#ifndef RTI_QUEUING_PRODUCERPARAMS_HPP_
#define RTI_QUEUING_PRODUCERPARAMS_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/Optional.hpp>
#include <rti/request/detail/EntityParams.hpp>

namespace rti { namespace queuing {
    
    
template<typename T>
class QueueConsumerListener;
    
/**
 * \dref_QueueEntityParams
 *
 * @headerfile rti/queuing/QueueParams.hpp
 */ 
template <typename ActualEntity>    
class QueueEntityParams
    : public rti::request::detail::EntityParamsWithSetters<QueueEntityParams<ActualEntity> > {
public:

    typedef rti::request::detail::EntityParamsWithSetters<QueueEntityParams<ActualEntity> > Base;

    explicit QueueEntityParams(dds::domain::DomainParticipant participant)
        : Base(participant)
    {
    }
    
    const std::string& qos_library_name() const
    {
        return qos_library_name_;
    }

    const std::string& qos_profile_name() const
    {
        return qos_profile_name_;
    }
    
    /**
     * \dref_QueueEntityParams_qos_profile
     */
    ActualEntity& qos_profile(const std::string& qos_library_name,
                                 const std::string& qos_profile_name)
    {
        qos_library_name_ = qos_library_name;
        qos_profile_name_ = qos_profile_name;
        return static_cast<ActualEntity&>(*this);
    }
       
   
    const std::string& shared_subscriber_name() const
    {
        return shared_subscriber_name_;
    }    

    /**
     * \dref_QueueEntityParams_shared_subscriber_name
     */
    ActualEntity& shared_subscriber_name(const std::string& name)
    {
        shared_subscriber_name_ = name;
        return static_cast<ActualEntity&>(*this);
    }
    
    const std::string& entity_name() const
    {
        return entity_name_;
    }    

    /**
     * \dref_QueueEntityParams_entity_name
     */
    ActualEntity& entity_name(const std::string& name)
    {
        entity_name_ = name;
        return static_cast<ActualEntity&>(*this);
    }
    
    void validate() const
    {
        Base::validate();

        if (shared_subscriber_name_.empty()) {
            throw dds::core::InvalidArgumentError(
                    "shared_subscriber_name is required");
        }
    }
    
    ~QueueEntityParams()
    {
    }
 protected:
    std::string shared_subscriber_name_;
    std::string entity_name_;
    std::string qos_library_name_;
    std::string qos_profile_name_;  
};
    
/**
 * \dref_QueueProducerParams
 *
 * @headerfile rti/queuing/QueueParams.hpp
 */    
class QueueProducerParams
    : public QueueEntityParams<QueueProducerParams> {
public:

    /**
     * \dref_QueueProducerParams_new_simple
     */
    explicit QueueProducerParams(dds::domain::DomainParticipant participant)
        : QueueEntityParams<QueueProducerParams>(participant),
          enable_sample_replication_(false),
          enable_wait_for_ack_(false)
    {
    }
        
    /**
     * \dref_QueueProducerParams_enable_sample_replication
     */
    bool enable_sample_replication() const
    {
        return enable_sample_replication_;
    }    

    QueueProducerParams& enable_sample_replication(bool enable)
    {
        enable_sample_replication_ = enable;
        return *this;
    }
    
    bool enable_wait_for_ack() const
    {
        return enable_wait_for_ack_;
    }    

    /**
     * \dref_QueueProducerParams_enable_wait_for_ack
     */
    QueueProducerParams& enable_wait_for_ack(bool enable)
    {
        enable_wait_for_ack_ = enable;
        return *this;
    }
    
    ~QueueProducerParams()
    {
    }
protected:
    bool enable_sample_replication_;
    bool enable_wait_for_ack_;
};


/**
 * \dref_QueueConsumerParams
 *
 * @headerfile rti/queuing/QueueParams.hpp
 */
class QueueConsumerParams
    : public QueueEntityParams<QueueConsumerParams >  {
public:

    /**
     * \dref_QueueConsumerParams_new_simple
     */
    explicit QueueConsumerParams(dds::domain::DomainParticipant participant)
        : QueueEntityParams<QueueConsumerParams>(participant),
          enable_availability_(false)
    {
    } 
        
    bool enable_availability() const
    {
        return enable_availability_;
    }    

    /**
     * \dref_QueueConsumerParams_enable_availability
     */
    QueueConsumerParams& enable_availability(bool enable)
    {
        enable_availability_ = enable;
        return *this;
    }
 
    QueueConsumerParams& availability_datawriter_qos(
        const dds::core::optional<dds::pub::qos::DataWriterQos>& qos)
    {
        availability_datawriter_qos_ = qos;
        return *this;
    }

    const dds::core::optional<dds::pub::qos::DataWriterQos>&
    availability_datawriter_qos() const
    {
        return availability_datawriter_qos_;
    }

    ~QueueConsumerParams()
    {
    }
protected:
    bool enable_availability_;
    dds::core::optional<dds::pub::qos::DataWriterQos> availability_datawriter_qos_;
};


/**
 * \dref_QueueRequesterParams
 *
 * @headerfile rti/queuing/QueueParams.hpp
 */
class QueueRequesterParams
    : public QueueEntityParams<QueueRequesterParams >  {
public:

    /**
     * \dref_QueueRequesterParams_new_simple
     */
    explicit QueueRequesterParams(dds::domain::DomainParticipant participant)
        : QueueEntityParams<QueueRequesterParams>(participant),
          enable_availability_(false),
          enable_sample_replication_(false),
          enable_wait_for_ack_(false)      
    {
    } 
    
    bool enable_availability() const
    {
        return enable_availability_;
    }    

    /**
     * \dref_QueueRequesterParams_enable_availability
     */
    QueueRequesterParams& enable_availability(bool enable)
    {
        enable_availability_ = enable;
        return *this;
    }
    
    bool enable_sample_replication() const
    {
        return enable_sample_replication_;
    }    
    
    /**
     * \dref_QueueRequesterParams_enable_sample_replication
     */
    QueueRequesterParams& enable_sample_replication(bool enable)
    {
        enable_sample_replication_ = enable;
        return *this;
    }

    QueueRequesterParams& availability_datawriter_qos(
            const dds::core::optional<dds::pub::qos::DataWriterQos>& qos)
    {
        availability_datawriter_qos_ = qos;
        return *this;
    }

    const dds::core::optional<dds::pub::qos::DataWriterQos>& 
    availability_datawriter_qos() const
    {
        return availability_datawriter_qos_;
    }
    
    bool enable_wait_for_ack() const
    {
        return enable_wait_for_ack_;
    }    

    /**
     * \dref_QueueRequesterParams_enable_wait_for_ack
     */
    QueueRequesterParams& enable_wait_for_ack(bool enable)
    {
        enable_wait_for_ack_ = enable;
        return *this;
    }
    
    ~QueueRequesterParams()
    {
    }
    
protected:
    bool enable_availability_;
    dds::core::optional<dds::pub::qos::DataWriterQos> availability_datawriter_qos_;
    bool enable_sample_replication_;
    bool enable_wait_for_ack_;
};


/**
 * \dref_QueueReplierParams
 *
 * @headerfile rti/queuing/QueueParams.hpp
 */
class QueueReplierParams
    : public QueueEntityParams<QueueReplierParams >  {
public:

    /**
     * \dref_QueueReplierParams_new_simple
     */
    explicit QueueReplierParams(dds::domain::DomainParticipant participant)
        : QueueEntityParams<QueueReplierParams>(participant),
          enable_availability_(false),
          enable_sample_replication_(false),
          enable_wait_for_ack_(false)      
    {
    } 
        

    bool enable_availability() const
    {
        return enable_availability_;
    }    

    /**
     * \dref_QueueReplierParams_enable_availability
     */
    QueueReplierParams& enable_availability(bool enable)
    {
        enable_availability_ = enable;
        return *this;
    }
    
    QueueReplierParams& availability_datawriter_qos(
            const dds::core::optional<dds::pub::qos::DataWriterQos>& qos)
    {
        availability_datawriter_qos_ = qos;
        return *this;
    }

    const dds::core::optional<dds::pub::qos::DataWriterQos>& 
    availability_datawriter_qos() const
    {
        return availability_datawriter_qos_;
    }
    
    
    bool enable_sample_replication() const
    {
        return enable_sample_replication_;
    }    

    /**
     * \dref_QueueReplierParams_enable_sample_replication
     */
    QueueReplierParams& enable_sample_replication(bool enable)
    {
        enable_sample_replication_ = enable;
        return *this;
    }
    
    bool enable_wait_for_ack() const
    {
        return enable_wait_for_ack_;
    }    

    /**
     * \dref_QueueReplierParams_enable_wait_for_ack
     */
    QueueReplierParams& enable_wait_for_ack(bool enable)
    {
        enable_wait_for_ack_ = enable;
        return *this;
    }

    ~QueueReplierParams()
    {
    }
protected:
    bool enable_availability_;
    dds::core::optional<dds::pub::qos::DataWriterQos> availability_datawriter_qos_;
    bool enable_sample_replication_;
    bool enable_wait_for_ack_;
};


} }

#endif // RTI_QUEUING_PRODUCERPARAMS_HPP_
