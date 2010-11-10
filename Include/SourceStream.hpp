#ifndef CASSIUS_INCLUDE_SOURCESTREAM_HPP
#define CASSIUS_INCLUDE_SOURCESTREAM_HPP

#include <string>
#include <iosfwd>
#include <sstream>

#include "Source.hpp"

namespace Cassius {
    /** Simple class representing an executable chunk of Source code as a istream
     */
    class SourceStream : public Source {
      public:
        SourceStream(std::istream &stream);
        virtual ~SourceStream();
        virtual std::string get();

      private:
        std::stringbuf code;
    };
}

#endif
