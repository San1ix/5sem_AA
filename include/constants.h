#ifndef CONSTANTS_H
#define CONSTANTS_H

#define INDEX_NOT_FOUND -1
#define MAX_RANDOM_STEP 10

#define BENCHMARK_START 1000
#define BENCHMARK_END 10000
#define BENCHMARK_STEP 1000

enum MainMenu 
{
    MENU_EXIT = 0,
    MENU_INPUT,
    MENU_PRINT,
    MENU_SEARCH,
    MENU_BENCHMARK
};

enum InputMenu 
{
    INPUT_BACK = 0,
    INPUT_GENERATE,
    INPUT_MANUAL
};

enum AlgoMenu 
{
    ALG_BACK = 0,
    ALG_LINEAR,
    ALG_BINARY_A,
    ALG_BINARY_B,
    ALG_BINARY_REC
};

#endif