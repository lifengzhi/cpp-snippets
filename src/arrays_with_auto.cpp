#include <array>

#define UNUSED(x) (void)(x)

// C++17 only
// requires template argument deduction for class templates
namespace std {
template <typename... T>
array(T... t)->array<std::common_type_t<T...>, sizeof...(t)>;
}

int main() {
  int a[] = {1, 2, 3};
  int b[]{4, 5, 6};

  // See: https://stackoverflow.com/q/7107606
  // not allowed as {1, 2, 3, 4} is purely a syntactic construct- it is not an
  // expression and does not have a type, therefore, auto cannot deduce its
  // type from it.
  // auto c[] = {1,2,3};
  // auto d[] {4,5,6};

  // Alternative via std::array (see above), but not quite the same...
  // https://stackoverflow.com/q/6114067
  std::array e{1, 2, 3, 4};

  UNUSED(a);
  UNUSED(b);
  UNUSED(e);
}
