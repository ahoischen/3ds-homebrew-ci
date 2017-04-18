#include "catch.hpp"

SCENARIO("Math works", "") {
    GIVEN("Two ints") {
        int a = 5;
        int b = 10;

        WHEN("Both are added"){
            int c = a + b;

            THEN("The result is correct"){
                REQUIRE(c == 15);
            }
        }

        WHEN("I want a failure"){
            THEN("I test if 1 = 0"){
                REQUIRE(1 == 0);
            }
        }
    }
}