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
    #define         PSO_MAX_DIM                 14              // ACCOUNTING FOR 1 BIAS FOR EVERY 13 WEIGHTS FOR DEMAND
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

#endif
#endif
