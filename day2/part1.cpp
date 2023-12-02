#include <fstream>
#include <iostream>
#include <ranges>
using namespace std::literals;

int main()
{
    std::ifstream in("input.txt");
    unsigned total = 0;

    for (std::string line; std::getline(in, line);)
    {
        size_t colon = line.find(":");
        int gameId = std::stoi(line.substr(4, colon));
        std::string gameInfo = line.substr(colon + 2);

        bool possibleGame = true;
        for (const auto reveal : std::views::split(gameInfo, "; "sv))
        {
            unsigned totalRed = 0, totalGreen = 0, totalBlue = 0;
            for (const auto cube : std::views::split(std::string_view(reveal), ", "sv))
            {
                 std::string_view cubeStr(cube);
                 size_t space = cubeStr.find(" ");
                
                 int count = std::stoi(cubeStr.substr(0, space).data());
                 std::string_view color = cubeStr.substr(space + 1);

                 if (color == "red")
                    totalRed += count;
                 else if (color == "green")
                    totalGreen += count;
                 else if (color == "blue")
                    totalBlue += count;
            }

            if (totalRed > 12 || totalGreen > 13 || totalBlue > 14)
            {
                possibleGame = false;
                break;
            }
        }

        if (possibleGame)
            total += gameId;
    }

    std::cout << total << std::endl;
}
