// SPDX-License-Identifier: ISC
// Copyright 2010, Terry M. Poulin.

#include <string>

#include <cstring>

#include <Cassius/SourceString.hpp>

using std::memcpy;
using std::string;

namespace Cassius
{
    SourceString::SourceString(const std::string& str)
        : Source()
        , mString(str)
    {
    }

    SourceString::SourceString(const char* code, size_t length)
        : Source()
        , mString(code, (length == 0 ? strlen(code) : length))
    {
    }

    SourceString::~SourceString()
    {
    }

    string SourceString::get() const
    {
        return mString;
    }
} // namespace Cassius
