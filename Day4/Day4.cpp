#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//https://adventofcode.com/2024/day/4

constexpr bool IS_PART1 = false;

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

void Part1_FindXMAS()
{
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
}

void Part2_FindXMas()
{
    //here we can find one of these 4 patterns: (where . can be any other character)
    //  M.S		S.S		S.M		M.M                                            
    //  .A.     .A.     .A.     .A.                        
    //  M.S     M.M     S.M     S.S
    //approach first we start looking for an A and then check the 4 diagonals for the other characters

    const int NUM_ROWS = s_Data.size();
    const int NUM_COLS = s_Data[0].size();

    int count = 0;
    for (int row = 1; row < NUM_ROWS - 1; ++row)
    {
        for (int col = 1; col < NUM_COLS - 1; ++col)
        {
            if (s_Data[row][col] == 'A') //okay, this might be a pattern, let's check both diagonals
            {
                if (s_Data[row - 1][col + 1] == 'M' && s_Data[row + 1][col - 1] == 'S'      //M.M
                    && s_Data[row - 1][col - 1] == 'M' && s_Data[row + 1][col + 1] == 'S')  //.A.
                    count++;                                                                //S.S
                
                else if (s_Data[row - 1][col + 1] == 'S' && s_Data[row + 1][col - 1] == 'M' //S.S
                    && s_Data[row - 1][col - 1] == 'S' && s_Data[row + 1][col + 1] == 'M')  //.A.
                    count++;                                                                //M.M                               
                
                else if (s_Data[row - 1][col + 1] == 'S' && s_Data[row + 1][col - 1] == 'M' //M.S
                    && s_Data[row - 1][col - 1] == 'M' && s_Data[row + 1][col + 1] == 'S')  //.A.
                    count++;                                                                //M.S   
                
                else if (s_Data[row - 1][col + 1] == 'M' && s_Data[row + 1][col - 1] == 'S' //S.M
                    && s_Data[row - 1][col - 1] == 'S' && s_Data[row + 1][col + 1] == 'M')  //.A.
                    count++;                                                                //S.M   
            }
        }
    }
    std::cout << "Findings: " << count << std::endl;
}

int main(int argc, char* argv[])
{
    ReadData();

    if (IS_PART1)
        Part1_FindXMAS();
    else
        Part2_FindXMas();
    
    return 0;
}
