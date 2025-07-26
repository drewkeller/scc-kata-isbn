#include "Isbn.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;
using namespace testing;
using namespace BookNumbers;

typedef struct IsbnTestStruct {
    char CheckCharacter;
    std::string IsbnCode;
} IsbnTestStruct;

void PrintTo(const IsbnTestStruct& testItem, std::ostream* os) {
    *os << "ISBN: " << testItem.IsbnCode;
}

typedef initializer_list<IsbnTestStruct> IsbnTestCodesList;

class Isbn13Test : public Test
{
public:
    Isbn Isbn;
};

class IsbnCodesTest : public Isbn13Test, public testing::WithParamInterface<IsbnTestStruct> { };

IsbnTestCodesList ValidIsbn13CodesWithoutFormatting = {
    { '9', "9780470059029" },
    { '0', "9780471486480" },
    { '5', "9780596809485" },
    { '0', "9780131495050" },
    { '9', "9780262134729" },
};

IsbnTestCodesList ValidIsbn13TestValuesWithSpaces = {
    { '9', "978 0 470 05902 9"},
    { '0', "978 0 471 48648 0"},
    { '5', "978 0596809485" },
    { '0', "978 0 13 149505 0"},
    { '9', "978 0 262 13472 9"},
};

IsbnTestCodesList ValidIsbn13TestValuesWithDashes = {
    { '9', "978-0-470-05902-9"},
    { '0', "978-0-471-48648-0"},
    { '5', "978-0596809485" },
    { '0', "978-0-13-149505-0"},
    { '9', "978-0-262-13472-9"},
};

INSTANTIATE_TEST_SUITE_P(ValidIsbn13CodesWithoutFormattingTest, IsbnCodesTest, ValuesIn(ValidIsbn13CodesWithoutFormatting));
INSTANTIATE_TEST_SUITE_P(ValidIsbn13CodesWithSpacesTest, IsbnCodesTest, ValuesIn(ValidIsbn13TestValuesWithSpaces));
INSTANTIATE_TEST_SUITE_P(ValidIsbn13CodesWithDashesTest, IsbnCodesTest, ValuesIn(ValidIsbn13TestValuesWithDashes));

TEST_P(IsbnCodesTest, GIVEN_ValidIsbn_WHEN_CalculateCheckCharacter_THEN_ReturnsCorrectValue)
{
    char checkCharacter = GetParam().CheckCharacter;
    string isbnCode = GetParam().IsbnCode;
    EXPECT_THAT(checkCharacter, Isbn.CalculateCheckCharacter(ISBN_13, isbnCode));
}

TEST_P(IsbnCodesTest, GIVEN_ValidIsbnCode_WHEN_Validated_THEN_ReturnTrue)
{
    string isbnCode = GetParam().IsbnCode;
    EXPECT_THAT(true, Isbn.Validate(ISBN_13, isbnCode));
}
