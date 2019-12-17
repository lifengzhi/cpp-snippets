// https://godbolt.org/z/GRUnq3
// https://godbolt.org/z/iYxW5p

#include <functional>
#include <iostream>
#include <utility>

template<typename... Funcs> 
struct overload_set : Funcs... 
{
    explicit overload_set(Funcs&&... funcs) : Funcs{std::forward<Funcs>(funcs)}... {}
    using Funcs::operator()...; 
};

template<class... Funcs> overload_set(Funcs...) -> overload_set<Funcs...>;

template<typename... Funcs>
[[nodiscard]] auto overloads(Funcs&&... funcs)
{
    return overload_set(std::function{std::forward<Funcs>(funcs)}...);
}

void pericombobulate_i16(int16_t x) { std::cout << x << "i16\n"; }
void pericombobulate_i32(int32_t x) { std::cout << x << "i32\n"; }
void pericombobulate_f32(float x)   { std::cout << x << "f32\n"; }
void pericombobulate_f64(double x)  { std::cout << x << "f64\n"; }

int main()
{
    auto const pericombobulate = overloads(
        pericombobulate_i16, pericombobulate_i32, pericombobulate_f32, pericombobulate_f64);

    auto const arg_i32{3};
    auto const arg_f32{3.0f};
    auto const arg_f64{3.0};

    pericombobulate(arg_i32);
    pericombobulate(arg_f32);
    pericombobulate(arg_f64);
}
