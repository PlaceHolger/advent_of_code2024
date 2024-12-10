//https://adventofcode.com/2024/day/9

#include <iostream>
#include <string>
#include <vector>

#include "Day9Data.h"

constexpr int EMPTY_SPACE = -666;

//#define IS_PART1

// std::string ReadDataFromFile()
// {
//     std::ifstream file("data.txt");
//     if (!file)
//     {
//         std::cerr << "Unable to open file\n";
//         return "";
//     }
//
//     //Read the whole file into a string
//     static std::string line;
//     std::getline(file, line);
//     return line;
// }

int main(int argc, char* argv[])
{
    const char* data = realData; //ReadDataFromFile;
    const auto NUM_DATA = strlen(data);
    std::vector<int> result;
    result.reserve(NUM_DATA * 5); //rough estimation
    //okay, we iterate over each char of the string, read it as a number (x) and then add alternating file or space to the result-string
    int currentFileId = 0;
    bool isFile = true;
    for (size_t i = 0; i < NUM_DATA; ++i)
    {
        int currentAmount = data[i] - '0';
        if (isFile)
        {
            //add x times the current item to the result
            for (int x = 0; x < currentAmount; ++x)
            {
                result.push_back(currentFileId);
            }
            currentFileId++;
        }
        else
        {
            //add x times the empty space to the result
            for (int x = 0; x < currentAmount; ++x)
            {
                result.push_back(EMPTY_SPACE);
            }
        }
        isFile = !isFile;
    }

    // //test print
    // for (const auto& i : result)
    // {
    //     i == EMPTY_SPACE ? std::cout << "." : std::cout << i;
    // }

#if defined(IS_PART1)
    //now we remove the empty spaces from the result, we do so by filling them with the numbers from the end of the vector
    uint64_t currentPosFromBack = result.size() - 1;
    for (uint64_t i=0; i < result.size() && i < currentPosFromBack; ++i)
    {
        if (result[i] == EMPTY_SPACE)
        {
            while (result[currentPosFromBack] == EMPTY_SPACE)
                currentPosFromBack--;
            result[i] = result[currentPosFromBack];
            currentPosFromBack--;
        }
    }
    result.resize(currentPosFromBack + 1);
#else
    //in part 2 we also fill the empty spaces, but we only move whole file blocks instead of single numbers
    //we first create a list with free blocks, then we start at the end of the vector and move the blocks to the empty spaces
    struct Block
    {
        int index;
        int size;
    };
    std::vector<Block> freeBlocks;
    for (int i = 0; i < result.size(); ++i)
    {
        if (result[i] == EMPTY_SPACE)
        {
            int blockSize = 1;
            while (result[i + blockSize] == EMPTY_SPACE)
            {
                blockSize++;
            }
            freeBlocks.push_back({i, blockSize});
            i += blockSize;
        }
    }
    //we do the same for the data blocks, but start at the end of the vector
    std::vector<Block> dataBlocks;
    for (int i = result.size() - 1; i >= 0; )
    {
        if (result[i] != EMPTY_SPACE)
        {
            int currentId = result[i];
            int blockSize = 1;
            while (i - blockSize > 0 && result[i - blockSize] == currentId)
            {
                blockSize++;
            }
            i -= blockSize;
            dataBlocks.push_back({i + 1, blockSize});
        }
        else
        {
            i--;
        }
    }
    //now we iterate over the data blocks and fill the empty spaces with the data blocks, if a block is too big, we skip it. we move to the first empty space that is large enough (can also be larger, in that case we adjust the block size is the free list)
    for (const auto& dataBlock : dataBlocks)
    {
        for (auto& freeBlock : freeBlocks)
        {
            if (freeBlock.index >= dataBlock.index)
                break;
            
            if (freeBlock.size >= dataBlock.size)
            {
                for (int i = 0; i < dataBlock.size; ++i)
                {
                    result[freeBlock.index + i] = result[dataBlock.index + i];
                    result[dataBlock.index + i] = EMPTY_SPACE;
                }
                freeBlock.size -= dataBlock.size;
                freeBlock.index += dataBlock.size;
                break;
            }
        }
    }
#endif
    // //test print cleaned up string
    // std::cout << '\n' << "After Cleaning: ";
    // for (const auto& i : result)
    // {
    //     i == EMPTY_SPACE ? std::cout << "." : std::cout << i;
    // }

    //now we need to calculate the score, we iterate over the result and calculate the score, for each position its current ID * its position
    uint64_t score = 0;
    for (uint64_t i = 0; i < result.size(); ++i)
    {
        if (result[i] != EMPTY_SPACE)
            score += result[i] * i;
    }
    std::cout << '\n' << "filesystem checksum: " << score << '\n';
    
    return 0;
}
