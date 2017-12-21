// g++ -o span01 -Wall -Wextra -pedantic -std=c++14 -I GSL/include span01.cpp
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include <gsl/span>

// See e.g.
// http://codexpert.ro/blog/2016/03/07/guidelines-support-library-review-spant/
template <typename T>
void write_data_pass_by_const_ref(gsl::span<T> const &s,
                                  std::string const &filename) {
  std::ofstream file(filename);
  std::copy(std::begin(s), std::end(s), std::ostream_iterator<T>(file, "\n"));
}

// See e.g. https://github.com/Microsoft/GSL/issues/380#issuecomment-250842034
template <typename T>
void write_data_pass_by_value(gsl::span<T> const s,
                              std::string const &filename) {
  std::ofstream file(filename);
  std::copy(std::begin(s), std::end(s), std::ostream_iterator<T>(file, "\n"));
}

// After reading Rainer Grimm's articles:
// https://www.heise.de/developer/artikel/C-Core-Guidelines-The-Guideline-Support-Library-3780760.html
// https://www.heise.de/developer/artikel/C-Core-Guidelines-Die-Regeln-fuer-In-Out-In-out-Consume-und-Forward-Funktionsparameter-3793753.html

template <typename T>
void write_data_gsl(gsl::span<const T> s, std::string const &filename) {
  std::ofstream file(filename);
  std::copy(std::begin(s), std::end(s), std::ostream_iterator<T>(file, "\n"));
}

int main() {
  const std::vector<int> v{1, 2, 3, 4, 5};
  write_data_pass_by_const_ref(gsl::make_span(v), "vector_const_ref.txt");
  write_data_pass_by_value(gsl::make_span(v), "vector_value.txt");

  write_data_gsl(gsl::make_span(v), "vector_gsl.txt");
}
