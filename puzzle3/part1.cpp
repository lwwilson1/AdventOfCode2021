#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>

int main(int argc, char** argv)
{
    std::string line;
    std::ifstream infile(argv[1]); 

    int length = 12;
    std::vector<std::string> input;
    std::string gamma, epsilon;

    while (std::getline(infile, line)) input.push_back(line);

    for (int i = 0; i < length; ++i)
    {
        int zeros = 0;
        int ones = 0;
        for (int j = 0; j < input.size(); ++j)
        {
            if (input[j][i] == '0') zeros++;
            if (input[j][i] == '1') ones++;
        }

        if (zeros > ones) {
            gamma.push_back('0');
            epsilon.push_back('1');

        } else if (ones > zeros) {
            gamma.push_back('1');
            epsilon.push_back('0');

        } else {
            gamma.push_back('1');
            epsilon.push_back('0');
        }
    }

    int gammanum = std::stoi(gamma, nullptr, 2);
    int epsnum = std::stoi(epsilon, nullptr, 2);

    std::cout << "gamma, eps, gamma * eps = " << gammanum << ", " << epsnum 
              << ", " << gammanum * epsnum << std::endl;

    return 0;
}
