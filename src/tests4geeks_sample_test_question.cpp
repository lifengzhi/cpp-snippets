#include <iostream>
#include <utility>

void dispatch(int const&, char const* label)
{
    std::cout << label << ": lvalue\n";
}

void dispatch(int&&, char const* label)
{
    std::cout << label << ": rvalue\n";
}

template <typename T>
void forward1(T&& value, char const* label)
{
    return dispatch(value, label);
}

template <typename T>
void forward2(T&& value, char const* label)
{
    return dispatch(std::forward<T>(value), label);
}

int main()
{
    auto i = 0;
    dispatch(i, "dispatch(i)");
    dispatch(std::move(i), "dispatch(std::move(i))");
    forward1(i, "forward1(i)");
    forward1(std::move(i), "forward1(std::move(i))");
    forward2(i, "forward2(i)");
    forward2(std::move(i), "forward2(std::move(i))");
}
