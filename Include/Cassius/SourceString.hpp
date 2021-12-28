#ifndef CASSIUS_INCLUDE_SOURCESTRING_HPP
#define CASSIUS_INCLUDE_SOURCESTRING_HPP

#include <string>

#include "Source.hpp"

namespace Cassius
{
    /** Simple class representing an executable chunk of Source code as a string
     */
    class CASSIUS_API SourceString
        : public Source
    {
      public:
        /**
         * @brief From standard string.
         * 
         * @param str the source code.
         */
        SourceString(const std::string& str);

        /**
         * @brief From C-string and length.
         * 
         * @param code the source code.
         * @param length length of code; if 0 then use strlen().
         */
        SourceString(const char* code, size_t length = 0);

        virtual ~SourceString();

        virtual std::string get();

      private:
        std::string mString;
    };
} // namespace Cassius

#endif
