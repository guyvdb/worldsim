#ifndef ENTITY_H
#define ENTITY_H

#include <graph_types.h>
#include <storeable.h>
#include <buffer.h>

namespace graph {
  class Entity : public Storeable {
    public:
      Entity();
      Entity(gid id);
      Entity(gid id, ByteBuffer *buffer);
      Entity(gid id, gid propid, gid inrelid, gid outrelid);
      ~Entity();

      gid PropId();
      gid InRelId();
      gid OutRelId();
      void SetPropId(gid value);
      void SetInRelId(gid value);
      void SetOutRelId(gid value);

      virtual ByteBuffer *Buffer() { return this->m_buf; }
      virtual Concept Type() { return Storeable::Concept::Entity; }
      virtual void SetFlag(std::uint8_t flag) {this->m_buf->Set(0,flag); }
      virtual std::uint8_t GetFlag() { return this->m_buf->GetUint8(0); }

    private:
      void CreateBuffer();
      ByteBuffer *m_buf;
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
