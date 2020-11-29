#include "entityencoder.h"

namespace graph {

  std::size_t EntityEncoder::EncodedSize() {
    return 0;
  }


  /*
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
  bool EntityEncoder::Encode(Storeable *s, ByteBuffer *buffer) {




    return false;
  }

}
