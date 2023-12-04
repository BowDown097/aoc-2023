#include <cstring>
#include <fstream>
#include <iostream>

#define SCHEMATIC_DIM 140
char schematic[SCHEMATIC_DIM][SCHEMATIC_DIM];

bool isSymbol(char c)
{
    return c != '.' && !isdigit(c);
}

bool rangeContainsSymbol(unsigned row, int start, int end)
{
    if (start < 0)
        start = 0;
    if (end > SCHEMATIC_DIM)
        end = SCHEMATIC_DIM;

    for (int i = start; i < end; i++)
        if (isSymbol(schematic[row][i]))
            return true;

    return false;
}

int main()
{
    std::ifstream in("input.txt");

    unsigned i = 0;
    for (std::string line; std::getline(in, line); i++)
        strcpy(schematic[i], line.data());

    unsigned total = 0;
    for (i = 0; i < SCHEMATIC_DIM; i++)
    {
        for (unsigned j = 0; j < SCHEMATIC_DIM; j++)
        {
            if (!isdigit(schematic[i][j]))
                continue;

            int numStartIndex = j, numEndIndex = j;
            while (++j < SCHEMATIC_DIM)
            {
                if (isdigit(schematic[i][j]))
                    numEndIndex++;
                else
                    break;
            }

            if ((numStartIndex >= 1 && isSymbol(schematic[i][numStartIndex - 1])) ||
                (numEndIndex < SCHEMATIC_DIM - 1 && isSymbol(schematic[i][numEndIndex + 1])) ||
                (i >= 1 && rangeContainsSymbol(i - 1, numStartIndex - 1, numEndIndex + 2)) ||
                (i < SCHEMATIC_DIM - 1 && rangeContainsSymbol(i + 1, numStartIndex - 1, numEndIndex + 2)))
            {
                total += atoi(strndup(schematic[i] + numStartIndex, numEndIndex - numStartIndex + 1));
            }
        }
    }

    std::cout << total << std::endl;
}
