// COPYRIGHT (C) HARRY CLARK 2025
// CS3_CI TRAVELLING SALESMAN PROBLEM 

// THIS FILE PERTAINS TOWARDS THE MODULARISATION OF AREAS ENCOMPASSING THE TSP
// AS PER MODULE AND LAB CONTENTS OF CS3_CI

// SPECIFICALLY, THIS FILE FOCUSSES ON THE MODULARISATION OF UTILITY
// USED THROUGHOUT THE IMPLEMENTATION - KEPT IN A SEPERATE FILE TO 
// REDUCE CLUTTER

// NESTED INCLUDES 

#include "tsp.h"

// CALCULATES THE EUCLIDEAN DISTANCE BETWEEN EACH CITY
// THE COMMONALITY WITH THE TSP IS THAT WE ALWAYS PRESUPPOSE
// THAT EACH OF THE CITY ARE REPRESENTED BY PLANAR MAPPING
//
// WHICH MAKES ACCOUNTING FOR AXIS' A LOT EASIER 
double TSP_EUC_DIST(const TSP_CITY* CITY_A, const TSP_CITY* CITY_B) 
{
    double DIST_X = CITY_A->X - CITY_B->X;
    double DIST_Y = CITY_A->Y - CITY_B->Y;

    // FORCE TYPE CAST FOR DISTANCE
    // WE LEVERAGE INT FOR GREATER PRECISION
    // SQUARE ROOT HELPS WITH PRECISION MULTIPLICATION
    return sqrt(DIST_X * DIST_X + DIST_Y * DIST_Y);
}

// CALCULATES THE DISTANCE MATRIX FOR ALL CITY PAIRS
// UTILISES MATRIX ADDITION TO INDEX THROUGH THE RESPECTIVE CITY COUNT
// AND DETERMINES THE DISTANCE BETWEEN THEM
void TSP_CALC_DIST(TSP_STATE* STATE)
{
    // DETERMINE THE DISTANCE SIZE BASED ON THE NUMBER OF CITIES
    // WHICH WILL GROW EXPONENTIALLY 
    STATE->DIST.SIZE = STATE->CITY_COUNT;

    for(int INDEX = 0; INDEX < STATE->CITY_COUNT; INDEX++)
    {
        for(int ITERATOR = 0; ITERATOR < STATE->CITY_COUNT; ITERATOR++)
        {
            // IF ANY TWO CITIES ARE NOT THE SAME
            if(INDEX != ITERATOR)
            {
                // CHECK THE DISTANCE BETWEEN SUCH
                // CASTING IT AS SUCH HELPS ESPECIALLY WITH THE DEBUG INFO
                double DISTANCE = TSP_EUC_DIST(&STATE->CITY[INDEX], &STATE->CITY[ITERATOR]);
                STATE->DIST.MATRIX[INDEX][ITERATOR] = DISTANCE;

                TSP_DEBUG_DIST(DIST, TSP_ERROR_NONE, INDEX, ITERATOR, DISTANCE, 
                    " - %s TO %s", STATE->CITY[INDEX].NAME, STATE->CITY[ITERATOR].NAME);
            }
            else
            {
                STATE->DIST.MATRIX[INDEX][ITERATOR] = 0;
            }
        }
    }
}

// SIMPLE DISPATCH FUNCTION FOR GETTING THE 
// CORRESPONDING ALGORITHM TYPE - PREVENTING UNWANTED EXECUTIONS
int TSP_ALGO_CHOICE(TSP_STATE* STATE, TSP_ALGO ALGO)
{
    switch (ALGO)
    {
        case TSP_NN:
            TSP_NEAREST(STATE);
            break;

        case TSP_ACO:
            TSP_ACO_BASE(STATE, 10);
            return 1;

        case TSP_LS:
            TSP_TWO_OPT(STATE);
            return 1;
    
        default:
            exit(1);
        break;
    }

    return 0;
}

// LOAD THE CORRESPONDING CSV FILE FOR THE ENCOMPASSING ALGORITHM OF CHOICE
// THIS IS NEEDED AS PER THE REQUIREMENTS OF THE SIGN OFF

