//https://adventofcode.com/2024/day/6

#include <iostream>
#include <iterator>

#include "Day6Data.h"

//some colors for the output
const std::string DEFAULT = "\033[0m";
const std::string VISITED = "\033[32m"; // "\033[38;5;94m";
const std::string EMPTY = "\033[38;5;240m";
const std::string OBSTACLE = "\033[31m";

constexpr bool IS_PART1 = false;

struct Position
{
    int x;
    int y;
};

constexpr auto& data = realdata; // testdata;
const int numRows = std::size(data);
const int numCols = std::size(data[0]);

bool isPositionValid(const Position& pPos)
{
    return pPos.x >= 0 && pPos.x < numCols && pPos.y >= 0 && pPos.y < numRows;
}

enum class Direction
{
    Up,
    Right,
    Down,
    Left
};

Position getStartPosition()
{
    for (int iRow = 0; iRow < numRows; ++iRow)
    {
        for (int iCol = 0; iCol < numCols; ++iCol)
        {
            if (data[iRow][iCol] == '^')
            {
                return {iCol, iRow};
            }
        }
    }
    return {-1, -1};
}

int main(int argc, char* argv[])
{
    //first find the starting position, that field is marked with a '^'
    Position startPos = getStartPosition();
    
    //now we simulate the movement of the agent, we start at the starting position and move in the direction of the arrow, if we hit an obstacle ('#') we turn 90 degrees to the right
    //we simulate this movement until the agent leaves the field

    Position currentPos = startPos;
    Direction currentDir = Direction::Up;
    while (true)
    {
        //first check if there is a field in front of us
        Position nextPos = currentPos;
        switch (currentDir)
        {
            case Direction::Up:
                nextPos.y -= 1;
                break;
            case Direction::Down:
                nextPos.y += 1;
                break;
            case Direction::Left:
                nextPos.x -= 1;
                break;
            case Direction::Right:
                nextPos.x += 1;
                break;
        }

        if (!isPositionValid(nextPos)) //we left the field, we are done
            break;

        if (data[nextPos.y][nextPos.x] != '#') //to include . and ^
        {
            currentPos = nextPos;
            //and we also mark the visited position in the data
            data[currentPos.y][currentPos.x] = 'X';
        }
        else
        {
            //turn right
            currentDir = static_cast<Direction>((static_cast<int>(currentDir) + 1) % 4);
        }
    }


    
    int numVisitedFields = 0;
    //now we print the result
    for (int iRow = 0; iRow < numRows; ++iRow)
    {
        for (int iCol = 0; iCol < numCols; ++iCol)
        {
            switch (data[iRow][iCol])
            {
                case 'X':
                    std::cout << VISITED << data[iRow][iCol];
                    ++numVisitedFields;
                    break;
                case '#':
                    std::cout << OBSTACLE << data[iRow][iCol];
                    break;
                case '.':
                    std::cout << EMPTY << data[iRow][iCol];
                    break;
                default:
                    std::cout << DEFAULT << data[iRow][iCol];
                    break;
            }
        }
        std::cout << '\n';
    }

    std::cout << "Number of visited fields: " << numVisitedFields << '\n';
    return 0;
}
