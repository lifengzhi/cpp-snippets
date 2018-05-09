// See: Kate Gregory's Pluralsight C++ Fundamentals - Part 2

#include <iostream>
#include <vector>
#define UNUSED(x) (void)(x)

// throw by value catch by const reference

int main() {
  std::vector<int> v = {1};

  // catch exceptions by reference
  // great for catching a derived exception, see exception hierarchy

  try {
    int const j = v.at(99);
    UNUSED(j);
  } catch (std::out_of_range &e) {
    // first block that catches the exception is called
    // other catch block are skipped
    std::cout << "" << e.what() << '\n';
  } catch (std::exception &e) {
    std::cout << "other: " << e.what() << '\n';
  }
}
