#ifndef CASSIUS_INCLUDE_SOURCESTRING_HPP
#define CASSIUS_INCLUDE_SOURCESTRING_HPP

#include <string>

#include "Source.hpp"

namespace Cassius {
    /** Simple class representing an executable chunk of Source code as a string
     */
    class SourceString : public Source {
      public:
        SourceString(const char *code, size_t length=0);
        virtual ~SourceString();
        virtual std::string get();

      private:
        SourceString(const SourceString &other);

        char *source;
        size_t _length;
    };
}

#endif
