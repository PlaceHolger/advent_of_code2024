//https://adventofcode.com/2024/day/13

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//#define USE_TEST_DATA
#define IS_PART2

constexpr int COST_BUTTON_A = 3;
constexpr int COST_BUTTON_B = 1;
constexpr int MAX_BUTTON_PRESSES = 100;

struct Vector2_i64
{
    int64_t x;
    int64_t y;
};

struct ClawMachine
{
    Vector2_i64 button_a;
    Vector2_i64 button_b;
    Vector2_i64 prize;
};

//test data
std::vector<ClawMachine> clawMachines =
{
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
                result = sscanf_s(line.c_str(), "Button A: X+%lld, Y+%lld", &clawMachine.button_a.x, &clawMachine.button_a.y);
            }
            else if (line.find("Button B:") != std::string::npos)
            {
                result = sscanf_s(line.c_str(), "Button B: X+%lld, Y+%lld", &clawMachine.button_b.x, &clawMachine.button_b.y);
            }
            else if (line.find("Prize:") != std::string::npos)
            {
                result = sscanf_s(line.c_str(), "Prize: X=%lld, Y=%lld", &clawMachine.prize.x, &clawMachine.prize.y);
            }
            assert(result == 2);
        }
        clawMachines.push_back(clawMachine);
        file.close();
    }
}

// Function to compute the determinant of a 2x2 matrix
static int64_t determinant(int64_t a, int64_t b, int64_t c, int64_t d)
{
    return a * d - b * c;
}

//REMARK: this only works because the data does not contain collinear movements for the buttons, therefore there is always at most one solution
// Function to calculate the minimum cost to win a prize on a single machine using Cramer's Rule (https://de.wikipedia.org/wiki/Cramersche_Regel)
int64_t calculate_min_cost(const ClawMachine& machine)
{
    // Coefficients of the system
    const int64_t ax = machine.button_a.x, ay = machine.button_a.y;
    const int64_t bx = machine.button_b.x, by = machine.button_b.y;
    const int64_t px = machine.prize.x, py = machine.prize.y;

    // Compute the determinant of the coefficient matrix
    const int64_t det = determinant(ax, bx, ay, by);

    // If the determinant is zero, no solution exists
    if (det == 0)
        return -1;

    // Compute the determinants for Cramer's Rule
    const int64_t det_na = determinant(px, bx, py, by);
    const int64_t det_nb = determinant(ax, px, ay, py);

    const int64_t na = det_na / det;
    const int64_t nb = det_nb / det;

    //check again, if the solution is valid (it might be that the solution is not an integer...?)
    if (na * ax + nb * bx != px || na * ay + nb * by != py)
        return -1;

    // Compute costs
    const int64_t cost_a = std::abs(na) * COST_BUTTON_A;
    int64_t cost_b;
    cost_b = std::abs(nb) * COST_BUTTON_B;

    std::cout << "Machine: " << machine.prize.x << ", " << machine.prize.y << " Button A presses: " << na << " Button B presses: " << nb << " Tokens: " << cost_a + cost_b << '\n';

    return cost_a + cost_b;
}

int main(int argc, char* argv[])
{
#if !defined(USE_TEST_DATA)
    ReadClawMachinesFromFile();
#endif

#if defined(IS_PART2)
    // for part 2 10000000000000 is added to the pricePosition (because of a conversion error ;) )
    for (auto& clawMachine : clawMachines)
    {
        clawMachine.prize.x += 10000000000000;
        clawMachine.prize.y += 10000000000000;
    }
#endif

    //Day1 brute force solution:
    // //okay, we have to start somewhere, lets iterate over the claw machines and calculate the number of button presses for each machine just by trying all combinations and find the one with the least amount of tokens (if a solution exists)
    // uint64_t sumUsedTokens = 0;
    // for (const auto& clawMachine : clawMachines)
    // {
    //     int minButtonAPresses = 0;
    //     int minButtonBPresses = 0;
    //     int minTokensForMachine = INT_MAX;
    //     
    //     for (int buttonAPresses = 0; buttonAPresses <= MAX_BUTTON_PRESSES; buttonAPresses++)
    //     {
    //         for (int buttonBPresses = 0; buttonBPresses <= MAX_BUTTON_PRESSES; buttonBPresses++)
    //         {
    //             const int totalX = buttonAPresses * clawMachine.button_a.change_x + buttonBPresses * clawMachine.button_b.change_x;
    //             const int totalY = buttonAPresses * clawMachine.button_a.change_y + buttonBPresses * clawMachine.button_b.change_y;
    //             if (totalX == clawMachine.prize.x && totalY == clawMachine.prize.y)
    //             {
    //                 const int totalTokens = buttonAPresses * COST_BUTTON_A + buttonBPresses * COST_BUTTON_B;
    //                 if (totalTokens < minTokensForMachine)
    //                 {
    //                     minTokensForMachine = totalTokens;
    //                     minButtonAPresses = buttonAPresses;
    //                     minButtonBPresses = buttonBPresses;
    //                 }
    //             }
    //         }
    //     }
    //     
    //     if (minTokensForMachine != INT_MAX)
    //     {
    //         sumUsedTokens += minTokensForMachine;
    //         std::cout << "Machine: " << clawMachine.prize.x << ", " << clawMachine.prize.y << " Button A presses: " << minButtonAPresses << " Button B presses: " << minButtonBPresses << " Tokens: " << minTokensForMachine << '\n';
    //     }
    // }

    uint64_t sumUsedTokens = 0;
    for (const auto& clawMachine : clawMachines)
    {
        int64_t cost = calculate_min_cost(clawMachine);
        if (cost != -1)
        {
            sumUsedTokens += cost;
        }
    }

    std::cout << "Total tokens: " << sumUsedTokens << '\n';
    
    return 0;
}
