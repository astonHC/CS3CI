## Travelling Salesman Problem

## Motive:

The following serves to provide my implememtation for the enigmatic Travelling Sales Problem presented as per the lecture materials within Week 1.

The idea with this introductory algorithm is that it is meant to provide us with an opportunity to be able to become accustomed to new means of Computational Intelligence, to look beyond the looking-glass at how we are able to implement.

This should prove to be fruitful once it comes to contextualisation and comparison betweens various other algorithms.

## What is TSP?

Akin to the likeness of Djisktra's or any other A* searching/path finding, TSP aims to be a quick and modularised implementation of being able to find the quickest path. The scenario is to project the quickest path by which the Salesman is able to get the most out of their sales.
Using Matrix Addition, we are able to create a pseudo-implementation to determine the most viable option in accordance with these parameters:

  - PARAMS OF THE CITY
  - NAME
  - X POS
  - Y POS
  - SUBSEQUENT DISTANCE

```c
int TSP_ADD_CITY(TSP_STATE* STATE, const char* NAME, int X, int Y);

// CITIES CAN BE DEFINED STATICALLY AS SHOWN
TSP_ADD_CITY(&STATE, "LONDON", 0, 0);
TSP_ADD_CITY(&STATE, "PARIS", 344, 0);
``` 

The following implementation of TSP looks to determine how efficiently we are able to traverse between cities leveraging Nearest Neighbour. Whereby, we concern ourselves with the Planar Projection of Axis to determine the Euclidean distance between the index of paramatised ``CITY_A`` & ``CITY_B``

```c
int TSP_EUC_DIST(const TSP_CITY* CITY_A, const TSP_CITY* CITY_B) 
{
    int DIST_X = CITY_A->X - CITY_B->X;
    int DIST_Y = CITY_A->Y - CITY_B->Y;

    // FORCE TYPE CAST FOR DISTANCE
    // WE LEVERAGE INT FOR GREATER PRECISION
    // SQUARE ROOT HELPS WITH PRECISION MULTIPLICATION
    return (int)sqrt(DIST_X * DIST_X + DIST_Y * DIST_Y);
}
```

## Features:

Keep track of the Euclidean Distance between Cities and their respective parameters by leveraging the ``TSP_DEBUG_DIST`` macro.

This aims to provide a compile-time solution to accessing the proper indexxing between cities and the journey taken between indexes - providing a greater "under the hood" look at what is going on.

```c
#define TSP_DEBUG_DIST(OP, ERROR, FROM, TO, DIST, MSG, ...)                                     \
        do {                                                                                        \
            printf("[DEBUG] %c -> %s ->     FROM: %d,   TO: %d,     DIST: %1d" MSG "\n",            \
                (char)OP, TSP_ERR[ERROR], FROM, TO, DIST, ##__VA_ARGS__);                           \
        } while(0)

// USAGE: - TSP_CALC_DIST
// CAST THE DISTANCE TO A VARIABLE TO GAIN BETTER DEBUG RESULTS
int DISTANCE = TSP_EUC_DIST(&STATE->CITY[INDEX], &STATE->CITY[ITERATOR]);
STATE->DIST.MATRIX[INDEX][ITERATOR] = DISTANCE;

TSP_DEBUG_DIST(DIST, TSP_ERROR_NONE, INDEX, ITERATOR, DISTANCE, 
  " - %s %s", STATE->CITY[INDEX].NAME, STATE->CITY[ITERATOR].NAME);
```

## Building:

It is just a simple case of running the following within this folder 
```
gcc --std=c99 -pedantic main.c tsp.c -o tsp -lm

./tsp
``` 

To buld the coursework ver, do the following
```
gcc --std=c99 -pedantic main.c tsp.c tsp_ls.c util.c -o tsp_cw -lm

./tsp_cw
```
