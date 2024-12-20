// --- Day 20: Race Condition ---

//#define USE_TEST_DATA
constexpr int CHEAT_SAVE_THRESHOLD = 100; //how many picoseconds we want to save by using a cheat before we count it for the solution

#include "Day20Data.h"

#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

struct PathNode;

struct Vector2
{
    int x;
    int y;

    bool operator==(const Vector2& vector2) const
    {
        return x == vector2.x && y == vector2.y;
    }

    bool operator!=(const Vector2& vector2) const
    {
        return x != vector2.x || y != vector2.y;
    }
};

Vector2 s_StartPos;
Vector2 s_EndPos;

constexpr const char* PATH_COLOR = "\033[32m";
constexpr const char* WALL_COLOR = "\033[38;5;94m";
//constexpr const char* REMOVED_WALL_COLOR = "\033[38;5;196m";
constexpr const char* DEFAULT_COLOR = "\033[0m";
constexpr const char* SPECIAL_COLOR = "\033[38;5;196m";

constexpr char PATH_TILE = 'O';
constexpr char WALL_TILE = '#';
constexpr char START_TILE = 'S';
constexpr char END_TILE = 'E';

static char GetTile(const Vector2& pos)
{
    return s_Map[pos.y][pos.x];
}

void FindStartAndEnd()
{
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            const auto currentPos = Vector2{ x, y };
            if (GetTile(currentPos) == START_TILE)
            {
                s_StartPos = currentPos;
            }
            else if (GetTile(currentPos) == END_TILE)
            {
                s_EndPos = currentPos;
            }
        }
    }
}

static void PrintMap(const std::vector<PathNode>& path)
{
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            Vector2 pos = {x, y};
            if (std::find(path.begin(), path.end(), pos) != path.end())
            {
                if (pos == s_StartPos || pos == s_EndPos)
                    std::cout << SPECIAL_COLOR << GetTile(pos);
                else
                    std::cout << PATH_COLOR << PATH_TILE;
            }
            //TODO: removed wall: else if
            else
            {
                const char tile = GetTile(pos);
                if (tile == WALL_TILE)
                    std::cout << WALL_COLOR << tile;
                else
                    std::cout << DEFAULT_COLOR << tile;
            }
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}

static bool IsInBounds(const Vector2& pos)
{
    return pos.x >= 0 && pos.x < MAP_WIDTH && pos.y >= 0 && pos.y < MAP_HEIGHT;
}

//do a djikstra to find the shortest path
Vector2 s_Directions[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; //right,down,left,up

struct PathNode
{
    Vector2 pos; // Position in the map.
    uint32_t distance = -1;   // Distance from the start position, -1 means not visited
    PathNode* pPreviousNode = nullptr; // Previous node in the path, nullptr means not visited

    bool IsVisited() const { return pPreviousNode != nullptr; }

    bool operator<(const PathNode& other) const
    {
        return distance > other.distance;
    }

    bool operator==(const Vector2& other) const
    {
        return pos == other;
    }
};

PathNode pathNodes[MAP_HEIGHT][MAP_WIDTH];  //posY, posX

bool IsValidMovePos(Vector2 nextPos)
{
    if (!IsInBounds(nextPos) || GetTile(nextPos) == WALL_TILE)
        return false;
    return true;
}

static std::vector<PathNode>& FindPath(Vector2 startPos, Vector2 endPos)
{
    //clear the path nodes
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            pathNodes[y][x].distance = -1;
            pathNodes[y][x].pPreviousNode = nullptr;
            pathNodes[y][x].pos = {x, y}; //todo: only do once
        }
    }
    static std::vector<PathNode> path;
    path.clear();
    
    std::priority_queue<PathNode> queue;
    pathNodes[startPos.y][startPos.x].distance = 0;
    queue.push(pathNodes[startPos.y][startPos.x]);

    while (!queue.empty())
    {
        PathNode currentNode = queue.top();
        queue.pop();

        const Vector2& currentPos = currentNode.pos;

        if (currentPos == endPos)
        {
            while (currentNode.pos != startPos) //backtrack the path
            {
                path.push_back(currentNode);
                currentNode = *currentNode.pPreviousNode;
            }
            path.push_back(currentNode);
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const auto& direction : s_Directions)
        {
            Vector2 nextPos = {currentPos.x + direction.x, currentPos.y + direction.y};

            if (!IsValidMovePos(nextPos) || pathNodes[nextPos.y][nextPos.x].IsVisited())
                continue;

            uint32_t newDistance = currentNode.distance + 1;

            if (newDistance < pathNodes[nextPos.y][nextPos.x].distance)
            {
                pathNodes[nextPos.y][nextPos.x].distance = newDistance;
                //pathNodes[nextPos.y][nextPos.x].pos = nextPos;
                pathNodes[nextPos.y][nextPos.x].pPreviousNode = &pathNodes[currentPos.y][currentPos.x];
                queue.push(pathNodes[nextPos.y][nextPos.x]);
            }            
        }
    }

    return path;
}

static uint32_t FindCheats(std::vector<PathNode>& path, int savedSteps)
{
    uint32_t numCheats = 0;

    //okay, we follow the path and check if we can cheat, if so, we add compare the saved steps with the threshold
    for (size_t i = 0; i < path.size(); i++)
    {
        const auto& currentNode = path[i];
        for (const auto& direction : s_Directions)
        {
            //when cheating, we can move two steps in the same direction (ignoring walls in between)
            Vector2 cheatPos = {currentNode.pos.x + direction.x + direction.x, currentNode.pos.y + direction.y + direction.y};
            
            if (!IsValidMovePos(cheatPos)) //the target must be a valid move
                continue;

            //we can cheat, let's see how many steps we save (if any)
            int distanceWithCheat = currentNode.distance + 2;
            int distanceWithoutCheat = 0;
            for (size_t j = i + 1; j < path.size(); j++) //we only need to check the remaining path, we never want to cheat backwards. This can probably be optimized by using a better structure to find nearby positions on the path without iterating over the whole path
            {
                if (path[j].pos == cheatPos)
                {
                    distanceWithoutCheat = path[j].distance;
                    break;
                }
            }
            if (distanceWithoutCheat - distanceWithCheat >= savedSteps)
            {
                numCheats++;
            }
        }
    }

    return numCheats;
}

int main(int argc, char* argv[])
{
    FindStartAndEnd();
    auto& path = FindPath(s_StartPos, s_EndPos);
    //okay, now we have the (only) path to the end, let's find all possible cheat positions
    int numCheats = FindCheats(path, CHEAT_SAVE_THRESHOLD);
    PrintMap(path);
    
    std::cout << "Number of cheats: " << numCheats << std::endl;
    
    return 0;
}
