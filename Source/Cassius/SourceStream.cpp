// SPDX-License-Identifier: ISC
// Copyright 2010, Terry M. Poulin.

#include <iostream>
#include <istream>

#include <Cassius/SourceStream.hpp>

using std::istream;
using std::ostream;
using std::string;

namespace Cassius
{
    SourceStream::SourceStream()
        : Source()
        , mStream()
    {
    }

    SourceStream::SourceStream(istream& stream)
        : Source()
        , mStream()
    {
        mStream << stream.rdbuf();
    }

    SourceStream::~SourceStream()
    {
    }

    string SourceStream::get() const
    {
        return mStream.str();
    }

    ostream& SourceStream::to_ostream()
    {
        return mStream;
    }

    istream& SourceStream::to_istream()
    {
        return mStream;
    }
} // namespace Cassius
