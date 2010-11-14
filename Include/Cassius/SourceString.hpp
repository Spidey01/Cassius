#ifndef CASSIUS_INCLUDE_SOURCESTRING_HPP
#define CASSIUS_INCLUDE_SOURCESTRING_HPP

#include <string>

#include "Source.hpp"

namespace Cassius {
    /** Simple class representing an executable chunk of Source code as a string
     */
    class CASSIUS_API SourceString : public Source {
      public:
        SourceString(const char *code, size_t length=0);
        SourceString(const SourceString &other) { docopy(other); }
        const SourceString &operator=(const SourceString &other);
        virtual ~SourceString();

        virtual std::string get();

      private:
        void docopy(const SourceString &other);

        char *source;
        size_t length;
    };
}

#endif
