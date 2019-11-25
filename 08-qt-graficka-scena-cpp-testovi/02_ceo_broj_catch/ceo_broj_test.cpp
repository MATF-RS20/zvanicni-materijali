#include <stdexcept>

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "ceo_broj.h"

TEST_CASE("When base is too large Then construction will throw", "[constructor]")
{
    // Ako neki izraz treba da izbaci izuzetak
    REQUIRE_THROWS(ceo_broj(0, 1000));
}

TEST_CASE("When base is too large Then construction will throw std::invalid_argument", "[constructor]")
{
    // Ako neki izraz treba da izbaci izuzetak odgovarajuceg tipa
    REQUIRE_THROWS_AS(ceo_broj(0, 1000), std::invalid_argument);
}

TEST_CASE("When two integers are created using the same values Then they need to be equal", "[equality]")
{
    // Testove u jednom skupu mozemo podeliti u sekcije
    SECTION("Base-10 tests")
    {
        // Ako neki izraz treba da bude jednak vrednosti true.
        // Razlika izmedju ova dva makroa je u tome sto:
        //   - CHECK ne prekida testiranje ostalih provera
        //   - REQUIRE prekida testiranje ostalih provera
        CHECK(ceo_broj(1000, 10) == ceo_broj(1000, 10));
        CHECK(ceo_broj(0, 10) == ceo_broj(0, 10));
        // Ako neki izraz treba da bude jednak vrednosti false
        REQUIRE_FALSE(ceo_broj(1, 10) == ceo_broj(0, 10));
    }

    SECTION("Base-16 tests")
    {
        CHECK(ceo_broj(1000, 16) == ceo_broj(1000, 16));
        CHECK(ceo_broj(0, 16) == ceo_broj(0, 16));
        REQUIRE_FALSE(ceo_broj(1, 16) == ceo_broj(0, 16));
    }
}

