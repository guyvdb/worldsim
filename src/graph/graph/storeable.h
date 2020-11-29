#ifndef STOREABLE_H
#define STOREABLE_H

#include <iostream>
#include <map>
#include <types.h>
#include <buffer.h>

/*
 * Buffer layout of all storables:
 * |------|---------|
 * | 0    | 1 2 3 4 |
 * | flag | typeid  |
 * |------|---------|
 */

namespace graph {
  // Any object that is stored in one of the data stores must inherit from Storable
  class Storeable {
    public:
      static const std::size_t EntitySize = 16;
      static const std::size_t RelationSize = 16;
      static const std::size_t AttributeSize = 16;
      static const std::size_t TypeSize = 16;

      // The storable type id's
      enum Concept : cid {
        NotStorable,
        Entity,
        Relation,
        Attribute,
        Type,
        Id,
        Test
      };


      Storeable(gid id, std::size_t size);
      Storeable(gid id, ByteBuffer *buf);
      virtual ~Storeable();

      // must be implemented by subclasses
      virtual Concept GetConcept() = 0;



      gid GetGraphId() {return m_graphid;}
      void SetGraphId(gid value) { this->m_graphid = value; }
      gid GetTypeId();
      void SetTypeId(gid type);
      ByteBuffer *Buffer() { return this->m_buffer; }
      std::uint8_t GetFlag();
      void SetFlag(std::uint8_t flag);

    protected:
      gid m_graphid;
      ByteBuffer *m_buffer;
  };


  struct StoreableId {
      gid Id;
      Storeable::Concept Type;
  };






}

#endif // STOREABLE_H
