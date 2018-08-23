// https://rob.conery.io/2018/08/21/mod-and-remainder-are-not-the-same/

#include <cstdlib>
#include <iostream>

int main() {
  {
    auto c{19};
    auto d{12};
    std::cout << c << " = " << c / d << " * " << d << " + " << c % d << '\n';

    auto res = std::div(c, d);
    std::cout << c << " = " << res.quot << " * " << d << " + " << res.rem
              << '\n';
  }

  {
    auto c{19};
    auto d{-12};
    std::cout << c << " = " << c / d << " * " << d << " + " << c % d << '\n';

    auto res = std::div(c, d);
    std::cout << c << " = " << res.quot << " * " << d << " + " << res.rem
              << '\n';
  }

  {
    auto c{-19};
    auto d{12};
    std::cout << c << " = " << c / d << " * " << d << " + " << c % d << '\n';

    auto res = std::div(c, d);
    std::cout << c << " = " << res.quot << " * " << d << " + " << res.rem
              << '\n';
  }
}