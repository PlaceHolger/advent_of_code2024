//https://adventofcode.com/2024/day/11

#include <iostream>
#include <unordered_map>
#include <vector>

//static std::vector<uint64_t> data = { 0, 1, 10, 99, 999 };
//static std::vector<uint64_t> data = { 125, 17 }; //testdata
static std::vector<uint64_t> data = { 3279, 998884, 1832781, 517, 8, 18864, 28, 0 };

static int getNumDigits(uint64_t num)
{
    int numDigits = 0;
    while (num > 0)
    {
        num /= 10;
        numDigits++;
    }
    return numDigits;
}

struct Result
{
    static constexpr uint64_t INVALID = -1;
    uint64_t stone1 = INVALID;
    uint64_t stone2 = INVALID;
};

Result SimulateBlink(uint64_t stone)
{
    //rules:
    // 1. If the stone is engraved with the number 0, it is replaced by a stone engraved with the number 1.
    // 2. If the stone is engraved with a number that has an even number of digits, it is replaced by two stones. The left half of the digits are engraved on the new left stone, and the right half of the digits are engraved on the new right stone. (The new numbers don't keep extra leading zeroes: 1000 would become stones 10 and 0.)
    // 3. If none of the other rules apply, the stone is replaced by a new stone; the old stone's number multiplied by 2024 is engraved on the new stone.
    if (stone == 0) //rule 1
    {
        return {1, Result::INVALID};
    }

    const int numDigits = getNumDigits(stone);
    if (numDigits % 2 == 0) // 2
    {
        const int halfNumDigits = numDigits / 2;
        const int divider = static_cast<int>(pow(10, halfNumDigits));
        const uint64_t leftStone = stone / divider;
        const uint64_t rightStone = stone % divider;
        return {leftStone, rightStone};
    }

    return {stone * 2024, Result::INVALID};  //3
}

constexpr bool IS_PART1 = false;

std::unordered_map<uint64_t, Result> resultsCache; //stoneNumber, result

std::unordered_map<uint64_t, uint64_t> stonesMap; //stoneNumber, amount
std::unordered_map<uint64_t, uint64_t> stonesMap2; //stoneNumber, amount

int main(int argc, char* argv[])
{
    constexpr int numSimulationSteps = (IS_PART1) ? 25 : 75;

    //convert the data into our map-format
    for (auto stone : data)
    {
        stonesMap[stone]++;
    }

    auto& inputMap = stonesMap;
    auto& resultMap = stonesMap2;
    
    for (int i = 0; i < numSimulationSteps; i++)
    {
        for (const auto stone : inputMap)
        {
            const auto cachedResult = resultsCache.find(stone.first);
            Result result;
            if (cachedResult != resultsCache.cend())
            {
                result = cachedResult->second;
            }
            else
            {
                result = SimulateBlink(stone.first);
                resultsCache[stone.first] = result;
            }

            resultMap[result.stone1] += stone.second;
            if (result.stone2 != Result::INVALID) {
                resultMap[result.stone2] += stone.second;
            }
        }

        // to count the number of stones, we have to add all the stones in the map
        uint64_t totalStones = 0;
        for (auto stone : resultMap)
        {
            totalStones += stone.second;
        }
        std::cout << "Step " << i << ": Stones: " << totalStones << " resultsCache " << resultsCache.size() << '\n';

        std::swap(inputMap, resultMap);
        resultMap.clear();
    }

    return 0;
}
