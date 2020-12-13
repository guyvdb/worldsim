#ifndef HEIRACHY_H
#define HEIRACHY_H


#include <storeable.h>
#include <buffer.h>
#include <decoder.h>



namespace graph {
  namespace type {


    /*
     * Buffer layout: Heirachy
     * |-----------|----------------------------------------------------------------------------------------|
     * | Storeable | Heirachy                                                                               |
     * |-----------|----------|-------------|----------------|----------------|--------------|--------------|
     * | 0         | 1 2 3 4  | 5 6 7 8     | 9 10 11 12     | 13 14 15 16    | 17 18 19 20  | 21 22 23 24  |
     * | flag      | Super Id | Subclass Id | Super Next Hid | Super Prev Hid | Sub Next Hid | Sub Prev Hid |
     * |-----------|----------|-------------|----------------|----------------|--------------|--------------|
     *
     * Type padded to 26 bytes long
     */

    // This is the type heirachy. It acts as a graph edge joining Type vertexes.
    class Heirachy : public Storeable {
      public:

        const static int SUPERCLASS_ID_OFFSET = 1;
        const static int SUBCLASS_ID_OFFSET = 5;
        const static int SUPERCLASS_NEXT_HEIRACHY_ID_OFFSET = 9;
        const static int SUPERCLASS_PREV_HEIRACHY_ID_OFFSET = 13;
        const static int SUBCLASS_NEXT_HEIRACHY_ID_OFFSET = 17;
        const static int SUBCLASS_PREV_HEIRACHY_ID_OFFSET = 21;


        Heirachy(gid id);
        Heirachy(gid id, ByteBuffer *buffer);

        gid GetSuperclassId();
        void SetSuperclassId(gid id);
        gid GetSubclassId();
        void SetSubclassId(gid id);
        gid GetSuperclassNextHeirachyId();
        void SetSuperclassNextHeirachyId(gid id);
        gid GetSuperclassPrevHeirachyId();
        void SetSuperclassPrevHeirachyId(gid id);
        gid GetSubclassNextHeirachyId();
        void SetSubclassNextHeirachyId(gid id);
        gid GetSubclassPrevHeirachyId();
        void SetSubclassPrevHeirachyId(gid id);




        virtual Concept GetConcept() { return Concept::HeirachyConcept; }
    };

/*
    class HeirachyDecoder : public Decoder {
      public:
        HeirachyDecoder() : Decoder() {}
        virtual Storeable *Decode(gid id, ByteBuffer *buffer) { return new Heirachy(id, buffer); }
        virtual Storeable *Empty() { return new Heirachy(NullGraphId); }
        virtual bool Decodeable() { return true; }
    };
*/
  }

}


#endif // HEIRACHY_H
