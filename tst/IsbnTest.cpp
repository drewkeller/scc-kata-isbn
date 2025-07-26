#include "Isbn.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;
using namespace testing;
using namespace BookNumbers;

typedef struct IsbnTestStruct {
    IsbnStandard Standard;
    bool IsValid;
    char CheckCharacter;
    std::string IsbnCode;
} IsbnTestStruct;

void PrintTo(const IsbnTestStruct& testItem, std::ostream* os) {
    *os << "ISBN: \"" << testItem.IsbnCode << "\"";
}

typedef initializer_list<IsbnTestStruct> IsbnTestCodesList;

class Isbn13Test : public Test
{
public:
    Isbn Isbn;
};

class IsbnCodesTest : public Isbn13Test, public testing::WithParamInterface<IsbnTestStruct> { };

IsbnTestCodesList ValidIsbn13CodesWithoutFormatting = {
    { ISBN_13, true, '9', "9780470059029" },
    { ISBN_13, true, '0', "9780471486480" },
    { ISBN_13, true, '5', "9780596809485" },
    { ISBN_13, true, '0', "9780131495050" },
    { ISBN_13, true, '9', "9780262134729" },
};

IsbnTestCodesList InvalidIsbn13Codes = {
    { ISBN_13, false, '-', "0000470059029" },
    { ISBN_13, false, '-', "HelloWorld" },
    { ISBN_13, false, '-', "978+0+470+05902+9"},
    { ISBN_13, false, '-', "9780470059029                     "},
    { ISBN_13, false, '-', "9780470059029999999999999999999999"},
};

IsbnTestCodesList ValidIsbn13TestValuesWithSpaces = {
    { ISBN_13, true, '9', "978 0 470 05902 9"},
    { ISBN_13, true, '0', "978 0 471 48648 0"},
    { ISBN_13, true, '5', "978 0596809485" },
    { ISBN_13, true, '0', "978 0 13 149505 0"},
    { ISBN_13, true, '9', "978 0 262 13472 9 "},
};

IsbnTestCodesList ValidIsbn13TestValuesWithDashes = {
    { ISBN_13, true, '9', "978-0-470-05902-9"},
    { ISBN_13, true, '0', "978-0-471-48648-0"},
    { ISBN_13, true, '5', "978-0596809485" },
    { ISBN_13, true, '0', "978-0-13-149505-0"},
    { ISBN_13, true, '9', "978-0-262-13472-9"},
};

IsbnTestCodesList ValidIsbn10Codes = {
    { ISBN_10, true, '7', "0471958697" },
    { ISBN_10, true, '2', "0 471 60695 2" },
    { ISBN_10, true, '2', "0-470-84525-2" },
    { ISBN_10, true, '0', "0-321-14653-0" },
};

INSTANTIATE_TEST_SUITE_P(ValidIsbn13CodesWithoutFormattingTest, IsbnCodesTest, ValuesIn(ValidIsbn13CodesWithoutFormatting));
INSTANTIATE_TEST_SUITE_P(InvalidIsbn13CodesTest, IsbnCodesTest, ValuesIn(InvalidIsbn13Codes));
INSTANTIATE_TEST_SUITE_P(ValidIsbn13CodesWithSpacesTest, IsbnCodesTest, ValuesIn(ValidIsbn13TestValuesWithSpaces));
INSTANTIATE_TEST_SUITE_P(ValidIsbn13CodesWithDashesTest, IsbnCodesTest, ValuesIn(ValidIsbn13TestValuesWithDashes));
INSTANTIATE_TEST_SUITE_P(ValidIsbn10CodesTest, IsbnCodesTest, ValuesIn(ValidIsbn10Codes));

TEST_P(IsbnCodesTest, GIVEN_ValidIsbn_WHEN_CalculateCheckCharacter_THEN_ReturnsCorrectValue)
{
    IsbnStandard standard = GetParam().Standard;
    char checkCharacter = GetParam().CheckCharacter;
    string isbnCode = GetParam().IsbnCode;
    if(GetParam().IsValid)
    {
        EXPECT_THAT(checkCharacter, Isbn.CalculateCheckCharacter(standard, isbnCode));
    } else {
        EXPECT_THAT(checkCharacter, Ne(Isbn.CalculateCheckCharacter(standard, isbnCode)));
    }
}

TEST_P(IsbnCodesTest, GIVEN_ValidIsbnCode_WHEN_Validated_THEN_ReturnTrue)
{
    IsbnStandard standard = GetParam().Standard;
    string isbnCode = GetParam().IsbnCode;
    if(GetParam().IsValid)
    {
        EXPECT_THAT(true, Isbn.Validate(standard, isbnCode));
    } else {
        EXPECT_THAT(false, Isbn.Validate(standard, isbnCode));
    }
}
