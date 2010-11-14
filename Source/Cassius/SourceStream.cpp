
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
    }

    SourceStream::~SourceStream()
    {
    }

    string SourceStream::get()
    {
        return code.str();
    }
}


