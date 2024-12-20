// --- Day 20: Race Condition ---

#define USE_TEST_DATA
constexpr int CHEAT_SAVE_THRESHOLD = 50; //how many picoseconds we want to save by using a cheat before we count it for the solution

#include "Day20Data.h"

#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <map>

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

template <>
struct std::hash<Vector2>
{
    size_t operator()(const Vector2& v) const noexcept
    {
        return v.x * 1000 + v.y;
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

std::map<int, int> debug_count_map;  //for debugging, we count the number of cheats for the saved steps

static uint32_t FindCheats(std::vector<PathNode>& path, int savedSteps)
{
    //since we are going to check a lot of positions on the path, we transfer it to a unordered_map for faster lookup
    std::unordered_map<Vector2, PathNode> pathMap;
    for (const auto& node : path)
    {
        pathMap[node.pos] = node;
    }
    
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
            if (pathMap.find(cheatPos) != pathMap.end())
            {
                distanceWithoutCheat = pathMap[cheatPos].distance; //original distance, might also include positions back on the track where we came from.
            }
            if (distanceWithoutCheat - distanceWithCheat >= savedSteps)
            {
                numCheats++;
            }
        }
    }

    return numCheats;
}

static uint64_t FindCheatsN(std::vector<PathNode>& path, const int savedSteps, const int numFieldsToCheck)
{
    //since we are going to check a lot of positions on the path, we transfer it to a unordered_map for faster lookup
    std::unordered_map<Vector2, PathNode> pathMap;
    for (const auto& node : path)
    {
        pathMap[node.pos] = node;
    }
    
    //okay almost the same as FindCheat, but we are allowed to jump to any field that is reachable in numFieldsToCheck steps (manhattan distance). we can also use less steps
    uint64_t numCheats = 0;

    //again we follow the path and for each node we check all reachable nodes in numFieldsToCheck steps
    for (size_t i = 0; i < path.size(); i++)
    {
        const auto& currentNode = path[i];
        Vector2 xRangeToCheck = {std::max(0, currentNode.pos.x - numFieldsToCheck), std::min(MAP_WIDTH, currentNode.pos.x + numFieldsToCheck)};
        Vector2 yRangeToCheck = {std::max(0, currentNode.pos.y - numFieldsToCheck), std::min(MAP_HEIGHT, currentNode.pos.y + numFieldsToCheck)};

        //check all reachable nodes in range
        for (int y = yRangeToCheck.x; y < yRangeToCheck.y; y++)
        {
            for (int x = xRangeToCheck.x; x < xRangeToCheck.y; x++)
            {
                //check manhattan distance
                const int manhattenDistance = abs(x - currentNode.pos.x) + abs(y - currentNode.pos.y);
                if (manhattenDistance > numFieldsToCheck)
                    continue;
                
                Vector2 cheatPos = {x, y};
                if (!IsValidMovePos(cheatPos)) //the target must be a valid move
                    continue;

                //we can cheat, let's see how many steps we save (if any)
                int distanceWithCheat = currentNode.distance + manhattenDistance;
                int distanceWithoutCheat = 0;
                if (pathMap.find(cheatPos) != pathMap.end())
                {
                    distanceWithoutCheat = pathMap[cheatPos].distance; //original distance, might also include positions back on the track where we came from.
                }
                if (distanceWithoutCheat - distanceWithCheat >= savedSteps)
                {
                    numCheats++;
                    debug_count_map[distanceWithoutCheat - distanceWithCheat] = debug_count_map[distanceWithoutCheat - distanceWithCheat] + 1;
                }
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
    //int numCheats = FindCheats(path, CHEAT_SAVE_THRESHOLD);
    uint64_t numCheats = FindCheatsN(path, CHEAT_SAVE_THRESHOLD, 20);
    //PrintMap(path);

    for (const auto& value : debug_count_map)
    {
        std::cout << "Key: " << value.first << " Value: " << value.second << std::endl;
    }
    
    std::cout << "Number of cheats: " << numCheats << std::endl;
    
    return 0;
}
