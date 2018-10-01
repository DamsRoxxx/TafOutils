#ifndef OMG_DDS_PUB_TDATA_WRITER_HPP_
#define OMG_DDS_PUB_TDATA_WRITER_HPP_

/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Corp.
 * Copyright 2010, Real-Time Innovations, Inc.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/InstanceHandle.hpp>
#include <dds/core/Time.hpp>
#include <dds/topic/Topic.hpp>
#include <dds/topic/TopicInstance.hpp>
#include <dds/pub/Publisher.hpp>

#include <dds/pub/detail/DataWriter.hpp>

namespace dds {
  namespace pub {
    template <typename T, template <typename Q> class DELEGATE>
    class DataWriter;

    template <typename T> class DataWriterListener;
  }
}

/** 
 * @ingroup DDSWriterModule 
 * @RTI_class_definition template <typename T> class dds::pub::DataWriter : public dds::core::Entity
 * @headerfile dds/pub/DataWriter.hpp
 *  
 * @brief @st_ref_type Allows an application to publish data for a dds::topic::Topic

 * @tparam T The topic-type that the DataWriter publishes
 *
 * @details \dref_details_DataWriter 
 * @section Deleting_DataWriter Notes about DataWriter destruction
 * \dref_details_Publisher_delete_datawriter 
 *
 * @see \ref DDSWriterExampleModule
 * @see \ref DDSEntityExampleModuleForCpp2
 */ 
template <typename T, template <typename Q> class DELEGATE>
class dds::pub::DataWriter : public dds::core::TEntity< DELEGATE<T> > {

public:
    typedef dds::pub::DataWriterListener<T> Listener;

public:
  OMG_DDS_REF_TYPE(DataWriter, dds::core::TEntity, DELEGATE<T>)

public:

  /**
   * @brief Creates a DataWriter.
   *
   * It uses the default DataWriterQos, and sets no listener.
   *
   * @param pub The publisher that this DataWriter belongs to
   * @param the_topic The Topic associated with this DataWriter
   *
   * @see DataWriter(const dds::pub::Publisher& pub,const dds::topic::Topic<T>& topic,const dds::pub::qos::DataWriterQos& qos,dds::pub::DataWriterListener<T>* listener,const dds::core::status::StatusMask& mask)
   */
  DataWriter(
      const dds::pub::Publisher& pub,
      const dds::topic::Topic<T>& the_topic)
      : dds::core::TEntity<DELEGATE<T> >(new DELEGATE<T>(pub, the_topic))
   {
      this->delegate()->remember_reference(this->delegate());
   }

  /**
   * @brief Creates a DataWriter with QoS and listener
   *
   * When a DataWriter is created, only those transports
   * already registered are available to the DataWriter.
   * See \ref NDDS_TransportBuiltinsComponent for details on when a builtin transport is registered.
   *
   * @pre If publisher is enabled, topic must have been enabled.
   * Otherwise, this operation will fail and no
   * DataWriter will be created.
   *
   * @pre The given dds::topic::Topic must have been created from
   * the same participant as this publisher. If it was created
   * from a different participant, this \method will fail.
   *
   * @param pub The publisher that this DataWriter belongs to
   * @param the_topic The Topic associated with this DataWriter
   * @param the_qos QoS to be used for creating the new Datawriter.
   * @param the_listener The DataWriter listener. The caller owns the listener and
   * is responsible for deleting it only after resetting it or after deleting
   * the DataWriter.
   * @param mask Changes of communication status to be invoked on the listener
   *
   * @see \ref DDSQosTypesModule_usage for information on setting QoS before entity creation
   * @see dds::pub::qos::DataWriterQos for rules on consistency among QoS
   * @see dds::core::QosProvider::datawriter_qos()
   * @see dds::pub::Publisher::default_datawriter_qos()
   * @see dds::pub::qos::DataWriterQos::operator=(const dds::topic::qos::TopicQos&) which allows assigning
   *      the contents of a TopicQos into a DataWriterQos
   * @see listener()
   */
  DataWriter(
      const dds::pub::Publisher& pub,
      const dds::topic::Topic<T>& the_topic,
      const dds::pub::qos::DataWriterQos& the_qos,
      dds::pub::DataWriterListener<T>* the_listener = NULL,
      const dds::core::status::StatusMask& mask =
          dds::core::status::StatusMask::all())
      : dds::core::TEntity<DELEGATE<T> >(
          new DELEGATE<T>(pub, the_topic, the_qos, the_listener, mask))
  {
      this->delegate()->remember_reference(this->delegate());
  }

  // Spec error CPPPSM-18: need this constructor to make
  // polymorphic_cast work.
  DataWriter(
      typename dds::core::smart_ptr_traits<DELEGATE<T> >::ref_type delegate_ref)
      : dds::core::TEntity<DELEGATE<T> >(delegate_ref)
  {
      if (this->delegate()) {
          this->delegate()->remember_reference(this->delegate());
      }
  }

