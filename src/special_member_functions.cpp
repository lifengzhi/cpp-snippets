// https://www.youtube.com/watch?v=uwv1uvi1OTU

#include <cstdio>
#include <type_traits>
#include <vector>

// https://en.wikipedia.org/wiki/Special_member_functions#Signatures
struct S {
  explicit S(int) { puts("S(int)"); }

  // Default constructor
  S() { puts("S()"); }
  // Copy constructor
  S(S const &) { puts("S(S const&"); }
  // Move constructor
  S(S &&) noexcept { puts("S(&&)"); }
  // Copy assignment operator
  S &operator=(S const &) {
    puts("operator=(S const&)");
    return *this;
  }
  // Move assignment operator
  S &operator=(S &&) noexcept {
    puts("operator=(S &&)");
    return *this;
  }
  // Destructor
  ~S() { puts("~S()"); }
};

int main() {
  static_assert(std::is_nothrow_move_constructible_v<S>);
  std::vector<S> vec;

  // vec.push_back(S(3));
  vec.emplace_back(3);
}