#include "slu/testing.hpp"

int main() {
  auto tests = std::initializer_list<slu::testing::test>{};
  auto f     = slu::testing::framework{tests};
}