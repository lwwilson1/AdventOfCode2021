#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>

int main(int argc, char** argv)
{
    std::string line;
    std::ifstream infile(argv[1]); 
    
    std::vector<int> fishes;

    std::getline(infile, line);
    line += ',';

    while (!line.empty()) {
        fishes.push_back(std::stoi(line.substr(0, line.find(','))));
        line.erase(0, line.find(',') + 1);
    }

    for (int i = 1; i <= 80; ++i) {
        std::vector<int> new_fishes;
        for (auto& x : fishes) {
            x--;
            if (x < 0) {
                x = 6;
                new_fishes.push_back(8);
            }
        }
        std::move(new_fishes.begin(), new_fishes.end(), std::back_inserter(fishes));
    }

    std::cout << "There are " << fishes.size() << " fishes" << std::endl;

    return 0;
}
