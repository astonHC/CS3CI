# CS3_CI
All of my study material pertaining towards the Computational Intelligence Module (Aston University)

## Motive:

This repository aims to provide reliable solutions for any and all problems discussed and studied in the Computational Intelligence module - this serves to be my learning aid moreover if anything else. 

## Contents:

The following topics and subject areas that will be provided in this repository are the following:

Note that some of the implementation was made pre-emptively before the module began. Anything shown may be subject to change or to reflect an outdated understanding of the module contents. Though, having said all of this, everything here should still be taken with the due-consideration for the module contents and subsequent preparations made therein.

- [Evolutionary Computation](https://github.com/astonHC/CS3_CI/tree/main/EC)
- [Travelling Salesman Problem - standalone lab ver](https://github.com/astonHC/CS3_CI/tree/main/TSP)
- [Particle Swarm Optimisation - sign-off ver](https://github.com/astonHC/CS3_CI/tree/main/PSO)
- [Travelling Salesman Problem - sign-off ver](https://github.com/astonHC/CS3_CI/tree/main/TSP/coursework)
- [Particle Swarm Optimsation - experimental study ver](https://github.com/astonHC/CS3_CI/tree/main/PSO/cw)
- [Particle Swarm Optimisation - experimental comparison ver](https://github.com/astonHC/CS3CI/blob/main/PSO/cw/pso_simple/)

## Repository Structure & Building:

Each of the subject areas will be delegated to their own folder, each with their own source file.

To run each solution, look at he provided build instructions in each folder's README

## Features:

One of the many features exclusive to this project is the ``ERROR_HANDLE`` handling for being able to properly discern the inner workings 
of all of the contents encompassing this repository

Each of these error handlers have been retooled to suit the needs of each algorithm type - a statically-available macro with respective error messages per algorithm

A similar addition has been made to properly discern the improvement rates of each algorithm using the respective Improvement macro
In the case of PSO, its a simple checker which looks through the dimensions of the current swarm to determine the current improvement based on updated position ([see](https://github.com/astonHC/CS3CI/tree/main/PSO/cw))

```c
#define PSO_ERROR_HANDLE(OP, ERROR, MSG, ...) \
            do { \
                printf("[ERROR] %c -> %-20s   " MSG "", \
                    (char)OP, PSO_ERR[ERROR], ##__VA_ARGS__); \
            } while(0)
```

```c
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
```
