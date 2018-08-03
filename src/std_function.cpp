// Taken from std::function and const-correctness in C++11/14/17
// by @walletfox (week's cheatsheet)

#include <functional>
#include <iostream>

struct function_object {
  void operator()() { std::cout << "non-const overload\n"; }
  void operator()() const { std::cout << "const overload\n"; }
};

int main() {
  const auto function_by_auto = function_object();
  function_by_auto();

  const std::function<void()> function_by_function = function_object();
  function_by_function();
}
