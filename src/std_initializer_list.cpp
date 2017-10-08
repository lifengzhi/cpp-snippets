#include <iostream>
#include <type_traits>

/*
C++98 	__cplusplus = 199711L 	ISO/IEC 14882:1998
C++11 	__cplusplus = 201103L 	ISO/IEC 14882:2011
C++14 	__cplusplus = 201402L 	ISO/IEC 14882:2014
*/

int main()
{
    // C++17: int
    // C++11/14: std::initializer_list<int>
    auto i{ 1 };
    std::cout << std::boolalpha;
#if __cplusplus > 201402L
    bool res = std::is_same_v<decltype(i), int>;
    std::cout << "After C++17: " << typeid(i).name() << ' ' << res << '\n';
#else
    bool res = std::is_same<decltype(i), std::initializer_list<int>>::value;
    std::cout << "Before C++17: " << res << '\n';
#endif
}
