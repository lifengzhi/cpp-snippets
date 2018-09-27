// https://herbsutter.com/2018/09/20/lifetime-profile-v1-0-posted/
// Roland Bock: The current analysis yields a false positive (uninitialized
// reference e), but does not find the actual issue (dangling reference msg).

#include <iostream>
#include <string>

struct MyException {
  const std::string& msg;

  explicit MyException(const std::string& s) : msg(s) {}
};

int main(int argc, char** argv) {
  for (int i = 0; i < argc; ++i) {
    try {
      throw MyException(argv[i]);
    } catch (const MyException& e) {
      std::cerr << e.msg << std::endl;
    }
  }
}
