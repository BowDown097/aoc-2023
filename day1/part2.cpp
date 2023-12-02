#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>

std::map<std::string, unsigned> wordNumberMap = {
    { "one", 1 },
    { "two", 2 },
    { "three", 3 },
    { "four", 4 },
    { "five", 5 },
    { "six", 6 },
    { "seven", 7 },
    { "eight", 8 },
    { "nine", 9 }
};

int main()
{
    std::ifstream in("input.txt");
    unsigned total = 0;

    for (std::string line; std::getline(in, line);)
    {
        size_t sz = line.size();
        size_t firstDigitIndex = SIZE_MAX, firstWordIndex = SIZE_MAX;
        ptrdiff_t lastDigitIndex = PTRDIFF_MIN, lastWordIndex = PTRDIFF_MIN;

        for (size_t i = 0; i < sz; i++)
        {
            if (isdigit(line[i]))
            {
                firstDigitIndex = i;
                break;
            }
        }

        for (size_t i = sz - 1; i >= 0; i--)
        {
            if (isdigit(line[i]))
            {
                lastDigitIndex = i;
                break;
            }
        }

        char firstWord, lastWord;

        for (const auto& [word, num] : wordNumberMap)
        {
            if (size_t f = line.find(word); f != std::string::npos && f < firstWordIndex)
            {
                firstWordIndex = f;
                firstWord = num + '0';
            }

            if (ptrdiff_t rf = line.rfind(word); rf != std::string::npos && rf > lastWordIndex)
            {
                lastWordIndex = rf;
                lastWord = num + '0';
            }
        }

        char comb[2] = {
            firstDigitIndex < firstWordIndex ? line[firstDigitIndex] : firstWord,
            lastDigitIndex > lastWordIndex ? line[lastDigitIndex] : lastWord
        };

        total += atoi(comb);
    }

    std::cout << total << std::endl;
}
