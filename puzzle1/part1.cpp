#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>

int main(int argc, char** argv)
{
    std::string line;
    std::ifstream infile(argv[1]); 
    std::vector<int> depths;

    int prev = std::numeric_limits<int>::max();
    int increased = 0;

    while (std::getline(infile, line))
    {
        depths.push_back(std::stod(line)); 
        int current = std::stod(line);
        if (current > prev) increased++;
        prev = current;
    }

    std::cout << "Increased " << increased << " times." << std::endl;

    return 0;
}
