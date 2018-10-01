/*
 Copyright (c) 2013, Real-Time Innovations, Inc. All rights reserved.

 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_CORE_SCOPED_LISTENER_HPP_
#define RTI_DDS_CORE_SCOPED_LISTENER_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/Reference.hpp>
#include <dds/core/Exception.hpp>
#include <dds/core/status/State.hpp>
#include <dds/domain/domainfwd.hpp>


namespace rti { namespace core {

/**
 * @ingroup DDSCPP2SupportingTypes
 * @headerfile rti/core/ListenerBinder.hpp
 * @brief @st_ref_type Automatically manages the association of an Entity and
 * a Listener
 *
 * Ties the association listener/Entity to the existence of references to this
 * type--that is, the constructor sets the listener and creates a reference and
 * when the last reference is destroyed it resets the listener. Depending on how
 * it is created it will also delete the listener or not:
 *
 * - \p rti::core::bind_listener() creates a ListenerBinder that doesn't own
 *   the listener and won't delete it
 * - \p rti::core::bind_and_manage_listener() creates a ListenerBinder that
 *   owns the listener and will delete it.
 *
 * The goal is to simplify the destruction of an Entity by the application, which
 * otherwise would have to reset the listener or close the Entity explicitly.
 *
 * Example:
 * \code
 *
 * class MyListener : public DataReaderListener<Foo> { ... };
 *
 * void f()
 * {
 *     MyListener listener;
 *     dds::sub::DataReader<Foo> reader(subscriber, topic);
 *
 *     {
 *         auto scoped_listener = rti::core::bind_listener(
 *             reader, listener, dds::core::status::StatusMask::data_available());
 *        // reader has a listener set
 *
 *        // ...
 *
 *     } // After this, reader doesn't have a listener
 *
 * } // reader deleted; if we hadn't used a ListenerBinder,
 *   // reader would not have been deleted
 * \endcode
 *
 * To create a ListenerBinder use rti::core::bind_listener() or
 * rti::core::bind_and_manage_listener(). To retrieve the listener use
 * ListenerBinder::get().
 *
 * If the Entity changes its listener while references to this ListenerBinder
 * still exist, the ListenerBinder will not reset the listener.
 *
 * @note ListenerBinder provides all the operations of a
 * \ref a_st_ref_type "reference type" except close() and retain().
 *
 * @tparam Entity A subclass of dds::core::Entity
 * @tparam Listener The listener type, by default \p Entity::Listener
 *
 * @see \ref a_st_ref_type "Reference types", for an explanation of how reference
 * types work and the reasons why an Entity may be retained.
 */
template <typename Entity, typename Listener = typename Entity::Listener>
class ListenerBinder : public dds::core::Reference<Listener> {
public:

    // --- Types: ------------------------------------------------------------

    typedef dds::core::Reference<Listener> Base;
    typedef typename dds::core::Reference<Listener>::DELEGATE_REF_T ref_type;

    // As a custom Deleter to the shared_ptr, it resets the Entity's listener
    struct ListenerUnbinder {
        ListenerUnbinder(Entity entity) : entity_(entity) {};

        void operator()(Listener* the_listener)
        {
            if (!entity_->closed()) {
                if (entity_.listener() == the_listener) {
                    entity_.listener(NULL, dds::core::status::StatusMask::none());
                }
            }
        }

        Entity entity_;
    };

    // It also deletes the listener
    struct ListenerDeleter : public ListenerUnbinder {
        ListenerDeleter(Entity entity) : ListenerUnbinder(entity) {};

        void operator()(Listener* the_listener)
        {
            ListenerUnbinder::operator()(the_listener);
            delete the_listener;
        }
    };

    // --- Members: -----------------------------------------------------------

    OMG_DDS_REF_TYPE(ListenerBinder, dds::core::Reference, Listener)

    // For internal use, applications should call bind_listener or
    // bind_and_manage_listener
    template <typename Deleter>
    ListenerBinder(
        Entity entity,
        Listener* the_listener,
        dds::core::status::StatusMask mask,
        Deleter deleter)
        : Base(ref_type(the_listener, deleter))
    {
        entity.listener(the_listener, mask);
    }

