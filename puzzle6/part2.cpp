#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>

class Fish
{
public:
    Fish(int c, long int n) : counter(c), num(n) {}
    int counter;
    long int num;
};

int main(int argc, char** argv)
{
    std::string line;
    std::ifstream infile(argv[1]); 
    
    std::vector<Fish> fishes;

    std::getline(infile, line);
    line += ',';

    while (!line.empty()) {
        fishes.push_back(Fish(std::stoi(line.substr(0, line.find(','))), 1));
        line.erase(0, line.find(',') + 1);
    }

    for (int i = 1; i <= 256; ++i) {
        long int num_new_fishes = 0;
        for (auto& x : fishes) {
            x.counter--;
            if (x.counter < 0) {
                x.counter = 6;
                num_new_fishes += x.num;
            }
        }
        fishes.push_back(Fish(8, num_new_fishes));
    }

    long int total_num_fishes = 0;
    for (auto& x : fishes)
        total_num_fishes += x.num;
    std::cout << "There are " << total_num_fishes << " fishes" << std::endl;

    return 0;
}