  // Spec error: need this constructor.
  // The additional bool is to disambiguate with respect to
  // TDomainParticipant(uint32_t id)
  DataWriter(dds::core::construct_from_native_tag_t, DELEGATE<T>* the_delegate)
      : dds::core::TEntity<DELEGATE<T> >(the_delegate)
  {
      this->delegate()->remember_reference(this->delegate());
  }

  ~DataWriter() {}

public:
  //==========================================================================
  //== Write API

  /**
   * @brief Modifies the value of a data instance.
   *
   * This operations does the same as write(const T&, const dds::core::InstanceHandle&)
   * except that it deduces the identity of the instance from \p instance_data
   * (by means of the key).
   *
   * @param instance_data The data sample to write.
   *
   * @see write(const T&, const dds::core::InstanceHandle&)
   */
  void write(const T& instance_data)
  {
      this->delegate()->write(instance_data);
  }

  /**
   * @brief Modifies the value of a data instance and specifies the timestamp.
   *
   * @see void write(const T&, const dds::core::InstanceHandle&, const dds::core::Time&) 
   * @see \ref Deleting_DataWriter 
   */
  void write(const T& instance_data, const dds::core::Time& timestamp)
  {
      this->delegate()->write(instance_data, timestamp);
  }

  /**
   * @brief Modifies the value of a data instance.
   *  
   * @details \dref_details_FooDataWriter_write
   */
  void write(const T& instance_data, const dds::core::InstanceHandle& handle)
  {
      this->delegate()->write(instance_data, handle);
  }

  /**
   * @brief Modifies the value of a data instance and specifies the timestamp.
   *  
   * @details \dref_details_FooDataWriter_write_w_timestamp
   * @see \ref Deleting_DataWriter 
   */
  void write(
      const T& instance_data,
      const dds::core::InstanceHandle& handle,
      const dds::core::Time& source_timestamp)
  {
      this->delegate()->write(instance_data, handle, source_timestamp);
  }

  /**
   * @brief Write a dds::topic::TopicInstance. 
   *  
   *  A TopicInstance encapsulates the sample and its associated 
   * instance handle.
   *
   * @param topic_instance The instance to write.
   *
   * @see write(const T&, const dds::core::InstanceHandle&)
   */
  void write(const dds::topic::TopicInstance<T>& topic_instance)
  {
      write(topic_instance.sample(), topic_instance.handle());
  }

  /**
   * @brief Write a topic instance with time stamp.
   *
   * @param topic_instance the TopicInstance to write.
   * @param timestamp the timestamp for this sample.
   *
   * @see void write(const T&, const dds::core::InstanceHandle&, const dds::core::Time&)
   * @see \ref Deleting_DataWriter 
   */
  void write(
      const dds::topic::TopicInstance<T>& topic_instance,
      const dds::core::Time& timestamp)
  {
      write(topic_instance.sample(), topic_instance.handle(), timestamp);
  }

  /**
   * Write a series of samples or TopicInstances
   *
   * @tparam FWIterator A forward iterator. Depending on its value type
   * this function can write data samples or TopicInstance objects.
   *
   * @param begin The beginning of the range
   * @param end The end of the range
   *
   * @see write(const T&)
   * @see write(const dds::topic::TopicInstance<T>&)
   */
  template <typename FWIterator>
  void write(const FWIterator& begin, const FWIterator& end)
  {
      FWIterator p = begin;
      while (p != end) {
          this->delegate()->write(*p);
          ++p;
      }
  }

  /**
   * Write a series of samples or TopicInstances with a given timestamp
   *
   * @tparam FWIterator A forward iterator. Depending on its value type
   * this function can write data samples or TopicInstance objects.
   *
   * @param begin The beginning of the range
   * @param end The end of the range
   * @param timestamp The timestamp to use for all samples in the range
   *
   * @see write(const T&, const dds::core::Time&)
   * @see write(const dds::topic::TopicInstance<T>&, const dds::core::Time&)
   * @see \ref Deleting_DataWriter 
   */
  template <typename FWIterator>
  void write(
      const FWIterator& begin,
      const FWIterator& end,
      const dds::core::Time& timestamp)
  {
      FWIterator p = begin;
      while (p != end) {
          this->delegate()->write(*p, timestamp);
          ++p;
      }
  }

/**
 * @brief Write a series of samples and their parallel instance handles.
 *
 * @tparam SamplesFWIterator Sample forward iterator
 * @tparam HandlesFWIterator InstanceHandle forward iterator
 * @param data_begin The beginning of the data sample range
 * @param data_end The end of the data sample range
 * @param handle_begin The beginning of the InstanceHandle range
 * @param handle_end The end of the InstanceHandle range
 *
 * @see write(const T&, const dds::core::InstanceHandle&)
 */
  template <typename SamplesFWIterator, typename HandlesFWIterator>
  void write(
      const SamplesFWIterator& data_begin,
      const SamplesFWIterator& data_end,
      const HandlesFWIterator& handle_begin,
      const HandlesFWIterator& handle_end)
  {
      SamplesFWIterator data_it = data_begin;
      HandlesFWIterator handle_it = handle_begin;
      while (data_it != data_end && handle_it != handle_end) {
          this->delegate()->write(*data_it, *handle_it);
          ++data_it;
          ++handle_it;
      }
  }

