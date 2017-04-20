#include "library.h"
#include "catch.hpp"

SCENARIO("I want to foo") {
    GIVEN("some number") {
        int a = 14;
        WHEN("I foo that number") {
            int result = foo(a);
            THEN("my number is still the same.") {
                REQUIRE(result == a);
            }
        }
    }
}

SCENARIO("I want to bar") {
    GIVEN("two numbers") {
        int a = 4;
        int b = 98123;
        WHEN("I bar them") {
            int result = bar(a,b);
            THEN("I get the better number") {
                REQUIRE(result == b);
            }
        }
    }
}

SCENARIO("I want to know a nice number"){
    GIVEN("boredom") {
        WHEN("I get the number"){
            int number = baz();
            THEN("It's the bestest number") {
                REQUIRE(number == 1);
            }
        }
    }
}