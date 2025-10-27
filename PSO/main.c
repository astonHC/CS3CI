// COPYRIGHT (C) HARRY CLARK 2025
// CS3_CI PARTICLE SWARM OPTIMISATION FOR ANTENNA ARRAY DESIGN

// THIS FILE PERTAINS TOWARDS THE MAIN FUNCTIONALITY OF THE PROGRAM

// NESTED INCLUDES

#include "pso.h"

#define         PSO_NUM_ANTTENNAE            8
#define         PSO_TARGET_ANGLE            (M_PI / 4.0) 

int main(void)
{    
    printf("========================================\n");
    printf("HARRY CLARK - CS3_CI PSO IMPLEMENTATION\n");
    printf("========================================\n");

    PSO STATE;
    time_t START_TIME = time(NULL);
    
    if(PSO_INIT(&STATE, PSO_NUM_ANTTENNAE, PSO_SIMPLE) != 0)
    {
        PSO_ERROR_HANDLE(NONE, PSO_ERROR_PARTICLE, "FAILED TO INITIALISE PSO%s", "");
        return 1;
    }
    
    // SET BOUNDS FOR ANTENNA PHASE WEIGHTS
    for(int DIM = 0; DIM < PSO_NUM_ANTTENNAE; DIM++)
    {
        PSO_SET_BOUNDS(&STATE, DIM, 0.0, 2.0 * M_PI);
    }
    
    if(PSO_OPTIMIZE_ANTENNA(&STATE, PSO_NUM_ANTTENNAE, PSO_TARGET_ANGLE) != 0)
    {
        PSO_ERROR_HANDLE(NONE, PSO_ERROR_PARTICLE, "PSO OPTIMIZATION FAILED%s", " ");
        return 1;
    }

    double ELAPSED = difftime(time(NULL), START_TIME);

     PSO_HANDLE(NONE, PSO_ERROR_NONE, "  ANTENNAE: %d | TARGET: %.2f | PARTICLES: %d", 
        PSO_NUM_ANTTENNAE, PSO_TARGET_ANGLE * 180.0 / M_PI, PSO_MAX_PARTICLES);

        PSO_HANDLE(NONE, PSO_ERROR_NONE, "  FINAL FITNESS: %.6f | ITERATIONS: %d | TIME: %.2fs", 
        STATE.SWARM.GLOBAL_FITNESS, 
        STATE.SWARM.PARTICLE_PARAMS.ITERATION + 1, 
        ELAPSED);

    // DETERMINES HOW MANY CONCURRENT ANTENNAE ARE IN THE SWARM
    for(int DIM = 0; DIM < PSO_NUM_ANTTENNAE; DIM++)
    {
        PSO_HANDLE(NONE, PSO_ERROR_NONE, "  ANTENNA %2d: %.4f RAD (%.2f)", 
            DIM, STATE.SWARM.GLOBAL_POS[DIM], 
            STATE.SWARM.GLOBAL_POS[DIM] * 180.0 / M_PI);
    }

    return 0;

    return 0;
}