int TSP_LOAD_CSV(TSP_STATE* STATE,  const char* FILENAME)
{
    FILE* FILE_PTR = NULL;
    char CSV_LINE_BUFFER[TSP_MAX_BUFFER];
    int CSV_LINE_NUM = 0;
    int CSV_COORDS = 0;

    FILE_PTR = fopen(FILENAME, "r");
    if(FILE_PTR == NULL)
    {
        TSP_ERROR_HANDLE(NONE, TSP_ERROR_NONE, "FAILED TO LOAD CSV FILE: %s\n", FILE_PTR);
        return 1;
    } 

    TSP_HANDLE(NONE, TSP_ERROR_NONE, "LOADING CITIES FROM CSV: %s\n", FILENAME);

    // NOW WE CAN BEGIN TO READ THE FILE LINE BY LINE
    // THIS IS SIMPLE AS ALL WE ARE CONCERNED WITH IS THE COLUMNS
    while(fgets(CSV_LINE_BUFFER, sizeof(CSV_LINE_BUFFER), FILE_PTR) != NULL)
    {
        CSV_LINE_NUM++;

        // SKIP WHITESPACES CAUSED BY TABS, SPACES OR COMMENTS
        if(CSV_LINE_BUFFER[0] == '\n' || CSV_LINE_BUFFER[0] == '#') continue;

        // ITERATE THROUGH EACH INSTANCE OF WHITESPACE WITHIN THE
        // FILE AND DETERMINE IT'S UNICODE REPRESENTTATION 
        int IS_EMPTY = 1;
        for(int INDEX = 0; CSV_LINE_BUFFER[INDEX] != '\0'; INDEX++)
        {
            if(CSV_LINE_BUFFER[INDEX] != ' ' && CSV_LINE_BUFFER[INDEX] != '\t' && 
               CSV_LINE_BUFFER[INDEX] != '\n' && CSV_LINE_BUFFER[INDEX] != '\r')
            {
                IS_EMPTY = 0;
                break;
            }
        }

        // READ FOR ALL OF THE POSSIBLE COORD
        // VALUES WITHIN EACH COLUMN
        double X_COORD, Y_COORD;
        int PARSED = 0;
        
        // CHECK TO SEE IF COORDS ARE SPLIT BASED ON COMMA (UNLIKELY)
        int COMMA = (strchr(CSV_LINE_BUFFER, ',') != NULL);
        PARSED = COMMA ? sscanf(CSV_LINE_BUFFER, "%lf, %lf", &X_COORD, &Y_COORD) 
                        : sscanf(CSV_LINE_BUFFER, "%lf %lf", &X_COORD, &Y_COORD);
        
        if(PARSED != 2)
        {
            // SKIP HEADER LINE TO PREVENT READING THE
            // X AND Y NOTATION
            if(CSV_LINE_NUM == 1)
            {
                TSP_HANDLE(NONE, TSP_ERROR_NONE, "SKIPPING HEADER LINE\n", " ");
            }
            else
            {
                TSP_HANDLE(NONE, TSP_ERROR_NONE, 
                    "SKIPPING INVALID LINE %d - EXPECTED TWO SET OF COORDINATES FOR X AND Y\n", CSV_LINE_NUM);
            }

            continue;
        }
        
        // EXPRESSION PERTAINING TOWARDS
        // THE X AND Y HEADERS FOR EACH COLUMN
        double X = X_COORD;
        double Y = Y_COORD;
        
        // FOR THE SAKE OF DEMONSTRATION
        // MAKE A REPRESENTATION OF THE CITY WITHIN THE 
        // TOUR BASED ON COORDS
        char NAME[TSP_MAX_NAME];
        snprintf(NAME, TSP_MAX_NAME, "CITY_%d", CSV_COORDS);
        
        if(TSP_ADD_CITY(STATE, NAME, X, Y) == 0)
        {
            CSV_COORDS++;
        }
        else
        {
            TSP_HANDLE(NONE, TSP_ERROR_NONE, 
                "WARNING: FAILED TO ADD CITY FROM LINE %d\n", CSV_LINE_NUM);
        }
    }
    
    fclose(FILE_PTR);
    TSP_HANDLE(NONE, TSP_ERROR_NONE, 
        "SUCCESSFULLY LOADED %d CITIES FROM CSV\n", CSV_COORDS);
    
    return 0;
}
