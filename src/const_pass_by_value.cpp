// See: https://stackoverflow.com/a/8714335/496459
// See: https://stackoverflow.com/q/117293/496459
// See: http://www.gotw.ca/gotw/006.htm
// See:
// https://groups.google.com/forum/#!topic/comp.lang.c++.moderated/DEQTho8OCj8

// Herb Sutter's point of view on this topic:
// >2. Self documentation. This tells the maintainer that the function is
// >   implemented in a way that does not change it's actual argument.
//
// Here, both pt and i are copied anyway...
// whether they're declared const or not doesn't affect the caller at all.
//
// It never will, since the function always uses only a copy of the actual
// argument.  That's why there's no benefit to declaring the parameter as const.

#include <iostream>

int f(int x) {
  x = 1;
  return x + 1;
}

// Passing argument by value with const qualifier prevent this kind of issue:
// it constraints the implementation
int g(const int x) { return x + 1; }

int main() {
  std::cout << f(0) << '\n';
  std::cout << g(0) << '\n';

  return 0;
}
