#ifndef ENTITYENCODER_H
#define ENTITYENCODER_H

#include <encoder.h>
#include <entity.h>



namespace graph {
  class EntityEncoder : public Encoder {
    public:
      EntityEncoder() : Encoder() {}
      virtual Storeable *Decode(gid id, ByteBuffer *buffer) { return new Entity(id, buffer); }
      virtual Storeable *Empty() { return new Entity(NullId); }
      virtual bool Decodeable() { return true; }
      virtual std::size_t EncodedSize();
      virtual bool Encode(Storeable *s, ByteBuffer *buffer);
  };
}


#endif // ENTITYENCODER_H
