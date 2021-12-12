#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <vector>
#include <array>

int main(int argc, char** argv)
{
    std::string line;
    std::ifstream infile(argv[1]); 

    std::vector<std::string> lines;
    std::array<int, 4> corrupted { 0 };

    while (std::getline(infile, line)) {
        lines.push_back(line);
    }

    int linenum = 0;
    for (auto & line : lines) {
        linenum++;
        int charnum = 0;
        std::string closingchars = {'\0'};

        for (auto & it : line) {
            charnum++;
            if (it == '(') closingchars.push_back(')');
            if (it == ')') {
                if (it != closingchars.back()) {
                    std::cout << "Line " << linenum << ", char " << charnum << " = " << it
                              << ", closing char should be " << closingchars.back() << std::endl;
                    corrupted[0]++;
                    break;
                } else {
                    closingchars.pop_back();
                }
            }
            if (it == '[') closingchars.push_back(']');
            if (it == ']') {
                if (it != closingchars.back()) {
                    std::cout << "Line " << linenum << ", char " << charnum << " = " << it
                              << ", closing char should be " << closingchars.back() << std::endl;
                    corrupted[1]++;
                    break;
                } else {
                    closingchars.pop_back();
                }
            }
            if (it == '{') closingchars.push_back('}');
            if (it == '}') {
                if (it != closingchars.back()) {
                    std::cout << "Line " << linenum << ", char " << charnum << " = " << it
                              << ", closing char should be " << closingchars.back() << std::endl;
                    corrupted[2]++;
                    break;
                } else {
                    closingchars.pop_back();
                }
            }
            if (it == '<') closingchars.push_back('>');
            if (it == '>') {
                if (it != closingchars.back()) {
                    std::cout << "Line " << linenum << ", char " << charnum << " = " << it
                              << ", closing char should be " << closingchars.back() << std::endl;
                    corrupted[3]++;
                    break;
                } else {
                    closingchars.pop_back();
                }
            }
        }
    }

    for (auto it : corrupted) std::cout << it << ", ";
    std::cout << std::endl;

    int score = corrupted[0] * 3 + corrupted[1] * 57
              + corrupted[2] * 1197 + corrupted[3] * 25137;
    std::cout << "Score is: " << score << std::endl;

    return 0;
}
