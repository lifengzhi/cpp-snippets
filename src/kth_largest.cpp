/*
edX->UBCx: How to Code: Complex Data->The Career Development Series->
Technical Interview->The Question: Given a list of numbers and an integer k,
write a function that returns the kth largest element of the list.
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <optional>
#include <vector>

template <typename T>
std::optional<T> kth_largest(std::vector<T> vec,
                             typename std::vector<T>::size_type k) {
  if ((vec.size() == 0) || (k > vec.size() - 1)) return std::nullopt;
  std::sort(std::begin(vec), std::end(vec), std::greater<T>());
  return vec[k];
}

template <typename T>
void check_kth_largest(std::vector<T> const& vec,
                       typename std::vector<T>::size_type k) {
  if (auto res = kth_largest<T>(vec, k)) {
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

  return 0;
}