#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>

int main(int argc, char** argv)
{
    std::string line;
    std::ifstream infile(argv[1]); 

    std::getline(infile, line);
    int depth0 = std::stod(line);

    std::getline(infile, line);
    int depth1 = std::stod(line);

    std::getline(infile, line);
    int depth2 = std::stod(line);

    int depthsum = depth0 + depth1 + depth2;;
    int increased = 0;

    while (std::getline(infile, line))
    {
        int currentdepth = std::stod(line);
        int currentsum = depth1 + depth2 + currentdepth;
        if (currentsum > depthsum) increased++;

        depth0 = depth1;
        depth1 = depth2;
        depth2 = currentdepth;
        depthsum = currentsum;
    }

    std::cout << "Increased " << increased << " times." << std::endl;

    return 0;
}
