#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

//#define USE_TEST_DATA
//#define IS_PART2

#include "Day10Data.h"

using namespace std;

struct Vector2
{
    int x;
    int y;

    bool operator==(const Vector2& other) const
    {
        return x == other.x && y == other.y;
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

constexpr int MAP_WIDTH = std::size(map[0]);
constexpr int MAP_HEIGHT = std::size(map);

constexpr Vector2 directions[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// Check if a pos is within bounds
bool isValid(const Vector2& pos)
{
    return pos.x >= 0 && pos.x < MAP_HEIGHT && pos.y >= 0 && pos.y < MAP_WIDTH;
}

void dfs(int x, int y, int currentHeight, unordered_set<Vector2>& visited, vector<Vector2>& reachableNines)
{
    Vector2 newPos = {x, y};
    if (!isValid(newPos)
#if !defined(IS_PART2) //for part2 we want to find all ways to reach the 9
        || visited.find(newPos) != visited.end()
#endif
        || map[x][y] != currentHeight)
    {
        return;
    }

    visited.insert(newPos);

    if (currentHeight == 9)
    {
        reachableNines.push_back(newPos);
        return;
    }

    for (const auto& dir : directions)
    {
        int newX = x + dir.x;
        int newY = y + dir.y;
        dfs(newX, newY, currentHeight + 1, visited, reachableNines);
    }
}

int calculateTrailheadScore(int startX, int startY)
{
    unordered_set<Vector2> visited;
    vector<Vector2> reachableNines;
    dfs(startX, startY, 0, visited, reachableNines);
    return reachableNines.size();
}

int main()
{
    int totalScore = 0;

    for (int i = 0; i < MAP_HEIGHT; ++i)
    {
        for (int j = 0; j < MAP_WIDTH; ++j)
        {
            if (map[i][j] == 0)
            {
                totalScore += calculateTrailheadScore(i, j);
            }
        }
    }

    cout << "Sum of the scores of all trailheads: " << totalScore << endl;

    return 0;
}