#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream file("data.txt");
    std::string line;
    // See: https://stackoverflow.com/q/7219062/496459
    // std::getline has no buffer-size limitation, per the standard.
    while(std::getline(file, line))
    {
        std::cout << line << '\n';
    }

    return 0;
}

