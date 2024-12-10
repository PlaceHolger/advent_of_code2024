#include <iostream>
#include <vector>
#include <set>

//#define USE_TEST_DATA

#include <unordered_set>

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

    bool operator<(const Vector2& other) const
    {
        return x < other.x || (x == other.x && y < other.y);
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

void dfs(int x, int y, int currentHeight, unordered_set<Vector2>& visited, set<Vector2>& reachableNines)
{
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT || visited.count({x, y}) || map[x][y] != currentHeight)
    {
        return;
    }

    visited.insert({x, y});

    if (currentHeight == 9)
    {
        reachableNines.insert({x, y});
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
    set<Vector2> reachableNines;
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