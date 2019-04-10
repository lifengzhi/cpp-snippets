// http://www.reedbeta.com/blog/cpp-compile-time-array-size/
// https://stackoverflow.com/a/1500439/496459

#include <cstddef>  // std::size_t

template <typename T, std::size_t N>
constexpr std::size_t dim(T (&)[N]) {
  return N;
}

int main() {
  int a[] = {1, 2, 3};
  static_assert(dim(a) == 3);

  int b[] = {4, 5, 6};
  static_assert(dim(a) == dim(b));

  return (dim(a) + dim(b));
}