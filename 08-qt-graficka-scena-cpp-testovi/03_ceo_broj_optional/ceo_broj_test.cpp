#include <stdexcept>

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "ceo_broj.h"

TEST_CASE("When base is too large Then construction will throw", "[constructor]")
{
    REQUIRE_THROWS(ceo_broj(0, 1000));
}

TEST_CASE("When base is too large Then construction will throw std::invalid_argument", "[constructor]")
{
    REQUIRE_THROWS_AS(ceo_broj(0, 1000), std::invalid_argument);
}

TEST_CASE("When two integers are created using the same values Then they need to be equal", "[equality]")
{
    SECTION("Base-10 tests")
    {
        CHECK(ceo_broj(1000, 10) == ceo_broj(1000, 10));
        CHECK(ceo_broj(0, 10) == ceo_broj(0, 10));
        REQUIRE_FALSE(ceo_broj(1, 10) == ceo_broj(0, 10));
    }

    SECTION("Base-16 tests")
    {
        CHECK(ceo_broj(1000, 16) == ceo_broj(1000, 16));
        CHECK(ceo_broj(0, 16) == ceo_broj(0, 16));
        REQUIRE_FALSE(ceo_broj(1, 16) == ceo_broj(0, 16));
    }
}

TEST_CASE("Should succeed When converted from valid string and base", "[conversion]")
{
    CHECK(ceo_broj::iz_niske("1000"));
    REQUIRE(ceo_broj::iz_niske("ABCD", 16));
}

TEST_CASE("Should fail When converted from non-valid base", "[conversion]")
{
    REQUIRE_FALSE(ceo_broj::iz_niske("ABCD"));
}

