#ifndef STOREABLE_H
#define STOREABLE_H

#include <iostream>
#include <map>
#include <graph_types.h>
#include <buffer.h>

namespace graph {




  // Any object that is stored in one of the data stores must inherit from Storable
  class Storeable {
    public:
      static const std::size_t EntitySize = 16;
      static const std::size_t EntityTypeSize = 16;
      //static const std::size_t PropertySize = 16;
      //static const std::size_t PropertyTypeSize = 16;
      static const std::size_t RelationSize = 16;
      static const std::size_t RelationTypeSize = 16;

      static const std::size_t AttributeSize = 16;
      static const std::size_t AttributeTypeSize = 16;

      // The storable type id's
      enum Concept : cid {
        NotStorable,
        Entity,
        EntityType,
        Relation,
        RelationType,
        Attribute,
        AttributeType,
        Id,
        Test
      };


      Storeable(gid id);
      virtual ~Storeable();

      // must be implemented by subclasses
      virtual ByteBuffer *Buffer() = 0;
      virtual Concept Type() = 0;
      virtual void SetFlag(std::uint8_t flag) = 0;
      virtual std::uint8_t GetFlag() = 0;


      gid GraphId() {return m_graphid;}
      gid TypeId() { return m_typeid; }
      void SetGraphId(gid value) { this->m_graphid = value; }
    protected:
      gid m_graphid;
      gid m_typeid;
  };


  struct StoreableId {
      gid Id;
      Storeable::Concept Type;
  };






}

#endif // STOREABLE_H
