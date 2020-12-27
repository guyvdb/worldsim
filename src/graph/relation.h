#ifndef RELATION_H
#define RELATION_H

#include "storeable.h"
#include "transaction.h"
#include "type/buffer.h"
#include "type/factory.h"




// a relation relates two entities


namespace graph {


  /*
   * Buffer layout: Relation
   * |-----------|--------------------|----------------------|
   * | Storeable | StoreableWithClass | StoreableWithProps   |
   * |-----------|--------------------|----------------------|
   * | 0         | 1 2 3 4            | 5 6 7 8              |
   * | flag      | class id           | Root AttribBucket Id |
   * |-----------|--------------------|----------------------| ...
   *
   * |-----------------------------------------------------------------------------------------|
   * | Relation                                                                                |
   * |----------------|--------------|---------------------------------------------------------|
   * | 9 10 11 12     | 13 14 15 16  | 17 18 19 20  | 21 22 23 24  | 25 26 27 28 | 29 30 31 32 |
   * | From Entity Id | To Entity Id | NextOutRelId | PrevOutRelId | NextInRelId | PrevInRelId |
   * |----------------|--------------|--------------|--------------|-------------|-------------|
   *
   *
   * Relation padded to 34 bytes long
   *
   */

  class Relation : public StoreableWithProps{
    public:
      const static int FROM_ENTITY_ID_OFFSET = 9;
      const static int TO_ENTITY_ID_OFFSET = 13;
      const static int NEXT_OUT_REL_ID_OFFSET = 17;
      const static int PREV_OUT_REL_ID_OFFSET = 21;
      const static int NEXT_IN_REL_ID_OFFSET = 25;
      const static int PREV_IN_REL_ID_OFFSET = 29;

      static Storeable* FactoryFunc(type::gid id, type::ByteBuffer *buffer);
      static type::FactoryFunc GetFactoryFunc();

      Relation();
      Relation(type::gid id);
      Relation(type::gid id, graph::type::ByteBuffer *buffer);
      //Relation(type::gid id, std::uint8_t *buffer, std::size_t size);
      ~Relation();

      Entity* From();
      Entity* To();

      type::gid GetFromEntityId();
      void SetFromEntityId(type::gid id);
      type::gid GetToEntityId();
      void SetToEntityId(type::gid id);

      type::gid GetNextOutRelationId();
      void SetNextOutRelationId(type::gid id);
      type::gid GetPrevOutRelationId();
      void SetPrevOutRelationId(type::gid id);

      type::gid GetNextInRelationId();
      void SetNextInRelationId(type::gid id);
      type::gid GetPrevInRelationId();
      void SetPrevInRelationId(type::gid id);

      virtual Concept GetConcept() {return Concept::RelationConcept; }
    private:
      Entity *m_fromEntity;
      Entity *m_toEntity;
  };



}
#endif // RELATION_H

