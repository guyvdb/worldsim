#ifndef TYPE_H
#define TYPE_H

#include "storeable.h"
#include "type/base.h"
#include "type/propertydef.h"
#include "inheritance.h"
namespace graph {





    /*
     * Buffer layout: Class
     * |-----------|---------------------------------------------------------------------------|
     * | Storeable | Class                                                                     |
     * |-----------|---------|---------|---------------|---------------------|-----------------|
     * | 0         | 1       | 2 .. 34 | 35 36 37 38   | 39 40 41 42         | 43 44 45 46     |
     * | flag      | Concept |  name   | SuperClass Id | Root Inheritance Id | Root PropDef Id |
     * |-----------|---------|---------|---------------|---------------------|-----------------|
     *
     * Name is a short string
     * Class padded to 48 bytes long
     */

    // A Type is a type of Entity or a Type of Relation. Type is a graph vertex. Type and
    // Heirachy form a graph with Heirachy being an edge. This is the type graph which is
    // independant of the main graph.
    //
    class Class : public Storeable {
      public:
        const static int CONCEPT_ID_OFFSET = 1;
        const static int NAME_OFFSET = 2;
        const static int SUPERCLASS_ID_OFFSET = 35;
        const static int ROOT_INHERITANCE_ID_OFFSET = 39;
        const static int ROOT_PROPDEF_ID_OFFSET = 43;
        Class(type::gid id);
        Class(type::gid id, type::ByteBuffer *buffer);
        virtual Concept GetConcept() { return Concept::ClassConcept; }
        Storeable::Concept GetTargetConcept();
        void SetTargetConcept(Storeable::Concept concept);
        std::string GetName();
        void SetName(std::string name);
        type::gid GetSuperclassId();
        void SetSuperclassId(type::gid id);
        type::gid GetRootInheritanceId();
        void SetRootInheritanceId(type::gid id);
        type::gid GetRootPropDefId();
        void SetRootPropDefId(type::gid id);
        Inheritance* AddSubclass(Class *subclass);
        Class *Superclass();
        std::vector<Inheritance*> GetInheritances();


        //     * | flag      | type id | name    | Dtid | ordinal | Required | Next ProfDef Id | Prev PropDef Id |

        type::PropertyDef *AddProperty(type::FixedString name, type::SimpleType datatype, bool required);
        void RemoveProperty(type::FixedString name);
        std::vector<type::PropertyDef*> Properties();

    };


}
#endif // TYPE_H