    // Constructor for listeners that don't use a mask
    template <typename Deleter>
    ListenerBinder(
        Entity entity,
        Listener* the_listener,
        Deleter deleter)
        : Base(ref_type(the_listener, deleter))
    {
        entity.listener(the_listener);
    }

    /**
     * @brief Retrieves the listener
     *
     * @return The listener.
     */
    Listener* get()
    {
        return Base::delegate().get();
    }

    /**
     * @brief Retrieves the listener
     */
    const Listener* get() const
    {
        return Base::delegate().get();
    }
};

/**
 * @relatesalso ListenerBinder
 *
 * @brief Sets the listener and creates a ListenerBinder that automatically
 * resets it when all references go out of scope
 *
 * The ListenerBinder created from this function does not delete the listener,
 * it simply sets the listener back to NULL in the Entity. The application is
 * responsible for the life-cycle of the listener.
 *
 * To also delete the listener when all references go out of scope, see
 * bind_and_manage_listener().
 *
 * \code
 * MyListener my_listener;
 * dds::sub::DataReader<Foo> reader(subscriber, topic);
 *
 * // reader will have no listener after scoped_listener (and any other 
 * // references created from scoped_listener) go out of scope--note that 
 * // my_listener is a stack variable so scoped_listener should not delete it
 * auto scoped_listener = bind_listener(
 *     reader, &my_listener, dds::core::status::StatusMask::data_available());
 * \endcode
 *
 */
template <typename Entity, typename Listener>
ListenerBinder<Entity, Listener> bind_listener(
    Entity entity, Listener* the_listener, dds::core::status::StatusMask mask)
{
    typedef typename ListenerBinder<Entity, Listener>::ListenerUnbinder Deleter;

    return ListenerBinder<Entity, Listener>(
        entity, the_listener, mask, Deleter(entity));
}

/**
 * @relatesalso ListenerBinder
 *
 * @brief Sets the listener and creates a ListenerBinder that automatically
 * resets it when all references go out of scope
 *
 * This overload works for listeners that don't use a mask
 *
 * @see bind_listener(Entity, Listener*, dds::core::status::StatusMask)
 */
template <typename Entity, typename Listener>
ListenerBinder<Entity, Listener> bind_listener(
    Entity entity, Listener* the_listener)
{
    typedef typename ListenerBinder<Entity, Listener>::ListenerUnbinder Deleter;

    return ListenerBinder<Entity, Listener>(
        entity, the_listener, Deleter(entity));
}

/**
 * @relatesalso ListenerBinder
 *
 * @brief Sets the listener and creates a ListenerBinder that automatically
 * resets and deletes it when all references go out of scope
 *
 * Example:
 *
 * \code
 * dds::sub::DataReader<Foo> reader(subscriber, topic);
 *
 * // The instance of MyListener we are creating and attaching to reader will be
 * // unset and deleted when scoped_listener (and any other references create from
 * // scoped_listener) go out of scope
 * auto scoped_listener = bind_and_manage_listener(
 *     reader, new MyListener(), dds::core::status::StatusMask::data_available());
 * \endcode
 *
 * @see bind_listener()
 */
template <typename Entity, typename Listener>
ListenerBinder<Entity, Listener> bind_and_manage_listener(
    Entity entity, Listener* the_listener, dds::core::status::StatusMask mask)
{
    typedef typename ListenerBinder<Entity, Listener>::ListenerDeleter Deleter;

    return ListenerBinder<Entity, Listener>(
        entity, the_listener, mask, Deleter(entity));
}

/**
 * @relatesalso ListenerBinder
 *
 * @brief Sets the listener and creates a ListenerBinder that automatically
 * resets and deletes it when all references go out of scope
 *
 * This overload works for listeners that don't use a mask
 *
 * @see bind_and_manage_listener(Entity, Listener*, dds::core::status::StatusMask)
 */
template <typename Entity, typename Listener>
ListenerBinder<Entity, Listener> bind_and_manage_listener(
    Entity entity, Listener* the_listener)
{
    typedef typename ListenerBinder<Entity, Listener>::ListenerDeleter Deleter;

    return ListenerBinder<Entity, Listener>(
        entity, the_listener, Deleter(entity));
}


} }
#endif /* RTI_DDS_CORE_SCOPED_LISTENER_HPP_ */
