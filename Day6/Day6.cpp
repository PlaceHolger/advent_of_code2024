//https://adventofcode.com/2024/day/6

#include <assert.h>
#include <iostream>
#include <iterator>

//#define USE_TEST_DATA

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

//constexpr dataFormat& data = data; //realdata; // testdata;
dataFormat simulationResultData; //realdata; // testdata;
constexpr int numRows = std::size(data);
constexpr int numCols = std::size(data[0]);

int loopTestHelper[131][130]; //hack-workaround: we need to store each direction in which we visited the field, so we use a bitset for that. can/should be combined with simulationResultData

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

//now we simulate the movement of the agent, we start at the starting position and move in the direction of the arrow, if we hit an obstacle ('#') we turn 90 degrees to the right
//we simulate this movement until the agent leaves the field (or a loop was detected)
bool SimulateGuard(Position startPos, const bool loopTest) //we return if the guard left the field (true), or if he is in a loop (false)
{
    memset(simulationResultData, '?', sizeof(simulationResultData));  //reset the simulation data
    memset(loopTestHelper, 0, sizeof(loopTestHelper));  //reset the loop test helper
    
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
            return true;

        if (loopTest)
        {
            //loop check: check if we did already visit this field, and if so, did we visit it in the same direction?
            switch (currentDir)
            {
            case Direction::Up:
                if (loopTestHelper[nextPos.y][nextPos.x] & 1 << (int)Direction::Up)
                    return false;
                break;
            case Direction::Down:
                if (loopTestHelper[nextPos.y][nextPos.x] & 1 << (int)Direction::Down)
                    return false;
                break;
            case Direction::Left:
                if (loopTestHelper[nextPos.y][nextPos.x] & 1 << (int)Direction::Left)
                    return false;
                break;
            case Direction::Right:
                if (loopTestHelper[nextPos.y][nextPos.x] & 1 << (int)Direction::Right)
                    return false;
                break;
            }
        }

        if (data[nextPos.y][nextPos.x] != '#') //to include . and ^
        {
            currentPos = nextPos;
            //and we also mark the visited position in the data, depending on his movement direction
            switch (currentDir)
            {
                case Direction::Up:
                    simulationResultData[currentPos.y][currentPos.x] = '^';
                    loopTestHelper[currentPos.y][currentPos.x] |= 1 << (int)Direction::Up;
                    break;
                case Direction::Down:
                    simulationResultData[currentPos.y][currentPos.x] = 'v';
                    loopTestHelper[currentPos.y][currentPos.x] |= 1 << (int)Direction::Down;
                    break;
                case Direction::Left:
                    simulationResultData[currentPos.y][currentPos.x] = '<';
                    loopTestHelper[currentPos.y][currentPos.x] |= 1 << (int)Direction::Left;
                    break;
                case Direction::Right:
                    simulationResultData[currentPos.y][currentPos.x] = '>';
                    loopTestHelper[currentPos.y][currentPos.x] |= 1 << (int)Direction::Right;
                    break;
            }
        }
        else
        {
            //turn right
            currentDir = static_cast<Direction>((static_cast<int>(currentDir) + 1) % 4);
            simulationResultData[currentPos.y][currentPos.x] = '+'; //we mark the field were we turned
        }
    }
}

int main(int argc, char* argv[])
{
    //first find the starting position, that field is marked with a '^'
    Position startPos = getStartPosition();

    if (IS_PART1)
    {
        SimulateGuard(startPos, false);
        
        int numVisitedFields = 0;
        //now we print the result
        for (int iRow = 0; iRow < numRows; ++iRow)
        {
            for (int iCol = 0; iCol < numCols; ++iCol)
            {
                char dataAtPos = simulationResultData[iRow][iCol];
                if (dataAtPos == '?')
                    dataAtPos = data[iRow][iCol];
                
                switch (dataAtPos)
                {
                case '^':
                case 'v':
                case '<':
                case '>':
                case '+':
                    std::cout << VISITED << dataAtPos;
                    ++numVisitedFields;
                    break;
                case '#':
                    std::cout << OBSTACLE << dataAtPos;
                    break;
                case '.':
                    std::cout << EMPTY << dataAtPos;
                    break;
                default:
                    std::cout << DEFAULT << dataAtPos;
                    break;
                }
            }
            std::cout << '\n';
        }
        std::cout << "Number of visited fields: " << numVisitedFields << '\n';
    }
    else
    {
        //for part 2 we can add one obstacle to the map, in order to cause the guard to end up in a loop
        //let's start again with an (optimized) bruteforce attempt, only fields that are visited are considered
        //after placing the obstacle we check if the guard ends up in a loop, which would be the case if he revisits a field in the same movement direction
        SimulateGuard(startPos, false);
        //we copy the simulation data, so that we can use it to determine were we place our obstacles
        dataFormat copyOfSimulatedData;
        memcpy(copyOfSimulatedData, simulationResultData, sizeof(simulationResultData));

        int numLoopsFound = 0;
        
        for (int iRow = 0; iRow < numRows; ++iRow)
        {
            std::cout << "Row: " << iRow << std::endl;
            for (int iCol = 0; iCol < numCols; ++iCol)
            {
                if (startPos.x == iRow && startPos.y == iCol)
                    continue;
                
                //for each field we check if it is visited, if yes, we place an obstacle an run the simulation again
                if (copyOfSimulatedData[iRow][iCol] == '<' || copyOfSimulatedData[iRow][iCol] == '>' || copyOfSimulatedData[iRow][iCol] == '^' || copyOfSimulatedData[iRow][iCol] == 'v' || copyOfSimulatedData[iRow][iCol] == '+')
                {
                    char orgData = data[iRow][iCol];
                    data[iRow][iCol] = '#';
                    if (!SimulateGuard(startPos, true))
                    {
                        std::cout << "Obstacle placed at " << iCol << ", " << iRow << '\n';
                        numLoopsFound++;
                    }
                    data[iRow][iCol] = orgData;
                }
            }
        }

        std::cout << "Number of loops found: " << numLoopsFound << '\n';
    }
    

    return 0;
}
