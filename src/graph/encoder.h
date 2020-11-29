#ifndef ENCODER_H
#define ENCODER_H

#include <storeable.h>
#include <types.h>
#include <buffer.h>

namespace graph {

  // Abstract class for creating object. Each type of Storeable object
  // should define a factory that creates objects of its type
  class Encoder {
    public:
      virtual ~Encoder() {}
      virtual Storeable *Decode(gid id, ByteBuffer *buffer) = 0;
      virtual Storeable *Empty() = 0;
      virtual std::size_t EncodedSize() = 0;
      virtual bool Encode(Storeable *s, ByteBuffer *buffer) = 0;
      virtual bool Decodeable() = 0;
  };

  class NullEncoder : public Encoder {
    public:
      virtual Storeable *Decode(gid, ByteBuffer *) { return 0x0; }
      virtual Storeable *Empty() {return 0x0; }
      virtual bool Decodeable() {return false; }
      virtual std::size_t EncodedSize() { return 0; }
      virtual bool Encode(Storeable *, ByteBuffer *){ return false; }
  };
}


#endif // ENCODER_H
