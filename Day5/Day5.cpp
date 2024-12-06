//https://adventofcode.com/2024/day/5

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <random>
#include <unordered_map>

#include "Day5Data.h"

constexpr bool IS_PART1 = false;

constexpr auto& s_Rules = realDataRules;
constexpr auto& s_Updates = realUpdates;
// constexpr auto& s_Rules = testDataRules;
// constexpr auto& s_Updates = testUpdates;

auto NUM_RULES = std::size(s_Rules);
auto NUM_UPDATES = std::size(s_Updates);
std::unordered_map<int, std::vector<int>> s_PerPageRulesMap;  //maps a pageIndex to the pageIndices which need to be placed after it

static bool isUpdateValid(const std::vector<int>& p_Update)
{
    for (size_t iPage = 0; iPage < p_Update.size(); ++iPage)
    {
        std::unordered_map<int, std::vector<int>>::const_iterator itRule = s_PerPageRulesMap.find(p_Update[iPage]); //where is auto when you need it
        if (itRule != s_PerPageRulesMap.cend())  //so there is a rule for this page
        {
            for (size_t iRule = 0; iRule < itRule->second.size(); ++iRule) //we check now all the following pages if they are in the list
            {
                for (size_t iRemainingPages = iPage+1; iRemainingPages < p_Update.size(); ++iRemainingPages)
                {
                    if (p_Update[iRemainingPages] == itRule->second[iRule])
                    {
                        std::cout << "Rule not matched: Update " /*<< p_Update*/ << ": Page " << p_Update[iPage] << " needs to be placed before page " << s_PerPageRulesMap[p_Update[iPage]][iRule] << '\n';
                        return false;                           
                    }
                }
            }
        }
    }
    return true;
}

int main(int argc, char* argv[])
{
    //this maps contains for each page the rules which pages needs to be placed after it, so 47,53 means page 47 needs to be placed before page 53
    for (int i = 0; i < NUM_RULES; ++i)
    {
        //pageRulesMap[pageRules[i][0]].push_back(pageRules[i][1]);
        s_PerPageRulesMap[s_Rules[i][1]].push_back(s_Rules[i][0]);  //are there duplicates?
    }

    int sumUpdates = 0;
    
    //now we go through all pages and check if the rules are met
    for (size_t iUpdate = 0; iUpdate < NUM_UPDATES; ++iUpdate)
    {
        std::cout << " -- Checking update " << iUpdate << std::endl;
        if (isUpdateValid(s_Updates[iUpdate]))
        {
            //seems like this update is fine, we now add the middle page to our sum
            if (IS_PART1)
                sumUpdates += s_Updates[iUpdate][s_Updates[iUpdate].size() / 2];         
        }
        else
        {
            // //lets first try a brute force approach, shuffle the pages until we find a valid order
            // auto copyOfUpdate = s_Updates[iUpdate];
            // //shuffle it
            // do
            // {
            //     std::shuffle(copyOfUpdate.begin(), copyOfUpdate.end(), std::mt19937(std::random_device()()));
            // } while (!isUpdateValid(copyOfUpdate));

            //nope... bruteforce is too slow :) But found this nice idea, we can simple "sort" the list by applying a custom sorter that checks the rules
            static const auto sorter = [&](int a, int b){ return std::find( s_PerPageRulesMap[a].begin(), s_PerPageRulesMap[a].end(), b) == s_PerPageRulesMap[a].end(); };
            auto copyOfUpdate = s_Updates[iUpdate];
            std::sort(copyOfUpdate.begin(), copyOfUpdate.end(), sorter);
            assert(isUpdateValid(copyOfUpdate));
            if (!IS_PART1)
                sumUpdates += copyOfUpdate[copyOfUpdate.size() / 2];    
        }
    }

    std::cout << "Sum of correct updates: " << sumUpdates << std::endl;
    
    return 0;
}
