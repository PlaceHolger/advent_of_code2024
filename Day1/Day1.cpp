#include <algorithm>
#include <cstdio>
#include <vector>
#include <unordered_map>

#include "Day1Input.h"

//https://adventofcode.com/2024/day/1

constexpr bool isPart1 = false;

int main(int argc, char* argv[])
{
    constexpr int NUM_DATA = std::size(data);

    if (isPart1)
    {
        std::vector<int> list1(NUM_DATA);
        std::vector<int> list2(NUM_DATA);
    
        for (int i = 0; i < NUM_DATA; i++)
        {
            list1[i] = data[i][0];
            list2[i] = data[i][1];
        }
        //sort lists
        std::sort(list1.begin(), list1.end());
        std::sort(list2.begin(), list2.end());
    
        int64_t totalDiff = 0;
    
        for (int i = 0; i < NUM_DATA; i++)
        {
            int diff = abs(list2[i] - list1[i]);
            totalDiff += diff;
            printf("list 1: %d list 2:%d diff:%d totalDiff:%lld\n", list1[i], list2[i], diff, totalDiff);
        }
        printf("Total diff: %lld\n", totalDiff);
    }
    else
    {
        std::unordered_map<int, uint64_t> occurrences;
        //iterate over data and count occurrences in the second column
        for (const auto i : data)
        {
            occurrences[i[1]]++;
        }
        uint64_t similarityValue = 0;
        for (const auto i : data)
        {
            similarityValue += i[0] * occurrences[i[0]];
        }
        printf("Similarity value: %llu\n", similarityValue);
    }
    
    return 0;
}
