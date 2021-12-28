#ifndef CASSIUS_INCLUDE_SOURCEFILE_HPP
#define CASSIUS_INCLUDE_SOURCEFILE_HPP

#include <string>

#include "Source.hpp"

namespace Cassius {
    /** Simple class representing a Source file
     */
    class CASSIUS_API SourceFile : public Source {
      public:
        SourceFile(const char *code)
            : source(code)
        {}
        virtual ~SourceFile()
        {}

        virtual std::string get() const
        {
            return std::string(source);
        }

      private:
        const char *source;
    };
}

#endif

