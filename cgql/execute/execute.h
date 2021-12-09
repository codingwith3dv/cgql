#ifndef EXECUTE_H
#define EXECUTE_H

#include "../cgqlPch.h"
#include "../type/Document.h"
#include "../schema/GraphQLDefinition.h"

namespace cgql {

using std::unordered_map;
using std::shared_ptr;

typedef unordered_map<string, vector<internal::Field>> GroupedField;

struct ResultMap;
typedef variant<
  GraphQLReturnTypes,
  shared_ptr<ResultMap>
> Data;

struct ResultMap {
  unordered_map<string, Data> data;
};

namespace internal {

GraphQLField findGraphQLFieldByName(
  const GraphQLObject& objectType,
  const string& fieldName
);

GroupedField collectFields(
  const GraphQLObject& objectType,
  const SelectionSet& selectionSet
);

Data executeField(
  const GraphQLField& field,
  const GraphQLScalarTypes& fieldType,
  const vector<Field>& fields
);

ResultMap executeSelectionSet(
  const SelectionSet& selectionSet,
  const GraphQLObject& objectType
);

ResultMap executeQuery(
  OperationDefinition& query,
  const GraphQLSchema& schema
);
OperationDefinition getOperation(
  const Document& document,
  OperationType operationName = OperationType::QUERY
);

} // internal 

ResultMap execute(
  const GraphQLSchema& schema,
  const internal::Document& document
);

}
#endif