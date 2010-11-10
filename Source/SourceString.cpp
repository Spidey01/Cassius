
#include <cstring>
#include <string>

#include "../Include/SourceString.hpp"

using std::string;

namespace Cassius {
    SourceString::SourceString(const char *code, size_t length)
        : Source()
    {
        if (!length)
            length = strlen(code)+1;
        this->length = length;

        source = new char[length];
        std::memcpy(source, code, length);
    }

    void SourceString::docopy(const SourceString &other)
    {
        length = other.length;
        source = new char[length];
        std::memcpy(source, other.source, length);

        // Some APIs get upset if the string is not nul terminated.
        if (length > 0 && source[length-1] != '\0') {
            source[length-1] = '\0';
        }
    }

    const SourceString &SourceString::operator=(const SourceString &other)
    {
        if (this != &other) {
            Source::operator=(other);
            delete[] source;
            docopy(other);
        }

        return *this;
    }

    SourceString::~SourceString()
    {
        delete[] source;
    }

    string SourceString::get()
    {
        // easy safe guard against mutability of this->source
        return string(source);
    }
}

