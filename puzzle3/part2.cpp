#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>

int main(int argc, char** argv)
{
    std::string line;
    std::ifstream infile(argv[1]); 

    int length = 12;
    std::vector<std::string> oxygen, scrubber;

    while (std::getline(infile, line)) oxygen.push_back(line);

    scrubber = oxygen;

    for (int i = 0; i < length; ++i)
    {
        int zeros = 0;
        int ones = 0;
        for (int j = 0; j < oxygen.size(); ++j)
        {
            if (oxygen[j][i] == '0') zeros++;
            if (oxygen[j][i] == '1') ones++;
        }

        if (zeros > ones) {
            oxygen.erase(std::remove_if(oxygen.begin(), oxygen.end(),
                [i](const std::string& x) { return x[i] == '1'; }), oxygen.end());

        } else if (ones > zeros) {
            oxygen.erase(std::remove_if(oxygen.begin(), oxygen.end(),
                [i](const std::string& x) { return x[i] == '0'; }), oxygen.end());

        } else {
            oxygen.erase(std::remove_if(oxygen.begin(), oxygen.end(),
                [i](const std::string& x) { return x[i] == '0'; }), oxygen.end());
        }

        if (oxygen.size() == 0) break;
    }

    for (int i = 0; i < length; ++i)
    {
        int zeros = 0;
        int ones = 0;
        for (int j = 0; j < scrubber.size(); ++j)
        {
            if (scrubber[j][i] == '0') zeros++;
            if (scrubber[j][i] == '1') ones++;
        }

        if (zeros > ones) {
            scrubber.erase(std::remove_if(scrubber.begin(), scrubber.end(),
                [i](const std::string& x) { return x[i] == '0'; }), scrubber.end());

        } else if (ones > zeros) {
            scrubber.erase(std::remove_if(scrubber.begin(), scrubber.end(),
                [i](const std::string& x) { return x[i] == '1'; }), scrubber.end());

        } else {
            scrubber.erase(std::remove_if(scrubber.begin(), scrubber.end(),
                [i](const std::string& x) { return x[i] == '1'; }), scrubber.end());
        }

        if (scrubber.size() == 0) break;
    }

    int oxygennum = std::stoi(oxygen[0], nullptr, 2);
    int scrubbernum = std::stoi(scrubber[0], nullptr, 2);

    std::cout << "oxy, scrub, oxy * scrub = " << oxygennum << ", " << scrubbernum
              << ", " << oxygennum * scrubbernum << std::endl;

    return 0;
}
