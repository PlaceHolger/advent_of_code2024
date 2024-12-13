//https://adventofcode.com/2024/day/13

#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

constexpr int PRIZE_BUTTON_A = 3;
constexpr int PRIZE_BUTTON_B = 1;
constexpr int MAX_BUTTON_PRESSES = 100;

struct Position
{
    int x;
    int y;
};

struct Button
{
    int change_x;
    int change_y;
};

struct ClawMachine
{
    Button button_a;
    Button button_b;
    Position prize;
};

//test data
std::vector<ClawMachine> clawMachines = {
    {{94, 34}, {22, 67}, {8400, 5400}},
    {{26, 66}, {67, 21}, {12748, 12176}},
    {{17, 86}, {84, 37}, {7870, 6450}},
    {{69, 23}, {27, 71}, {18641, 10279}}
};

void ReadClawMachinesFromFile()
{
    // Read the claw machines from file data.txt //thanks GPT ; )
    std::ifstream file("data.txt");
    if (file.is_open())
    {
        clawMachines.clear();
        std::string line;
        ClawMachine clawMachine;
        while (std::getline(file, line))
        {
            int result = 2;
            if (line.empty())
            {
                clawMachines.push_back(clawMachine);
            }
            else if (line.find("Button A:") != std::string::npos)
            {
                result = sscanf_s(line.c_str(), "Button A: X+%d, Y+%d", &clawMachine.button_a.change_x, &clawMachine.button_a.change_y);
            }
            else if (line.find("Button B:") != std::string::npos)
            {
                result = sscanf_s(line.c_str(), "Button B: X+%d, Y+%d", &clawMachine.button_b.change_x, &clawMachine.button_b.change_y);
            }
            else if (line.find("Prize:") != std::string::npos)
            {
                result = sscanf_s(line.c_str(), "Prize: X=%d, Y=%d", &clawMachine.prize.x, &clawMachine.prize.y);
            }
            assert(result == 2);
        }
        clawMachines.push_back(clawMachine);
        file.close();
    }
}

//#define USE_TEST_DATA

int main(int argc, char* argv[])
{
#if !defined(USE_TEST_DATA)
    ReadClawMachinesFromFile();
#endif

    //okay, we have to start somewhere, lets iterate over the claw machines and calculate the number of button presses for each machine just by trying all combinations and find the one with the least amount of tokens (if a solution exists)
    uint64_t sumUsedTokens = 0;
    for (const auto& clawMachine : clawMachines)
    {
        int minButtonAPresses = 0;
        int minButtonBPresses = 0;
        int minTokensForMachine = INT_MAX;
        
        for (int buttonAPresses = 0; buttonAPresses <= MAX_BUTTON_PRESSES; buttonAPresses++)
        {
            for (int buttonBPresses = 0; buttonBPresses <= MAX_BUTTON_PRESSES; buttonBPresses++)
            {
                const int totalX = buttonAPresses * clawMachine.button_a.change_x + buttonBPresses * clawMachine.button_b.change_x;
                const int totalY = buttonAPresses * clawMachine.button_a.change_y + buttonBPresses * clawMachine.button_b.change_y;
                if (totalX == clawMachine.prize.x && totalY == clawMachine.prize.y)
                {
                    const int totalTokens = buttonAPresses * PRIZE_BUTTON_A + buttonBPresses * PRIZE_BUTTON_B;
                    if (totalTokens < minTokensForMachine)
                    {
                        minTokensForMachine = totalTokens;
                        minButtonAPresses = buttonAPresses;
                        minButtonBPresses = buttonBPresses;
                    }
                }
            }
        }
        
        if (minTokensForMachine != INT_MAX)
        {
            sumUsedTokens += minTokensForMachine;
            std::cout << "Machine: " << clawMachine.prize.x << ", " << clawMachine.prize.y << " Button A presses: " << minButtonAPresses << " Button B presses: " << minButtonBPresses << " Tokens: " << minTokensForMachine << '\n';
        }
    }

    std::cout << "Total tokens: " << sumUsedTokens << '\n';
    
    return 0;
}
