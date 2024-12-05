//https://adventofcode.com/2024/day/5

#include <iostream>
#include <unordered_map>

#include "Day5Data.h"

int main(int argc, char* argv[])
{
    // constexpr auto& pageRules = testDataRules;
    // constexpr auto& pages = testUpdates;
    constexpr auto& pageRules = realDataRules;
    constexpr auto& pages = realUpdates;
    auto NUM_RULES = std::size(pageRules);
    auto NUM_UPDATES = std::size(pages);
    
    //this maps contains for each page the rules which pages needs to be placed after it, so 47,53 means page 47 needs to be placed before page 53
    std::unordered_map<int, std::vector<int>> pageRulesMap;
    for (int i = 0; i < NUM_RULES; ++i)
    {
        //pageRulesMap[pageRules[i][0]].push_back(pageRules[i][1]);
        pageRulesMap[pageRules[i][1]].push_back(pageRules[i][0]);  //are there duplicates?
    }

    int sumCorrectUpdates = 0;
    
    //now we go through all pages and check if the rules are met
    for (size_t i = 0; i < NUM_UPDATES; ++i)
    {
        for (size_t j = 0; j < pages[i].size(); ++j)
        {
            std::unordered_map<int, std::vector<int>>::const_iterator itRule = pageRulesMap.find(pages[i][j]); //where is auto when you need it
            if (itRule != pageRulesMap.cend())  //so there is a rule for this page
            {
                for (size_t k = 0; k < itRule->second.size(); ++k) //we check now all of the following pages if they are in the list
                {
                    for (size_t l = j+1; l < pages[i].size(); ++l)
                    {
                        if (pages[i][l] == itRule->second[k])
                        {
                            std::cout << "Rule not matched: Update " << i << ": Page " << pages[i][j] << " needs to be placed before page " << pageRulesMap[pages[i][j]][k] << std::endl;
                            //okay so we found a page that does not meet the rule, so we continue with the next update
                           goto nextPage;                           
                        }
                    }
                }
            }
        }
        //seems like this update is fine, we now add the middle page to our sum
        sumCorrectUpdates += pages[i][pages[i].size() / 2];
        nextPage: ;
    }

    std::cout << "Sum of correct updates: " << sumCorrectUpdates << std::endl;
    
    return 0;
}
