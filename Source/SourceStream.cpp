#include <istream>
#include <iostream>

#include "../Include/SourceStream.hpp"

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

    std::string SourceStream::get()
    {
        return code.str();
    }
}


