//
// Created by Aleardo on 02/08/22.
//

#include "test_coverage.h"
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()
#include "../third_party/catch.hpp"       // only do this in one cpp file

unsigned Factorial(unsigned number) {
  return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed", "[Factorial]") {
  REQUIRE(Factorial(1) == 1);
  REQUIRE(Factorial(2) == 2);
  REQUIRE(Factorial(3) == 6);
  REQUIRE(Factorial(10) == 3628800);
}