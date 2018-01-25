// See: http://en.cppreference.com/w/cpp/utility/program/exit
// Stack is not unwound after std::exit(): destructors of variables with
// automatic storage duration are not called.

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>

namespace {
auto const boom{false};
}

struct S {
  S() { std::cout << __FUNCTION__ << '\n'; }
  ~S() { std::cout << __FUNCTION__ << '\n'; }
};

void foo() {
  auto const my_S = std::make_unique<S const>();
  if (boom) std::exit(1);
}

int main() { foo(); }
