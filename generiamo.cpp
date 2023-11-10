#include <iostream>

int main() {
int b;
  for (int i; i < 10; ++i) {
    b = 0;
    for (int j = 0; j < 100; ++j) {
      ++b;
    }
    std::cout << b << std::endl;
  }
}