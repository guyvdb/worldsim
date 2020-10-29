#ifndef RELATION_H
#define RELATION_H

#include <storeable.h>
#include <tx.h>
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
  class Graph;


  class Relation : public Storeable{
    public:
      Relation(gid id) : Storeable(id){};
    private:

  };
}
#endif // RELATION_H
