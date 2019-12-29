#include <stdexcept>

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "ceo_broj.h"

// Ako neki izraz treba da bude jednak vrednosti true,
// koristimo makroe CHECK i REQUIRE.
// Razlika izmedju ova dva makroa je u tome sto:
//   - CHECK ne prekida testiranje ostalih provera u jednom testu
//   - REQUIRE prekida testiranje ostalih provera u jednom testu
TEST_CASE("When two integers are created using the same values Then they need to be equal", "[equality]")
{
    // Testove u jednom skupu mozemo podeliti u sekcije
    SECTION("Base-10 tests")
    {
        // Arrange
        const auto value = 1000;
        const auto base = 10;

        // Act
        ceo_broj num1(value, base);
        ceo_broj num2(value, base);

        // Assert
        REQUIRE(num1 == num2);
    }

    SECTION("Base-16 tests")
    {
        // Arrange
        const auto value = 1000;
        const auto base = 16;

        // Act
        ceo_broj num1(value, base);
        ceo_broj num2(value, base);

        // Assert
        REQUIRE(num1 == num2);
    }
}

// Ako neki izraz treba da bude jednak vrednosti false,
// koristimo makroe CHECK_FALSE i REQUIRE_FALSE.
// Razlika je kao kod CHECK i REQUIRE.
TEST_CASE("When two integers are created using the different values Then they need to be different", "[inequality]")
{
    SECTION("Base-10 tests")
    {
        // Arrange
        const auto value1 = 42;
        const auto value2 = 0;
        const auto base = 10;

        // Act
        ceo_broj num1(value1, base);
        ceo_broj num2(value2, base);

        // Assert
        CHECK_FALSE(value1 == value2);
        REQUIRE_FALSE(num1 == num2);
    }

    SECTION("Base-16 tests")
    {
        // Arrange
        const auto value1 = 42;
        const auto value2 = 0;
        const auto base = 16;

        // Act
        ceo_broj num1(value1, base);
        ceo_broj num2(value2, base);

        // Assert
        CHECK_FALSE(value1 == value2);
        REQUIRE_FALSE(num1 == num2);
    }
}

// Ako neki izraz treba da izbaci izuzetak,
// koristimo makro REQUIRE_THROWS
TEST_CASE("When base is too large Then construction will throw", "[constructor]")
{
    REQUIRE_THROWS(ceo_broj(0, 1000));
}

// Ako neki izraz treba da izbaci izuzetak odgovarajuceg tipa,
// koristimo makro REQUIRE_THROWS_AS
TEST_CASE("When base is too large Then construction will throw std::invalid_argument", "[constructor]")
{
    REQUIRE_THROWS_AS(ceo_broj(0, 1000), std::invalid_argument);
}