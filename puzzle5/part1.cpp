#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
#include <list>

bool xmaxfn(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs)
{ return lhs.first < rhs.first; }

bool ymaxfn(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs)
{ return lhs.second < rhs.second; }

int main(int argc, char** argv)
{
    std::string line;
    std::ifstream infile(argv[1]); 

    std::vector<std::pair<int, int>> startCoord;
    std::vector<std::pair<int, int>> endCoord;

    while (std::getline(infile, line))
    {
        auto coord1 = line.substr(0, line.find(" -> "));
        auto coord2 = line.substr(line.find(" -> ") + 4, line.back());

        startCoord.push_back(std::pair<int, int>(
            std::stoi(coord1.substr(0, coord1.find(","))),
            std::stoi(coord1.substr(coord1.find(",") + 1, line.back()))));
        endCoord.push_back(std::pair<int, int>(
            std::stoi(coord2.substr(0, coord2.find(","))),
            std::stoi(coord2.substr(coord2.find(",") + 1, line.back()))));
    }

    auto xmax = std::max(std::max_element(startCoord.begin(), startCoord.end(), xmaxfn)->first,
                         std::max_element(endCoord.begin(), endCoord.end(), xmaxfn)->first);

    auto ymax = std::max(std::max_element(startCoord.begin(), startCoord.end(), ymaxfn)->second,
                         std::max_element(endCoord.begin(), endCoord.end(), ymaxfn)->second);

    std::vector<std::vector<int>> board(ymax+1, std::vector<int>(xmax+1, 0));
    int numCoords = startCoord.size();

    for (int n = 0; n < numCoords; ++n) {
        if (startCoord[n].first == endCoord[n].first) {
            for (int j =  std::min(startCoord[n].second, endCoord[n].second); 
                     j <= std::max(startCoord[n].second, endCoord[n].second);
                     ++j)
                board[j][startCoord[n].first]++;
        } else if (startCoord[n].second == endCoord[n].second) {
            for (int i =  std::min(startCoord[n].first, endCoord[n].first); 
                     i <= std::max(startCoord[n].first, endCoord[n].first);
                     ++i)
                board[startCoord[n].second][i]++;
        }
    }

    int numcrosses = 0;
    for (int j = 0; j < ymax+1; ++j) {
        for (int i = 0; i < xmax+1; ++i) {
            if (board[j][i] > 1) numcrosses++;
        }
    }

    std::cout << "Num multi crosses = " << numcrosses << std::endl;

    return 0;
}
