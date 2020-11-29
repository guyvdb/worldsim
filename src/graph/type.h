#ifndef TYPE_H
#define TYPE_H

#include <storeable.h>
#include <buffer.h>

#include <string>


/*
 * Buffer layout of type:
 * |------|---------|-----------|
 * | 0    | 1 2 3 4 | 5 .. 63   |
 * | flag | typeid  | bucket    |
 * |------|---------|-----------|
 */
namespace graph {

  /* Everything is typed in the graph. There are the built in types and user defined types. All types follow
     the same layout.

     Types are applied to entities, relations, attributes, roles and built-ins.

     Attribute types can only be made up of the built-ins

     Entity types define a set of attributes and roles

     Relation types define a set of roles

     Built-ins are a set of hard coded types (int, string, bool, etc)



     built in types:
     --------------------
     flag, id, name, datatype
     0, 1, string, string
     0, 2, double, double
     0, 3, string-set, string[]

     use = has, key, role, relates, rule???


     enum type
     ----------------
     gender -> use(enum), string, next-bucket->
     male -> use(enum-value), string, next-bucket->
     female -> use(enum-value), string, null-bucket-id->



     entity type
     -------------------
     person is entity,
           has full-name,
           has age,
           has gender,
           plays spouse,
           plays sibbling;


     person -> use(inherits) entity, next-bucket->
     full-name -> use(has), string, next-bucket->
     age -> use(has), integer, next-bucket->
     gender -> use(has), gender, next-bucket->
     spouse -> use(role),









   */



  class Type : public Storeable {
    public:
      Type(gid id);
      Type(gid id, ByteBuffer *buffer);
      Type(gid id, std::string name);
      ~Type();
  };

}
#endif // TYPE_H
