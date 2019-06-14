// https://www.fluentcpp.com/2017/07/07/optional-monad-cpp-without-ugly-stuff/

#include <iostream>
#include <optional>

template <typename R, typename... P>
auto make_failable(R (*f)(P... ps)) {
  return [f](std::optional<P>... xs) -> std::optional<R> {
    if ((xs && ...)) {
      return {f(*(xs)...)};
    } else {
      return {};
    }
  };
}

template <typename R, typename... P>
auto make_failable(std::optional<R> (*f)(P... ps)) {
  return [f](std::optional<P>... xs) -> std::optional<R> {
    if ((xs && ...)) {
      return f(*(xs)...);
    } else {
      return {};
    }
  };
}

int f1(int a) { return 2 * a; }
int f2(int b, int c) { return b + c; }
int f3(int d) { return d + 2; }
int f4(int e) { return e - 2; }

int main() {
  auto failable_f1{make_failable(f1)};
  auto failable_f2{make_failable(f2)};
  auto failable_f3{make_failable(f3)};
  auto failable_f4{make_failable(f4)};

  std::cout << f4(f4(f3(f2(f1(42), f1(55))))) << '\n';

  auto res{failable_f4(
      failable_f4(failable_f3(failable_f2(failable_f1(42), failable_f1(55)))))};
  if (res) {
    std::cout << *res << '\n';
  }
}
