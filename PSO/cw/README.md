## Particle Swarm Optimisation - coursework variations

## Motive:

The ambitiion behind the following implementations is to provide a penultimate understanding by which I am able to understand the requirements and context of a project brief. Notably, in being able to counteract the implications of finanical and environmental costs created by the result of a hub-and-spoke model.

As such, we have been taskd with creating an optimisation technique as a sort of proof-of-concept to help mtiigate these issues in accordance with the aforementioned model.

## How does it work?

The hub-and-spoke model works on the basis by which you have a centralised hub area encompassing all of the correspondence within a particular field. For the sake of the brief in question, this involves a delivery company and the due considerations made when dealing with palletised freight and extnedeed travels as a result.

The penultimate idea is to be able to help reduce this by discerning the best route for travel in relation to the centralised hub area, with the intent of mitigating time, fuel and environmental concerns.


## The dichotomy between the two:

The stark contrast between the two penultimate implementations goes as follows:

There is PSO with Adaptive Inertia Control and MAE - which aims to provide an ease of use means of being able to properly and dynamically reduce unwanted travels by adjusting the position of each swarm in the direction of an arbitrary personal and global best.
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
