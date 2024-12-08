//https://adventofcode.com/2024/day/8

#include <iostream>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Day8Data.h"

//some colors for the output
const std::string DEFAULT = "\033[0m";
const std::string ANTENA = "\033[32m";
const std::string ANTENA_AND_ANTINODE = "\033[38;5;214m";
const std::string ANTINODE =  "\033[31m";

struct Position
{
    int x;
    int y;

    
    bool operator==(const Position& other) const
    {
        return x == other.x && y == other.y;
    }
};

std::vector<Position> Antinodes; //all positions where there is an antinode
constexpr auto& data = realData; //testData;
constexpr int NUM_ROWS = std::size(data);
constexpr int NUM_COLS = std::size(data[0]) - 1;

void addAntinode(const Position& pos)
{
    //check if the position is within the field
    if (pos.x < 0 || pos.x >= NUM_COLS || pos.y < 0 || pos.y >= NUM_ROWS)
        return;
    
    //checks if the position is already in the list, if not adds
    if (std::find(Antinodes.begin(), Antinodes.end(), pos) == Antinodes.end())
    {
        Antinodes.push_back(pos);
    }
}

constexpr bool IS_PART1 = false;

int main(int argc, char* argv[])
{
    std::unordered_map<char, std::vector<Position>> Antenas;  //mapping of antena ID and all positions for that ID
    
    for (int iRow = 0; iRow < NUM_ROWS; ++iRow)
    {
        for (int iCol = 0; iCol < NUM_COLS; ++iCol)
        {
            if (data[iRow][iCol] != '.')
            {
                Antenas[data[iRow][iCol]].push_back({iCol, iRow});
            }
        }
    }

    //okay, now we iterate over all antenas and calculate the direction to the next antena with the same id.
    for  (const auto& antena : Antenas)
    {
        const auto numAntenas = antena.second.size();
        for (size_t iAntena = 0; iAntena < numAntenas; ++iAntena)
        {
            const Position& currentPos = antena.second[iAntena];
            for (size_t iOtherAntena = iAntena + 1; iOtherAntena < numAntenas; ++iOtherAntena)
            {
                const Position& otherPos = antena.second[iOtherAntena];
                const Position direction = {otherPos.x - currentPos.x, otherPos.y - currentPos.y};

                if (IS_PART1)
                {
                    //there will be an antinode, at the position of pos1+dir, and at pos2-dir, so we mark these positions on the map
                    addAntinode({currentPos.x - direction.x, currentPos.y - direction.y});
                    addAntinode({otherPos.x + direction.x, otherPos.y + direction.y});                    
                }
                else
                {
                    //we have antinodes at any position in the direction (and the reverse direction) between the two antenas
                    const int STUPIDLY_BIG_NUMBER = 50; //well... we could be more clever than that...
                    for (int i = -STUPIDLY_BIG_NUMBER; i < STUPIDLY_BIG_NUMBER; ++i)
                    {
                        addAntinode({currentPos.x + direction.x * i, currentPos.y + direction.y * i});
                    }
                }
            }
        }
    }

    //test: print the map again, but add the antinodes
    for (int iRow = 0; iRow < NUM_ROWS; ++iRow)
    {
        for (int iCol = 0; iCol < NUM_COLS; ++iCol)
        {
            if (std::find(Antinodes.begin(), Antinodes.end(), Position{iCol, iRow}) != Antinodes.end())
            {
                if (data[iRow][iCol] != '.')
                    std::cout << ANTENA_AND_ANTINODE << data[iRow][iCol];
                else
                    std::cout << ANTINODE << '#';
            }
            else
            {
                if (data[iRow][iCol] != '.')
                    std::cout << ANTENA << data[iRow][iCol];
                else
                    std::cout << DEFAULT << '#';
            }
        }
        std::cout << '\n';
    }

    std::cout << "Number of antinodes: " << Antinodes.size() << '\n';
    
    return 0;
}
