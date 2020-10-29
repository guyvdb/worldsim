#include "entity.h"

#include <iostream>


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

  Entity::Entity() : Storeable(NullId) {
    this->SetPropId(NullId);
    this->SetInRelId(NullId);
    this->SetOutRelId(NullId);
  }


  Entity::Entity(gid id) : Storeable(id) {
    this->SetPropId(NullId);
    this->SetInRelId(NullId);
    this->SetOutRelId(NullId);
  }

  // The caller ownes the data byte buffer
  Entity::Entity(gid id, const char *data) : Storeable(id) {
    const char *ptr = data;
    for(int i=0;i< (int)Storeable::EntitySize; i++) {
      this->m_buf[i] = *ptr;
      ptr++;
    }
  }

  Entity::Entity(gid id, gid propid, gid inrelid, gid outrelid) : Storeable(id) {
    this->SetPropId(propid);
    this->SetInRelId(inrelid);
    this->SetOutRelId(outrelid);
  }

  Entity::~Entity()  {

  }

  gid Entity::PropId() {
    return (gid)this->GetUInt32(&this->m_buf[2]);
  }

  gid Entity::InRelId() {
    return (gid)this->GetUInt32(&this->m_buf[6]);
  }

  gid Entity::OutRelId() {
    return (gid)this->GetUInt32(&this->m_buf[10]);
  }

  void Entity::SetPropId(gid value) {
    this->SetUInt32(value, &this->m_buf[2]);
  }

  void Entity::SetInRelId(gid value) {
    this->SetUInt32(value,&this->m_buf[6]);
  }

  void Entity::SetOutRelId(gid value) {
    this->SetUInt32(value,&this->m_buf[10]);
  }

}
