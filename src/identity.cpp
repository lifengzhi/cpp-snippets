// https://codereview.stackexchange.com/q/134627/28000
// https://stackoverflow.com/a/15202612/496459

#include <array>
#include <iostream>

struct identity {
  template <typename U>
  constexpr auto operator()(U&& v) const noexcept -> decltype(auto) {
    return std::forward<U>(v);
  }
};

template <class Type, std::size_t Size, class Function = identity>
void index(std::array<Type, Size>& x, Function&& f = Function()) {
  for (unsigned int i = 0; i < Size; ++i) {
    x[i] = f(i);
  }
}

int main() {
  std::array<int, 5> arr;
  index(arr);
  for (auto const& elem : arr) {
    std::cout << elem << '\n';
  }
}