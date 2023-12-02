#include <algorithm>
#include <fstream>
#include <iostream>

int main()
{
    std::ifstream in("input.txt");
    unsigned total = 0;

    for (std::string line; std::getline(in, line);)
    {
        auto itFirst = std::find_if(line.cbegin(), line.cend(), [](const char& c) { return isdigit(c); });
        auto itLast = std::find_if(line.crbegin(), line.crend(), [](const char& c) { return isdigit(c); });

        // unsafe, but input is guaranteed to have digits so this is fine
        const char comb[2] = { *itFirst, *itLast };
        total += atoi(comb);
    }

    std::cout << total << std::endl;
}
