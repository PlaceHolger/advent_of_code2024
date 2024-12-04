
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

#include "Day3Data.h"

constexpr bool isPart1 = false;

int main(int argc, char* argv[])
{
    std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
    std::smatch matches;

    //std::string data = testdata2; //realdata;  //somehow i broke the realdata when copying it :/
    std::ifstream file("Day3Data.txt");
    if (!file) {
        std::cerr << "Unable to open file\n";
        return 1;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string data = buffer.str();
    
    if constexpr (!isPart1)
    {
        //We remove everything between don't() and do()
        std::regex removePattern(R"(don't\(\)(.*?)do\(\))");
        data = std::regex_replace(data, removePattern, "XXXXXX");
        //and if there is a don't block at the end of the string, we remove it too
        std::regex removePattern2(R"(don't\(\)(.*))");
        data = std::regex_replace(data, removePattern2, "XXXXXX");
    }
    
    int64_t result = 0;
    std::string::const_iterator searchStart(data.cbegin());
    while (std::regex_search(searchStart, data.cend(), matches, pattern))
    {
        int product = std::stoi(matches[1]) * std::stoi(matches[2]);
        std::cout << "Found: " << matches[0] << " = " << product << '\n';
        result += product;
        searchStart = matches.suffix().first;
    }
    std::cout << "Result: " << result << '\n';

    return 0;
}
