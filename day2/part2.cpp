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
        std::string gameInfo = line.substr(line.find(":") + 2);
        unsigned maxRed = 0, maxGreen = 0, maxBlue = 0;

        for (const auto reveal : std::views::split(gameInfo, "; "sv))
        {
            for (const auto cube : std::views::split(std::string_view(reveal), ", "sv))
            {
                 std::string_view cubeStr(cube);
                 size_t space = cubeStr.find(" ");
                
                 int count = std::stoi(cubeStr.substr(0, space).data());
                 std::string_view color = cubeStr.substr(space + 1);

                 if (color == "red" && count > maxRed)
                    maxRed = count;
                 else if (color == "green" && count > maxGreen)
                    maxGreen = count;
                 else if (color == "blue" && count > maxBlue)
                    maxBlue = count;
            }
        }

        total += maxRed * maxGreen * maxBlue;
    }

    std::cout << total << std::endl;
}
