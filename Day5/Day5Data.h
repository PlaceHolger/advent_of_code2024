#pragma once
#include <vector>

constexpr int testDataRules[][2] =
    {
    {47,53},
    {97,13},
    {97,61},
    {97,47},
    {75,29},
    {61,13},
    {75,53},
    {29,13},
    {97,29},
    {53,29},
    {61,53},
    {97,53},
    {61,29},
    {47,13},
    {75,47},
    {97,75},
    {47,61},
    {75,61},
    {47,29},
    {75,13},
    {53,13}};

std::vector<int> testUpdates[] =
    {
    {75,47,61,53,29},
{97,61,53,29,13},
{75,29,13},
{75,97,47,61,53},
{61,13,29},
{97,13,75,29,47}
    };

std::vector<int> realUpdates[] =
{
    {38,68,88,11,13,64,29,37,92,72,26,83,89},
{92,12,72,26,51,83,79,76,24,17,49,42,87,25,63,18,84},
{37,26,79,73,87},
{15,47,78,68,53},
{93,17,49,63,18,23,96,47,36,34,44},
{11,36,88,13,59,38,46,34,71,68,12,31,92,54,47,44,29,37,64,78,74},
{26,72,42,84,87,65,24,12,79},
{41,13,53,92,51,83,76,93,49},
{26,78,74,51,56,37,41,88,59,31,68,13,34,92,44,64,71,15,72},
{47,59,15,71,41,53,12},
{72,82,89,83,92,37,42,53,87,73,76,26,78,49,79},
{13,51,83,29,37,92,78,68,41,44,88,38,26,53,11,64,34,12,74},
{93,73,17,49,42,35,87,25,98,63,18,84,65,23,96,47,54,36,46,59,34,38,74},
{23,35,63,42,46,25,93,79,98,87,36,54,18,76,73,49,65},
{93,73,17,49,42,35,98,84,23,96,47,54,36,46,59,34,38,44,74},
{51,64,72,37,12,42,35,49,89,82,73,26,93,56,13,29,79,78,92,24,83},
{24,73,17,49,87,63,96,47,36,59,34,38,44},
{44,59,71,78,37,92,12,31,88},
{93,11,51,82,26,53,24,42,76},
{72,56,51,83,89,82,79,76,24,73,42,87,98,63,84,65,23},
{15,88,41,13,29,53,92,56,51,89,76},
{15,46,38,36,17,23,63,84,35,73,59,74,98,65,34,96,25},
{23,54,36,46,59,34,44,74,15,31,88,71,41,11,13,29,37},
{68,71,41,11,13,64,29,53,78,37,92,12,72,56,26,51,83,89,82,79,24},
{31,92,74,46,38,13,47,59,29,41,68,11,15,12,78,71,54,53,44},
{93,73,17,49,87,98,18,84,65,23,96,47,54,36,59,34,38,44,74},
{87,98,84,65,96,47,46,59,34,74,15,31,88,71,41},
{87,42,18,98,72},
{72,56,51,83,89,76,24,93,17,49,35,98,63,18,84},
{13,89,11,64,73,76,29,26,53,72,56,17,83,42,37,49,78,82,79},
{44,15,68,31,88,71,41,13,29,53,92,12,56,26,51,83,89},
{93,44,35,98,87,63,46,84,47,25,59,42,54,17,73,34,24,49,96,65,18,23,38},
{53,78,37,92,12,72,56,26,51,83,89,82,79,76,24,73,17,49,42,35,87,25,98},
{89,79,76,49,35},
{15,88,13,29,56,79,76},
{83,56,42,12,92,73,49,72,93,18,98,87,37,17,79,82,63},
{15,68,88,71,41,11,13,53,78,37,92,12,72,56,26,51,83,89,82,79,76},
{49,23,96,42,79,98,65,59,84,87,34},
{25,98,65,36,15,41,11},
{47,11,59,38,23,41,44,54,34,64,71,15,63,84,46,36,88,74,31,96,18},
{74,15,68,31,71,11,13,64,29,78,37,92,12,72,56,26,51,83,89,82,79},
{38,15,71,11,78,56,51,83,89},
{74,34,15,88,31,12,47,44,38,78,68,41,36,64,46,92,53,13,71,54,59,29,37},
{41,11,13,64,29,53,92,12,56,26,83,89,82,79,76,93,73,17,49},
{24,73,49,35,87,63,54,46,59,38,44},
{46,41,36,88,44,47,74,63,54,65,15,84,59,23,96,98,13,11,31},
{78,38,68,26,92,56,12,41,34,11,13,53,46},
{98,47,38,65,49,42,35,31,34,36,23,63,68},
{35,87,98,63,18,84,65,23,96,47,54,46,34,44,74,68,31,88,71},
{79,93,17,49,35,25,98,63,18,84,65,59,34},
{87,68,65,17,46,74,63,59,47},
{11,23,59,88,84,34,31,44,36,18,64,15,71,41,65,13,68,54,38},
{56,71,34,59,44,11,78,38,36},
{88,31,89,53,56,13,71},
{74,68,71,41,11,13,64,12,72,82,79},
{47,36,59,38,68,88,37},
{84,76,24,96,18,87,73,65,36,23,54,17,93,49,83,82,79,35,42,63,47},
{53,54,71,29,47,46,34,23,31,96,13,78,68,59,36,88,11,37,38,15,74},
{18,49,36,84,17,59,96,79,87,93,47,34,42,73,54},
{31,59,56,13,11},
{24,93,17,49,42,35,87,25,63,18,84,65,96,47,54,36,46,59,34,38,44},
{89,92,79,64,37,31,41,26,93},
{64,37,92,51,89,76,24,73,87},
{23,65,46,84,47,88,98,59,11,36,18,68,74,38,31,25,96},
{18,64,41,23,15,74,84,59,46,13,47,71,36,88,44,38,63,31,68,54,34,11,65},
{89,82,76,73,35,25,65,54,46},
{24,73,17,25,98,18,96,47,36,59,34,38,44},
{36,59,68,71,41,13,53},
{92,12,72,56,26,51,89,82,79,76,24,93,73,17,49,42,35,87,25,98,63,18,84},
{74,15,88,71,41,11,64,29,53,78,37,92,72,26,51,83,89,82,79},
{51,83,89,76,24,87,18,65,23},
{74,68,64,29,78,37,92,12,83,89,79},
{74,15,44,64,31,41,38,26,92,71,88,29,78,59,68,34,11,46,56},
{47,24,36,65,98,59,96,84,46,25,34,54,35,73,23,38,93,18,17,87,42,76,63},
{17,98,63,18,44,15,68},
{26,51,83,89,82,76,24,93,73,17,49,42,35,87,25,98,63,18,84,65,23,96,47},
{18,74,65,42,84,88,31,35,63},
{36,46,59,34,38,44,74,15,68,31,88,71,41,11,13,29,53,78,37,92,12,72,56},
{82,79,76,24,93,17,42,35,25,98,18,84,65,23,96,47,54,36,59},
{34,38,44,74,88,13,64,29,53,37,72,56,26,51,83},
{29,53,78,37,92,12,72,56,26,51,83,89,82,79,76,24,93,73,17,49,42,35,25},
{53,79,56,72,78,26,29,15,88,92,76,11,64},
{63,12,49,84,56,17,18,87,65},
{74,15,31,88,41,11,13,64,29,53,78,92,12,72,56,26,51,83,89,82,79},
{96,47,38,44,31,11,64,29,78},
{23,54,11,47,63,64,15},
{82,24,93,73,17,49,42,98,23,96,36,46,59},
{51,83,89,82,76,93,73,17,49,42,35,87,25,18,84,23,96,47,54},
{11,13,64,29,37,92,12,72,56,26,83,89,79,24,93,73,17,49,42},
{83,76,42,63,84},
{84,23,47,68,31,71,64,29,53},
{34,35,63,36,96,38,25,54,74,49,59},
{44,29,59,41,54,34,36,71,37,13,53,88,96,11,31,47,74,64,92},
{76,93,73,17,49,42,35,87,25,98,63,18,84,65,23,96,47,54,36,46,34},
{82,79,76,73,42,35,87,25,63,18,84,96,47,36,59},
{56,84,25,42,87,23,73,76,96},
{78,12,83,89,93,73,49,35,87},
{74,72,12,53,11,34,29,64,59,46,15},
{12,72,79,26,56},
{29,53,78,37,12,56,26,51,83,89,82,79,76,24,93,73,17,42,35,87,25},
{12,76,31,24,37,26,92,68,82,56,83,71,89,29,11,78,41,79,51},
{54,74,73,36,63,93,17},
{46,92,15,11,13,56,78,44,36,53,34,68,37,12,59},
{18,35,93,65,73,54,76,17,59,46,82},
{36,15,74,84,68,71,34,44,65,63,41,96,38,87,88,47,18,46,23,31,54},
{64,15,44,78,51,13,71,74,41,83,38,26,34,12,92,31,68,11,88,56,29},
{63,18,84,23,96,47,54,36,46,59,34,38,44,74,15,68,31,88,71,41,11,13,64},
{98,76,65,17,51,83,24,42,84,73,35,72,82},
{54,46,59,34,74,11,64,12,72},
{93,34,63,35,73,98,65,18,46,54,17,44,42,59,74},
{26,37,49,42,51,18,73,93,79},
{65,23,96,54,46,59,34,38,44,15,68,31,88,71,41,11,13,64,29,53,78},
{83,89,82,76,73,35,87,25,18,84,96,47,36},
{26,41,93,12,79,64,31},
{84,23,47,54,34,38,44,74,15,68,88,29,53},
{88,41,11,13,64,29,53,37,92,12,72,51,79,93,73},
{44,74,15,68,31,88,71,41,11,64,29,53,78,37,92,12,72,56,26,51,83,89,82},
{29,74,92,34,41,26,11,64,12},
{17,49,42,87,25,98,63,18,84,65,23,96,47,54,36,46,59,34,38,44,74,15,68},
{79,18,82,49,76,36,24,96,87,73,59,35,63,65,17,98,54,23,42},
{41,73,83,53,17,93,71,89,56,92,26},
{87,25,98,63,65,23,54,36,59,34,44,74,15,68,88,71,41},
{24,26,92,12,93,17,49,42,83,56,78,89,63},
{49,25,56,76,79,63,12,51,65,84,18,35,87},
{23,46,47,42,87,17,25,38,63,84,74,34,59,44,54,98,96,35,65,18,93,73,49},
{84,65,34,38,25},
{25,35,98,42,88,23,84,31,18,54,36,96,87},
{17,24,47,87,79,83,63,25,26},
{82,79,76,42,18,47,36},
{37,17,83,26,18,79,25,24,35},
{41,37,92,56,89,79,49},
{34,18,79,63,98,23,47},
{34,44,74,68,31,41,13,53,12,56,83},
{23,47,54,46,59,44,74,15,68,31,88,71,41,11,29,53,37},
{54,79,65,18,24,47,34,63,25},
{84,54,59,34,15,71,41,13,53},
{63,84,65,23,96,47,36,46,59,34,38,44,74,15,68,31,88,71,11,13,64},
{37,12,26,51,89,79,73},
{35,18,31,47,42,49,36,63,74,59,38,15,87,46,25,44,68,98,54},
{96,47,36,59,34,44,74,15,68,31,13,64,53,78,92},
{17,49,42,35,25,98,18,84,65,23,96,47,54,36,46,59,34,38,44,74,15},
{42,83,87,56,65,18,35,17,89,63,12,26,84,25,49,51,24},
{15,68,31,88,71,41,11,13,64,29,53,78,37,92,12,72,56,26,51,83,89,82,79},
{17,42,35,87,98,84,23,96,47,54,36,59,34,74,68},
{26,51,83,89,82,79,76,24,93,73,17,49,42,35,87,25,63,18,84,65,23,96,47},
{54,46,59,34,44,74,15,68,31,71,41,11,13,64,37,92,72},
{31,37,72,56,26,83,82},
{34,38,44,74,15,68,31,88,71,11,13,64,29,53,78,37,92,12,72,56,26,51,83},
{63,25,84,98,34,49,54,73,47,74,96,46,65,42,35,15,59,44,23},
{88,71,64,29,37,92,72,89,73},
{65,31,15,84,46,34,23,38,71,53,54,68,41},
{44,31,88,71,41,13,64,78,37,92,12,72,89},
{35,83,56,73,72,84,49,25,87,24,23,42,82,18,93},
{12,72,56,26,51,83,89,82,79,24,93,73,17,49,87,25,98,63,84},
{31,88,71,41,11,13,64,29,53,78,37,92,12,72,56,26,51,83,89,79,76,24,93},
{98,65,23,96,47,54,36,46,59,34,38,74,31,41,13},
{89,98,18,84,96,54,46},
{53,78,72,56,51,76,49,25,98},
{98,37,12,92,17,56,93,42,51,63,25,79,87,49,73,89,26,72,83,35,82},
{23,96,74,71,13},
{88,53,72,29,38,68,78,83,26,74,56,41,64,89,37,11,13,71,44,31,12},
{13,53,92,12,51,83,79,76,24,17,35},
{17,42,35,25,84,65,23,96,54,46,44},
{63,44,84,34,23,36,88,74,38,59,15,18,35,71,25,47,98,46,65},
{38,53,44,37,59,12,15,13,54,72,46},
{13,93,41,12,26,89,31,29,82,71,92},
{25,36,65,63,98,84,35,49,93,54,47,17,24},
{78,37,92,12,26,51,79,24,49,42,35,87,25,98,63},
{65,23,96,47,54,46,59,34,44,74,15,31,88,41,64,29,78},
{44,42,31,63,98,68,49,84,34,18,15},
{31,41,11,64,29,92,93},
{34,12,88,37,74,41,15,71,38,13,92,31,83,11,51,56,64,68,53},
{89,49,83,76,78,64,26,93,41,53,73,24,79,51,17,37,92,11,72,29,82,13,56},
{44,37,38,59,74,92,31,54,47,46,64,41,78,36,15,96,68,88,11},
{88,25,54,18,34,41,11,71,59,65,47,38,68},
{18,65,23,96,47,54,36,59,44,15,31,71,41,11,13,64,29},
{13,78,49,24,92,53,72,11,26,51,17,37,56,73,12,42,89},
{83,89,79,76,24,93,73,17,49,35,25,98,63,84,65,47,36},
{88,41,13,64,53,78,37,12,26,83,79,76,24,93,73},
{84,87,82,42,63,49,96,73,56},
{71,13,29,44,53,59,54,74,47,64,37,38,68,96,15,23,34},
{87,44,18,54,31,71,74,84,47,65,15,23,98,35,59},
{79,51,68,12,53,29,72,26,83,71,88,11,31,13,74,82,15,37,64,92,56},
{89,87,64,26,79,56,83}};

