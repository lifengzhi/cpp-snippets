/*
edX->UBCx: How to Code: Complex Data->The Career Development Series->
Technical Interview->The Question: Given a list of numbers and an integer k,
write a function that returns the kth largest element of the list.
*/

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <numeric>
#include <optional>
#include <vector>

template <typename Container, typename T = typename std::remove_cv_t<
                                  std::remove_reference_t<Container>>>
std::optional<typename T::value_type> kth_largest(T container,
                                                  typename T::size_type k) {
  if ((std::size(container) == 0) || (k > std::size(container) - 1))
    return std::nullopt;
  std::sort(std::begin(container), std::end(container),
            std::greater<typename T::value_type>());
  return container[k];
}

template <typename Container>
void check_kth_largest(Container const& container,
                       typename Container::size_type k) {
  if (auto res = kth_largest<Container>(container, k)) {
    std::cout << *res << '\n';
  } else {
    std::cout << "No kth element\n";
  }
}

int main() {
  std::vector<int> vec(10);
  std::iota(std::begin(vec), std::end(vec), 0);

  check_kth_largest(vec, 3);
  check_kth_largest(vec, 10);
  check_kth_largest(vec, -1);

  std::array<int, 10> arr;
  std::iota(std::begin(arr), std::end(arr), 0);

  check_kth_largest(arr, 3);
  check_kth_largest(arr, 10);
  check_kth_largest(arr, -1);

  return 0;
}