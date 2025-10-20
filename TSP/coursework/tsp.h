// COPYRIGHT (C) HARRY CLARK 2025
// CS3_CI TRAVELLING SALESMAN PROBLEM 

// THIS FILE PERTAINS TOWARDS THE MODULARISATION OF AREAS ENCOMPASSING THE TSP
// AS PER MODULE AND LAB CONTENTS OF CS3_CI

// SPECIFICALLY, THIS VERSION FOCUSSES MORE SO ON THE CONTENTS PERTAINING
// TOWARDS THE COURSEWORK - KEEPING MY ORIGINAL IMPLEMENTATION ADJACENT

#ifndef TSP_CW_H
#define TSP_CW_H

// SYSTEM INCLUDES

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(USE_TSP)
    #define USE_TSP
#else
    #define USE_TSP
    
    #define     TSP_OPT_OFF             0
    #define     TSP_OPT_ON              1

    #define     TSP_MAX_CITIES      50          // MAX AMOUNT WE HAVE AT A GIVEN TIME
    #define     TSP_CSV_MAX_LINE    256         // ARBITRARY BUFFER VALUE FOR MAX LINE COUNT
    #define     TSP_ACO_ANTS        20
    #define     TSP_ACO_ALPHA       1.0         // ANT COLONY IMPORTANCE       
    #define     TSP_ACO_HEUR        2.0         // ANT COLONY HEURISTIC 
    #define     TSP_ACO_EVAP        0.5         // ANT COLONY EVAPORATION RATE 
    #define     TSP_ACO_DEPO        100.0       // ANT COLONY PHEROMONE DEPOSIT             

    #define     TSP_SEED()                      srand((unsigned int)time(NULL))     // RANDOM SEED WITH TYPE CAST
    #define     TSP_RAND_CITY(VALUE)            (rand() % (VALUE))                  // RANDOM CITY AGAINST A VALUE (MAX_CITIES)

    #define     TSP_RAND_POS(VALUE)             (rand() % (TSP_STATE.CITY_COUNT))

    #define     TSP_VALID_DIST(VALUE)           ((VALUE) >= 0 && (VALUE) < INT_MAX)
    #define     TSP_VALID_CITY(VALUE, MAX)      ((VALUE) >= 0 && (VALUE) < (MAX))

    #define     TSP_DEBUG_OPT                   TSP_OPT_OFF 

        // SIMPLE IMPLEMENTATION FOR BEING ABLE TO CATCH
        // AND STRINGIFY ERROR MESSAGES FOR ALLOCATING STRUCTS
        #define     TSP_MEM_ERROR(VALUE) \
            do { \
                if ((VALUE) == NULL) { \
                    printf("MEMORY ALLOCATION FAILED FOR %s, 0x%p\n", #VALUE, (void*)&(VALUE)); \
                    return 1; \
                } \
            } while(0)

    // DEFINE AN ENUM WHICH REPRESENTS THE VARIOUS ALGORITHM TYPES
    // THAT CAN BE TESTED AGAINST
    typedef enum
    {
        TSP_NN,
        TSP_LS,
        TSP_ACO

    } TSP_ALGO;

    // DEFINE THE BASELINE IMPLEMENTATION FOR HOW
    // WE CAN REPRESENT A CITY
    typedef struct
    {
        char NAME[32];          
        int X;                  
        int Y;

    } TSP_CITY;

    // DEFINE THE BASELINE IMPLEMENTAITON FOR HOW
    // WE CAN REPRESENT THE MATRICES BETWEEN CITY

    // THIS IS THE MEANS BY WHICH WE CAN DETERMINE THE
    // DISTANCE BETWEEN CITIES
    typedef struct
    {
        int MATRIX[TSP_MAX_CITIES][TSP_MAX_CITIES];         // 2D ARRAY FOR MAX DIST BETWEEN
        int SIZE;
            
    } TSP_DIST;

    // DEFINE THE BASELINE IMPLEMENTATION FOR HOW
    // WE CAN REPRESENT THE PATHING THAT STARTS AT
    // A SPECIFIC CITY (TOUR)
    typedef struct
    {
        int TSP_PATH[TSP_MAX_CITIES + 1];
        int TSP_TOTAL_DIST;
        int TSP_CITY_COUNT;
        TSP_ALGO ALGO;

    } TSP_TOUR;

    // DEFINE THE BASIS FOR WORKING WITH 
    // ANT COLONY OPTIMISATION
    typedef struct
    {   
        double PHEROMONE[TSP_MAX_CITIES][TSP_MAX_CITIES];
        int BEST_PATH[TSP_MAX_CITIES + 1];
        int BEST_DIST;

    } TSP_ACO_STATE;

    // ALL ENCOMPASSING TSP STRUCT TO ACCESS THESE METHODS
    typedef struct
    {
        TSP_CITY CITY[TSP_MAX_CITIES];
        TSP_DIST DIST;
        TSP_TOUR TOUR;
        int CITY_COUNT;
        TSP_ALGO ALGO;
        TSP_ACO_STATE ACO;

    } TSP_STATE;

    // ERROR HANDLING REPRESENTATION
    typedef enum
    {
        TSP_ERROR_NONE = 0,
        TSP_ERROR_OOB,
        TSP_ERROR_CITY,
        TSP_ERROR_DIST,

    } TSP_ERROR;

    typedef enum
    {
        NONE = 'N',
        OOB = 'O',
        CITY = 'C',
        DIST = 'D',
        PATH = 'P'

    } TSP_ERROR_OP;

    #define TSP_HANDLE(OP, ERROR, MSG, ...) \
                do { \
                    printf("[INFO] %c -> %- 11s" MSG "\n", \
                        (char)OP, TSP_ERR_MSG[ERROR], ##__VA_ARGS__); \
                } while(0)

    #define TSP_ERROR_HANDLE(OP, ERROR, MSG, ...) \
                do { \
                    printf("[ERROR] %c -> %-18s   " MSG "\n", \
                        (char)OP, TSP_ERR_MSG[ERROR], ##__VA_ARGS__); \
                } while(0)

    #define TSP_ALGO_TYPE(VALUE) \
            ((VALUE) == TSP_NN ? "NEAREST NEIGHBOUR" : \
            (VALUE) == TSP_LS ? "TWO OPT LOCAL SEARCH" : \
            (VALUE) == TSP_ACO ? "ANT COLONY" : \
            "UNKNOWN")

    // SIMILAR TO ABOVE BUT FOR PARSING THE COMMAND LINE ARG
    #define TSP_ALGO_ARG(VALUE) \
            (strcmp((VALUE), "--nn") == 0 ? TSP_NN : \
            strcmp((VALUE), "--ls") == 0 ? TSP_LS : \
            strcmp((VALUE), "--ac") == 0 ? TSP_ACO : \
            -1)

    #define TSP_CITY_NAME(NAME, INDEX, X, Y) \
                do { \
                    printf("[CITY] -> %12s | INDEX: %d | X: %d  Y: %d\n", NAME, INDEX, X, Y); \
                } while(0)

    #define TSP_IMPROVE(ALGO, PATH, DIST, CITY_COUNT)                                           \
        do { \
            printf("[IMPROVEMENT] %s | TOTAL COST: %d | PATH: ", TSP_ALGO_TYPE(ALGO), DIST);    \
            for(int INDEX = 0; INDEX <= CITY_COUNT; INDEX++)                                    \
            {                                                                                   \
                printf("%d -> %s ", PATH[INDEX], STATE->CITY[PATH[INDEX]].NAME);                \
            }                                                                                   \
            printf("\n");                                                                       \
        } while(0)

    // SIMPLE MACROS FOR HANDLING THE DISTANCE BETWEEN CITIES
    // PROVIDES MORE OF A VERBOSE EXPLAINATION FOR THE HANDLINGS
    // OF THE DISTANCES BETWEEN CITIES (HELPS ESP. FOR RANDOM)

    #if TSP_DEBUG_OPT
    #define TSP_DEBUG_DIST(OP, ERROR, FROM, TO, DIST, MSG, ...)                                     \
        do {                                                                                        \
            printf("[DEBUG] %c -> %s ->     FROM: %d,   TO: %d,     DIST: %1d" MSG "\n",            \
                (char)OP, TSP_ERR_MSG[ERROR], FROM, TO, DIST, ##__VA_ARGS__);                           \
        } while(0)
    #else
        #define TSP_DEBUG_DIST(OP, ERROR, FROM, TO, DIST, MSG, ...) ((void)0)
    #endif

    /////////////////////////////////////////////////////
    //             TSP FUNCTION PROTOTYPES
    /////////////////////////////////////////////////////

    int TSP_INIT(TSP_STATE*, TSP_ALGO);
    int TSP_ADD_CITY(TSP_STATE*, const char*, int, int);
    int TSP_EUC_DIST(const TSP_CITY*, const TSP_CITY*);
    void TSP_CALC_DIST(TSP_STATE*);
    int TSP_NEAREST(TSP_STATE*);
    int TSP_TWO_OPT(TSP_STATE*);
    void TSP_RESULT(const TSP_STATE*);

    int TSP_RAND(TSP_STATE*);
    int TSP_LOAD_CSV(TSP_STATE*, const char*);

    extern int TSP_BEST_DIST;
    extern int TSP_BEST_PATH[TSP_MAX_CITIES + 1];

    static const char* TSP_ERR_MSG[] =
    {
        "OK",
        "INDEX OUT OF BOUNDS",
        "MAX CITIES EXCEEDED",
        "MAX DISTANCE EXCEEDED",
        "MAX VALUE FOR PATHING"
    };

    int TSP_ALGO_CHOICE(TSP_STATE*, TSP_ALGO ALGO);

#endif
#endif
