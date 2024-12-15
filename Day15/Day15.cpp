
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "Day15Data.h"

constexpr char WALL = '#';
constexpr char BOX = 'O';
constexpr char ROBOT = '@';
constexpr char FREE = '.';

constexpr static auto& data = RealData;
constexpr static auto& moves = RealMoves;

constexpr int MAP_WIDTH = std::size(data[0]);
constexpr int MAP_HEIGHT = std::size(data);
constexpr int NUM_MOVES = std::size(moves) - 1;

struct Vector2
{
    int x;
    int y;
    
    Vector2& operator+=(const Vector2& vector2)
    {
        x += vector2.x;
        y += vector2.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& vector2)
    {
        x -= vector2.x;
        y -= vector2.y;
        return *this;
    }

    Vector2 operator+(const Vector2& vector2) const
    {
        return {x + vector2.x, y + vector2.y};
    }
};

Vector2 s_RobotPosition;


bool IsInBounds(const Vector2& pos)
{
    return pos.x >= 0 && pos.x < MAP_WIDTH && pos.y >= 0 && pos.y < MAP_HEIGHT;
}

char GetTile(const Vector2& pos)
{
    return data[pos.y][pos.x];
}

void SetTile(const Vector2& pos, char tile)
{
    data[pos.y][pos.x] = tile;
}

void FindRobotPosition()
{
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            if (data[y][x] == ROBOT)
            {
                s_RobotPosition = {x, y};
                SetTile(s_RobotPosition, FREE); //remove the robot from the map, since we store the position in a separate variable
                return;
            }
        }
    }
}

static Vector2 GetMoveDIrection(char move)
{
    switch (move)
    {
    case '<':
        return {-1, 0};
    case '>':
        return {1, 0};
    case '^':
        return {0, -1};
    case 'v':
        return {0, 1};
    default:
        assert(false);
    }
    return {0, 0};
}

void MoveRobot(char move)
{
    //new approach: the robot always just moves one step, if there is a box in front of it, it will move the box one step in the same direction
    const Vector2 moveDir = GetMoveDIrection(move);
    const Vector2 nextPos = s_RobotPosition + moveDir;
    if (GetTile(nextPos) == WALL)
        return;  //we cant move
    if (GetTile(nextPos) == BOX)
    {
        Vector2 boxPos = nextPos + moveDir;
        //now the movement starts, we stop when we hit a wall or an empty space. we remmber that we can any amount of boxes
        while (true)
        {
            if (GetTile(boxPos) == WALL)
                return; //we cant move the box(es)
            if (GetTile(boxPos) == FREE)
            {
                SetTile(boxPos, BOX); //move the box
                SetTile(nextPos, FREE); //remove the box from the previous positionS
                break;
            }
            boxPos += moveDir;
        }
    }
    s_RobotPosition = nextPos;
}

void PrintMap()
{
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            if (s_RobotPosition.x == x && s_RobotPosition.y == y)
                std::cout << ROBOT;
            else
                std::cout << data[y][x];
        }
        std::cout << "\n";
    }
}

int main(int argc, char* argv[])
{
    //Find start position of robot
    FindRobotPosition();
    //now we can start moving the robot
    for (int i = 0; i < NUM_MOVES; ++i)
    {
        const char move = moves[i];
        MoveRobot(move);
        std::cout << "Move " << i << ": " << move << '\n';
    }
    
    PrintMap();

    //now we calulate the GPS value for each box and sum them up
    int sum = 0;
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            if (data[y][x] == BOX)
            {
                sum += y * 100 + x;
            }
        }
    }
    std::cout << "GPS sum: " << sum << '\n';
    
    return 0;
}
