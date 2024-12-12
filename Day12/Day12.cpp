//https://adventofcode.com/2024/day/12

//#define USE_TEST_DATA

#include <cstdint>
#include <iostream>

#include "Day12Data.h"
constexpr int NUM_ROWS = std::size(data);
constexpr int NUM_COLS = std::size(data[0]) - 1;
//constexpr char VISITED = '#';
bool visitedMap[NUM_ROWS][NUM_COLS] = {{false}};

// 4-way connectivity, right, down, left, up
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

bool IsInBounds(const int x, const int y)
{
    return x < 0 || x >= NUM_COLS || y < 0 || y >= NUM_ROWS;
}

void floodFillRecursive(const int x, const int y, const int target, int& currentArea, int& currentPerimeter)
{
    if (IsInBounds(x,y) || data[y][x] != target || visitedMap[y][x])
    {
        return;
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
            floodFillRecursive(nextX, nextY, target, currentArea, currentPerimeter);
        }
    }
}

int main(int argc, char* argv[])
{
    //iterate over the data and calculate the area and perimeter of each island, with that we can calulate the price for the fence. the price is the sum of area * perimeter for each island
    uint64_t fencePrice = 0;
    for (int row = 0; row < NUM_ROWS; row++)
    {
        for (int col = 0; col < NUM_COLS; col++)
        {
            if (!visitedMap[row][col])
            {
                const char target = data[row][col];
                int currentArea = 0;
                int currentPerimeter = 0;
                floodFillRecursive(col, row, target, currentArea, currentPerimeter);
                std::cout << "Area '" << target << "': " << currentArea << " Perimeter: " << currentPerimeter << " price: " << currentArea * currentPerimeter << '\n';
                fencePrice += currentArea * currentPerimeter;
            }
        }
    }
    std::cout << "Fence price: " << fencePrice << std::endl;
    
    return 0;
}
