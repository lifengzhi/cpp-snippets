// See:
// https://www.heise.de/developer/artikel/C-Core-Guidelines-The-Guideline-Support-Library-3780760.html

// In compiler explorer, use: -I/opt/compiler-explorer/libs/gsl-lite/include -O2

#include <gsl/span>

#define UNUSED(x) (void)(x)

template <typename T>
void copy_n(const T *src, T *des, int len) noexcept {
  UNUSED(src);
  UNUSED(des);
  UNUSED(len);
}

template <typename T>
void copy(gsl::span<const T> src, gsl::span<T> des) noexcept {
  UNUSED(src);
  UNUSED(des);
}

int main() {
  const int arr1[]{1, 2, 3};
  int arr2[]{3, 4, 5};
  copy_n(arr1, arr2, 3);

  gsl::span<const int> const s1{arr1};
  gsl::span<int> const s2{arr2};
  copy(s1, s2);

  // C++17
  // copy(gsl::make_span(arr1), gsl::make_span(arr2));
}
