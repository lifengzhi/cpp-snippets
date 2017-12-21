// See:
// http://articles.emptycrate.com/2008/10/31/why_is_i_faster_than_i_in_c.html
// https://stackoverflow.com/questions/24886/is-there-a-performance-difference-between-i-and-i-in-c
//
// On a side note, it’s rare that you literally want to increment and return the
// old value, so ++i is often more semantically correct than i++, besides being
// more efficient.

#include <iostream>

class integer {
 public:
  explicit integer(int t_value) : m_value(t_value) {}

  int get_value() const { return m_value; }

  // pre increment operator
  integer &operator++() {
    ++m_value;
    return *this;
  }

  // post increment operator
  integer operator++(int) {
    // a copy is made, it's cheap, but it's still a copy
    integer old = *this;
    ++m_value;
    // Return old copy
    return old;
  }

  friend std::ostream &operator<<(std::ostream &os, const integer &i);

 private:
  int m_value;
};

std::ostream &operator<<(std::ostream &os, const integer &i) {
  os << i.m_value;
  return os;
}

int main() {
  integer i{0};
  std::cout << "Without operator<< overloading: " << (++i).get_value() << '\n';
  std::cout << "With operator<< overloading: " << i << '\n';
}
