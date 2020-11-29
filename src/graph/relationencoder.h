#ifndef RELATIONENCODER_H
#define RELATIONENCODER_H

#include <encoder.h>
#include <relation.h>
#include <gid.h>

namespace graph {

  class RelationEncoder : public Encoder {
    public:
      RelationEncoder() : Encoder() {}
      virtual Storeable *Decode(gid id, ByteBuffer *buffer) { return new Relation(id, buffer); }
      virtual Storeable *Empty() { return new Relation(NullId); }
      virtual bool Decodeable() { return true; }

      virtual std::size_t EncodedSize();
      virtual bool Encode(Storeable *s, ByteBuffer *buffer);
  };
}

#endif // RELATIONENCODER_H
