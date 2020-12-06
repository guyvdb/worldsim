#ifndef RELATION_H
#define RELATION_H

#include <storeable.h>
#include <transaction.h>
#include <buffer.h>
#include <encoder.h>



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
   * |-----------------------------------------------------------------------------------------------------|
   * | Relation                                                                                            |
   * |----------------|--------------|---------------------------------------------------------------------|
   * | 9 10 11 12     | 13 14 15 16  | 17 18 19 20     | 21 22 23 24      | 25 26 27 28   | 29 30 31 32    |
   * | From Entity Id | To Entity Id | NextFromInRelId | NextFromOutRelId | NextToInRelId | NextToOutRelId |
   * |----------------|--------------|-----------------|------------------|---------------|----------------|
   *
   *
   * Relation padded to 34 bytes long
   *
   */

  class Relation : public StoreableWithAttributes{
    public:
      const static int FROM_ENTITY_ID_OFFSET = 9;
      const static int TO_ENTITY_ID_OFFSET = 13;
      const static int NEXT_FROM_IN_REL_ID_OFFSET = 17;
      const static int NEXT_FROM_OUT_REL_ID_OFFSET = 21;
      const static int NEXT_TO_IN_REL_ID_OFFSET = 25;
      const static int NEXT_TO_OUT_REL_ID_OFFSET = 29;


      Relation(gid id);
      Relation(gid id, ByteBuffer *buffer);
      Relation(gid id, std::uint8_t *buffer, std::size_t size);
      ~Relation();

      gid GetFromEntityId();
      void SetFromEntityId(gid id);
      gid GetToEntityId();
      void SetToEntityId(gid id);

      gid GetNextFromInRelationId();
      void SetNextFromInRelationId(gid id);
      gid GetNextFromOutRelationId();
      void SetNextFromOutRelationId(gid id);

      gid GetNextToInRelationId();
      void SetNextToInRelationId(gid id);
      gid GetNextToOutRelationId();
      void SetNextToOutRelationId(gid id);



      virtual Concept GetConcept() {return Concept::CRelation; }
    private:
  };


  class RelationCollection {
    public:
      RelationCollection();
      ~RelationCollection();
      std::size_t Size();
      void Add(Relation *relation);
      Relation* operator[](std::size_t index);
    private:
      std::vector<Relation*> m_relations;
  };

  class RelationEncoder : public Encoder {
    public:
      RelationEncoder() : Encoder() {}
      virtual Storeable *Decode(gid id, ByteBuffer *buffer) { return new Relation(id, buffer); }
      virtual Storeable *Empty() { return new Relation(InvalidGraphId); }
      virtual bool Decodeable() { return true; }
  };

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
