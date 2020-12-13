#ifndef RELATION_H
#define RELATION_H

#include <storeable.h>
#include <tx/transaction.h>
#include <buffer.h>
#include <decoder.h>



// a relation relates two entities


namespace graph {


  /*
   * Buffer layout: Relation
   * |-----------|-------------------|----------------------|
   * | Storeable | StoreableWithType | StoreableWithAttrib  |
   * |-----------|-------------------|----------------------|
   * | 0         | 1 2 3 4           | 5 6 7 8              |
   * | flag      | typeid            | Root AttribBucket Id |
   * |-----------|-------------------|----------------------| ...
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

  class Relation : public StoreableWithAttributes{
    public:
      const static int FROM_ENTITY_ID_OFFSET = 9;
      const static int TO_ENTITY_ID_OFFSET = 13;
      const static int NEXT_OUT_REL_ID_OFFSET = 17;
      const static int PREV_OUT_REL_ID_OFFSET = 21;
      const static int NEXT_IN_REL_ID_OFFSET = 25;
      const static int PREV_IN_REL_ID_OFFSET = 29;


      Relation(type::gid id);
      Relation(type::gid id, ByteBuffer *buffer);
      Relation(type::gid id, std::uint8_t *buffer, std::size_t size);
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


/*
  class RelationDecoder : public Decoder {
    public:
      RelationDecoder() : Decoder() {}
      virtual Storeable *Decode(type::gid id, ByteBuffer *buffer) { return new Relation(id, buffer); }
      virtual Storeable *Empty() { return new Relation(type::NullGraphId); }
      virtual bool Decodeable() { return true; }
  };
*/
}
#endif // RELATION_H





/*
Relationship store:
Each relationship record is a fixed record of 34 bytes
The relationship record’s layout is as follows:
Start node ID
End node ID
Pointer to the relationship type
Pointer to the next and previous relationship record for each of the start node and end node
Each relationship record belongs to two nodes, the start node and the end node. Each relationship also has a type associated with it, which signifies which type of relationship is connecting the 2 nodes. The pointer to the relationship type helps to determine this.
The relationship node contains 4 other pointers or misdirections to relationship records. They point to the previous and next relationship of both the start node and end node similar to how doubly linked lists behave.
*/
