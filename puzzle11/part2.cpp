#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <vector>
#include <array>
#include <list>

int main(int argc, char** argv)
{
    std::string line;
    std::ifstream infile(argv[1]); 

    std::vector<std::vector<int>> dumboOctopodes;

    while (std::getline(infile, line)) {
        std::vector<int> octoline;
        for (auto strchar : line) octoline.push_back(std::atoi(&strchar));
        dumboOctopodes.push_back(octoline);
    }

    int xdim = dumboOctopodes[0].size();
    int ydim = dumboOctopodes.size();
    int numsteps = 0;

    for (auto& itline : dumboOctopodes) {
        for (auto& it : itline) {
            std::cout << it << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    while (true) {
        numsteps++;
        for (auto& dumboLine : dumboOctopodes)
            std::transform(std::begin(dumboLine), std::end(dumboLine), std::begin(dumboLine),
                           [](int x){ return ++x; });

        std::vector<std::vector<bool>> exploded(ydim, std::vector<bool>(xdim, false));

        std::list<std::pair<int, int>> check;

        for (int i = 0; i < ydim; ++i) {
            for (int j = 0; j < xdim; ++j) {
                if (dumboOctopodes[i][j] > 9) {
                    exploded[i][j] = true;
                    check.push_back(std::pair<int, int>(i, j));
                }
            }
        }

        for (auto it = check.begin(); it != check.end();) {
            int i = it->first;
            int j = it->second;

            if (i > 0) {
                dumboOctopodes[i-1][j]++;
                if (dumboOctopodes[i-1][j] > 9) {
                    if (exploded[i-1][j] == false) {
                        exploded[i-1][j] = true;
                        check.push_back(std::pair<int, int>(i-1, j));
                    }
                }
            }
            if (i < ydim-1) {
                dumboOctopodes[i+1][j]++;
                if (dumboOctopodes[i+1][j] > 9) {
                    if (exploded[i+1][j] == false) {
                        exploded[i+1][j] = true;
                        check.push_back(std::pair<int, int>(i+1, j));
                    }
                }
            }
            if (j > 0) {
                dumboOctopodes[i][j-1]++;
                if (dumboOctopodes[i][j-1] > 9) {
                    if (exploded[i][j-1] == false) {
                        exploded[i][j-1] = true;
                        check.push_back(std::pair<int, int>(i, j-1));
                    }
                }
            }
            if (j < xdim-1) {
                dumboOctopodes[i][j+1]++;
                if (dumboOctopodes[i][j+1] > 9) {
                    if (exploded[i][j+1] == false) {
                        exploded[i][j+1] = true;
                        check.push_back(std::pair<int, int>(i, j+1));
                    }
                }
            }
            if (i > 0 && j > 0) {
                dumboOctopodes[i-1][j-1]++;
                if (dumboOctopodes[i-1][j-1] > 9) {
                    if (exploded[i-1][j-1] == false) {
                        exploded[i-1][j-1] = true;
                        check.push_back(std::pair<int, int>(i-1, j-1));
                    }
                }
            }
            if (i > 0 && j < xdim-1) {
                dumboOctopodes[i-1][j+1]++;
                if (dumboOctopodes[i-1][j+1] > 9) {
                    if (exploded[i-1][j+1] == false) {
                        exploded[i-1][j+1] = true;
                        check.push_back(std::pair<int, int>(i-1, j+1));
                    }
                }
            }
            if (i < ydim-1 && j > 0) {
                dumboOctopodes[i+1][j-1]++;
                if (dumboOctopodes[i+1][j-1] > 9) {
                    if (exploded[i+1][j-1] == false) {
                        exploded[i+1][j-1] = true;
                        check.push_back(std::pair<int, int>(i+1, j-1));
                    }
                }
            }
            if (i < ydim-1 && j < xdim-1) {
                dumboOctopodes[i+1][j+1]++;
                if (dumboOctopodes[i+1][j+1] > 9) {
                    if (exploded[i+1][j+1] == false) {
                        exploded[i+1][j+1] = true;
                        check.push_back(std::pair<int, int>(i+1, j+1));
                    }
                }
            }

            it = check.erase(it);
        }

        int flashes = 0;
        for (auto& dumboLine : dumboOctopodes)
            std::transform(std::begin(dumboLine), std::end(dumboLine), std::begin(dumboLine),
                           [&flashes](int x){ if (x > 9) { ++flashes; return 0; }
                                              else return x; });
        if (flashes == xdim * ydim) break;
    }

    std::cout << "Final board is: " << std::endl;
    for (auto& itline : dumboOctopodes) {
        for (auto& it : itline) {
            std::cout << it << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << "Number of steps = " << numsteps << std::endl;

    return 0;
}
