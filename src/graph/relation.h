#ifndef RELATION_H
#define RELATION_H

#include <storeable.h>
#include <transaction.h>
#include <buffer.h>
/*
Relationship store:
Each relationship record is a fixed record of 34 bytes
The relationship record’s layout is as follows:
Start node ID
End node ID
Pointer to the relationship type
Pointer to the next and previous relationship record for each of the start node and end node
Each relationship record belongs to two nodes, the start node and the end node. Each relationship also has a type associated with it, which signifies which type of relationship is connecting the 2 nodes. The pointer to the relationship type helps to determine this.
The relationship node contains 4 other pointers or misdirections to relationship records. They point to the previous and next relationship of both the start node and end node similar to how doubly linked lists behave.
*/



namespace graph {
  //class Graph;


  class Relation : public Storeable{
    public:
      Relation(gid id);
      Relation(gid id, ByteBuffer *buffer);
      ~Relation();


      virtual ByteBuffer* Buffer() { return this->m_buf; }
      virtual Concept GetConcept() {return Concept::Relation; }
      virtual void SetFlag(std::uint8_t flag){this->m_buf->Set(0,flag); }
      virtual std::uint8_t GetFlag() {return this->m_buf->GetUint8(0); }

      /*

      virtual Buffer *Buf() = 0;
      virtual Type ObjectType() = 0;
      virtual void SetFlag(std::uint8_t flag) = 0;
      virtual std::uint8_t GetFlag() = 0;

      */



    private:
      ByteBuffer *m_buf;
  };



}
#endif // RELATION_H
