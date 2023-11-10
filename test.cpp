#include <iostream>

int main() {
  int merda = 0;
  int cacca = 100;
  for (int i = 0; i < 100; ++i) {
    ++merda;
  }
  for (int i = 0; i < merda; ++i) {
    ++cacca;
  }
  
  std::cout << cacca << std::endl;
}