// https://arne-mertz.de/2018/09/make_shared-vs-the-normal-shared_ptr-constructor/

#include <cstddef>
#include <memory>

int main() {
  /*
  Comment from Helge Penne:
  There is a little known problem with make_shared: It will suppress warnings.
  The first of the following two lines will compile with no warning or error,
  while the second will fail as expected:
  */

  auto zero1 = std::make_shared<uint8_t>(256);
  // std::shared_ptr<uint8_t> zero2{new uint8_t{256}};

  // GCC8:
  // error: narrowing conversion of ‘256’ from ‘int’ to ‘uint8_t’ {aka ‘unsigned
  // char’} inside { } [-Wnarrowing]

  /*
  The problem is that the narrowing happens inside the STL, where all warnings
  are disabled. This can be a problem for security critical code, and one could
  argue that make_shared and its siblings should be prohibited there.
  */
}
