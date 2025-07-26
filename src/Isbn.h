#pragma once

#include <string>

namespace BookNumbers {

    constexpr char NULL_CHAR  = '\0';

    typedef enum IsbnStandard {
        ISBN_10 = 10, 
        ISBN_13 = 13
    } IsbnStandard;

    class Isbn {
    public:
        std::string Input;
        std::string Identifier; // unformatted ID

        Isbn();
        bool Validate(const IsbnStandard, const std::string& input);
        char CalculateCheckCharacter(const IsbnStandard standard, const std::string& input);

        bool IsDigit(const char* ptr);
        bool IsValidCharacter(const char* ptr);
        bool IsValidCheckCharacter(const char* ptr);
        int GetDigitFactor(const IsbnStandard standard, int digitPosition);
        char CalculateCheckCharacterFromSum(const IsbnStandard standard, int sum);
        char GetCheckCharacter(const std::string& isbnString);
    };
}
