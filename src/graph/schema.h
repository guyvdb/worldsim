#ifndef SCHEMA_H
#define SCHEMA_H

namespace graph {

  /*
   * The graph maintains a schema that includes entity type and entity property types. It
   * also includes relation type and relation property types. The schema is built automatically
   * and can be compacted to remove unsed types.
   */
  class Schema {
    public:
      Schema();
  };

}
#endif // SCHEMA_H
