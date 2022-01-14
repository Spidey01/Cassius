#ifndef CASSIUS_INCLUDE_SOURCESTREAM_HPP
#define CASSIUS_INCLUDE_SOURCESTREAM_HPP
// SPDX-License-Identifier: ISC
// Copyright 2010, Terry M. Poulin.

#include <iosfwd>
#include <sstream>
#include <string>

#include "Source.hpp"

namespace Cassius
{
    /** Simple class representing an executable chunk of Source code as a istream
     */
    class CASSIUS_API SourceStream
        : public Source
    {
      public:
        SourceStream();
        SourceStream(std::istream& stream);
        virtual ~SourceStream();
        virtual std::string get() const;

        /**
         * @brief Allows raw ostream access.
         * 
         * Useful if you want to build a Source using operator<<.
         * 
         * @returns reference to the internal stream.
         */
        std::ostream& to_ostream();

        /**
         * @brief Allows raw istream access.
         * 
         * @returns reference to the internal stream.
         */
        std::istream& to_istream();

      private:
        std::stringstream mStream;
    };
} // namespace Cassius

#endif