#ifndef ENTITY_H
#define ENTITY_H

#include <types.h>
#include <storeable.h>
#include <buffer.h>
#include <decoder.h>

namespace graph {
  class Relation;
  class RelationCollection;
  class AttributeCollection;
  class Attribute;

  /*
   * Buffer layout: Entity
   * |-----------|-------------------|----------------------|----------------------------------|
   * | Storeable | StoreableWithType | StoreableWithAttrib  | Entity                           |
   * |-----------|-------------------|----------------------|-----------------|----------------|
   * | 0         | 1 2 3 4           | 5 6 7 8              | 9 10 11 12      | 13 14 15 16    |
   * | flag      | typeid            | Root AttribBucket Id | Root Out Rel Id | Root In Rel Id |
   * |-----------|-------------------|----------------------|-----------------|----------------|
   *
   * Entity padded to 18 bytes long
   */



  class Entity : public StoreableWithAttributes {
    public:
      const static int ROOT_OUT_REL_ID_OFFSET = 9;
      const static int ROOT_IN_REL_ID_OFFSET = 13;

      // Constructors/Destructor
      Entity();
      Entity(gid id);
      Entity(gid id, ByteBuffer *buffer);
      Entity(gid id, gid attribid, gid outRelId, gid inRelid);
      ~Entity();

      // Root Out Relation
      gid GetRootOutRelationId();
      void SetRootOutRelId(gid id);

      // Root In Relation
      gid GetRootInRelationId();
      void SetRootInRelationId(gid id);

      // Create a relation
      Relation *CreateRelation(Entity *to, gid type);

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

      // Get a list of attributes
      AttributeCollection *Attributes();

    private:
  };

  /*
  class EntityCollection {
    public:
      EntityCollection();
      ~EntityCollection();
      std::size_t Size();
      void Add(Entity *entity);
      //void Remove(Entity *entity);
      Entity* operator[](std::size_t index);
      //Entity* At(std::size_t index);
    private:
      std::vector<Entity*> m_entities;
  };
*/

  class EntityDecoder : public Decoder {
    public:
      EntityDecoder() : Decoder() {}
      virtual Storeable *Decode(gid id, ByteBuffer *buffer) { return new Entity(id, buffer); }
      virtual Storeable *Empty() { return new Entity(NullGraphId); }
      virtual bool Decodeable() { return true; }
  };
}
#endif // ENTITY_H






/*
Node store:
All the nodes in the database are stored in the node store file.
Each node record accounts for a fixed 15 bytes.
The layout is as follows:
1st byte — isInUse
Next 4 bytes — ID of the node
Next byte — First relationship ID
Next byte — First property ID
Next 5 bytes — Label store
Remaining byte — for future use
The first byte is used to determine whether the record is being used or has been deleted. If not, the record will be used for newer entries.
The next 3 sectors are the IDs of the node itself, first relationship ID, first property ID and label store. Some of the labels are stored in the node itself if possible for lesser jumps. The other bytes are to saved for future use.

On Disk Representation
================================
Object Id                -- Not stored
Deleted                 1
Entity Type Id          2
First Property Page Id	4
First Property Type     1
First Out Relation Id   4
First In Relation Id    4
--------------------------
Total                   16

*/
