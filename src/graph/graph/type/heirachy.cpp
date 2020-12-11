#include "heirachy.h"


namespace graph {
  namespace type {

    Heirachy::Heirachy(gid id) : graph::Storeable(id, Storeable::HeirarchSize) {
      this->Load(SUPERCLASS_ID_OFFSET, NullGraphId);
      this->Load(SUBCLASS_ID_OFFSET, NullGraphId);
      this->Load(SUPERCLASS_NEXT_HEIRACHY_ID_OFFSET, NullGraphId);
      this->Load(SUPERCLASS_PREV_HEIRACHY_ID_OFFSET, NullGraphId);
      this->Load(SUBCLASS_NEXT_HEIRACHY_ID_OFFSET, NullGraphId);
      this->Load(SUBCLASS_PREV_HEIRACHY_ID_OFFSET, NullGraphId);
    }

    Heirachy::Heirachy(gid id, ByteBuffer *buffer) : Storeable(id, buffer) {

    }

    gid Heirachy::GetSuperclassId() {

    }

    void Heirachy::SetSuperclassId(gid id) {

    }

    gid Heirachy::GetSubclassId() {

    }

    void Heirachy::SetSubclassId(gid id) {

    }

    gid Heirachy::GetSuperclassNextHeirachyId() {

    }

    void Heirachy::SetSuperclassNextHeirachyId(gid id) {

    }

    gid Heirachy::GetSuperclassPrevHeirachyId() {

    }

    void Heirachy::SetSuperclassPrevHeirachyId(gid id) {

    }

    gid Heirachy::GetSubclassNextHeirachyId() {

    }

    void Heirachy::SetSubclassNextHeirachyId(gid id) {

    }

    gid Heirachy::GetSubclassPrevHeirachyId() {

    }

    void Heirachy::SetSubclassPrevHeirachyId(gid id) {

    }


  }

}



