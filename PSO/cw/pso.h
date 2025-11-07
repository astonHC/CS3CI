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

    #define         PSO_OPT_ON                  1
    #define         PSO_OPT_OFF                 0

    #define         PSO_MAX_PARTICLES           50
    #define         PSO_MAX_ITER                1000
    #define         PSO_MAX_IND                 13
    #define         PSO_MAX_DEM                 14                  // ACCOUNTING FOR 1 BIAS FOR EVERY 13 WEIGHTS FOR DEMAND
    #define         PSO_MAX_CSV                 100
    #define         PSO_CSV_BUFFER              1024
    
    #define         PSO_MAX_INERTIA             0.9
    #define         PSO_MIN_INERTIA             0.6
    #define         PSO_COG_INIT                2.0
    #define         PSO_COG_FIN                 2.0
    #define         PSO_SOC_INIT                2.0
    #define         PSO_SOC_FIN                 2.0
    #define         PSO_INER_DAMP               -0.5

    #define         PSO_VELO_DELTA              0.2
    #define         PSO_ADAPT_GRAD              1.0
    #define         PSO_ADAPT_PEAK              10.0
    #define         PSO_ADAPT_INTER             0.5

    #define         PSO_VALID_DIM(MIN, MAX)     ((MIN) >= 0 && (MIN) < (MAX))
    #define         PSO_RAND()                  ((double)rand()/ (double)RAND_MAX)
    #define         PSO_SEED()                  srand((unsigned)time(NULL))

    #define         PSO_DEBUG                   PSO_OPT_OFF

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
        double INDICATIONS[PSO_MAX_IND];

    } PSO_DEMAND;
    
    // DEFINE THE BASIS FOR THE DATASET
    // THAT WILL BE TRAINED ON IN RELATION TO THE CSV
    typedef struct
    {
        PSO_DEMAND* DATA;
        int SIZE;
        int CAPACITY;

    } PSO_DATASET;

    // DEFINE THE BASIS FOR THE PARTICLES WITHIN THE ALGO
    typedef struct
    {
        double POSITION[PSO_MAX_DEM];
        double VELOCITY[PSO_MAX_DEM];
        double PBEST[PSO_MAX_DEM];
        double PBEST_FITNESS;
        double CURRENT_FITNESS;
        int STAGNATE;
        int COUNT;

    } PSO_PARTICLE;

    // DEFINE THE BASIS FOR THE SWARM
    typedef struct
    {
        PSO_PARTICLE PARTICLES[PSO_MAX_PARTICLES];
        int ITERATION;
        double GBEST[PSO_MAX_DEM];
        double GBEST_FITNESS;

        int CONVERGED;
        double DIVERSITY;
        int STAGNATE;

    } PSO_SWARM;

    // DEFINE THE BASIS FOR TRACKING THE STATISTICS
    // OF THE RUNTIME AND IMPROVEMENTS OF THE ALGO
    typedef struct
    {
        int HISTORY_SIZE;
        int CONVERGENCE_ITER;
        double INIT_FITNESS;
        double FINAL_FITNESS;
        double IMPROVEMENT_RATE;
        double* GBEST_HISTORY;
        double* FITNESS_HISTORY;
        double* DIVERSITY_HISTORY;

    } PSO_STATS;

    // DEFINE THE BASIS FOR THE ALL ENCOMPASSING
    // STATE FOR THE ALGO
    typedef struct
    {
        PSO_SWARM SWARM;
        PSO_BOUND BOUNDS[PSO_MAX_DEM];
        PSO_STATS STATS;
        PSO_DATASET DATASET;

        int DIMENSIONS;
        double CONV_THRESHOLD;
        double CURRENT_INERTIA;
        double CURRENT_COG;
        double CURRENT_SOC;

    } PSO_STATE;

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

    typedef enum
    {
        NONE = 'N',
        OOB = 'O',
        PART = 'P',
        CONV = 'C',
        FIT = 'F',
        DIM = 'D',
        IO = 'I',
        MEM = 'M'

    } PSO_ERROR_OP;

    #define PSO_HANDLE(OP, ERROR, MSG, ...) \
            do { \
                printf("\n[INFO] %c -> %-20s   " MSG "", \
                    (char)OP, PSO_ERR[ERROR], ##__VA_ARGS__); \
            } while(0)

    #define PSO_ERROR_HANDLE(OP, ERROR, MSG, ...) \
            do { \
                printf("[ERROR] %c -> %-20s   " MSG "", \
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
            for(int D = 0; D < DIMENSIONS; D++)                                                 \
            {                                                                                   \
                printf("%.4f", POSITION[D]);                                                    \
                if(DIM < DIMENSIONS - 1) printf(", ");                                          \
            }                                                                                   \
            printf("\n");                                                                       \
        } while(0)

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
    
    int PSO_LOAD_CSV(PSO_DATASET*, const char*);
    int PSO_INIT(PSO_STATE*, int);
    void PSO_SET_BOUNDS(PSO_STATE*, int, double, double);
    double PSO_DEMAND_FITNESS(const double*, const PSO_DATASET*);
    void PSO_OPTIMISE(PSO_STATE*);

    typedef PSO_STATE* STATE;
    typedef PSO_DATASET* DATASET;
    typedef PSO_PARTICLE* PARTICLE;
    typedef PSO_SWARM* SWARM;

#endif
#endif
