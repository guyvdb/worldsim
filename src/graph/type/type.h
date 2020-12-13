#ifndef TYPE_H
#define TYPE_H

#include <storeable.h>
#include <decoder.h>
#include <type/base.h>
#include <type/propertydef.h>

namespace graph {

  namespace type {



    /*
     * Buffer layout: Type
     * |-----------|---- ----|--------------------------------------------|
     * | Storeable | Type                                                 |
     * |-----------|---------|---------|---------------|------------------|
     * | 0         | 1       | 2 .. 66 | 67 68 69 70   | 71 72 73 74      |
     * | flag      | Concept |  name   | SuperClass Id | Root Subclass Id |
     * |-----------|---------|---------|---------------|------------------|
     *
     * Name is a short string
     * Type padded to 76 bytes long
     */

    // A Type is a type of Entity or a Type of Relation. Type is a graph vertex. Type and
    // Heirachy form a graph with Heirachy being an edge. This is the type graph which is
    // independant of the main graph.
    //
    class Type : public Storeable {
      public:
        const static int CONCEPT_ID_OFFSET = 1;
        const static int NAME_OFFSET = 2;
        const static int SUPERCLASS_ID_OFFSET = 67;
        const static int ROOT_SUBCLASS_ID_OFFSET = 71;
        Type(gid id);
        Type(gid id, ByteBuffer *buffer);
        virtual Concept GetConcept() { return Concept::TypeConcept; }
        Storeable::Concept GetTargetConcept();
        void SetTargetConcept(Storeable::Concept concept);
        std::string GetName();
        void SetName(std::string name);
        gid GetSuperclassId();
        void SetSuperclassId(gid id);
        gid GetRootSubclassId();
        void SetRootSubclassId(gid id);
        void AddSubclass(Type *subclass);

        type::Type *Superclass();


        //     * | flag      | type id | name    | Dtid | ordinal | Required | Next ProfDef Id | Prev PropDef Id |

        PropertyDef *AddProperty(FixedString name, SimpleType datatype, bool required);
        void RemoveProperty(FixedString name);
        std::vector<PropertyDef*> Properties();

    };


/*
    class TypeDecoder : public Decoder {
      public:
        TypeDecoder() : Decoder() {}
        virtual Storeable *Decode(gid id, ByteBuffer *buffer) { return new Type(id, buffer); }
        virtual Storeable *Empty() { return new Type(NullGraphId); }
        virtual bool Decodeable() { return true; }
    };
*/
  }
}
#endif // TYPE_H
