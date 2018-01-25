// https://www.fluentcpp.com/2017/12/12/mixin-classes-yang-crtp/
// See: Template Normal Programming, Part 2 - Arthur O'Dwyer - CppCon 2016

#include <iostream>
#include <string>

// Goal => to add a generic functionality to a class

// Mixin class

// 1 - leaves the original class unchanged.
// 2 - client code doesn’t use the original class directly, it needs to wrap it
// into the mixin to use the augmented functionality.
// 3 - inherits from a the original class even if it doesn’t have a virtual
// destructor. This is ok unless the mixin class is deleted polymorphically
// through a pointer to the original class.
// 4 - copies the original instance and so has no possibility to modify the
// original.

template <typename Printable>
struct RepeatPrintMixin : Printable {
  explicit RepeatPrintMixin(Printable const& printable)
      : Printable(printable) {}
  void times(unsigned int n) const {
    while (n-- > 0) {
      this->print();
    }
  }
};

template <typename Printable>
RepeatPrintMixin<Printable> repeatedlyPrint(Printable const& printable) {
  return RepeatPrintMixin<Printable>(printable);
}

class NameMixin {
 public:
  NameMixin(std::string firstName, std::string lastName)
      : firstName_(std::move(firstName)), lastName_(std::move(lastName)) {}

  void print() const { std::cout << lastName_ << ", " << firstName_ << '\n'; }

 private:
  std::string firstName_;
  std::string lastName_;
};

// CRTP

// 1 - impacts the definition of the existing class, because it has to inherit
// from the CRTP
// 2 - client code uses the original class directly and benefits
// from its augmented functionalities.

template <typename Printable>
struct RepeatPrint {
  void repeat(unsigned int n) const {
    while (n-- > 0) {
      static_cast<Printable const&>(*this).print();
    }
  }
};

class NameCRTP : public RepeatPrint<NameCRTP> {
 public:
  NameCRTP(std::string firstName, std::string lastName)
      : firstName_(std::move(firstName)), lastName_(std::move(lastName)) {}

  void print() const { std::cout << lastName_ << ", " << firstName_ << '\n'; }

 private:
  std::string firstName_;
  std::string lastName_;
};

int main() {
  // Mixin class
  NameMixin nedMixin("Eddard", "Stark");
  repeatedlyPrint(nedMixin).times(10);

  // CRTP
  NameCRTP nedCRTP("Eddard", "Stark");
  nedCRTP.repeat(10);
}
