#ifndef ENTITY_H
#define ENTITY_H

#include <types.h>
//#include <properties.h>
#include <storeable.h>
#include <gid.h>
//#include <tx.h>
//#include <relation.h>
//#include <relationtype.h>
//#include <bytebuffer.h>
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

  //class Graph;
  //class Entity;
  //class Relation;
  //class Tx;



  class Entity : public Storeable {
    public:
      Entity();
      Entity(gid id);
      Entity(gid id, const char *data);
      Entity(gid id, gid propid, gid inrelid, gid outrelid);
      ~Entity();


      gid PropId();
      gid InRelId();
      gid OutRelId();
      void SetPropId(gid value);
      void SetInRelId(gid value);
      void SetOutRelId(gid value);

      virtual const char * Data() {return this->m_buf; }
      virtual Storeable::Type ObjectType() { return Storeable::Type::Entity; }
      virtual void SetFlag(const char flag) {this->m_buf[0] = flag; }
      virtual char GetFlag() { return this->m_buf[0]; }
    private:
      gid m_id;
      char m_buf[16];
  };

  class EntityFactory : public ObjectFactory {
    public:
      virtual Storeable *CreateObject(gid id, const char *data) { return new Entity(id, data); }
      virtual Storeable *CreateEmptyObject() { return new Entity(NullId); }
      virtual bool CanCreateObjects() { return true; }
  };
}
#endif // ENTITY_H
