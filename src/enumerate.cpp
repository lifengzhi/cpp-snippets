// http://reedbeta.com/blog/python-like-enumerate-in-cpp17/
// https://wandbox.org/permlink/T5xVd3Vll5on02aK

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

template <typename T, typename TIter = decltype(std::begin(std::declval<T>())),
          typename = decltype(std::end(std::declval<T>()))>
constexpr auto enumerate(T&& iterable) {
  struct iterator {
    std::size_t i;
    TIter iter;
    bool operator!=(const iterator& other) const { return iter != other.iter; }
    void operator++() {
      ++i;
      ++iter;
    }
    auto operator*() const { return std::tie(i, *iter); }
  };
  struct iterable_wrapper {
    T iterable;
    auto begin() { return iterator{0, std::begin(iterable)}; }
    auto end() { return iterator{0, std::end(iterable)}; }
  };
  return iterable_wrapper{std::forward<T>(iterable)};
}

int main() {
  const auto things =
      std::vector<std::string>{"once", "deuce", "thrice", "quart"};

  for (auto [i, thing] : enumerate(things)) {
    std::cout << i << ": " << thing << '\n';
  }
}