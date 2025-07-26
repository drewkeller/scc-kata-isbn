#include "Isbn.h"

using namespace std;
using namespace BookNumbers;

// ISBN-10 is made up of 9 digits plus a check digit (which may be 'X').
// ISBN-13 is made up of 12 digits plus a check digit. 
// Spaces and hyphens may be included in a code, but are not significant. 
// This means that 9780471486480 is equivalent to 978-0-471-48648-0 and 978 0 471 48648 0.

// The check digit for ISBN-13 is calculated by: 
//   1. multiplying each digit alternately by 1 or 3 
//      (i.e., 1 x 1st digit, 3 x 2nd digit, 1 x 3rd digit, 3 x 4th digit, etc.)
//   2. summing these products together
//   3. taking modulo 10 of the result 
//   4. subtracting this value from 10 (use '0' if the result is 10)

// The check digit for ISBN-10 is calculated by:
//  1. multiplying each digit by its position 
//     (i.e., 1 x 1st digit, 2 x 2nd digit, etc.)
//  2. summing these products together 
//  3. taking modulo 11 of the result (with 'X' being used if the result is 10)

namespace BookNumbers {
    constexpr int MAX_LENGTH = 32;
}

Isbn::Isbn()
{

}

bool Isbn::Validate(const IsbnStandard standard, const string& input) 
{
    char actualCheckCharacter = GetCheckCharacter(input);
    char calculatedCheckCharacter = CalculateCheckCharacter(standard, input);
    return actualCheckCharacter != NULL_CHAR 
        && actualCheckCharacter == calculatedCheckCharacter;
}

char Isbn::CalculateCheckCharacter(const IsbnStandard standard, const std::string& input)
{
    constexpr int QTY_CHECK_DIGITS = 1;

    char checkCharacter = NULL_CHAR;
    int requiredQtyDigits = static_cast<int>(standard);
    int digitCount = 0;
    int sum = 0;
    const char* ptr = &input[0];
    int charCount = 0;

    while(IsValidCharacter(ptr) && digitCount < requiredQtyDigits - QTY_CHECK_DIGITS && charCount < MAX_LENGTH)
    {
        if(IsDigit(ptr))
        {
            digitCount++;

            int digitValue = *ptr - '0';
            int digitFactor = GetDigitFactor(standard, digitCount);
            int digitProduct = digitValue * digitFactor;
            sum += digitProduct;
        }
        
        ptr++;
        charCount++;
    }

    while(IsValidCharacter(ptr) && digitCount == requiredQtyDigits - QTY_CHECK_DIGITS && charCount < MAX_LENGTH)
    {
        if(IsValidCheckCharacter(ptr))
        {
            digitCount++;
            checkCharacter = CalculateCheckCharacterFromSum(standard, sum);
        }
        ptr++;
    }

    while(IsIgnorableCharacter(ptr) && charCount < MAX_LENGTH) {
        ptr++;
        charCount++;
    }

    // if we're not at the end of the string, it's not valid
    bool isValid = *ptr == '\0';

    return isValid ? checkCharacter : NULL_CHAR;
}

bool Isbn::IsDigit(const char* ptr) 
{    
    return *ptr >= '0' && *ptr <= '9';
}

bool Isbn::IsIgnorableCharacter(const char* ptr)
{
    return *ptr == ' ' || *ptr == '-';
}

bool Isbn::IsValidCharacter(const char* ptr) 
{    
    return *ptr == ' ' || *ptr == '-' || (*ptr >= '0' && *ptr <= '9');
}

bool Isbn::IsValidCheckCharacter(const char* ptr)
{
    return *ptr == 'X' || (*ptr >= '0' && *ptr <= '9');
}

int Isbn::GetDigitFactor(const IsbnStandard standard, int digitPosition)
{
    int factor = 0;
    if(standard == ISBN_10) {
        factor = digitPosition;
    } else {
        bool isOdd = digitPosition % 2 == 1;
        factor = isOdd ? 1 : 3;
    }
    return factor;
}

char Isbn::CalculateCheckCharacterFromSum(const IsbnStandard standard, int sum) {
    constexpr int MODULO_ISBN_13 = 10;
    constexpr int MODULO_ISBN_10 = 11;

    char checkDigitChar = '\0';
    int checkDigitValue = 0;
    if (standard == ISBN_10) {
        int moduloValue = sum % MODULO_ISBN_10;
        checkDigitChar = moduloValue == 10 ? 'X' : '0' + static_cast<char>(moduloValue);
    } else {
        int moduloValue = sum % MODULO_ISBN_13;
        int checkDigitValue = moduloValue == 0 ? 0 : 10 - moduloValue;
        checkDigitChar = '0' + static_cast<char>(checkDigitValue);
    }
    return checkDigitChar;
}

char Isbn::GetCheckCharacter(const string& isbnString) {
    char checkCharacter = NULL_CHAR;
    const char* ptr = &isbnString[0];
    int charCount = 0;

    // find the last valid check character in the string
    while (*ptr != NULL_CHAR && charCount < MAX_LENGTH)
    {
        if(IsValidCheckCharacter(ptr))
        {
            checkCharacter = *ptr;
        }
        ptr++;
        charCount++;
    }

    return checkCharacter;
}
