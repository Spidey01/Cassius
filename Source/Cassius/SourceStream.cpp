// SPDX-License-Identifier: ISC
// Copyright 2010, Terry M. Poulin.

#include <iostream>
#include <istream>

#include <Cassius/SourceStream.hpp>

using std::istream;
using std::string;

namespace Cassius {
    SourceStream::SourceStream(istream &stream)
        : Source()
    {
        while (stream.good()) {
            this->code.sputc(stream.get());
        }
        // this should deal with errors by throwing
    }

    SourceStream::~SourceStream()
    {
    }

    string SourceStream::get() const
    {
        return code.str();
    }
}


