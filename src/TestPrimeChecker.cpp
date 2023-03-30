#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "PrimeChecker.hpp"

TEST_CASE("Test Primechecker 1.") {
    PrimeChecker pc;
    REQUIRE(pc.isPrime(5));
}

TEST_CASE("Test PrimeChecker 2.") {
    PrimeChecker pc;
    REQUIRE_FALSE(pc.isPrime(1)); 
}

TEST_CASE("Test PrimeChecker 3.") {
    PrimeChecker pc;
    REQUIRE_FALSE(pc.isPrime(3)); 
}

TEST_CASE("Test PrimeChecker 4.") {
    PrimeChecker pc;
    REQUIRE_FALSE(pc.isPrime(-5)); 
}

TEST_CASE("Test PrimeChecker 5.") {
    PrimeChecker pc;
    REQUIRE_FALSE(pc.isPrime(0)); 
}
