#include "Utils.hpp"

std::string generate_random_digits_string(size_t len) {
  std::string generated_string;
  generated_string.erase(begin(generated_string), end(generated_string));
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<int> distribution(0, 9);

  for (size_t i = 0; i < len; ++i) {
    generated_string += std::to_string(distribution(generator));
  }
  
  return generated_string;
}
