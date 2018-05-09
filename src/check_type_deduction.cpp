#include <type_traits>

int main() noexcept {
  auto const i{1};
  const auto c_i{1};
  constexpr auto cxp_i{1};

  #if 0
  // C++11/14
  static_assert(std::is_same<int, decltype(i)>::value, "i is not int");
  static_assert(std::is_same<const int, decltype(c_i)>::value,
                "c_i is not const int");
  static_assert(std::is_same<const int, decltype(cxp_i)>::value,
                "cxp_i is not const int");

  // C++17
  static_assert(std::is_same_v<int, decltype(i)>, "i is not int");
  static_assert(std::is_same_v<const int, decltype(c_i)>,
                "c_i is not const int");
  static_assert(std::is_same_v<const int, decltype(cxp_i)>,
                "cxp_i is not const int");
#endif
  return 0;
}
