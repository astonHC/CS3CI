## PSO (Particle Swarm Optimisation)

## Motive:

The ambition behind this sub-section of this repository is to provide my penultimate implementation for the contents surrounding Particle Swarm Optimisation. Given the contents of the coursework, I decided to retool this implementation to serving that purpose.

The purpose of such was to provide an understanding and subsequent implementation of a novel variant of a generic EC algorithm leveraging antenna array design - which presupposes two points which diffuse from one another to optimise the link between points.

The aforementioned "diffuse" between these points is the result of a desired radiation pattern based on areas of concentration where the Particles mostly reside.

Leveraging this novel variant allows for greater optimisations to generating minimal search space to garner greater results.


## Features:

As of right now, what with this implementation being a WIP, implementation in terms of core functionality through header files for accessing debug information remains to be the same - though this will vary marginally throughout subsequent changes and additions.

## Building:

To build this project, it is a simple case of running the following within this folder:

```
gcc gcc --std=c99 -pedantic main.c pso.c -o pso -lm

./pso
``` 
