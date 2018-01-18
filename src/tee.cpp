// See:
// https://www.fluentcpp.com/2017/09/29/tee-getting-precious-debug-info-easily/

#include <iostream>

template <typename T>
decltype(auto) tee14(T&& value) {
  std::cout << value << '\n';
  return std::forward<T>(value);
}

template <typename T>
auto tee11(T&& value) -> decltype(std::forward<T>(value)) {
  std::cout << value << '\n';
  return std::forward<T>(value);
}

template <typename T>
auto increment(T value) {
  return ++value;
}

template <typename T>
auto decrement(T value) {
  return --value;
}

int main() {
  tee14("Hello");

  // Retrieve intermediate values
  auto i{4};
  tee14(increment(tee14(decrement(i))));
}