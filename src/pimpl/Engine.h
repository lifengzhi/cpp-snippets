#pragma once

#include <iostream>

struct Engine {
  Engine() { std::cout << __FUNCTION__ << '\n'; };
  ~Engine() { std::cout << __FUNCTION__ << '\n'; };
};
