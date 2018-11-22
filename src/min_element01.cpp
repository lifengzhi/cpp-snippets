// See: CodinGame demo interview question

#include <algorithm>  // std::min_element
#include <iostream>
#include <vector>

int main() {
  std::vector<double> v{1.0, 2.0, 3.0};
  auto const min_value {*std::min_element(std::cbegin(v), std::cend(v))};
  std::cout << "Minimal value: " << min_value << "\n";

  return 0;
}
