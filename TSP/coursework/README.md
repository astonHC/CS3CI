## Travelling Salesman Problem - Coursework Variation

## Motive:

The ambition behind this sub-section of the TSP implementation is to provide a modularised means by which we can validate novel variants and subsequent adjacencies of my TSP implementation. 
As per the contents of the coursework, I have opted to implement the Local Search Novel Variant which presupposes edge cases for handling cities that are close to each other.

This is predominantly measured through the means of some sort of cost in terms of how many steps each journey makes. 
As such, 2 Opt (Local Search), looks to mitigate any potential overhead and or oversight when it comes to travel - utilising the aforementioned edge cases to eliminate a potential journey that would cost more.

## Example of the above:

```
USAGE: TSP_TWO_OPT in tsp_ls.c
``` 
```c
// DELTA IS THE MEASUREMENT OF TIME ACROSS THE DURATION OF THE ALGO
// IT STORES TIME IN FRAME INTERVALS AND MAPS THAT TO THE CORRESPONDING COST
// OF EACH EDGE CASE - TO DETERMINE EFFICIENCY 
int DELTA = 0;

// REMOVE OLD EDEGS
DELTA -= STATE->DIST.MATRIX[CURRENT_TOUR[INDEX-1]][CURRENT_TOUR[INDEX]];
DELTA -= STATE->DIST.MATRIX[CURRENT_TOUR[ITERATOR]][CURRENT_TOUR[ITERATOR+1]];

// ADD NEW EDGES
DELTA += STATE->DIST.MATRIX[CURRENT_TOUR[INDEX-1]][CURRENT_TOUR[ITERATOR]];
DELTA += STATE->DIST.MATRIX[CURRENT_TOUR[INDEX]][CURRENT_TOUR[ITERATOR+1]];
```

From here it is a case of being able to compare against the previous journey from before, map the new distance to the current and iterate that against the amount of cities provided

```c
// IF WE DONT HAVE ANY NEW SWAPS WITHIN THE TIME FRAME
// REVERSE THE EDGE CASES AGAINST THE CURRENT TOUR
if(DELTA < 0)
{
    // PERFROM THE LOCAL SWAP AGAINST THE EDGE CASES
    TSP_REVERSE(CURRENT_TOUR, INDEX, ITERATOR);

    // DISCERN THE NEW DISTANCE FROM THIS SWAP AND DETERMINE
    // IF THE SWAP IN TERMS OF COST, IS BETTER THAN THE PREVIOUS
    CURRENT_DIST += DELTA;

    // IF THE NEW DISTANCE IS LESS
    // THEN WE SHOULD BE SURE TO MAP IT TO VALIDATE THE IMPROVEMENT
    if(CURRENT_DIST < BEST_DIST)
    {
        BEST_DIST = CURRENT_DIST;
        for(int TOUR_INDEX = 0; TOUR_INDEX <= STATE->CITY_COUNT; TOUR_INDEX++)
        {
            BEST_TOUR[TOUR_INDEX] = CURRENT_TOUR[TOUR_INDEX];
        }

        IMPROVEMENTS++;
        TSP_IMPROVE(STATE->ALGO, BEST_TOUR, BEST_DIST, STATE->CITY_COUNT);
    }

    IMPROVED = 1;
}
```

## Features:

One of the encompassing features found in this variation of the implementation is a pre-processed macro to handle Improvements seen to the Journey at runtime
The benefit of having it arranged as so is to be able tm mitigate function calls - allowing for generic parametisation for all of the pre-requisities

The following will index through each city that is available and print out the current index of the Path against the Name of the City

```c
#define TSP_IMPROVE(ALGO, PATH, DIST, CITY_COUNT)                                           \
        do { \
            printf("[IMPROVEMENT] %s | TOTAL COST: %d | PATH: ", TSP_ALGO_TYPE(ALGO), DIST);    \
            for(int INDEX = 0; INDEX <= CITY_COUNT; INDEX++)                                    \
            {                                                                                   \
                printf("%d -> %s ", PATH[INDEX], STATE->CITY[PATH[INDEX]].NAME);                \
            }                                                                                   \
            printf("\n");                                                                       \
        } while(0)
``` 

## Academic Reference:

[Implementing Local Search - Lourenço, Martin, Stützle (2003)](https://www.metaheuristics.org/downloads/mic2001-ils.pdf)
