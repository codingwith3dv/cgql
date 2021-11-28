#include <iostream>
namespace logger {
  #define INFO "\u001b[38;5;226m"
  #define SUCCESS "\u001b[38;5;86m"
  #define ERROR "\u001b[38;5;196m"
  #define RESET "\u001b[0m"

  void print(const char* ansiCode, const char* msg);
  void info(const char* msg);
};