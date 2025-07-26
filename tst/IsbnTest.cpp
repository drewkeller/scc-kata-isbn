#include "Isbn.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;
using namespace BookNumbers;

class Isbn13Test : public Test
{
public:
    Isbn Isbn;
};

TEST_F(Isbn13Test, GIVEN_ValidIsbn13WithoutFormatting_WHEN_CalculateCheckCharacter_THEN_ReturnsCorrectValue)
{
    EXPECT_THAT('9', Isbn.CalculateCheckCharacter(ISBN_13, "9780470059029"));
    EXPECT_THAT('0', Isbn.CalculateCheckCharacter(ISBN_13, "9780471486480"));
    EXPECT_THAT('5', Isbn.CalculateCheckCharacter(ISBN_13, "9780596809485"));
    EXPECT_THAT('0', Isbn.CalculateCheckCharacter(ISBN_13, "9780131495050"));
    EXPECT_THAT('9', Isbn.CalculateCheckCharacter(ISBN_13, "9780262134729"));
}

TEST_F(Isbn13Test, GIVEN_ValidIsbn13WithSpaces_WHEN_CalculateCheckCharacter_THEN_ReturnsCorrectValue)
{
    EXPECT_THAT('9', Isbn.CalculateCheckCharacter(ISBN_13, "978 0 470 05902 9"));
    EXPECT_THAT('0', Isbn.CalculateCheckCharacter(ISBN_13, "978 0 471 48648 0"));
    EXPECT_THAT('5', Isbn.CalculateCheckCharacter(ISBN_13, "978 0596809485"));
    EXPECT_THAT('0', Isbn.CalculateCheckCharacter(ISBN_13, "978 0 13 149505 0"));
    EXPECT_THAT('9', Isbn.CalculateCheckCharacter(ISBN_13, "978 0 262 13472 9"));
}

TEST_F(Isbn13Test, GIVEN_ValidIsbn13WithDashes_WHEN_CalculateCheckCharacter_THEN_ReturnsCorrectValue)
{
    EXPECT_THAT('9', Isbn.CalculateCheckCharacter(ISBN_13, "978-0-470-05902-9"));
    EXPECT_THAT('0', Isbn.CalculateCheckCharacter(ISBN_13, "978-0-471-48648-0"));
    EXPECT_THAT('5', Isbn.CalculateCheckCharacter(ISBN_13, "978-0596809485"));
    EXPECT_THAT('0', Isbn.CalculateCheckCharacter(ISBN_13, "978-0-13-149505-0"));
    EXPECT_THAT('9', Isbn.CalculateCheckCharacter(ISBN_13, "978-0-262-13472-9"));
}
