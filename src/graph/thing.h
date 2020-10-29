#ifndef THING_H
#define THING_H

#include <types.h>
#include <properties.h>
#include <storeable.h>
//#include <tx.h>
#include <relation.h>
#include <relationtype.h>
#include <bytebuffer.h>
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



namespace graph {

  class Graph;
  class Thing;
  class Relation;
  class Tx;

  class Thing : public Storeable {
    public:
      Thing();
      Thing(gid id);
      Thing(gid id, ByteBuffer *data);
      Thing(gid id, gid propid, gid inrelid, gid outrelid);
      ~Thing();

      gid Id() {return m_id;}
      gid PropId() { return m_propId; }
      gid InRelId() { return m_inRelId; }
      gid OutRelId() { return m_outRelId; }
      //PropertyCollection *Properties() { return  m_properties; }
      virtual ByteBuffer *Buffer();

    protected:
      // This might need to be friended
      bool Deleted() {return m_deleted;}
      gid PropertiesId() { return m_propId; }
      gid OutRelationId() { return m_outRelId; }
      gid InRelationId() { return m_inRelId; }
    private:
      Graph *g;
      gid m_id;
      gid m_propId;
      gid m_inRelId;
      gid m_outRelId;
      bool m_deleted;
      EntityPropertyCollection *m_properties;
  };
}
#endif // THING_H
