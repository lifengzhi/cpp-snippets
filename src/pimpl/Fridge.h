#pragma once

#include <memory>

class Fridge {
 public:
  Fridge();
  ~Fridge();
  void coolDown();

 private:
  class FridgeImpl;
  std::unique_ptr<FridgeImpl> impl_;
};
