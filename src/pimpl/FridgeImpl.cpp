#include "Engine.h"
#include "Fridge.h"

#include <memory>

class Fridge::FridgeImpl {
 public:
  void coolDown() {}

 private:
  Engine engine_;
};

Fridge::Fridge() : impl_(std::make_unique<FridgeImpl>()) {}
Fridge::~Fridge() = default;

void Fridge::coolDown() { impl_->coolDown(); }
