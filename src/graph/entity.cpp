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

  void printbuf(std::string title, ByteBuffer *buf) {

    std::cout << title << "[";
    for(std::size_t i=0;i<buf->Size();i++){
      std::printf("%X ", buf->At(i));
    }
    std::cout << "], size=" << buf->Size() << std::endl;
  }

  Entity::Entity() : Storeable(NullId) {
    //this->m_buf = new Buffer(Storeable::EntitySize);

    this->CreateBuffer();

    this->SetPropId(NullId);
    this->SetInRelId(NullId);
    this->SetOutRelId(NullId);

    printbuf("Entity()", this->m_buf);
  }


  Entity::Entity(gid id) : Storeable(id) {
    //this->m_buf = new Buffer(Storeable::EntitySize);
    this->CreateBuffer();

    this->SetPropId(NullId);
    this->SetInRelId(NullId);
    this->SetOutRelId(NullId);

    printbuf("Entity(id)", this->m_buf);
  }


  // The caller ownes the data byte buffer
  Entity::Entity(gid id, ByteBuffer *buffer) : Storeable(id) {

    this->m_buf = new ByteBuffer(buffer);

    printbuf("Entity(id, buf)", this->m_buf);


    /*const char *ptr = data;
    for(int i=0;i< (int)Storeable::EntitySize; i++) {
      this->m_buf[i] = *ptr;
      ptr++;
    }*/
  }

  Entity::Entity(gid id, gid propid, gid inrelid, gid outrelid) : Storeable(id) {
    //this->m_buf = new Buffer(Storeable::EntitySize);
    this->CreateBuffer();

    this->SetPropId(propid);
    this->SetInRelId(inrelid);
    this->SetOutRelId(outrelid);
    printbuf("Entity(id, propid, inrelid, outrelid)", this->m_buf);
  }

  Entity::~Entity()  {
    std::cout << "[ENTITY] Release resource: " << this->GraphId() << std::endl;
    delete this->m_buf;
  }

  void Entity::CreateBuffer() {
    this->m_buf = new ByteBuffer(Storeable::EntitySize);
    for(std::size_t i=0;i<Storeable::EntitySize;i++){
      this->m_buf->Append(0x0);
    }
  }

  gid Entity::PropId() {
    std::cout << "m_buf is " << ((long)this->m_buf) << ", size=" << this->m_buf->Size() << std::endl;
    return (gid)this->m_buf->GetUint32(2);
    //return (gid)this->GetUInt32(&this->m_buf[2]);
  }

  gid Entity::InRelId() {
    return (gid)this->m_buf->GetUint32(6);
    //return (gid)this->GetUInt32(&this->m_buf[6]);
  }

  gid Entity::OutRelId() {
    return (gid)this->m_buf->GetUint32(10);
    //return (gid)this->GetUInt32(&this->m_buf[10]);
  }

  void Entity::SetPropId(gid value) {
    this->m_buf->Set(2,(std::uint32_t)value);
    //this->SetUInt32(value, &this->m_buf[2]);
  }

  void Entity::SetInRelId(gid value) {
    this->m_buf->Set(6,(std::uint32_t)value);
    //this->SetUInt32(value,&this->m_buf[6]);
  }

  void Entity::SetOutRelId(gid value) {
    this->m_buf->Set(10,(std::uint32_t)value);
    //this->SetUInt32(value,&this->m_buf[10]);
  }

}
