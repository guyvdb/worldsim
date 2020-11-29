#ifndef ENTITY_H
#define ENTITY_H

#include <types.h>
#include <storeable.h>
#include <buffer.h>



/*
 * Buffer layout of entity:
 * |------|---------|-----------|------------|
 * | 0    | 1 2 3 4 | 5 6 7 8   | 9 10 11 12 |
 * | flag | typeid  | relid     | attribid   |
 * |------|---------|-----------|------------|
 */

namespace graph {
  class Entity : public Storeable {
    public:
      Entity();
      Entity(gid id);
      Entity(gid id, ByteBuffer *buffer);
      Entity(gid id, gid attribid, gid relid);
      ~Entity();
      gid AttributeId();
      gid RelationId();
      void SetAttributeId(gid value);
      void SetRelationId(gid value);
      virtual Concept GetConcept() { return Storeable::Concept::Entity; }
    private:
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
