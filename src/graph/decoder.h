#ifndef DECODER_H
#define DECODER_H

#include <storeable.h>
#include <type/base.h>
#include <buffer.h>

namespace graph {
/*
  // Abstract class for creating object. Each type of Storeable object
  // should define a factory that creates objects of its type
  class Decoder {
    public:
      virtual ~Decoder() {}
      virtual Storeable *Decode(type::gid id, ByteBuffer *buffer) = 0;
      virtual Storeable *Empty() = 0;
      virtual bool Decodeable() = 0;
  };

  class NullDecoder : public Decoder {
    public:
      virtual Storeable *Decode(type::gid, ByteBuffer *) { return 0x0; }
      virtual Storeable *Empty() {return 0x0; }
      virtual bool Decodeable() {return false; }
  };
  */
}


#endif // DECODER_H