  /**
   * @brief Write a series of samples and their parallel instance handles and a
   * timestamp.
   * @see \ref Deleting_DataWriter 
   */
  template <typename SamplesFWIterator, typename HandlesFWIterator>
  void write(
      const SamplesFWIterator& data_begin,
      const SamplesFWIterator& data_end,
      const HandlesFWIterator& handle_begin,
      const HandlesFWIterator& handle_end,
      const dds::core::Time& timestamp)
  {
      SamplesFWIterator data_it = data_begin;
      HandlesFWIterator handle_it = handle_begin;
      while (data_it != data_end && handle_it != handle_end) {
          this->delegate()->write(*data_it, *handle_it, timestamp);
          ++data_it;
          ++handle_it;
      }
  }


  /**
   * @brief Writes a sample
   *
   * @see write(const T&)
   */
  DataWriter& operator << (const T& data)
  {
      this->write(data);
      return *this;
  }

  /**
   * @brief Writes a sample with a timestamp
   *
   * @see write(const T&, const dds::core::Time&)
   * @see \ref Deleting_DataWriter 
   */
  DataWriter& operator << (const std::pair<T, dds::core::Time>& data)
  {
      this->write(data.first, data.second);
      return *this;
  }

  /**
   * @brief Writes a sample with an instance handle
   *
   * @see write(const T&, const dds::core::InstanceHandle&)
   */
  DataWriter& operator << (
      const std::pair<T, dds::core::InstanceHandle>& data)
  {
      this->write(data.first, data.second);
      return *this;
  }

  // Issue CPPPSM-322: this operator is not implemented
  // DataWriter& operator <<(DataWriter& (*manipulator)(DataWriter&));

  //==========================================================================
  //== Instance Management

  /**
   * @brief Informs \ndds that the application will be modifying a particar instance
   *
   * @details \dref_details_FooDataWriter_register_instance
   */
  const dds::core::InstanceHandle register_instance(const T& instance_data)
  {
      return this->delegate()->register_instance(instance_data);
  }

  /**
   * @brief Informs \ndds that the application will be modifying a particular
   * instance and specifies the timestamp
   *
   * @details \dref_details_FooDataWriter_register_instance_w_timestamp
   * @see \ref Deleting_DataWriter 
   */
  const dds::core::InstanceHandle register_instance(
      const T& instance_data,
      const dds::core::Time& source_timestamp)
  {
      return this->delegate()->register_instance(instance_data, source_timestamp);
  }

  /**
   * @brief Unregister an instance.
   *
   * @details \dref_details_FooDataWriter_unregister_instance
   */
  DataWriter& unregister_instance(const dds::core::InstanceHandle& handle)
  {
      this->delegate()->unregister_instance(handle);
      return *this;
  }

  /**
   * @brief Unregister an instance with timestamp.
   *
   * @details \dref_details_FooDataWriter_unregister_instance_w_timestamp
   */
  DataWriter& unregister_instance(
      const dds::core::InstanceHandle& handle,
      const dds::core::Time& source_timestamp)
  {
      this->delegate()->unregister_instance(handle, source_timestamp);
      return *this;
  }

  /**
   * @brief Dispose an instance.
   *
   * @details \dref_details_FooDataWriter_dispose
   */
  DataWriter& dispose_instance(const dds::core::InstanceHandle& handle)
  {
      this->delegate()->dispose_instance(handle);
      return *this;
  }

  /**
   * @brief Dispose an instance with a timestamp.
   *
   * @details \dref_details_FooDataWriter_dispose_w_timestamp
   */
  DataWriter& dispose_instance(
      const dds::core::InstanceHandle& the_instance_handle,
      const dds::core::Time& source_timestamp)
  {
      this->delegate()->dispose_instance(the_instance_handle, source_timestamp);
      return *this;
  }

  /**
   * @brief Retrieve the instance key that corresponds to an instance handle.
   *
   * @details \dref_details_FooDataWriter_get_key_value
   */
  T& key_value(T& key_holder, const dds::core::InstanceHandle& handle)
  {
      return this->delegate()->key_value(key_holder, handle);
  }

