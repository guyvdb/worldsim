#ifndef SCANNER_H
#define SCANNER_H

#include <cstdint>
#include <type/base.h>

namespace graph {
  namespace store {
    class Scanner {
      public:
        virtual void Scan(type::gid id, bool active, ByteBuffer *buffer, std::size_t len) = 0;
    };

  }
}


#endif // SCANNER_H
