#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <vector>
#include <types.h>
#include <storeable.h>

#include <buffer.h>
#include <encoder.h>

namespace graph {

  class Transaction;

  // attribute definition
  // id, flag(1), target-cid(1),datatype(1), len(2), name(27),
  class AttributeDefinition : public Storeable {
    public:
      static const std::size_t MaxNameLen = 27;

      virtual Concept GetConcept() { return Storeable::Concept::CAttributeDefinition; }
      AttributeDefinition(gid id);
      AttributeDefinition(gid id, ByteBuffer *buffer);
      cid GetTarget();
      void SetTarget(cid id);
      DataType GetDataType();
      void SetDataType(DataType type);
      std::uint16_t GetLen();
      void SetLen(std::uint16_t len);
      std::string GetName();
      void SetName(std::string name);
  };



  class Attribute {
    public:
      Attribute();
  };

  // attribute is a 64 byte block that can contain
  // a partial attribute, a whole attribute or more
  // than one attribute with continuation....

  // rec =  flag(1), bflag(1), data(62)
  // data = item, item, ... item, <next-bucket-id>(4)
  // item = def(4), len(1), bytes (len bytes)


  /*
   * Buffer layout: AttributeBucket
   * |----------------|---------------------|------------|
   * | Storeable      | AttributeBucket
   * |------|---------|---------------------|------------|
   * | 0    | 1 2 3 4 | 5      |
   * | flag | typeid  | bflag  | Root RelId |
   * |------|---------|---------------------|------------|
   */

  class AttributeBucket : public Storeable {
     public:
       AttributeBucket(gid id);
       AttributeBucket(gid id, ByteBuffer *buffer);
       virtual Concept GetConcept() { return Storeable::Concept::CAttributeBucket; }
       void SetNextBucketId(gid id);
       gid GetNextBucketId();
       AttributeBucket *NextBucket();
    private:
  };


  class AttributeCollection {
    public:
      AttributeCollection(Transaction *tx, StoreableWithAttributes *storeable);
      ~AttributeCollection();
      std::size_t Size();
      void Add(AttributeBucket *bucket);
      void Add(Attribute *attribute);
      Attribute* operator[](std::size_t index);
    private:
      std::vector<AttributeBucket*> m_buckets;
      Transaction *m_transaction;
      StoreableWithAttributes *m_storeable;
  };




  class AttributeBucketEncoder : public Encoder {
    public:
      AttributeBucketEncoder() : Encoder() {}
      virtual Storeable *Decode(gid id, ByteBuffer *buffer) { return new AttributeBucket(id, buffer); }
      virtual Storeable *Empty() { return new AttributeBucket(InvalidGraphId); }
      virtual bool Decodeable() { return true; }
  };

  class AttributeDefinitionEncoder : public Encoder {
    public:
      AttributeDefinitionEncoder() : Encoder() {}
      virtual Storeable *Decode(gid id, ByteBuffer *buffer) { return new AttributeDefinition(id, buffer); }
      virtual Storeable *Empty() { return new AttributeDefinition(InvalidGraphId); }
      virtual bool Decodeable() { return true; }
  };
}
#endif // ATTRIBUTE_H
