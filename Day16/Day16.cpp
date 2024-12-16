//#define TEST_DATA

#include <iostream>
#include <iterator>
#include <queue>
#include <vector>

#include "Day16Data.h"

#define DEBUG_OUTPUT_PATH

struct Vector2
{
    int x;
    int y;

    bool operator == (const Vector2& other) const
    {
        return x == other.x && y == other.y;
    }
};

enum class Direction
{
    Right,
    Down,
    Left,
    Up
};

constexpr Vector2 directions[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
constexpr int NUM_DIRECTIONS = std::size(directions);

constexpr int NUM_ROWS = std::size(map);
constexpr int NUM_COLS = std::size(map[0]) - 1;
//we always start at bottom left
constexpr Vector2 START_POSITION = { 1, NUM_ROWS - 2 };
constexpr Vector2 END_POSITION = { NUM_COLS - 2, 1 };

char GetTile(const Vector2& pos)
{
    return map[pos.y][pos.x];
}

static int distances[NUM_ROWS][NUM_COLS] = {{0x7FFFFFFF}};

struct PathPosition
{
    Vector2 position;
    Vector2 previousPosition;
    
    int getCost() const
    {
        return distances[position.y][position.x];
    }

    bool operator < (const PathPosition& other) const
    {
        return getCost() > other.getCost();
    }
};

#if defined(DEBUG_OUTPUT_PATH)
//Debugging helper, to be able to print the path after we found it, we need keep the visited positions
std::vector<PathPosition> visitedPositions;
std::vector<Vector2> positionsOnPath;
void CreatePathToStart(Vector2 pos)
{
    if (pos == START_POSITION)
    {
        positionsOnPath.push_back(pos);
        return;
    }
    for (const auto& pathPos : visitedPositions)
    {
        if (pathPos.position == pos)
        {
            positionsOnPath.push_back(pathPos.position);
            CreatePathToStart(pathPos.previousPosition);
            break;
        }
    }
}

const std::string DEFAULT = "\033[0m";
const std::string VISITED = "\033[32m"; // "\033[38;5;94m";
const std::string EMPTY = "\033[38;5;15m";
const std::string OBSTACLE = "\033[38;5;94m";
void PrintMapWithPath()
{
    for (int y = 0; y < NUM_ROWS; ++y)
    {
        for (int x = 0; x < NUM_COLS; ++x)
        {
            Vector2 pos = { x, y };
            if (std::find(positionsOnPath.begin(), positionsOnPath.end(), pos) != positionsOnPath.end())
            {
                std::cout << VISITED << 'x';
            }
            else
            {
                char tile = GetTile(pos);
                if (tile == '#')
                    std::cout << OBSTACLE << tile;
                else if (tile == '.')
                    std::cout << EMPTY << tile;
                else
                    std::cout << DEFAULT << tile;
            }
        }
        std::cout << '\n';
    }
}
#endif

//djikstra. where moving forward costs 1, and changing direction costs 1000
int FindPath(Vector2 startPos, Vector2 endPos)
{
    memset(distances, 0x7f, sizeof(distances));
    bool visited[NUM_ROWS][NUM_COLS] = { {false}};
    
    //initialize the queue
    std::priority_queue<PathPosition> queue;
    PathPosition startPath = { startPos, startPos };
    distances[startPos.y][startPos.x] = 0;
    queue.push(startPath);

    Direction currentDirection = Direction::Right;

    while (!queue.empty())
    {
        PathPosition currentPathPos = queue.top();
        //update the current direction
        if (currentPathPos.position.x > currentPathPos.previousPosition.x)
            currentDirection = Direction::Right;
        else if (currentPathPos.position.x < currentPathPos.previousPosition.x)
            currentDirection = Direction::Left;
        else if (currentPathPos.position.y > currentPathPos.previousPosition.y)
            currentDirection = Direction::Down;
        else if (currentPathPos.position.y < currentPathPos.previousPosition.y)
            currentDirection = Direction::Up;
        
        Vector2& currentPos = currentPathPos.position;
        queue.pop();
#if defined(DEBUG_OUTPUT_PATH)
        visitedPositions.push_back(currentPathPos);
#endif

        //check if we reached the end
        if (currentPos == endPos)
        {
            return currentPathPos.getCost();
        }

        //mark current position as visited
        visited[currentPos.y][currentPos.x] = true;

        //check all 4 directions
        for (int i = 0; i < NUM_DIRECTIONS; ++i)
        {
            Vector2 nextPos = { currentPos.x + directions[i].x, currentPos.y + directions[i].y };

            //check if we visited this position before or if it is a wall
            if (visited[nextPos.y][nextPos.x] || GetTile(nextPos) == '#')
                continue;

            //calculate the new distance
            int newDistance = currentPathPos.getCost() + 1;
            if (static_cast<int>(currentDirection) != i)
            {
                newDistance += 1000;
            }
            
            if (newDistance < distances[nextPos.y][nextPos.x])
            {
                distances[nextPos.y][nextPos.x] = newDistance;
                PathPosition nextPath = { nextPos, currentPos };
                queue.push(nextPath);
            }
        }
    }

    return -1;    
}

int main(int argc, char* argv[])
{
    //okay, now we have to find the shortest path from S to E
    //since it is a maze, i guess dijkstra should work just fine
    int lowestCost = FindPath(START_POSITION, END_POSITION);
#if defined(DEBUG_OUTPUT_PATH)
    CreatePathToStart(END_POSITION);
    PrintMapWithPath();
#endif
    std::cout << "Lowest cost: " << lowestCost << '\n';
    
    return 0;
}
