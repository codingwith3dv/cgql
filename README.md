# ⚠ note
> The repository has been moved to https://github.com/cgql/cgql. All the new features and releases will be on the new repository!

# cgql
An implementation of GraphQL Service in C++, made from reference of official specifications! 😎 

## Getting Started!
### CMake

**Prerequisites**
- C++17 compiler
  - [GCC](https://gcc.gnu.org)
  - [Clang](https://clang.llvm.org)
  - [MSVC](https://docs.microsoft.com/en-us/cpp/?view=msvc-170)
- [CMake](https://cmake.org) ( >= 3.16 )
- A build tool
  - [Make](https://www.gnu.org/software/make)

**Downloading CGQL**
- Cloning using Git
```bash
git clone https://github.com/codingwith3dv/cgql.git
```
Doing this will clone the repository to your current working directory.
- Using tarball file ( *.tar.gz )
```bash
tar -xzvf <file-name>.tar.gz
```
Download the tarball file from release page and untar it using the above command.

- Using CGQL

CGQL is a statically linked library for Graphql which you can use on your own project to work with GraphQL in C++.
That means you will have to link the library with your project

Suppose you have a folder structure like this:
```
project/
  |-> src/
  | |-> main.cpp
  | |-> CMakeLists.txt
  |-> lib/
  | |-> cgql/ // this is the cloned / untar-ed cgql folder
  | |-> CMakeLists.txt
  |-> CMakeLists.txt
```

In the root level `CMakeLists.txt` add
```cmake
cmake_minimum_required(VERSION 3.16)

project(next_billion_dollar_startup)

# basic configuration for project like C++ standard, etc...
/.../

add_subdirectory(src) # includes "your" source code
add_subdirectory(lib) # includes libraries for your project
```

The `CMakeLists.txt` in `lib` should contain:
```cmake
add_subdirectory(cgql)
```
That's it... CGQL is included in your project like magic!

The `CMakeLists.txt` in `src` would contain something this:
```cmake
project(Source)

add_executable(Source main.cpp)

target_link_libraries(
  Source # your project
  cgqlSource # the static library of cgql ( source )
)
```

**Yeah that's it now you can use CGQL in your project**.

An example of executing a basic request
```cpp
#include <cgql/execute/execute.h>
#include <cgql/type/parser/parser.h>

using namespace cgql;

int main() {
  // schema
  auto typeDef = parseSchema(
    "type Person {"
    "  name: String"
    "  age: Int"
    "}"
    ""
    "type Query {"
    "  person: Person"
    "}"
  );

  // resolvers
  ResolverMap resolvers {
    {
      "person",
      []() -> Data {
        ResultMap p {
          { "name", "cw3dv" },
          { "age", 14 }
        };
        return cgqlSMakePtr<ResultMap>(p);
      }
    }
  };

  // query
  auto query = parse(
    "{"
    "  cw3dv: person {"
    "    name"
    "    age"
    "  }"
    "}"
  );

  // execution
  auto executionResult = execute(schema, query, resolvers);
  printResultMap(executionResult);
  /* prints result to stdout

  cw3dv
    name cw3dv
    age 14

  */ 
}
```

Finally run:
```bash
cmake -B ./build/
cmake --build ./build/
./build/src/Source
```

Output:
```bash
cw3dv
  name cw3dv
  age 14
```

And there you go, you have a working GraphQL service... :)
More to come like networking stuff, better error management, etc...
