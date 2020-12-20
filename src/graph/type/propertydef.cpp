#include "propertydef.h"
namespace graph {
  namespace type {


    PropertyDef::PropertyDef(gid id) : Storeable(id, Storeable::PropertyDefSize){

    }

    PropertyDef::PropertyDef(gid id, ByteBuffer *buffer) : Storeable(id, buffer) {

    }

    PropertyDef::~PropertyDef() {

    }

  }
}
