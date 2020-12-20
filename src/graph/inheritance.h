#ifndef HEIRACHY_H
#define HEIRACHY_H


#include "storeable.h"
#include "type/buffer.h"
#include "type/base.h"



namespace graph {


      class Class;

    /*
     * Buffer layout: Inheritance
     * |-----------|--------------------------------------------------------------|
     * | Storeable | Inheritance                                                  |
     * |-----------|----------|-------------|------------------|------------------|
     * | 0         | 1 2 3 4  | 5 6 7 8     | 9 10 11 12       | 13 14 15 16      |
     * | flag      | Super Id | Subclass Id | Next Inheritance | Prev Inheritance |
     * |-----------|----------|-------------|------------------|------------------|
     *
     * Inheritance padded to 18 bytes long
     */

    // This is the type heirachy. It acts as a graph edge joining Type vertexes.
    class Inheritance : public Storeable {
      public:

        const static int SUPERCLASS_ID_OFFSET = 1;
        const static int SUBCLASS_ID_OFFSET = 5;
        const static int NEXT_INHERITANCE_ID_OFFSET = 9;
        const static int PREV_INHERITANCE_ID_OFFSET = 16;


        Inheritance(type::gid id);
        Inheritance(type::gid id, type::ByteBuffer *buffer);

        type::gid GetSuperclassId();
        void SetSuperclassId(type::gid id);
        type::gid GetSubclassId();
        void SetSubclassId(type::gid id);

        type::gid GetNextInheritanceId();
        void SetNextInheritanceId(type::gid id);
        type::gid GetPrevInheritanceId();
        void SetPrevInheritanceId(type::gid id);


        Class *GetSuperclass();
        Class *GetSubclass();
        Inheritance *GetNextInheritance();
        Inheritance *GetPrevInheritance();

        /*
        type::gid GetSuperclassNextHeirachyId();
        void SetSuperclassNextHeirachyId(type::gid id);
        type::gid GetSuperclassPrevHeirachyId();
        void SetSuperclassPrevHeirachyId(type::gid id);
        type::gid GetSubclassNextHeirachyId();
        void SetSubclassNextHeirachyId(type::gid id);
        type::gid GetSubclassPrevHeirachyId();
        void SetSubclassPrevHeirachyId(type::gid id);
        */


        virtual Concept GetConcept() { return Concept::InheritanceConcept; }
    };

}


#endif // HEIRACHY_H
