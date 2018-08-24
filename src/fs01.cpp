#include <filesystem>
#include <iostream>

int main() {
  namespace fs = std::filesystem;

  for (auto const& entry :
       fs::recursive_directory_iterator{fs::current_path()}) {
    if (fs::is_regular_file(entry)) {
      std::cout << entry << '\n';
    }
  }
}