/*
(c) Copyright, Real-Time Innovations, 2016-2017.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission. Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

 */

#ifndef RTI_REQUEST_DETAIL_GENERICSENDER_HPP_
#define RTI_REQUEST_DETAIL_GENERICSENDER_HPP_

#include <dds/core/QosProvider.hpp>
#include <dds/core/BuiltinTopicTypes.hpp>
#include <dds/domain/DomainParticipant.hpp>
#include <dds/pub/find.hpp>
#include <dds/pub/DataWriter.hpp>
#include <rti/request/detail/Common.hpp>
#include <rti/request/detail/EntityParams.hpp>

namespace rti { namespace request { namespace detail {

XMQCPP2DllExport
dds::pub::qos::DataWriterQos default_writer_qos();

template <typename T>
class GenericSender {
public:
    typedef T DataType;

    GenericSender(
            const EntityParams& params, 
            dds::topic::Topic<T> topic,
            const std::string& role_name,
            dds::pub::DataWriterListener<T>* listener = NULL,
            const dds::core::status::StatusMask& mask = 
                dds::core::status::StatusMask::none())
        : writer_(dds::core::null)
    {
        // Get customized Qos, if specified
        dds::pub::qos::DataWriterQos qos;
        if (params.datawriter_qos().is_set()) {
            qos = params.datawriter_qos().get();
        } else {
            qos = default_writer_qos();
        }

        set_role_name(qos, role_name);

        // Get Publisher
        dds::pub::Publisher publisher = params.publisher();
        if (publisher == dds::core::null) {
            // Use implicit publisher
            publisher = rti::pub::implicit_publisher(params.participant());
        }

        // Create Writer
        if (listener != NULL) {
            writer_ = dds::pub::DataWriter<T>(publisher, topic, qos, listener, mask);
        } else {
            writer_ = dds::pub::DataWriter<T>(publisher, topic, qos);
        }
    }
    
    void write(const T& data)
    {
        writer_.write(data);
    }

    void write(const T& data, rti::pub::WriteParams& params)
    {
        writer_->write(data, params);
    }

    dds::pub::DataWriter<T> writer() const
    {
        return writer_;
    }

private:
    dds::pub::DataWriter<T> writer_;
};

} } } // namespace rti::request::detail

#endif // RTI_REQUEST_DETAIL_GENERICSENDER_HPP_
