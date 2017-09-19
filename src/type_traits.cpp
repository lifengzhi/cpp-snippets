#include <iostream>
#include <type_traits>

namespace mpt
{
    // C++11 possible implementation
    template <typename T> struct remove_reference      { typedef T type; };
    template <typename T> struct remove_reference<T&>  { typedef T type; };
    template <typename T> struct remove_reference<T&&> { typedef T type; };

    // C++14 alias template helper type
    template <typename T> using remove_reference_t = typename remove_reference<T>::type;

    // C++11 possible implementation
    template <typename T> struct is_reference      : std::false_type {};
    template <typename T> struct is_reference<T&>  : std::true_type  {};
    template <typename T> struct is_reference<T&&> : std::true_type  {};

    // C++14 alias template helper type
    template <typename T> constexpr bool is_reference_v = is_reference<T>::value;
}

int main()
{
    std::cout << std::boolalpha;

    std::cout << std::is_same<int, mpt::remove_reference<int>::type>() << '\n';
    std::cout << std::is_same<int, mpt::remove_reference<int&>::type>() << '\n';
    std::cout << std::is_same<int, mpt::remove_reference<int&&>::type>() << '\n';

    std::cout << std::is_same<int, mpt::remove_reference_t<int>>() << '\n';
    std::cout << std::is_same<int, mpt::remove_reference_t<int&>>() << '\n';
    std::cout << std::is_same<int, mpt::remove_reference_t<int&&>>() << '\n';

    std::cout << mpt::is_reference<int>::value << '\n';
    std::cout << mpt::is_reference<int&>::value << '\n';
    std::cout << mpt::is_reference<int&&>::value << '\n';

    std::cout << mpt::is_reference_v<int> << '\n';
    std::cout << mpt::is_reference_v<int&> << '\n';
    std::cout << mpt::is_reference_v<int&&> << '\n';

    return 0;
}

