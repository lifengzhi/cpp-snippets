#include <type_traits>

int main() {
  // in C++ character literals have type char
  // in C   character literals have type int
  auto single_character_literal{'a'};

  static_assert(std::is_same_v<decltype(single_character_literal), char>);
}
