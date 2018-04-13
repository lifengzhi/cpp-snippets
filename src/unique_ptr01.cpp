// Ben Deane:
// https://twitter.com/ben_deane/status/964549956437606400
// https://t.co/mkOX0mf8jt
// When giving unique_ptr a custom deleter, prefer a stateless functor type over
// a function pointer type. The implementation won't have to store the pointer
// or call through it, and EBO means no overhead.

#include <memory>

struct custom_deleter_t {
  void operator()(int *) {}
};

int main() {
  using T = std::unique_ptr<int, void (*)(int *)>;
  using U = std::unique_ptr<int, custom_deleter_t>;
  static_assert(sizeof(T) == sizeof(int *) * 2);
  static_assert(sizeof(U) == sizeof(int *));
}
