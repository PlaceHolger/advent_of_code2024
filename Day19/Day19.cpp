//#define USE_TEST_DATA
#define IS_PART2

#include <iostream>
#include <unordered_map>

#include "Day19Data.h"

#if !defined(IS_PART2)

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
        if (design.rfind(pattern, 0) == 0)  //starts with pattern
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

#else

static std::unordered_map<std::string, uint64_t> memoization_count;

// for part2 we count the number of solutions for a design
static uint64_t CountSolutions(const std::string& design)
{
    if (design.empty())
        return 1; // if nothing is left to construct, we are done
    if (memoization_count.find(design) != memoization_count.end())
        return memoization_count[design];

    uint64_t solutions = 0;

    // Try all patterns to see if the design starts with one
    for (const auto& pattern : towels)
    {
        if (design.rfind(pattern, 0) == 0)
        {
            solutions += CountSolutions(design.substr(pattern.length()));
        }
    }
    memoization_count[design] = solutions;
    return solutions;
}

#endif

int main(int argc, char* argv[])
{
    uint64_t possibleCombinations = 0;
    for (const auto& combination : data)
    {
#if !defined(IS_PART2)
        if (CanConstruct(combination))
        {
            possibleCombinations++;
            std::cout << "Combination: " << combination << " can be created\n";
        }
        else
            std::cout << "Combination: " << combination << " CANNOT be created\n";
#else
        const uint64_t solutions = CountSolutions(combination);
        std::cout << "Combination: " << combination << " has " << solutions << " solutions\n";
        possibleCombinations += solutions;
#endif
    }

    std::cout << "Possible combinations: " << possibleCombinations << std::endl;
    
    return 0;
}
