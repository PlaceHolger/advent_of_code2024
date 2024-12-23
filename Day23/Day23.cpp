// --- Day 23: LAN Party ---

#include <unordered_map>

//#define USE_TEST_DATA
#define IS_PART1

#include <iostream>
#include <set>
#include <string>
#include <unordered_set>

#include "Day23Data.h"

struct Computer
{
    Computer(const char* name) : id(CreateComputerIndex(name))
    {
        this->name[0] = name[0];
        this->name[1] = name[1];
    }

    static int CreateComputerIndex(const char* computer)
    {
        return static_cast<uint8_t>(computer[0] - 'a') << 8 | static_cast<uint8_t>(computer[1] - 'a');
    }

    // const static char* GetComputerName(int computer)  //not needed currently, because we simply store the name in addition
    // {
    //     static char name[3];
    //     name[0] = static_cast<char>((computer >> 8) + 'a');
    //     name[1] = static_cast<char>((computer & 0xFF) + 'a');
    //     name[2] = '\0';
    //     return name;
    // }

    bool operator==(const Computer& other) const
    {
        return id == other.id;
    }

    int id;
    char name[2]; //can probably be optimized away, but makes debugging easier
};

//hash fct for Computer
namespace std
{
    template <>
    struct hash<Computer>
    {
        std::size_t operator()(const Computer& computer) const noexcept
        {
            return computer.id;
        }
    };
}

static std::unordered_map<Computer, std::vector<Computer>> connections; //computer, list of connected computers

void CreateConnections(const char** arr)
{
    for (int i = 0; i < NUM_DATA; i++)
    {
        const char* line = arr[i];
        Computer computer1(line);
        Computer computer2(line + 3);
        connections[computer1].push_back(computer2);
        connections[computer2].push_back(computer1);
    }
}

static int FindSetsOfThree()
{
    int numSetsOfThree = 0;
    //for each computer that starts with t we simply check all connected computers if they have a connection to another computer that has then a connection to first computer

    for (const auto& connection : connections)
    {
        const auto& firstComputer = connection.first;
        const auto& firstConnections = connection.second;
        //if (firstComputer.name[0] == 't') // we only want to check sets that contain a computer that starts with 't' fix me...
        {
            for (const auto& secondComputer : firstConnections) //for all connected computers of the first computer
            {
                const auto& secondConnections = connections[secondComputer];
                for (const auto& thirdComputer : secondConnections)
                //for all connected computers of the connected computer
                {
                    const auto& thirstConnections = connections[thirdComputer];
                    for (const auto& thirdConnection : thirstConnections)
                    //for all connected computers of the connected computer of the first computer
                    {
                        if (thirdConnection.id == firstComputer.id) //we found a set of 3
                        {
                            const bool anyComputerStartsWithT = firstComputer.name[0] == 't' || secondComputer.name[0]
                                == 't' || thirdComputer.name[0] == 't';
                            if (anyComputerStartsWithT && firstComputer.id < secondComputer.id && secondComputer.id <
                                thirdComputer.id)
                            {
                                //printf("Found set of 3: %c%c, %c%c, %c%c\n", firstComputer.name[0], firstComputer.name[1], secondComputer.name[0], secondComputer.name[1], thirdComputer.name[0], thirdComputer.name[1]);
                                numSetsOfThree++;
                            }
                        }
                    }
                }
            }
        }
    }
    return numSetsOfThree;
}

//okay, i confess, i did not find this solution myself: https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm
// Helper function to run Bron-Kerbosch recursively 
void bronKerbosch(const std::unordered_set<Computer>& R,
                  std::unordered_set<Computer>& P,
                  std::unordered_set<Computer>& X,
                  std::vector<std::unordered_set<Computer>>& cliques)
{
    if (P.empty() && X.empty())
    {
        cliques.push_back(R); // Found a maximal clique
        return;
    }

    auto P_copy = P; // Copy of P to iterate safely
    for (const auto& v : P_copy)
    {
        std::unordered_set<Computer> newR = R, newP, newX;
        newR.insert(v);

        for (const auto& neighbor : connections[v])
        {
            if (P.find(neighbor) != P.end())
                newP.insert(neighbor);
            if (X.find(neighbor) != X.end())
                newX.insert(neighbor);
        }

        bronKerbosch(newR, newP, newX, cliques);

        P.erase(v); // Remove v from P
        X.insert(v); // Add v to X
    }
}

std::unordered_set<Computer> findLargestClique()
{
    std::unordered_set<Computer> R, P, X;
    for (const auto& element : connections)
    {
        P.insert(element.first);
    }

    std::vector<std::unordered_set<Computer>> cliques;
    bronKerbosch(R, P, X, cliques);

    // Find the largest clique
    std::unordered_set<Computer> largestClique;
    for (const auto& clique : cliques)
    {
        if (clique.size() > largestClique.size())
        {
            largestClique = clique;
        }
    }

    return largestClique;
}


int main(int argc, char* argv[])
{
    CreateConnections(data);

#if IS_PART1
    int count = FindSetsOfThree();
    printf("Sets of three: %d\n", count);
#else
    auto largestClique = findLargestClique();
    //sort the computer names alphabetically, simply by adding their names to a set
    std::set<std::string> sortedNames;
    for (const auto& computer : largestClique)
        sortedNames.insert(std::string(computer.name, 2));
    std::string result;
    for (const auto& name : sortedNames)
        result += name + ",";
    std::cout << "Largest clique: " << result << '\n';
#endif

    return 0;
}
