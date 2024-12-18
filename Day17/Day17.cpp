//https://adventofcode.com/2024/day/17

#include <cassert>
#include <iostream>

//#define USE_TESTDATA
#define IS_PART2

#ifdef USE_TESTDATA
    #if !defined(IS_PART2)
        static int64_t s_Register[3] = { 729, 0, 0 };
        static int s_Program[] = { 0,1,5,4,3,0 };
    #else
        static int64_t s_Register[3] = { 0, 0, 0 };
        static int s_Program[] = { 0,3,5,4,3,0 };
    #endif
#else
    static int64_t s_Register[3] = { 66245665, 0, 0 };
    static constexpr int s_Program[] = { 2,4,1,7,7,5,1,7,4,6,0,3,5,5,3,0 };
#endif

constexpr int s_ProgramLength = std::size(s_Program);

int64_t GetOperandValue(int operand)
{
    switch (operand)
    {
    case 0:
    case 1:
    case 2:
    case 3:
        return operand;
    case 4:
        return s_Register[0];
    case 5:
        return s_Register[1];
    case 6:
        return s_Register[2];
    case 7:
    default:
        assert(false);
        break;
    }
    return 0;
}

bool RunProgram(int* const p_OutChars = nullptr)  // returns false if the output is not as expected
{
    int instructionPointer = 0;
    bool firstOutput = true;
    int currentOutputPos = 0;
    
    while (instructionPointer < s_ProgramLength)
    {
        const int opcode = s_Program[instructionPointer];
        const int operand = s_Program[instructionPointer + 1];
        switch (opcode)
        {
        case 0: //adv - A division: A by 2^operand and store in A
        {
            const int64_t denominator = 1ll << GetOperandValue(operand);
            s_Register[0] /= denominator;
        }
        break;
        case 1: //bxl - bitwise XOR B with operand
        {
            s_Register[1] ^= operand;
        }
        break;
        case 2: //bst - modulo 8 of operand
        {
            s_Register[1] = GetOperandValue(operand) % 8;
        }
        break;
        case 3: //jnz - jump (to operand position) if A != 0 
        {
            if (s_Register[0] != 0)
            {
                instructionPointer = operand;
                continue;
            }
        }
        break;
        case 4: //bxc - bitwise XOR B with C
        {
            s_Register[1] ^= s_Register[2];
        }
        break;
        case 5: //out - output modulo 8 of operand
        {
                const int64_t value = GetOperandValue(operand) % 8;
                if (p_OutChars)
                {
                    (*p_OutChars)++;
                    currentOutputPos++;                    
                }
#if defined(IS_PART2)
                else
                {
                    if (value != s_Program[currentOutputPos])
                        return false;
                    currentOutputPos++;
                    if (currentOutputPos == s_ProgramLength)
                        return true;
                }
#else
                if (!firstOutput)
                    std::cout << ",";
                std::cout << value;
                firstOutput = false;
#endif
        }
        break;
        case 6: //bdv - B division: A by 2^operand and store in B
        {
            const int denominator = 1 << GetOperandValue(operand);
            s_Register[1] = s_Register[0] / denominator;
        }
        break;
        case 7: //cdv - C division: A by 2^operand and store in C
        {
            const int denominator = 1 << GetOperandValue(operand);
            s_Register[2] = s_Register[0] / denominator;
        }
        break;
        default:
            assert(false);
            break;
        }
        instructionPointer += 2;
    }

#if !defined IS_PART2
    return true;
#else
    return false;
#endif
}

    
int main(int argc, char* argv[])
{
#if !defined(IS_PART2)
    RunProgram();
#else
    //for part2 simple bruteforce does not help, but I observed, that the strings gets longer with increasing values of register A
    //so lets try to find the range where to start with our bruteforce approach first. we double the value of register A until the string length is too long
    int64_t currentRegisterAStartValue = 1;
    double factor = 2.0;
    while (true)
    {
        int numChars = 0;
        s_Register[0] = currentRegisterAStartValue;
        s_Register[1] = 0;
        s_Register[2] = 0;
        RunProgram(&numChars);
        currentRegisterAStartValue *= factor;
        std::cout << "Current A value: " << currentRegisterAStartValue << " - string length: " << numChars << std::endl;
        if (numChars >= s_ProgramLength) //okay, too large, try to narrow down the range by adjusting the factor
        {
            std::cout << "Too large, adjusting factor" << std::endl;
            currentRegisterAStartValue /= factor; //go back to the last value that was still in the range
            factor *= 0.999;
            if (factor <= 1.0f)
                break;
        }
    }
    s_Register[0] = currentRegisterAStartValue;
    while (!RunProgram())
    {
        s_Register[0] = ++currentRegisterAStartValue;
        s_Register[1] = 0;
        s_Register[2] = 0;
        if (currentRegisterAStartValue % 10000000 == 0)
            std::cout << "Current A value: " << currentRegisterAStartValue << '\n';
    }
    std::cout << "Lowest value for register A: " << currentRegisterAStartValue << std::endl;
    std::getchar();
#endif
    
    return 0;
}
