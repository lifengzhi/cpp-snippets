// See: https://stackoverflow.com/q/25612262/496459

#include <iostream>
#include <type_traits>

/*
C++98 	__cplusplus = 199711L 	ISO/IEC 14882:1998
C++11 	__cplusplus = 201103L 	ISO/IEC 14882:2011
C++14 	__cplusplus = 201402L 	ISO/IEC 14882:2014
*/

int main() {
  // C++17: int
  // C++11/14: std::initializer_list<int>
  auto const i{1};
  std::cout << std::boolalpha;
#if __cplusplus > 201402L
  std::cout << "After C++17: " << typeid(i).name()
            << " is int: " << std::is_same_v<decltype(i), int> << '\n';
#else
  std::cout << "Before C++17: " << typeid(i).name()
            << " is int: " << std::is_same<decltype(i), int>::value << '\n';
#endif
}
