#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>

int main(int argc, char** argv)
{
    std::string line;
    std::ifstream infile(argv[1]); 
    
    std::vector<int> posns;

    std::getline(infile, line);
    line += ',';

    while (!line.empty()) {
        posns.push_back(std::stoi(line.substr(0, line.find(','))));
        line.erase(0, line.find(',') + 1);
    }

    auto minpos = *std::min_element(posns.begin(), posns.end());
    auto maxpos = *std::max_element(posns.begin(), posns.end());
    std::vector<int> costs(maxpos-minpos);

    std::cout << "minpos: " << minpos << ", " << "maxpos: " << maxpos << std::endl;

    for (int n = minpos; n < maxpos; ++n) {
        int cost = 0;
        for (auto x : posns) {
            cost += std::abs(n - x) * (std::abs(n-x) + 1) / 2;
        }
        costs[n-minpos] = cost;
    }

    auto mincostit = std::min_element(costs.begin(), costs.end());
    auto mincostpos = std::distance(costs.begin(), mincostit);

    std::cout << "Lowest cost posn is " << mincostpos + minpos
              << " with cost " << costs[mincostpos] << std::endl;

    return 0;
}
