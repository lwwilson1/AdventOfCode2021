#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <vector>
#include <array>

class BingoBoard
{
public:
    BingoBoard(std::vector<int> boardEntries)
    {
        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j)
                entries[i][j] = boardEntries[5*i + j];

        for (auto& line : called) line.fill(false);
    }

    void call(int num)
    {
        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j)
                if (entries[i][j] == num) called[i][j] = true;
    }
    
    bool won()
    {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (called[i][j] == false) break;
                if (j == 4) {
                    return true;
                }
            }
        }

        for (int j = 0; j < 5; ++j) {
            for (int i = 0; i < 5; ++i) {
                if (called[i][j] == false) break;
                if (i == 4) {
                    return true;
                }
            }
        }

        return false;
    }

    int unmarkedSum()
    {
        int sum = 0;
        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j)
                if (called[i][j] == false) sum += entries[i][j];
    
        return sum;
    }

    std::array<std::array<int, 5>, 5> entries;
    std::array<std::array<bool, 5>, 5> called;
    int order;
    int score;

    friend std::ostream& operator<<(std::ostream& os, const BingoBoard& bb)
    {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                os << bb.entries[i][j] << " ";
            }
            os << std::endl;
        }
        os << std::endl;

        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                os << bb.called[i][j] << " ";
            }
            os << std::endl;
        }
        os << std::endl;

        return os;
    }
};

int main(int argc, char** argv)
{
    std::string line;
    std::ifstream infile(argv[1]); 

    std::vector<BingoBoard> boards;
    std::vector<int> calledNums;

    std::getline(infile, line);
    std::stringstream buffer(line);

    while (buffer.good()) {
        std::string substr;
        std::getline(buffer, substr, ',');
        calledNums.push_back(std::stoi(substr));
    }

    std::getline(infile, line);
    std::vector<int> boardEntries;

    while (std::getline(infile, line)) {
        if (line.empty()) {
            boards.push_back(BingoBoard(boardEntries));
            boardEntries.clear();
            continue;
        }

        std::stringstream buffer(line);
        std::vector<std::string> entryStr { std::istream_iterator<std::string>(buffer), 
                                            std::istream_iterator<std::string>() };

        std::transform(entryStr.begin(), entryStr.end(), std::back_inserter(boardEntries),
                       [](const std::string& str) { return std::stoi(str); });
    }

    boards.push_back(BingoBoard(boardEntries));

    int winOrder = 0;
    for (auto num : calledNums) {
        std::cout << "Calling num... " << num << std::endl;
        for (auto& board : boards) {
            if (!board.won()) {
                board.call(num);
                if (board.won()) {
                    std::cout << "The following board won on entry " << num << std::endl;
                    std::cout << board;
                    std::cout << "The board score is " << board.unmarkedSum() * num << std::endl;
                    board.score = board.unmarkedSum() * num;
                    board.order = winOrder;
                    winOrder++;
                }
            }
        }
    }

    int lastFound = -1;
    int lastFoundIdx = -1;
    for (int idx = 0; idx < boards.size(); ++idx) {
        if (boards[idx].order > lastFound) {
            lastFound = boards[idx].order;
            lastFoundIdx = idx;
        }
    }

    std::cout << "Last found board at " << lastFound << " has idx " << lastFoundIdx << std::endl;
    std::cout << "The board score is " << boards[lastFoundIdx].score << std::endl;
        

    return 0;
}
