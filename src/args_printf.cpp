#include <cstdio>

int main(int argc, char *argv[]) {
  for (int i = 0; i < argc; ++i) {
    std::printf("%s\n", argv[i]);
  }
}
