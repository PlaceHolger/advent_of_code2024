//#define USE_TEST_DATA

#include <iostream>
#include <unordered_map>

#include "Day19Data.h"

static std::unordered_map<std::string, bool> memoization;

// Function to check if a design can be constructed
static bool CanConstruct(const std::string& design)
{
    if (design.empty())
        return true; // if nothing is left to construct, we are done
    if (memoization.find(design) != memoization.end())
        return memoization[design]; 

    // Try all patterns to see if the design starts with one
    for (const auto& pattern : towels)
    {
        if (design.rfind(pattern, 0) == 0)
        {
            // If the design starts with the pattern
            if (CanConstruct(design.substr(pattern.length())))
            {
                return memoization[design] = true;
            }
        }
    }
    return memoization[design] = false; // No pattern matched
}

int main(int argc, char* argv[])
{
    int possibleCombinations = 0;
    for (const auto& combination : data)
    {
        bool canBeCreated = CanConstruct(combination);
        if (canBeCreated)
        {
            possibleCombinations++;
            std::cout << "Combination: " << combination << " can be created\n";
        }
        else
            std::cout << "Combination: " << combination << " CANNOT be created\n";
    }

    std::cout << "Possible combinations: " << possibleCombinations << std::endl;
    
    return 0;
}
