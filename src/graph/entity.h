#ifndef ENTITY_H
#define ENTITY_H


#include "graph.h"
#include "storeable.h"
#include "type/base.h"
#include "type/buffer.h"
#include "type/factory.h"


namespace graph {
  class Relation;


  /*
   * Buffer layout: Entity
   * |-----------|--------------------|----------------------|----------------------------------|
   * | Storeable | StoreableWithClass | StoreableWithProps   | Entity                           |
   * |-----------|--------------------|----------------------|-----------------|----------------|
   * | 0         | 1 2 3 4            | 5 6 7 8              | 9 10 11 12      | 13 14 15 16    |
   * | flag      | class id           | Root AttribBucket Id | Root Out Rel Id | Root In Rel Id |
   * |-----------|--------------------|----------------------|-----------------|----------------|
   *
   * Entity padded to 18 bytes long
   */

  /*
   *  typedef graph::Storeable* (*FactoryFunc)(gid id, ByteBuffer *buffer);
   */



  class Entity : public StoreableWithProps {
    public:
      const static int ROOT_OUT_REL_ID_OFFSET = 9;
      const static int ROOT_IN_REL_ID_OFFSET = 13;

      static Storeable* FactoryFunc(type::gid id, type::ByteBuffer *buffer);
      static type::FactoryFunc GetFactoryFunc();


      // Constructors/Destructor
      Entity();
      Entity(type::gid id);
      Entity(type::gid id, graph::type::ByteBuffer *buffer);
      Entity(type::gid id, type::gid attribid, type::gid outRelId, type::gid inRelid);
      ~Entity();

      // Root Out Relation
      type::gid GetRootOutRelationId();
      void SetRootOutRelId(type::gid id);

      // Root In Relation
      type::gid GetRootInRelationId();
      void SetRootInRelationId(type::gid id);

      // Create a relation
      Relation *CreateRelation(Entity *to, type::gid type);

      // Attach a relation to the linked list - in & out
      // Relations are in a double linked list. There are two linked lists.
      // One for in and one for out.
      bool LinkInRelation(Relation *r);
      bool LinkOutRelation(Relation *r);
      bool UnlinkInRelation(Relation *r);
      bool UnlinkOutRelation(Relation *r);



      // Get the concept of this storeable
      virtual Concept GetConcept() { return Storeable::Concept::EntityConcept; }

      // Get A list of relations
      std::vector<Relation*> InRelations();
      std::vector<Relation*> OutRelations();


    private:
  };







}
#endif // ENTITY_H





