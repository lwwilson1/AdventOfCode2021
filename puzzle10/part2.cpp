#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <vector>
#include <array>
#include <list>

int main(int argc, char** argv)
{
    std::string fileline;
    std::ifstream infile(argv[1]); 

    std::list<std::pair<std::string, std::string>> lines;

    while (std::getline(infile, fileline)) {
        lines.push_back(std::pair<std::string, std::string>(fileline, {'\0'}));
    }

    for (auto& linesit : lines) {

        auto& line = linesit.first;
        auto& closingchars = linesit.second;

        for (auto & it : line) {
            if (it == '(') closingchars.push_back(')');
            if (it == ')') {
                if (it != closingchars.back()) {
                    line={};
                    break;
                } else {
                    closingchars.pop_back();
                }
            }
            if (it == '[') closingchars.push_back(']');
            if (it == ']') {
                if (it != closingchars.back()) {
                    line={};
                    break;
                } else {
                    closingchars.pop_back();
                }
            }
            if (it == '{') closingchars.push_back('}');
            if (it == '}') {
                if (it != closingchars.back()) {
                    line={};
                    break;
                } else {
                    closingchars.pop_back();
                }
            }
            if (it == '<') closingchars.push_back('>');
            if (it == '>') {
                if (it != closingchars.back()) {
                    line={};
                    break;
                } else {
                    closingchars.pop_back();
                }
            }
        }
    }

    lines.remove_if([](std::pair<std::string, std::string> x){ return (x.first == ""); });
    
    std::vector<long int> scores;

    for (auto& it : lines) {
        std::reverse(it.second.begin(), it.second.end());
        
        long int score = 0;
        for (auto cc : it.second) {
           if (cc == ')') score = (5*score + 1);
           if (cc == ']') score = (5*score + 2);
           if (cc == '}') score = (5*score + 3);
           if (cc == '>') score = (5*score + 4);
        }
        scores.push_back(score);
    }

    std::sort(scores.begin(), scores.end());
    std::cout << "Middle score: " << scores[scores.size()/2] << std::endl;

    return 0;
}
