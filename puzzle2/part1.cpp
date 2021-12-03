#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>

int main(int argc, char** argv)
{
    std::string line;
    std::ifstream infile(argv[1]); 

    int vertical = 0;
    int horizontal = 0;

    while (std::getline(infile, line))
    {
        std::string command = line.substr(0, line.find(' '));
        int move = std::stod(line.erase(0, line.find(' ')));

        if (command == "forward") horizontal += move;
        if (command == "up") vertical -= move;
        if (command == "down") vertical += move;
    }

    std::cout << "Horizontal is: " << horizontal << std::endl;
    std::cout << "Vertical is: " << vertical << std::endl;
    std::cout << "Product is: " << horizontal * vertical << std::endl;

    return 0;
}
