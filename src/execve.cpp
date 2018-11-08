#include <unistd.h>

#include <iostream>
#include <type_traits>

int main() {
  // execve: declare argv as array of const pointer to char
  // https://cdecl.org/?q=char+*const+argv%5B%5D

  // error: ISO C++ forbids converting a string constant to ‘char*’
  // char* const argv[] = {"args_printf", "argv1", "argv2", nullptr};

  const char* const argv[] = {"args_printf", "argv1", "argv2", nullptr};

  // clang-format off
  std::cout << std::boolalpha;
  // true: the argv array decays to a pointer to const pointer to const char
  std::cout << std::is_same_v<const char* const*, std::decay_t<decltype(argv)>> << '\n';
  // false: the argv array does not decay to a pointer to const pointer to char
  std::cout << std::is_same_v<char* const*, std::decay_t<decltype(argv)>> << '\n';
  // true: const_cast<T> returns a value of type T
  // https://en.cppreference.com/w/cpp/language/const_cast
  // Two possibly multilevel pointers to the same type may be converted between each other, regardless of cv-qualifiers at each level.
  std::cout << std::is_same_v<char* const*, decltype(const_cast<char* const*>(argv))> << '\n';
  // clang-format on

  // error: invalid conversion from ‘const char* const*’ to ‘char* const*’
  // return execve(argv[0], argv, nullptr);
  return execve(argv[0], const_cast<char* const*>(argv), nullptr);
}