  /**
   * @brief Retrieve the instance key that corresponds to an instance handle.
   *
   * @see key_value(T&, const dds::core::InstanceHandle&)
   */
  dds::topic::TopicInstance<T>& key_value(
      dds::topic::TopicInstance<T>& key_holder,
      const dds::core::InstanceHandle& handle)
  {
      return this->delegate()->key_value(key_holder, handle);
  }

  /**
   * @brief Retrieve the instance handle that corresponds to an instance
   * key_holder
   *
   * @details \dref_details_FooDataWriter_lookup_instance
   */
  dds::core::InstanceHandle lookup_instance(const T& key_holder)
  {
      return this->delegate()->lookup_instance(key_holder);
  }

  //==========================================================================
  //== QoS Management

  /**
   * @brief Gets the DataWriterQos.
   */
  dds::pub::qos::DataWriterQos qos() const
  {
      return this->delegate()->qos();
  }

  /**
   * @brief Sets the DataWriterQos.
   *
   * @details \dref_details_DataWriter_set_qos
   */
  void qos(const dds::pub::qos::DataWriterQos& the_qos)
  {
      this->delegate()->qos(the_qos);
  }

  /**
   * @brief Set the DataWriterQos. 
   *  
   * @param the_qos the new qos for this DataWriter. 
   *  
   * @see qos()
   */
  DataWriter& operator <<(const dds::pub::qos::DataWriterQos& the_qos)
  {
      qos(the_qos);
      return *this;
  }

  /**
   * @brief Get the DataWriterQos.
   *
   * @param the_qos the object to populate with the qos for this DataWriter.
   *
   * @see qos()
   */
  const DataWriter& operator >> (dds::pub::qos::DataWriterQos& the_qos) const
  {
      the_qos = qos();
      return *this;
  }


  //==========================================================================
  //== Entity Navigation

  /**
   * @brief Get the Topic associated with this DataWriter
   */
  const dds::topic::Topic<T>& topic() const
  {
      return this->delegate()->topic();
  }

  /**
   * @brief Get the Publisher that owns this DataWriter.
   */
  const dds::pub::Publisher& publisher() const
  {
      return this->delegate()->publisher();
  }

  //==========================================================================
  //== ACKs

  /**
   * @brief Blocks the calling thread until all data written by reliable
   * DataWriter entity is acknowledged, or until timeout expires.
   *
   * @details \dref_details_DataWriter_wait_for_acknowledgments
   */
  void wait_for_acknowledgments(const dds::core::Duration& max_wait)
  {
      this->delegate()->wait_for_acknowledgments(max_wait);
  }

  //==========================================================================
  //== Listeners Management

  /**
   * @brief Sets the DataWriter listener
   *
   * @param l The DataWriterListener to set
   * @param mask The dds::core::status::StatusMask associated with the listener  
   */
  void listener(
      DataWriterListener<T>* l, const dds::core::status::StatusMask& mask)
  {
      this->delegate()->listener(l, mask);
  }

  /**
   * @brief Returns the listener currently associated with this DataWriter.
   *
   * If there's no listener it returns NULL.
   */
  DataWriterListener<T>* listener() const
  {
      return this->delegate()->listener();
  }

  //==========================================================================
  //== Status Management

  /**
   * @brief Get the LivelinessLostStatus.
   *
   * @details \dref_details_DataWriter_get_liveliness_lost_status
   */
  const dds::core::status::LivelinessLostStatus liveliness_lost_status()
  {
      return this->delegate()->liveliness_lost_status();
  }

  /**
   * @brief Get the OfferedDeadlineMissedStatus.
   *
   * @details \dref_details_DataWriter_get_offered_deadline_missed_status
   */
  const dds::core::status::OfferedDeadlineMissedStatus offered_deadline_missed_status()
  {
      return this->delegate()->offered_deadline_missed_status();
  }

  /**
   * @brief Get the OfferedIncompatibleQosStatus.
   *
   * @details \dref_details_DataWriter_get_offered_incompatible_qos_status
   */
  const dds::core::status::OfferedIncompatibleQosStatus offered_incompatible_qos_status()
  {
      return this->delegate()->offered_incompatible_qos_status();
  }

  /**
   * @brief Get the PublicationMatchedStatus.
   *
   * @details \dref_details_DataWriter_get_publication_matched_status
   */
  const dds::core::status::PublicationMatchedStatus publication_matched_status()
  {
      return this->delegate()->publication_matched_status();
  }

  //==========================================================================
  //== Liveliness Management

  /**
   * @brief Manually asserts the liveliness of this DataWriter
   *
   * @details \dref_details_DataWriter_assert_liveliness
   */
  void assert_liveliness()
  {
      this->delegate()->assert_liveliness();
  }
};

#endif /* OMG_DDS_PUB_TDATA_WRITER_HPP_ */
