// https://stackoverflow.com/q/8147027/496459
// https://stackoverflow.com/a/25069711/496459

#include <memory>

class A {
 public:
  static std::unique_ptr<A> create() {
    struct make_unique_enabler : public A {};
    return std::make_unique<make_unique_enabler>();
  }

 private:
  A(){};
};

int main() {
  auto const my_unique_ptr_to_A{A::create()};
  return 0;
}
