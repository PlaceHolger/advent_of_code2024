//https://adventofcode.com/2024/day/12

//#define USE_TEST_DATA

#include <cassert>
#include <cstdint>
#include <iostream>

#include "Day12Data.h"
constexpr int NUM_ROWS = std::size(data);
constexpr int NUM_COLS = std::size(data[0]) - 1;
//constexpr char VISITED = '#';
bool visitedMap[NUM_ROWS][NUM_COLS] = {{false}};

enum eDirection
{
    NONE = 0,
    RIGHT = 1 << 0,
    DOWN = 1 << 1,
    LEFT = 1 << 2,
    UP = 1 << 3
};
static int visitedDirectionMap[NUM_ROWS][NUM_COLS] = {{NONE}};

// 4-way connectivity, right, down, left, up
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

bool IsInBounds(const int x, const int y)
{
    return x < 0 || x >= NUM_COLS || y < 0 || y >= NUM_ROWS;
}

void floodFillRecursive(const int x, const int y, const int target, int& currentArea, int& currentPerimeter, int& sideCount)
{
    if (IsInBounds(x,y) || data[y][x] != target || visitedMap[y][x])
    {
        return;
    }

    //side counts:
    for (eDirection dir = RIGHT; dir <= UP; dir = static_cast<eDirection>(dir << 1))
    {
        if (visitedDirectionMap[y][x] & dir)
            continue;

        int dirX = x;
        int dirY = y;
        
        switch (dir)
        {
        case RIGHT:
            //check if we are at the border or the next island
            if (x + 1 >= NUM_COLS || data[y][x + 1] != target)
            {
                sideCount++;
                //mark the direction as visited for self and all up/down neighbors
                visitedDirectionMap[y][x] |= RIGHT;
                //go up and mark the direction as visited for the neighbor
                dirY = y - 1;
                while (dirY >= 0 && data[dirY][x] == target && data[dirY][x + 1] != target)  //check if the next neighbour is part of the same straight line
                {
                    visitedDirectionMap[dirY][x] |= RIGHT;
                    dirY--;
                }
                //go down and mark the direction as visited for the neighbor
                dirY = y + 1;
                while (dirY < NUM_ROWS && data[dirY][x] == target && data[dirY][x + 1] != target)  //check if the next neighbour is part of the same straight line
                {
                    visitedDirectionMap[dirY][x] |= RIGHT;
                    dirY++;
                }  
            }
            break;
        case DOWN:
            //check if we are at the border or the next island
            if (y + 1 >= NUM_ROWS || data[y + 1][x] != target)
            {
                sideCount++;
                //mark the direction as visited for self and all left/right neighbors
                visitedDirectionMap[y][x] |= DOWN;
                //go left and mark the direction as visited for the neighbor
                dirX = x - 1;
                while (dirX >= 0 && data[y][dirX] == target && data[y + 1][dirX] != target)  //check if the next neighbour is part of the same straight line
                {
                    visitedDirectionMap[y][dirX] |= DOWN;
                    dirX--;
                }
                //go right and mark the direction as visited for the neighbor
                dirX = x + 1;
                while (dirX < NUM_COLS && data[y][dirX] == target && data[y + 1][dirX] != target)  //check if the next neighbour is part of the same straight line
                {
                    visitedDirectionMap[y][dirX] |= DOWN;
                    dirX++;
                } 
            }
            break;
        case LEFT:
            //check if we are at the border or the next island
            if (x - 1 < 0 || data[y][x - 1] != target)
            {
                sideCount++;
                //mark the direction as visited for self and all up/down neighbors
                visitedDirectionMap[y][x] |= LEFT;
                //go up and mark the direction as visited for the neighbor
                dirY = y - 1;
                while (dirY >= 0 && data[dirY][x] == target && data[dirY][x - 1] != target)  //check if the next neighbour is part of the same straight line
                {
                    visitedDirectionMap[dirY][x] |= LEFT;
                    dirY--;
                }
                //go down and mark the direction as visited for the neighbor
                dirY = y + 1;
                while (dirY < NUM_ROWS && data[dirY][x] == target && data[dirY][x - 1] != target)  //check if the next neighbour is part of the same straight line
                {
                    visitedDirectionMap[dirY][x] |= LEFT;
                    dirY++;
                }
            }
            break;
        case UP:
            //check if we are at the border or the next island
            if (y - 1 < 0 || data[y - 1][x] != target)
            {
                sideCount++;
                //mark the direction as visited for self and all left/right neighbors
                visitedDirectionMap[y][x] |= UP;
                //go left and mark the direction as visited for the neighbor
                dirX = x - 1;
                while (dirX >= 0 && data[y][dirX] == target && data[y - 1][dirX] != target)  //check if the next neighbour is part of the same straight line
                {
                    visitedDirectionMap[y][dirX] |= UP;
                    dirX--;
                }
                //go right and mark the direction as visited for the neighbor
                dirX = x + 1;
                while (dirX < NUM_COLS && data[y][dirX] == target && data[y - 1][dirX] != target)  //check if the next neighbour is part of the same straight line
                {
                    visitedDirectionMap[y][dirX] |= UP;
                    dirX++;
                } 
            }
            break;
        default:
            assert(false);
        }
    }
    

    visitedMap[y][x] = true;
    currentArea++;
    
    // perimeter is the number of edges that are of a different target or out of bounds
    for (int i = 0; i < 4; i++)
    {
        const int nextX = x + dx[i];
        const int nextY = y + dy[i];
        if (IsInBounds(nextX, nextY) || data[nextY][nextX] != target)
            currentPerimeter++;
        else
        {
            floodFillRecursive(nextX, nextY, target, currentArea, currentPerimeter, sideCount);
        }
    }
}

int main(int argc, char* argv[])
{
    //iterate over the data and calculate the area and perimeter of each island, with that we can calulate the price for the fence. the price is the sum of area * perimeter for each island
    uint64_t fencePrice = 0;
    uint64_t fencePriceDiscounted = 0;
    for (int row = 0; row < NUM_ROWS; row++)
    {
        for (int col = 0; col < NUM_COLS; col++)
        {
            if (!visitedMap[row][col])
            {
                const char target = data[row][col];
                int currentArea = 0;
                int currentPerimeter = 0;
                int sides = 0;
                floodFillRecursive(col, row, target, currentArea, currentPerimeter, sides);
                std::cout << "Area '" << target << "': " << currentArea << " Perimeter: " << currentPerimeter << " sides:" << sides << " price: " << currentArea * currentPerimeter << '\n';
                fencePrice += currentArea * currentPerimeter;
                fencePriceDiscounted += currentArea * sides;
            }
        }
    }
    std::cout << "Fence price: " << fencePrice << std::endl;
    std::cout << "Fence price discounted: " << fencePriceDiscounted << std::endl;
    
    return 0;
}
