#ifndef CASSIUS_INCLUDE_SOURCE_HPP
#define CASSIUS_INCLUDE_SOURCE_HPP
// SPDX-License-Identifier: ISC
// Copyright 2010, Terry M. Poulin.

#include <string>

#include "Cassius.hpp"

namespace Cassius
{
    /** Abstract base class representing an executable chunk of Source code
     *
     */
    class CASSIUS_API Source
    {
      public:
        virtual ~Source(){};
        virtual std::string get() const = 0;
    };

    inline bool operator==(const Source& lhs, const Source& rhs)
    {
        return lhs.get() == rhs.get();
    }

    inline bool operator!=(const Source& lhs, const Source& rhs)
    {
        return !(lhs == rhs);
    }

} // namespace Cassius

#endif
