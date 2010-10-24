
#include <cstring>
#include <string>

#include "../Include/SourceString.hpp"

using std::strncpy;
using std::string;

namespace Cassius {
    SourceString::SourceString(const char *code, size_t length)
        : Source()
    {

        if (!length)
            _length = length = strlen(code)+1;

        source = new char[length];
        strncpy(source, code, length);
    }

    SourceString::~SourceString()
    {
        delete[] source;
    }

    const string SourceString::get()
    {
        // easy safe guard against mutability of this->source
        return string(source);
    }
}