constexpr int realDataRules[][2] =    
{{15,78},
{65,46},
{65,23},
{54,46},
{54,41},
{54,15},
{53,42},
{53,24},
{53,82},
{53,73},
{38,53},
{38,83},
{38,78},
{38,56},
{38,44},
{73,74},
{73,34},
{73,49},
{73,54},
{73,84},
{73,23},
{41,26},
{41,78},
{41,72},
{41,79},
{41,83},
{41,73},
{41,76},
{87,65},
{87,25},
{87,44},
{87,18},
{87,23},
{87,47},
{87,63},
{87,74},
{76,36},
{76,23},
{76,93},
{76,54},
{76,49},
{76,46},
{76,25},
{76,73},
{76,34},
{72,96},
{72,76},
{72,83},
{72,79},
{72,17},
{72,51},
{72,35},
{72,65},
{72,23},
{72,82},
{84,15},
{84,64},
{84,68},
{84,31},
{84,71},
{84,54},
{84,44},
{84,36},
{84,47},
{84,96},
{84,29},
{88,41},
{88,13},
{88,93},
{88,71},
{88,17},
{88,56},
{88,37},
{88,83},
{88,24},
{88,82},
{88,11},
{88,79},
{93,35},
{93,36},
{93,49},
{93,74},
{93,87},
{93,47},
{93,96},
{93,23},
{93,17},
{93,18},
{93,42},
{93,59},
{93,46},
{46,29},
{46,26},
{46,13},
{46,31},
{46,88},
{46,37},
{46,15},
{46,71},
{46,11},
{46,64},
{46,59},
{46,53},
{46,51},
{46,74},
{18,13},
{18,47},
{18,36},
{18,64},
{18,11},
{18,68},
{18,41},
{18,23},
{18,46},
{18,34},
{18,84},
{18,29},
{18,96},
{18,54},
{18,53},
{35,23},
{35,54},
{35,74},
{35,38},
{35,68},
{35,18},
{35,47},
{35,63},
{35,34},
{35,65},
{35,87},
{35,98},
{35,84},
{35,46},
{35,59},
{35,41},
{92,73},
{92,98},
{92,84},
{92,83},
{92,35},
{92,26},
{92,89},
{92,63},
{92,24},
{92,82},
{92,79},
{92,65},
{92,87},
{92,93},
{92,49},
{92,72},
{92,42},
{24,42},
{24,17},
{24,93},
{24,87},
{24,54},
{24,96},
{24,38},
{24,59},
{24,46},
{24,35},
{24,84},
{24,44},
{24,18},
{24,47},
{24,65},
{24,73},
{24,49},
{24,25},
{29,72},
{29,42},
{29,56},
{29,73},
{29,37},
{29,51},
{29,87},
{29,17},
{29,82},
{29,49},
{29,83},
{29,98},
{29,53},
{29,93},
{29,79},
{29,78},
{29,24},
{29,12},
{29,26},
{74,15},
{74,78},
{74,41},
{74,64},
{74,51},
{74,88},
{74,83},
{74,12},
{74,82},
{74,31},
{74,79},
{74,92},
{74,89},
{74,53},
{74,26},
{74,71},
{74,68},
{74,11},
{74,29},
{74,72},
{37,89},
{37,26},
{37,83},
{37,72},
{37,92},
{37,93},
{37,63},
{37,25},
{37,51},
{37,79},
{37,98},
{37,56},
{37,12},
{37,49},
{37,24},
{37,17},
{37,18},
{37,35},
{37,87},
{37,84},
{37,73},
{17,31},
{17,18},
{17,42},
{17,98},
{17,25},
{17,46},
{17,54},
{17,35},
{17,87},
{17,23},
{17,68},
{17,47},
{17,96},
{17,38},
{17,59},
{17,63},
{17,15},
{17,34},
{17,36},
{17,44},
{17,49},
{17,74},
{56,26},
{56,79},
{56,42},
{56,51},
{56,25},
{56,47},
{56,84},
{56,98},
{56,17},
{56,73},
{56,49},
{56,83},
{56,89},
{56,76},
{56,23},
{56,35},
{56,63},
{56,24},
{56,18},
{56,93},
{56,65},
{56,96},
{56,82},
{26,24},
{26,47},
{26,83},
{26,98},
{26,49},
{26,87},
{26,63},
{26,25},
{26,82},
{26,76},
{26,51},
{26,35},
{26,54},
{26,96},
{26,79},
{26,42},
{26,84},
{26,18},
{26,93},
{26,23},
{26,17},
{26,65},
{26,89},
{26,73},
{11,26},
{11,73},
{11,92},
{11,29},
{11,76},
{11,64},
{11,37},
{11,53},
{11,79},
{11,89},
{11,83},
{11,35},
{11,72},
{11,93},
{11,12},
{11,49},
{11,24},
{11,42},
{11,51},
{11,17},
{11,82},
{11,56},
{11,78},
{11,13},
{71,26},
{71,51},
{71,17},
{71,93},
{71,24},
{71,41},
{71,78},
{71,89},
{71,64},
{71,92},
{71,11},
{71,79},
{71,76},
{71,29},
{71,82},
{71,37},
{71,13},
{71,73},
{71,49},
{71,83},
{71,72},
{71,12},
{71,53},
{71,56},
{13,12},
{13,73},
{13,42},
{13,29},
{13,35},
{13,89},
{13,51},
{13,53},
{13,76},
{13,26},
{13,17},
{13,78},
{13,56},
{13,79},
{13,64},
{13,37},
{13,93},
{13,49},
{13,87},
{13,82},
{13,24},
{13,92},
{13,72},
{13,83},
{25,96},
{25,84},
{25,74},
{25,34},
{25,46},
{25,68},
{25,63},
{25,71},
{25,54},
{25,18},
{25,41},
{25,88},
{25,65},
{25,47},
{25,44},
{25,31},
{25,11},
{25,23},
{25,38},
{25,36},
{25,59},
{25,15},
{25,98},
{25,13},
{82,17},
{82,47},
{82,18},
{82,46},
{82,79},
{82,84},
{82,42},
{82,76},
{82,54},
{82,23},
{82,87},
{82,63},
{82,59},
{82,98},
{82,96},
{82,36},
{82,24},
{82,93},
{82,25},
{82,34},
{82,49},
{82,73},
{82,35},
{82,65},
{36,64},
{36,78},
{36,38},
{36,41},
{36,59},
{36,68},
{36,72},
{36,37},
{36,29},
{36,88},
{36,53},
{36,71},
{36,31},
{36,26},
{36,13},
{36,12},
{36,34},
{36,15},
{36,46},
{36,44},
{36,74},
{36,56},
{36,92},
{36,11},
{47,11},
{47,92},
{47,74},
{47,36},
{47,71},
{47,64},
{47,31},
{47,12},
{47,78},
{47,68},
{47,46},
{47,38},
{47,59},
{47,34},
{47,53},
{47,72},
{47,13},
{47,54},
{47,37},
{47,15},
{47,44},
{47,41},
{47,88},
{47,29},
{98,65},
{98,11},
{98,59},
{98,63},
{98,44},
{98,31},
{98,74},
{98,71},
{98,68},
{98,23},
{98,41},
{98,88},
{98,34},
{98,36},
{98,84},
{98,13},
{98,38},
{98,15},
{98,18},
{98,54},
{98,64},
{98,47},
{98,96},
{98,46},
{44,41},
{44,92},
{44,15},
{44,37},
{44,26},
{44,72},
{44,64},
{44,71},
{44,89},
{44,83},
{44,88},
{44,78},
{44,74},
{44,51},
{44,13},
{44,11},
{44,53},
{44,79},
{44,31},
{44,56},
{44,82},
{44,68},
{44,29},
{44,12},
{96,29},
{96,54},
{96,38},
{96,92},
{96,13},
{96,68},
{96,34},
{96,31},
{96,88},
{96,46},
{96,53},
{96,74},
{96,47},
{96,36},
{96,44},
{96,71},
{96,59},
{96,64},
{96,78},
{96,12},
{96,15},
{96,11},
{96,37},
{96,41},
{79,49},
{79,63},
{79,59},
{79,96},
{79,87},
{79,18},
{79,23},
{79,36},
{79,34},
{79,54},
{79,42},
{79,98},
{79,24},
{79,93},
{79,46},
{79,25},
{79,73},
{79,65},
{79,84},
{79,35},
{79,38},
{79,17},
{79,47},
{79,76},
{12,83},
{12,87},
{12,51},
{12,72},
{12,76},
{12,49},
{12,93},
{12,89},
{12,42},
{12,82},
{12,25},
{12,56},
{12,65},
{12,18},
{12,35},
{12,24},
{12,84},
{12,26},
{12,79},
{12,23},
{12,98},
{12,63},
{12,73},
{12,17},
{31,82},
{31,51},
{31,76},
{31,78},
{31,26},
{31,56},
{31,89},
{31,88},
{31,83},
{31,29},
{31,93},
{31,24},
{31,37},
{31,92},
{31,79},
{31,64},
{31,11},
{31,12},
{31,72},
{31,73},
{31,13},
{31,53},
{31,71},
{31,41},
{49,98},
{49,15},
{49,44},
{49,88},
{49,68},
{49,36},
{49,46},
{49,84},
{49,65},
{49,31},
{49,47},
{49,59},
{49,25},
{49,38},
{49,42},
{49,54},
{49,74},
{49,23},
{49,87},
{49,63},
{49,96},
{49,35},
{49,34},
{49,18},
{78,51},
{78,89},
{78,98},
{78,56},
{78,87},
{78,72},
{78,79},
{78,83},
{78,25},
{78,24},
{78,76},
{78,73},
{78,63},
{78,17},
{78,35},
{78,49},
{78,37},
{78,12},
{78,26},
{78,93},
{78,42},
{78,92},
{78,18},
{78,82},
{42,63},
{42,31},
{42,46},
{42,87},
{42,96},
{42,23},
{42,71},
{42,74},
{42,15},
{42,36},
{42,88},
{42,54},
{42,25},
{42,98},
{42,68},
{42,44},
{42,84},
{42,38},
{42,34},
{42,59},
{42,65},
{42,47},
{42,35},
{42,18},
{68,72},
{68,53},
{68,13},
{68,79},
{68,41},
{68,64},
{68,24},
{68,88},
{68,82},
{68,71},
{68,76},
{68,93},
{68,31},
{68,83},
{68,26},
{68,92},
{68,29},
{68,51},
{68,56},
{68,11},
{68,89},
{68,12},
{68,78},
{68,37},
{64,93},
{64,37},
{64,79},
{64,83},
{64,87},
{64,72},
{64,26},
{64,49},
{64,73},
{64,17},
{64,25},
{64,92},
{64,56},
{64,76},
{64,78},
{64,12},
{64,35},
{64,82},
{64,51},
{64,89},
{64,24},
{64,29},
{64,42},
{64,53},
{63,74},
{63,36},
{63,71},
{63,68},
{63,65},
{63,23},
{63,13},
{63,11},
{63,34},
{63,46},
{63,54},
{63,44},
{63,15},
{63,29},
{63,88},
{63,59},
{63,64},
{63,47},
{63,96},
{63,84},
{63,31},
{63,18},
{63,38},
{63,41},
{51,25},
{51,47},
{51,49},
{51,35},
{51,89},
{51,82},
{51,42},
{51,79},
{51,98},
{51,65},
{51,54},
{51,83},
{51,84},
{51,24},
{51,73},
{51,17},
{51,23},
{51,63},
{51,36},
{51,18},
{51,96},
{51,76},
{51,93},
{51,87},
{23,54},
{23,34},
{23,88},
{23,64},
{23,36},
{23,78},
{23,37},
{23,53},
{23,92},
{23,96},
{23,46},
{23,13},
{23,59},
{23,74},
{23,71},
{23,15},
{23,38},
{23,31},
{23,44},
{23,68},
{23,29},
{23,11},
{23,47},
{23,41},
{83,65},
{83,63},
{83,18},
{83,54},
{83,36},
{83,82},
{83,96},
{83,46},
{83,47},
{83,76},
{83,35},
{83,17},
{83,87},
{83,79},
{83,98},
{83,73},
{83,25},
{83,93},
{83,24},
{83,49},
{83,42},
{83,89},
{83,23},
{83,84},
{89,82},
{89,73},
{89,79},
{89,63},
{89,76},
{89,36},
{89,49},
{89,17},
{89,65},
{89,59},
{89,24},
{89,93},
{89,54},
{89,87},
{89,47},
{89,98},
{89,25},
{89,84},
{89,46},
{89,35},
{89,18},
{89,42},
{89,96},
{89,23},
{59,31},
{59,38},
{59,51},
{59,53},
{59,68},
{59,29},
{59,13},
{59,41},
{59,11},
{59,78},
{59,74},
{59,72},
{59,92},
{59,37},
{59,15},
{59,44},
{59,71},
{59,88},
{59,12},
{59,34},
{59,26},
{59,64},
{59,83},
{59,56},
{34,38},
{34,83},
{34,31},
{34,68},
{34,71},
{34,74},
{34,37},
{34,64},
{34,53},
{34,89},
{34,51},
{34,56},
{34,72},
{34,44},
{34,41},
{34,88},
{34,78},
{34,11},
{34,15},
{34,12},
{34,26},
{34,29},
{34,13},
{34,92},
{15,82},
{15,79},
{15,13},
{15,76},
{15,26},
{15,53},
{15,56},
{15,41},
{15,51},
{15,31},
{15,11},
{15,83},
{15,64},
{15,29},
{15,24},
{15,72},
{15,12},
{15,37},
{15,88},
{15,71},
{15,89},
{15,68},
{15,92},
{65,74},
{65,78},
{65,41},
{65,88},
{65,71},
{65,59},
{65,13},
{65,47},
{65,37},
{65,11},
{65,53},
{65,44},
{65,29},
{65,64},
{65,38},
{65,96},
{65,36},
{65,54},
{65,15},
{65,34},
{65,31},
{65,68},
{54,37},
{54,71},
{54,29},
{54,88},
{54,31},
{54,53},
{54,13},
{54,38},
{54,12},
{54,92},
{54,74},
{54,56},
{54,44},
{54,36},
{54,68},
{54,34},
{54,11},
{54,78},
{54,59},
{54,72},
{54,64},
{53,89},
{53,37},
{53,51},
{53,63},
{53,83},
{53,87},
{53,35},
{53,76},
{53,98},
{53,26},
{53,25},
{53,92},
{53,49},
{53,79},
{53,12},
{53,72},
{53,93},
{53,78},
{53,56},
{53,17},
{38,13},
{38,31},
{38,29},
{38,82},
{38,12},
{38,68},
{38,72},
{38,92},
{38,88},
{38,89},
{38,41},
{38,51},
{38,37},
{38,71},
{38,64},
{38,15},
{38,11},
{38,26},
{38,74},
{73,98},
{73,36},
{73,35},
{73,44},
{73,63},
{73,15},
{73,17},
{73,47},
{73,65},
{73,46},
{73,18},
{73,96},
{73,87},
{73,42},
{73,59},
{73,25},
{73,38},
{73,68},
{41,37},
{41,82},
{41,12},
{41,51},
{41,53},
{41,29},
{41,56},
{41,13},
{41,89},
{41,49},
{41,64},
{41,93},
{41,17},
{41,42},
{41,24},
{41,92},
{41,11},
{87,11},
{87,31},
{87,38},
{87,59},
{87,15},
{87,36},
{87,84},
{87,54},
{87,34},
{87,88},
{87,71},
{87,96},
{87,68},
{87,46},
{87,98},
{87,41},
{76,17},
{76,96},
{76,42},
{76,24},
{76,63},
{76,44},
{76,38},
{76,35},
{76,18},
{76,47},
{76,84},
{76,87},
{76,65},
{76,59},
{76,98},
{72,89},
{72,25},
{72,26},
{72,24},
{72,42},
{72,56},
{72,49},
{72,93},
{72,87},
{72,18},
{72,73},
{72,98},
{72,63},
{72,84},
{84,11},
{84,13},
{84,74},
{84,53},
{84,34},
{84,59},
{84,65},
{84,38},
{84,78},
{84,46},
{84,41},
{84,88},
{84,23},
{88,78},
{88,26},
{88,12},
{88,76},
{88,72},
{88,51},
{88,73},
{88,92},
{88,64},
{88,89},
{88,29},
{88,53},
{93,54},
{93,25},
{93,63},
{93,84},
{93,73},
{93,34},
{93,98},
{93,15},
{93,44},
{93,65},
{93,38},
{46,78},
{46,56},
{46,34},
{46,12},
{46,92},
{46,41},
{46,72},
{46,44},
{46,38},
{46,68},
{18,65},
{18,38},
{18,59},
{18,88},
{18,31},
{18,44},
{18,71},
{18,15},
{18,74},
{35,25},
{35,71},
{35,96},
{35,31},
{35,15},
{35,36},
{35,44},
{35,88},
{92,17},
{92,25},
{92,76},
{92,56},
{92,18},
{92,12},
{92,51},
{24,34},
{24,98},
{24,63},
{24,74},
{24,36},
{24,23},
{29,89},
{29,25},
{29,92},
{29,35},
{29,76},
{74,76},
{74,56},
{74,37},
{74,13},
{37,82},
{37,76},
{37,42},
{17,65},
{17,84},
{56,87}};

