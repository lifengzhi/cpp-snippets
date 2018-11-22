// https://twitter.com/SeanParent/status/1063942839527071745

#include <iostream>
#include <numeric>
#include <vector>

int main() {
  std::vector<int> v(10);
  std::iota(std::begin(v), std::end(v), 0);

  {
    // i is an index
    for (size_t i = 0, n = std::size(v); i != n; ++i) {
      std::cout << v[i] << '\n';
    }

    // f and l are iterators
    for (auto f = std::cbegin(v), l = std::cbegin(v); f != l; ++f) {
      std::cout << *f << '\n';
    }

    // e is an element
    for (auto const& element : v) {
      std::cout << element << '\n';
    }
  }

  // Using list initialization
  // recommended by Nicolai M. Josuttis at his Meeting C++ 2018 keynote
  {
    // i is an index
    for (auto i = std::size_t{0}, n{std::size(v)}; i != n; ++i) {
      std::cout << v[i] << '\n';
    }

    // Alternative:
    // https://twitter.com/JSMuellerRoemer/status/1064104488984813569
    for (auto n = std::size(v), i = 0 * n; i != n; ++i) {
      std::cout << v[i] << '\n';
    }

    // f and l are iterators
    for (auto f{std::cbegin(v)}, l{std::cbegin(v)}; f != l; ++f) {
      std::cout << *f << '\n';
    }

    // e is an element
    for (auto const& element : v) {
      std::cout << element << '\n';
    }
  }
}
