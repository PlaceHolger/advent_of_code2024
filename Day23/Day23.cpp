// --- Day 23: LAN Party ---
//     As The Historians wander around a secure area at Easter Bunny HQ, you come across posters for a LAN party scheduled for today! Maybe you can find it; you connect to a nearby datalink port and download a map of the local network (your puzzle input).
//
//     The network map provides a list of every connection between two computers. For example:
//
//     kh-tc
//     qp-kh
//     de-cg
//     ka-co
//     yn-aq
//     qp-ub
//     cg-tb
//     vc-aq
//     tb-ka
//     wh-tc
//     yn-cg
//     kh-ub
//     ta-co
//     de-co
//     tc-td
//     tb-wq
//     wh-td
//     ta-ka
//     td-qp
//     aq-cg
//     wq-ub
//     ub-vc
//     de-ta
//     wq-aq
//     wq-vc
//     wh-yn
//     ka-de
//     kh-ta
//     co-tc
//     wh-qp
//     tb-vc
//     td-yn
//     Each line of text in the network map represents a single connection; the line kh-tc represents a connection between the computer named kh and the computer named tc. Connections aren't directional; tc-kh would mean exactly the same thing.
//
//     LAN parties typically involve multiplayer games, so maybe you can locate it by finding groups of connected computers. Start by looking for sets of three computers where each computer in the set is connected to the other two computers.
//
//     In this example, there are 12 such sets of three inter-connected computers:
//
//     aq,cg,yn
//     aq,vc,wq
//     co,de,ka
//     co,de,ta
//     co,ka,ta
//     de,ka,ta
//     kh,qp,ub
//     qp,td,wh
//     tb,vc,wq
//     tc,td,wh
//     td,wh,yn
//     ub,vc,wq
//     If the Chief Historian is here, and he's at the LAN party, it would be best to know that right away. You're pretty sure his computer's name starts with t, so consider only sets of three computers where at least one computer's name starts with t. That narrows the list down to 7 sets of three inter-connected computers:
//
//     co,de,ta
//     co,ka,ta
//     de,ka,ta
//     qp,td,wh
//     tb,vc,wq
//     tc,td,wh
//     td,wh,yn
//     Find all the sets of three inter-connected computers. How many contain at least one computer with a name that starts with t?

#include <cstdio>
#include <unordered_map>

//#define USE_TEST_DATA
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
        return static_cast<uint8_t>(computer[0] - 'a') << 8 | static_cast<uint8_t>(computer[1] - 'a') ;
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

static std::unordered_map<Computer, std::vector<Computer>> connections;  //computer, list of connected computers

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
            for (const auto& secondComputer : firstConnections)  //for all connected computers of the first computer
            {
                const auto& secondConnections = connections[secondComputer];
                for (const auto& thirdComputer : secondConnections)  //for all connected computers of the connected computer
                {
                    const auto& thirstConnections = connections[thirdComputer];
                    for (const auto& thirdConnection : thirstConnections) //for all connected computers of the connected computer of the first computer
                    {
                        if (thirdConnection.id == firstComputer.id) //we found a set of 3
                        {
                            const bool anyComputerStartsWithT = firstComputer.name[0] == 't' || secondComputer.name[0] == 't' || thirdComputer.name[0] == 't';
                            if (anyComputerStartsWithT && firstComputer.id < secondComputer.id && secondComputer.id < thirdComputer.id)
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

int main(int argc, char* argv[])
{
    CreateConnections(data);
    int count = FindSetsOfThree();
    printf("Sets of three: %d\n", count);
    
    return 0;
}
