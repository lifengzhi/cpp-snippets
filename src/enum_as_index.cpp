// See: https://joshpeterson.github.io/using-span-with-argv

#include <gsl/multi_span>
#include <iostream>

namespace command {
namespace line {
enum parameter_position { PARAM1 = 1, PARAM2 = 2, PARAM3 = 3 };
const auto NUMBER_OF_PARAMS{3};
}  // namespace line
}  // namespace command

int main(int argc, char *argv[]) {
  if (argc != command::line::NUMBER_OF_PARAMS + 1) {
    return -1;
  }

  for (int i = 1; i <= command::line::NUMBER_OF_PARAMS; ++i) {
    std::cout << "Parameter " << i << ": " << argv[i] << '\n';
  }

  auto args = gsl::multi_span<char *>(argv, argc);

  for (int i = 1; i <= command::line::NUMBER_OF_PARAMS; ++i) {
    std::cout << "Parameter " << i << ": " << args[i] << '\n';
  }

  for (int i = 1; i <= command::line::NUMBER_OF_PARAMS; ++i) {
    std::cout << "Parameter " << i << ": " << gsl::at(args, i) << '\n';
  }
}