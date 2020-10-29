#ifndef BYTEBUFFER_H
#define BYTEBUFFER_H

#include <vector>
#include <types.h>
#include <cstdint>

namespace graph {

  class ByteBuffer {
    public:
      ByteBuffer();
      ByteBuffer(const char *data, std::size_t size);
      ByteBuffer(std::size_t size);

      ~ByteBuffer();


      ByteBuffer *Push(uint8_t value);
      ByteBuffer *Push(uint16_t value);
      ByteBuffer *Push(uint32_t value);

      uint8_t PopUInt8();
      uint16_t PopUInt16();
      uint32_t PopUInt32();

      char *Data();
      std::size_t Size();

      void Print();
    private:
      std::vector<char> *m_buf;
  };

}
#endif // BYTEBUFFER_H
