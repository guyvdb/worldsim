#ifndef INSTANCE_H
#define INSTANCE_H

#include "storeable.h"

namespace graph {


  /*
   * Buffer layout: Instance
   * |-----------|--------------------------------------------------|
   * | Storeable | Instance                                         |
   * |-----------|----------|-------|----------------|--------------|
   * | 0         | 1 2 3 4  | 5     | 6 7 8 9        | 10..n        |
   * | flag      | Class Id | Count | NextInstanceId | Instance Ids |
   * |-----------|----------|-------|----------------|--------------|
   *
   * Name is a short string
   * Class padded to 48 bytes long
   *
   * Overhead is 10 bytes
   * Id storage is 4 bytes per id
   *
   * 253 ids x 4 bytes = 1012 bytes
   * 10 bytes overhead + 1012 bytes + 2 bytes padding = 1024
   *
   */

  class Instance : public Storeable {
    public:
      static const std::size_t INSTANCE_IDS_PER_PAGE = 10;
      static const std::size_t INSTANCE_OVERHEAD_SPACE = 11;
      static const std::size_t INSTANCE_ID_SPACE = 4 * INSTANCE_IDS_PER_PAGE;

      Instance();
      Instance(type::gid id);
      Instance(type::gid id, graph::type::ByteBuffer *buffer);
  };

}


#endif // INSTANCE_H
