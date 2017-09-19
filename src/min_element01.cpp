// See: CodinGame demo interview question

#include <iostream>
#include <vector>
#include <algorithm> // std::min_element

int main()
{
    std::vector<double> v = {1.0, 2.0, 3.0};
    auto min_value = *std::min_element(std::begin(v), std::end(v));
    std::cout << "Minimal value: " << min_value << "\n";

    return 0;
}

