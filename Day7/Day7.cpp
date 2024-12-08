//https://adventofcode.com/2024/day/7

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Day7Data.h"

using namespace std;

//Creates all permutations of the operations
void generatePermutations(const string& ops, string current, int n, vector<string>& result) {
    if (n == 0)
    {
        result.push_back(current);
        return;
    }
    for (const char op : ops)
    {
        generatePermutations(ops, current + op, n - 1, result);
    }
}

unordered_map<int, vector<string>> permutations;  //maps number of numbers to the permutations

//#define IS_PART1

int main(int argc, char* argv[])
{
#if defined(IS_PART1)
    const string operations = "+*";
#else
    const string operations = "+*|";
#endif

    //iterate over data and count occurrences in the second column
    constexpr auto& data = realData; //testData;
    uint64_t sumCorrectValues = 0;
    for (const auto& numbers : data)
    {
        auto expectedResults = numbers[0];
        int numOperations = static_cast<int>(numbers.size()) - 2;
        if (permutations.find(numOperations) == permutations.end())
        {
            generatePermutations(operations, "", numOperations, permutations[numOperations]);
        }

        //now we have all permutations, we need to calculate the result
        for (const string& perm : permutations[numOperations])
        {
            //now we iterate over each operation in the permutation, and based on that add/multiply the numbers
            auto result = numbers[1];
            for (int i = 0; i < numOperations; ++i)
            {
                if (perm[i] == '+')
                {
                    result += numbers[i + 2];
                }
                else if (perm[i] == '*')
                {
                    result *= numbers[i + 2];
                }
                else if (perm[i] == '|')
                {
                    //this operation concatenates the numbers left with the current, so 73|45 = 7345 or 421|123 = 421123
                    // int numDigits = static_cast<int>(log10(numbers[i + 2])) + 1;
                    // result = result * static_cast<int>(pow(10, numDigits)) + numbers[i + 2];
                    const auto rightNumber = numbers[i + 2];
                    if (rightNumber < 10)
                        result = result * 10 + rightNumber;
                    else if (rightNumber < 100)
                        result = result * 100 + rightNumber;
                    else
                        result = result * 1000 + rightNumber;
                }

                if (result > expectedResults)
                {
                    break; //already too high
                }
            }
            if (result == expectedResults)
            {
                cout << "Found result: " << expectedResults << " with permutation: " << perm << '\n';
                sumCorrectValues += result;
                break;
            }
        }
    }

    std::cout << "Sum of correct values: " << sumCorrectValues << '\n';
    
    return 0;
}
