#include "thing.h"

#include <iostream>
#include <gid.h>

namespace graph {


  Thing::Thing() : Storeable(), m_id(InvalidId), m_propId(InvalidId), m_inRelId(InvalidId), m_outRelId(InvalidId)  {
  }

  Thing::Thing(gid id) : Storeable(), m_id(id), m_propId(InvalidId), m_inRelId(InvalidId), m_outRelId(InvalidId)   {
  }

  // The caller ownes the data byte buffer
  Thing::Thing(gid id, ByteBuffer *data) : Storeable(), m_id(id), m_propId(InvalidId), m_inRelId(InvalidId), m_outRelId(InvalidId)   {
    // Flag       1
    // PropId     4
    // InRelId    4
    // OutRelId   4
    // Reserved   1
    // Reserved   1
    // Reserved   1

    // pop the reserved
    data->PopUInt8();
    data->PopUInt8();
    data->PopUInt8();

    this->m_outRelId = (gid)data->PopUInt32();
    this->m_inRelId = (gid)data->PopUInt32();
    this->m_propId = (gid)data->PopUInt32();
  }

  Thing::Thing(gid id, gid propid, gid inrelid, gid outrelid) : Storeable(),
    m_id(id), m_propId(propid), m_inRelId(inrelid), m_outRelId(outrelid)   {
  }

  Thing::~Thing()  {

  }


  ByteBuffer *Thing::Buffer() {
    // Flag       1
    // PropId     4
    // InRelId    4
    // OutRelId   4
    // Reserved   1
    // Reserved   1
    // Reserved   1
    ByteBuffer *b = new ByteBuffer(16);

    // Push the data
    b->Push((std::uint8_t)0x0)->Push(this->m_propId)->Push(this->m_inRelId)->Push(this->m_outRelId);

    // Push the reserved
    b->Push((std::uint8_t)0x0);
    b->Push((std::uint8_t)0x0);
    b->Push((std::uint8_t)0x0);


    return b;
  }
}
