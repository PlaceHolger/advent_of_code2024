//https://adventofcode.com/2024/day/2

#include <iterator>

#include "Day2Data.h"

constexpr auto& data = realData;
constexpr int NUM_REPORTS = std::size(data);

//#define IS_PART1 1

bool isReportSafe(const std::vector<int>& report)
{
    size_t numIncrements = 0;
    size_t numDecrements = 0;
    
    for (size_t levelIndex = 1; levelIndex < report.size(); ++levelIndex)
    {
        const int dif = report[levelIndex] - report[levelIndex - 1];
        if (dif >= 1 && dif <= 3)
        {
            numIncrements++;
        }
        else if (dif <= -1 && dif >= -3)
        {
            numDecrements++;
        }
        else return false;
    }
    bool monotonicAndChangesInRange = (numIncrements == report.size() - 1) || (numDecrements == report.size() - 1); //checks for the correct amount of increments or decrements
    return monotonicAndChangesInRange;
}

int main(int argc, char* argv[])
{
    int unsafeReports = 0;
    for (const auto& report : data)
    {
        if (!isReportSafe(report))
#if IS_PART1
            unsafeReports++;
#else
        //lets try bruteforce, when the report is not safe, we remove one element and check if the report is safe.. of course it would be better to remove the element that is causing the issue. But then IsSave would need to return the index of the element that is causing the issue...don't want to refactor that now
        for (int i = 0; i < report.size(); ++i)
        {
            std::vector<int> reportCopy = report;
            reportCopy.erase(reportCopy.begin() + i);
            if (isReportSafe(reportCopy))
            {
                break; //error damping worked
            }
            if (i == report.size() - 1)
            {
                unsafeReports++; //we tried all elements and the report is still not safe
            }
        }
#endif
    }

    printf("Unsafe reports: %d -  safe reports: %d\n", unsafeReports, NUM_REPORTS - unsafeReports);
    return 0;
}
