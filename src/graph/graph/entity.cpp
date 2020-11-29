#include "entity.h"

#include <iostream>
#include <cstdio>

/*
 * Entity is a storable object. This is the file layout of the entity object:
 *
 * Field    Size    Offset   Comment
 * -------  -----   ------   -------
 * Free     1       0         first byte of all storables is a free flag (or deleted)
 * Flag     1       1         reserved
 * PropId   4       2
 * InRelId  4       6
 * OutRelId 4       10
 * Reserved 2       14        reserved
 * =========================
 * Total    16 bytes
 */


namespace graph {


  Entity::Entity() : Storeable(NullId, Storeable::EntitySize) {
    this->SetAttributeId(NullId);
    this->SetRelationId(NullId);
  }


  Entity::Entity(gid id) : Storeable(id, Storeable::EntitySize) {
    this->SetAttributeId(NullId);
    this->SetRelationId(NullId);
  }


  // The caller ownes the data byte buffer
  Entity::Entity(gid id, ByteBuffer *buffer) : Storeable(id, buffer) {
  }

  Entity::Entity(gid id, gid attribid, gid relid) : Storeable(id, Storeable::EntitySize) {
    this->SetAttributeId(attribid);
    this->SetRelationId(relid);
  }

  Entity::~Entity()  {
  }
  /*

 * |------|---------|-----------|------------|
 * | 0    | 1 2 3 4 | 5 6 7 8   | 9 10 11 12 |
 * | flag | typeid  | relid     | attribid   |
 * |------|---------|-----------|------------|
  */

  gid Entity::AttributeId() {
    return (gid)this->Buffer()->GetUint32(9);
  }

  gid Entity::RelationId() {
    return (gid)this->Buffer()->GetUint32(5);
  }

  void Entity::SetAttributeId(gid value) {
    this->Buffer()->Set(9,(std::uint32_t)value);
  }

  void Entity::SetRelationId(gid value) {
    this->Buffer()->Set(5,(std::uint32_t)value);
  }

}
