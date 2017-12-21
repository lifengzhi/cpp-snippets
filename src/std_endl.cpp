// CppCon 2017: Dietmar Kühl "The End of std::endl"
// https://www.youtube.com/watch?v=6WeEMlmrfOI

#include <iostream>

namespace std {
std::ostream &nl(std::ostream &out) { return out << '\n'; }
}  // namespace std

int main() {
  std::cout << "Hello world!" << std::nl << std::flush;
  std::cout << "Hello world!" << std::endl;
}
