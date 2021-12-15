#ifndef DEFAULT_RESOLVER_H
#define DEFAULT_RESOLVER_H

#include "../schema/GraphQLDefinition.h"
#include "execute.h"

namespace cgql {
namespace internal {

using std::string;

inline Data defaultFieldResolver(
  const ResultMap& source,
  const string& name
) {
  // auto it = source.data.find(name);
  return source.data.at(name);
}

} // internal
} // cgql
#endif
