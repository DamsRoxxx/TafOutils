/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_UTIL_STREAM_FLAG_SAVER_HPP_
#define RTI_UTIL_STREAM_FLAG_SAVER_HPP_

#include <iosfwd>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

namespace rti { namespace util {

/**
 * RAII utility to save and restore the flags of a std::ostream
 *
 * Use:
 *   void example(std::ostream& out)
 *   {
 *      rti::util::StreamFlagSaver flag_saver (out);
 *      out << std::hex << 33;
 *      // ...
 *   } // out flags restored
 *
 */
class StreamFlagSaver {
public:
    explicit StreamFlagSaver (std::ostream& out)
        : out_(out), flags_(out.flags()) // save flags
    {
    }

    ~StreamFlagSaver()
    {
        out_.flags(flags_); // restore flags
    }

private:
    // Disable copies
    StreamFlagSaver(const StreamFlagSaver&);
    StreamFlagSaver& operator= (const StreamFlagSaver&);

private:
    std::ostream& out_;
    std::ios::fmtflags flags_;
};

} }

#endif // RTI_UTIL_STREAM_FLAG_SAVER_HPP_
