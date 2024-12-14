// --- Day 14: Restroom Redoubt ---

//https://adventofcode.com/2024/day/14

#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Vector2_i64
{
    int64_t x;
    int64_t y;
};

struct Robot
{
    Vector2_i64 position;
    Vector2_i64 velocity;
};

constexpr int NUM_SIMULATED_SECONDS = 100;

//#define USE_TEST_DATA

//test data
#if defined(USE_TEST_DATA)
constexpr int MAP_WIDTH = 11;
constexpr int MAP_HEIGHT = 7;

std::vector<Robot> robots =
{
    {{0, 4}, {3, -3}},
    {{6, 3}, {-1, -3}},
    {{10, 3}, {-1, 2}},
    {{2, 0}, {2, -1}},
    {{0, 0}, {1, 3}},
    {{3, 0}, {-2, -2}},
    {{7, 6}, {-1, -3}},
    {{3, 0}, {-1, -2}},
    {{9, 3}, {2, 3}},
    {{7, 3}, {-1, 2}},
    {{2, 4}, {2, -3}},
    {{9, 5}, {-3, -3}}
};
#else
constexpr int MAP_WIDTH = 101;
constexpr int MAP_HEIGHT = 103;
static std::vector<Robot> robots;
#endif

static void MoveRobots(std::vector<Robot>& robots, int64_t seconds)
{
    for (auto& robot : robots)
    {
        robot.position.x += robot.velocity.x * seconds;
        robot.position.y += robot.velocity.y * seconds;
    }
    //wrap around the edges
    for (auto& robot : robots)
    {
        if (robot.position.x < 0)
            robot.position.x += MAP_WIDTH;
        if (robot.position.x >= MAP_WIDTH)
            robot.position.x -= MAP_WIDTH;
        if (robot.position.y < 0)
            robot.position.y += MAP_HEIGHT;
        if (robot.position.y >= MAP_HEIGHT)
            robot.position.y -= MAP_HEIGHT;
    }
}

static void ReadRobotsFromFile()
{
    // Read the robots from file data.txt //thanks GPT ; )
    std::ifstream file("data.txt");
    if (file.is_open())
    {
        robots.clear();
        std::string line;
        Robot robot;
        while (std::getline(file, line))
        {
            if (line.find("p=") != std::string::npos)
            {
                int result = sscanf_s(line.c_str(), "p=%lld,%lld v=%lld,%lld", &robot.position.x, &robot.position.y, &robot.velocity.x, &robot.velocity.y);
                assert(result == 4);
                robots.push_back(robot);
            }
        }
    }
}

static void PrintMap()
{
    //print the robots
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            int foundRobot = 0;
            for (const auto& robot : robots)
            {
                if (robot.position.x == x && robot.position.y == y)
                {
                    foundRobot++;
                }
            }
            if (foundRobot > 0)
                std::cout << foundRobot;
            else
                std::cout << '.';
        }
        std::cout << "\n";
    }
}

int main(int argc, char* argv[])
{
    //simple test, we just start with one robot and move it for 5 seconds, p=2,4 v=2,-3
#if !defined(USE_TEST_DATA)
    ReadRobotsFromFile();
#endif
    
    for (int i = 0; i < NUM_SIMULATED_SECONDS; ++i)
    {
        std::cout << "After " << i + 1 << " seconds: \n";
        MoveRobots(robots, 1);
        //PrintMap();
    }

    //After 100 seconds, we can count the number of robots in each quadrant
    //and multiply them together to get the safety factor
    int numRobotsQuadrant[4] = { 0, 0, 0, 0 };
    //half the map width and height (rounded down)
    constexpr int halfWidth = MAP_WIDTH / 2;
    constexpr int halfHeight = MAP_HEIGHT / 2;
    //count the robots, if a robot is exactly in the middle, it doesn't count
    for (const auto& robot : robots)
    {
        if (robot.position.x < halfWidth && robot.position.y < halfHeight)
            numRobotsQuadrant[0]++;
        else if (robot.position.x > halfWidth && robot.position.y < halfHeight)
            numRobotsQuadrant[1]++;
        else if (robot.position.x < halfWidth && robot.position.y > halfHeight)
            numRobotsQuadrant[2]++;
        else if (robot.position.x > halfWidth && robot.position.y > halfHeight)
            numRobotsQuadrant[3]++;
    }
    const int safetyFactor = numRobotsQuadrant[0] * numRobotsQuadrant[1] * numRobotsQuadrant[2] * numRobotsQuadrant[3];
    std::cout << "Safety factor: " << safetyFactor << std::endl;
    
    return 0;
}
