## PSO (Particle Swarm Optimisation)

## Motive:

The ambition behind this sub-section of this repository is to provide my penultimate implementation for the contents surrounding Particle Swarm Optimisation. Given the contents of the coursework, I decided to retool this implementation to serving that purpose.

The purpose of such was to provide an understanding and subsequent implementation of a novel variant of a generic EC algorithm leveraging antenna array design - which presupposes two points which diffuse from one another to optimise the link between points.

The aforementioned "diffuse" between these points is the result of a desired radiation pattern based on areas of concentration where the Particles mostly reside.

Leveraging this novel variant allows for greater optimisations to generating minimal search space to garner greater results.

## Implementation:

The implementation regarding Antenna Array goes as follows:

The first call of order is to establish the basis by which we are able to generate the cluster of Particles within the Swarm, to determine the inertia and convergence of it's type.

This is important because during Antenna Array, a wavelength pattern is created - much similar to the diffuse description above. Using variables such as Phase Shift and Summation, we are able to derive a pseudo implementation of interpolation betweens particles to create a smoother convergence/diffuse.

The main goal of Antenna Array above all is to create this convergence through a desired Antenna Angle, which subsequently plays into the "smoothing out" so to speak of the pattern overtime based on these parameters:

``PSO_ANTENNA_FITNESS``

```c
for(int INDEX = 0; INDEX < NUM_ANTENNAE; INDEX++)
{
  double PHASE = POSITION[INDEX];
  double ELEMENT_POS = (double)INDEX * PSO_ANTENNA_SPACE * WAVELENGTH;
  double PHASE_SHIFT = K * ELEMENT_POS * sin(ANGLE);
  double TOTAL_PHASE = PHASE + PHASE_SHIFT;
            
  REAL_SUM += cos(TOTAL_PHASE);
  IMAGE_SUM += sin(TOTAL_PHASE);
}
```

All of the constants pertaining towards the lifetime of the algorithm, the countless iteratiosn and the space by which Swarms take up and their respective convergence can all be tweaked with here:

```c
    #define         PSO_MAX_PARTICLES           30
    #define         PSO_MAX_ITERATIONS          100
    #define         PSO_MAX_DIMENSIONS           10

    #define         PSO_WEIGHT                      0.8
    #define         PSO_COG                         1.5
    #define         PSO_SOC                         1.5
    #define         PSO_RANGE_EXPO                  0.1

    #define         PSO_INERTIA_MIN                 0.1
    #define         PSO_INERTIA_MAX                 1.0
    #define         PSO_VELOCITY_CLAMP              0.2
    #define         PSO_DAMP                        0.5
    #define         PSO_ANTENNA_WAVELENGTH          1.0
    #define         PSO_ANTENNA_SPACE               0.5
    #define         PSO_ANTENNA_SAMPLES             180
    #define         PSO_MAINLOBE_WIDTH              0.1

    #define         PSO_LIMIT                       5.0
``` 

## Building:

To build this project, it is a simple case of running the following within this folder:

```
gcc --std=c99 -pedantic main.c pso.c -o pso -lm

./pso
``` 
