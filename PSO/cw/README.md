## Particle Swarm Optimisation - coursework variations

## Motive:

The ambitiion behind the following implementations is to provide a penultimate understanding by which I am able to understand the requirements and context of a project brief. Notably, in being able to counteract the implications of finanical and environmental costs created by the result of a hub-and-spoke model.

As such, we have been taskd with creating an optimisation technique as a sort of proof-of-concept to help mtiigate these issues in accordance with the aforementioned model.

## How does it work?

The hub-and-spoke model works on the basis by which you have a centralised hub area encompassing all of the correspondence within a particular field. For the sake of the brief in question, this involves a delivery company and the due considerations made when dealing with palletised freight and extnedeed travels as a result.

The penultimate idea is to be able to help reduce this by discerning the best route for travel in relation to the centralised hub area, with the intent of mitigating time, fuel and environmental concerns.


## The dichotomy between the two:

The stark contrast between the two penultimate implementations goes as follows:

There is PSO with Adaptive Inertia Control and MAE - which aims to provide an ease of use means of being able to properly and dynamically reduce unwanted travels by adjusting the position of each swarm in the direction of an arbitrary personal and global best. The other focusses more so on the updating in the velocity and position without any due regard and or knowhow for how components will sway the result of the aforementioned.

Each of these will get updated overtime whenever a new improvement has been made.

The all encompassing method which helps to garner this greater result is through the determinant of the Demand Fitness
It leverages MAE to help produce this result in this tiered guide:

1. A swarm is created of x indicators for y parameters (in the case of the brief, 13 indicators with 14 parameters which act as the amount of demand dimensions as per the indicators)
2. It leverages that previous bias to be able to calculate the absolute value of that indicator by determining the current fitness within the current demand
3. Updates the cureent fitness to be the new personal best assuming that the MAE has been found.
4. Updates the Adaptation of the bias of each indicator against the current swarm iteration (assuming that the current swarm is divisible by the max amount of iterations)
5. Updates the cognitive and social components of the current Swarm. This helps in updating the Velocity against the Inertia to push it along in the aforementioned best direction.
6. Assign the new velocity from said components into the velocity of the current inertia
7. Determine the improvement rates after the fact, assign the final fitness to the global best and record said improvements.


## Where does that leave PSO as a baseline?

Above all, what matters is that we have a means of comparison between the two. When it comes to dealing with PSO as a baseline, we are only concerned with the current iterations of the Swarm. 

The difference being is that there is no longer a need for determining a demand and or predictions as the swarm will update automatically regardless. Through this, while the update is slower in theory, we want this baseline implementation to act as the point of comparison to determine the effectiveness of working with the correspondence from the brief (demand fitness and predictions based on indicators)


## Building:

The structure of this folder is akin to the likeness of any other folder within this repo.
I have split it up based on the simple implementation and the in-depth implementation to make testing easier.

To build either or, run the following within the respective folders:

```
gcc --std=c99 -pedantic main.c pso.c -o pso_adapt -lm

gcc --std=c99 -pedantic main.c pso.c -o pso_simple -lm
``` 

## Academic References:

[PSO Fundamentals](https://www.researchgate.net/publication/228518470_Particle_Swarm_Optimization)

[PSO Optimisations for Parameter Control](https://www.researchgate.net/publication/3755900_A_Modified_Particle_Swarm_Optimizer)

[PSO Adaptive Params](https://arxiv.org/pdf/2308.00936)

[PSO Demand forecasting](https://www.researchgate.net/publication/321815095_Short_term_load_forecasting_using_particle_swarm_optimization_neural_network)

[PSO for Logistics encompassing Demand](https://foi.se/rest-api/report/FOI-R--1180--SE)

[PSO Inertia Weight Formulae](http://www.softcomputing.net/nabic11_7.pdf)
