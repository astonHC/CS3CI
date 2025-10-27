// COPYRIGHT (C) HARRY CLARK 2025
// CS3_CI PARTICLE SWARM OPTIMISATION FOR GENETIC PROGRAMMING

// THIS FILE PERTAINS TOWARDS THE PSO ALGORITHM FOR OPTIMISING
// GENETIC PROGRAMMING PARAMETERS AND FITNESS EVALUATION

// SPECIFICALLY, THIS VERSION OF THE PSO IMPLEMENTATION
// AIMS TO PROVIDE AN UNDERSTANDING FOR HOW TO MITIGATE AN ISSUE
// RELATED TO THE DAILY DEMAND OF A LOGISTICS COMPANY

// LEVERAGING ADAPTIVE INERTIA CONTROL FOR GENERATING
// A BEST FIT SOLUTION BASED CURRENT FITNESS - MADE POSSIBLE BY DYNAMICALLY
// ADJUSTING THE WEIGHT OF PARTICLES BASED ON THEIR CHARACTERISTICS 
// DURING THE LIFETIME OF THE ALGORITHM

#ifndef PSO_H
#define PSO_H

// SYSTEM INCLUDES

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(USE_PSO)
    #define USE_PSO
#else
    #define USE_PSO

    #define         PSO_MAX_PARTICLES           50
    #define         PSO_MAX_ITER                1000
    #define         PSO_MAX_IND                 13
    #define         PSO_MAX_DEM                 14              // ACCOUNTING FOR 1 BIAS FOR EVERY 13 WEIGHTS FOR DEMAND
    #define         PSO_MAX_CONV                20
    
    #define         PSO_MAX_INERTIA             1.2
    #define         PSO_MIN_INERTIA             0.9
    #define         PSO_COG_INIT                2.5
    #define         PSO_COG_FIN                 0.5
    #define         PSO_SOC_INIT                0.5
    #define         PSO_SOC_FIN                 2.5
    #define         PSO_DIV                     0.01

    #define         PSO_RAND()                  ((double)rand()/ (double)RAND_MAX)
    #define         PSO_SEED()                  srand((unsigned)time(NULL))

    // DEFINE THE BASIS FOR THE BOUNDARYS FOR THE SEARCH SPACE
    typedef struct
    {
        double LOWER;
        double UPPER;
        
    } PSO_BOUND;

    // DEFINE THE BASIS FOR THE DEMAND DATA
    // PRESUPPOSES THE FOLLOWING PARAMETERS:
    //
    // DEMAND: THE ACTUAL DEMAND VALUE AGAINST THE BIAS
    // INDICATIONS: THE WEIGHTS INDICATING CHANGE OF DEMAND IN RELATION TO INERTIA
    typedef struct
    {
        double DEMANDS;
        double INDICTIONS[PSO_MAX_IND];

    } PSO_DEMAND;   

    // DEFINE THE BASIS FOR THE PARTICLES WITHIN THE ALGO
    typedef struct
    {
        double POSITION[PSO_MAX_DEM];
        double VELOCITY[PSO_MAX_DEM];
        double PBEST[PSO_MAX_DEM];
        double PBEST_FITNESS[PSO_MAX_DEM];
        double CURRENT_FITNESS;
        int STAGNATE;
        
    } PSO_PARTICLE;

    // DEFINE THE BASIS FOR THE ERROR HANDLING 
    // EXCLUSIVE TO THIS IMPLEMENTATION OF PSO
    typedef enum
    {
        PSO_ERROR_NONE = 0,
        PSO_ERROR_OOB,
        PSO_ERROR_PARTICLE,
        PSO_ERROR_CONVERGENCE,
        PSO_ERROR_FITNESS,
        PSO_ERROR_DIM,
        PSO_ERROR_FILE,
        PSO_ERROR_MEM

    } PSO_ERROR_TYPE;

    static const char* PSO_ERR[] =
    {
        "OK",
        "INDEX OUT OF BOUNDS",
        "PARTICLE ERROR",
        "CONVERGENCE ERROR",
        "FITNESS ERROR",
        "DIMENSION ERROR",
        "FILE IO ERROR",
        "MEMORY ERROR"
    };


    typedef enum
    {
        NONE = 'N',
        OOB = 'O',
        PART = 'P',
        CONV = 'C',
        FIT = 'F',
        DIM = 'D'

    } PSO_ERROR_OP;

    #define PSO_HANDLE(OP, ERROR, MSG, ...) \
            do { \
                printf("\n[INFO] %c -> %-20s   " MSG "\n", \
                    (char)OP, PSO_ERR[ERROR], ##__VA_ARGS__); \
            } while(0)

    #define PSO_ERROR_HANDLE(OP, ERROR, MSG, ...) \
            do { \
                printf("[ERROR] %c -> %-20s   " MSG "\n", \
                    (char)OP, PSO_ERR[ERROR], ##__VA_ARGS__); \
            } while(0)

    #define PSO_FITNESS_NAME(VALUE) \
        ((VALUE) == PSO_SIMPLE ? "SIMPLE" : \
        (VALUE) == PSO_VALLEY ? "VALLEY" : \
        "UNKNOWN")

    #define PSO_IMPROVE(ITER, FITNESS, POSITION, DIMENSIONS)                                    \
        do {                                                                                    \
            printf("[PSO-ADAPTIVE] ITERATION %d | FITNESS: %.6f | SOLUTION: ",                  \
                ITER, FITNESS);                                                                 \
            for(int DIM = 0; DIM < DIMENSIONS; DIM++)                                           \
            {                                                                                   \
                printf("%.4f", POSITION[DIM]);                                                  \
                if(DIM < DIMENSIONS - 1) printf(", ");                                          \
            }                                                                                   \
            printf("\n");                                                                       \
        } while(0)

    #define PSO_VALID_DIM(MIN, MAX)         ((MIN) > 0 && (MIN) < (MAX))
    

#endif
#endif
