//https://adventofcode.com/2024/day/11

#include <iostream>
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

void SimulateBlink(uint64_t stone, std::vector<uint64_t>& result)
{
    //rules:
    // If the stone is engraved with the number 0, it is replaced by a stone engraved with the number 1.
    // If the stone is engraved with a number that has an even number of digits, it is replaced by two stones. The left half of the digits are engraved on the new left stone, and the right half of the digits are engraved on the new right stone. (The new numbers don't keep extra leading zeroes: 1000 would become stones 10 and 0.)
    // If none of the other rules apply, the stone is replaced by a new stone; the old stone's number multiplied by 2024 is engraved on the new stone.
    if (stone == 0)
    {
        result.push_back(1);
    }
    else
    {
        const int numDigits = getNumDigits(stone);
        if (numDigits % 2 == 0)
        {
            const int halfNumDigits = numDigits / 2;
            const int divider = static_cast<int>(pow(10, halfNumDigits));
            const int leftStone = stone / divider;
            const int rightStone = stone % divider;
            result.push_back(leftStone);
            result.push_back(rightStone);
        }
        else
        {
            result.push_back(stone * 2024);
        }
    }
}

int main(int argc, char* argv[])
{
    constexpr int numSimulationSteps = 25;
    std::vector<uint64_t> stones2;

    std::vector<uint64_t>& result = stones2;
    std::vector<uint64_t>& input = data;
    
    for (int i = 0; i < numSimulationSteps; i++)
    {
        for (const auto stone : input)
        {
            SimulateBlink(stone, result);
        }

        // //print the current state
        // std::cout << "Step " << i << ": ";
        // for (const auto stone : input)
        // {
        //     std::cout << stone << " ";
        // }
        // std::cout << std::endl;

        input = result;
        result.clear();        
    }

    std::cout << "Amount of stones: " << input.size() << std::endl;
    
    return 0;
}
