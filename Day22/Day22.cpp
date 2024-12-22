// --- Day 22: Monkey Market ---

#include <cstdint>
#include <iostream>

//#define USE_TEST_DATA
//#define IS_PART1

#include <cassert>
#include <unordered_map>

#include "Day22Data.h"

static int CalcNextSecretNumber(int64_t secretNumber)  //our pseudorandom number generator
{
    secretNumber = (secretNumber * 64) ^ secretNumber;  //*64 , mix
    secretNumber %= 16777216;  //prune
    secretNumber = (secretNumber / 32) ^ secretNumber; // :32, mix
    secretNumber %= 16777216;  //prune
    secretNumber = (secretNumber * 2048) ^ secretNumber;  //*2048, mix
    secretNumber %= 16777216;  //prune
    return static_cast<int>(secretNumber);
}

static int hashChanges(const std::list<int8_t>& changesList)  //compute a hash from the last 4 changes
{
    auto it = changesList.begin();
    uint8_t num1 = *it++;
    uint8_t num2 = *it++;
    uint8_t num3 = *it++;
    uint8_t num4 = *it;
    //shift the numbers to the correct position
    const int hash = num1 | (num2 << 8) | (num3 << 16) | (num4 << 24);
    
    return hash;
}

static void Unhash(const int hash, int8_t* pOutValues)  //extract the last 4 changes from the hash
{
    //const int hash = num1 | (num2 << 8) | (num3 << 16) | (num4 << 24);
    pOutValues[0] = hash & 0xFF;
    pOutValues[1] = (hash >> 8) & 0xFF;
    pOutValues[2] = (hash >> 16) & 0xFF;
    pOutValues[3] = (hash >> 24) & 0xFF;
}

int main(int argc, char* argv[])
{
#if defined (IS_PART1)
    std::vector<int> secretNumbers; //2000th off all buyers
    secretNumbers.reserve(NUM_DATA);
    for (int secretNumber : data)
    {
        for (int i = 0; i < 2000; i++)
        {
            secretNumber = CalcNextSecretNumber(secretNumber);
        }
        secretNumbers.push_back(secretNumber);
    }
    uint64_t sum = 0;
    for (const auto secretNumber : secretNumbers)
    {
        sum += secretNumber;
    }
    std::cout << "Day 22 part 1 | Sum of the 2000th secret number generated by each buyer: " << sum << '\n';

#else

    //okay for part2 we check the last 4 changes in the numbers, and store the current value in a map (if no entry exists).
    //this way we now for each change the value of the offer
    std::unordered_map<int, int> globalOfferMap; //maps the (hash) of the last 4 changes to the sum of the offers (for all buyers)
    for (int secretNumber : data)
    {
        std::unordered_map<int, uint8_t> offerMap; //maps the (hash) of the last 4 changes to the current offer (for current buyer)
        std::list<int8_t> changesQueue; //stores the last 4 changes (potential for optimize)

        int lastSecret = secretNumber;

        for (int i = 1; i < 4; i++) //fill the queue with the first 4 changes (no need to store the offers in the map)
        {
            const int newSecret = CalcNextSecretNumber(lastSecret);
            const int8_t offer = newSecret % 10;
            int8_t change = offer - lastSecret % 10;
            changesQueue.push_back(change);            
            lastSecret = newSecret;
        }
        //for the rest of the 2000 changes we calculate the offer and store it in the map
        for (int i = 4; i < 2000; i++)
        {
            const int newSecret = CalcNextSecretNumber(lastSecret);
            const int8_t offer = newSecret % 10;
            int8_t change = offer - lastSecret % 10;
            changesQueue.push_back(change);
            assert(changesQueue.size() == 4);
            int hash = hashChanges(changesQueue);
            if (offerMap.find(hash) == offerMap.end()) //add offer if not already in the map
                offerMap[hash] = offer;
            lastSecret = newSecret;
            changesQueue.pop_front();
        }
        //now we add the offers of the current buyer to the global map
        for (const auto& value : offerMap)
        {
            auto it = globalOfferMap.find(value.first);
            if (it == globalOfferMap.end())
                globalOfferMap[value.first] = value.second;
            else
                it->second += value.second;
        }
            
    }
    //the solution is now the largest value in the global map
    int maxOffer = 0;
    int maxOfferChangesHash = 0;
    for (const auto& value : globalOfferMap)
    {
        maxOfferChangesHash = value.first;
        maxOffer = std::max(maxOffer, value.second);
    }
    //extract the last 4 changes from the hash
    int8_t last4Changes[4];
    Unhash(maxOfferChangesHash, last4Changes);
    std::cout << "Day 22 part 2 | Max offer: " << maxOffer << " for the last 4 changes: " << (int)last4Changes[3] << "," << (int)last4Changes[2] << "," << (int)last4Changes[1] << "," << (int)last4Changes[0] << '\n';

#endif

    return 0;
}
