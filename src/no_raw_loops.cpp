// https://www.youtube.com/watch?v=IzNtM038JuI

// https://blogs.msdn.microsoft.com/vcblog/2018/04/09/msvc-now-correctly-reports-__cplusplus/

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

// I models RandomAccessIterator
template <typename I>
auto slide(I first, I last, I position) -> std::pair<I, I> {
  if (position < first) return {position, std::rotate(position, first, last)};
  if (last < position) return {std::rotate(first, last, position), position};
  return {first, last};
}

// I models BidirectionalIterator
// S models UnaryPredicate

#if __cplusplus == 201703L
// C++17 negator: std::not_fn needs a callable object
template <typename I, typename P>
auto gather(I first, I last, I position, P predicate) -> std::pair<I, I> {
  return {std::stable_partition(first, position, std::not_fn(predicate)),
          std::stable_partition(position, last, predicate)};
}
#else
// C++03 negator: std::not1 needs a std::unary_function
template <typename I, typename P>
auto gather(I first, I last, I position, P predicate) -> std::pair<I, I> {
  return {std::stable_partition(first, position, std::not1(predicate)),
          std::stable_partition(position, last, predicate)};
}

struct is_odd : std::unary_function<int, bool> {
  bool operator()(int i) const { return i % 2 ? true : false; }
};

#endif

int main() {
  std::vector<int> vec(10);
  std::iota(std::begin(vec), std::end(vec), 0);

  for (auto const& value : vec) {
    std::cout << value << '\n';
  }

  auto slided =
      slide(std::begin(vec) + 2, std::begin(vec) + 4, std::end(vec) - 1);

  for (auto i = slided.first; i != slided.second; ++i) {
    std::cout << "slided: " << *i << '\n';
  }

  for (auto const& value : vec) {
    std::cout << value << '\n';
  }

#if __cplusplus == 201703L
  auto gathered17 = gather(std::begin(vec), std::end(vec), std::end(vec),
                           [](int i) { return i % 2 ? true : false; });

  for (auto i = gathered17.first; i != gathered17.second; ++i) {
    std::cout << "gathered: " << *i << '\n';
  }
#else
  auto gathered03 =
      gather(std::begin(vec), std::end(vec), std::end(vec), is_odd());

  for (auto i = gathered03.first; i != gathered03.second; ++i) {
    std::cout << "gathered: " << *i << '\n';
  }

  auto gathered11 = gather(
      std::begin(vec), std::end(vec), std::end(vec),
      std::function<bool(int)>([](int i) { return i % 2 ? true : false; }));

  for (auto i = gathered11.first; i != gathered11.second; ++i) {
    std::cout << "gathered: " << *i << '\n';
  }
#endif

  for (auto const& value : vec) {
    std::cout << value << '\n';
  }
}
