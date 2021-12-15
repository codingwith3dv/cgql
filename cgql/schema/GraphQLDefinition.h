#ifndef GRAPHQL_DEFINITION_H
#define GRAPHQL_DEFINITION_H
#include "GraphQLObject/GraphQLObject.h"

namespace cgql {

class GraphQLSchema {
public:
  GraphQLSchema(
    GraphQLObject& query
  ): query(query) {};
  ~GraphQLSchema() {};
  inline const GraphQLObject& getQuery() const {
    return this->query;
  }
private:
  GraphQLObject query;
};

} // cgql

#endif
