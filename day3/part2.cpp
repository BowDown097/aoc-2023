#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>

#define SCHEMATIC_DIM 140
char schematic[SCHEMATIC_DIM][SCHEMATIC_DIM];

struct Gear
{
    unsigned index = 0;
    unsigned ratio = 1;
    unsigned totalPartNumbers = 0;
};

enum ReadDirection { READ_LEFT, READ_RIGHT };

std::string readDigitsFromIndex(int row, int index, ReadDirection direction)
{
    std::string out;
    out.reserve(3); // 3 digit number max
    
    if (direction == READ_LEFT)
    {
        while (--index >= 0)
        {
            if (isdigit(schematic[row][index]))
                out += schematic[row][index];
            else
                break;
        }

        if (out.size() > 1)
            std::reverse(out.begin(), out.end());
    }
    else
    {
        while (++index < SCHEMATIC_DIM)
        {
            if (isdigit(schematic[row][index]))
                out += schematic[row][index];
            else
                break;
        }
    }

    return out;
}

bool readRow(int row, Gear& gear)
{
    if (row < 0 || row >= SCHEMATIC_DIM)
        return gear.totalPartNumbers <= 2;

    if (isdigit(schematic[row][gear.index])) // if immediate digit
    {
        std::string digits = readDigitsFromIndex(row, gear.index, READ_LEFT)
                           + schematic[row][gear.index]
                           + readDigitsFromIndex(row, gear.index, READ_RIGHT);

        gear.ratio *= std::stoi(digits);
        gear.totalPartNumbers++;
        return gear.totalPartNumbers <= 2;
    }

    if (gear.index - 1 > 0 && isdigit(schematic[row][gear.index - 1])) // if digit to the left
    {
        gear.ratio *= std::stoi(readDigitsFromIndex(row, gear.index, READ_LEFT));
        gear.totalPartNumbers++;
    }

    if (gear.index < SCHEMATIC_DIM && isdigit(schematic[row][gear.index + 1])) // if digit to the right
    {
        gear.ratio *= std::stoi(readDigitsFromIndex(row, gear.index, READ_RIGHT));
        gear.totalPartNumbers++;
    }

    return gear.totalPartNumbers <= 2;
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
            if (schematic[i][j] != '*')
                continue;

            Gear gear { .index = j };
            if (!readRow(i - 1, gear) || !readRow(i, gear) || !readRow(i + 1, gear))
                continue;

            if (gear.totalPartNumbers == 2)
                total += gear.ratio;
        }
    }

    std::cout << total << std::endl;
}
