#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//https://adventofcode.com/2024/day/4

static std::vector<std::string> s_Data;

bool ReadData()
{
    std::ifstream file("Day4TestData.txt"); //Day4RealData.txt // Day4TestData.txt
    if (!file)
        {
        std::cerr << "Unable to open file\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        s_Data.emplace_back(line);
    }
}

int main(int argc, char* argv[])
{
    ReadData();

    const int NUM_ROWS = s_Data.size();
    const int NUM_COLS = s_Data[0].size();
    constexpr char SEARCH_WORD[] = "XMAS";
    constexpr int SEARCH_WORD_LEN = sizeof(SEARCH_WORD) - 1;

    const int dy[] = {0, 1, 1, 1, 0, -1, -1, -1}; //y-axis: starting with: right, right-down, down, down-left...
    const int dx[] = {1, 1, 0, -1, -1, -1, 0, 1}; //x-axis

    // the search word can be in any direction, so we need to check all 8 directions
    int count = 0;
    for (int row = 0; row < NUM_ROWS; ++row)
    {
        for (int col = 0; col < NUM_COLS; ++col)
        {
            if (s_Data[row][col] == SEARCH_WORD[0])
            {
                // check all 8 directions
                for (int dir = 0; dir < 8; ++dir)
                {
                    int k;
                    int rd = row + dy[dir]; // row direction
                    int cd = col + dx[dir]; // column direction

                    // First character is already checked, match remaining characters
                    for (k = 1; k < SEARCH_WORD_LEN; ++k)
                    {
                        // If out of bound break
                        if (rd >= NUM_ROWS || rd < 0 || cd >= NUM_COLS || cd < 0)
                            break;

                        // If not matched, break
                        if (s_Data[rd][cd] != SEARCH_WORD[k])
                            break;

                        // Moving in particular direction
                        rd += dy[dir];
                        cd += dx[dir];
                    }

                    // If all character matched, then value of must
                    // be equal to length of search word
                    if (k == SEARCH_WORD_LEN)
                        count++;
                }
            }
        }
    }

    std::cout << "Findings: " << count << std::endl;
    
    return 0;
}
