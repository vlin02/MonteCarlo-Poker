# MonteCarlo-Poker
Flexible Texas Holdem Poker algorithm for calculating winning probabilities using fast Monte Carlo Simulation.

## About
Currently an exculsively Texas Holdem probability calculator, using random (MonteCarlo) simulation. 
Takes advantage of a comprehensive, but compact (10MB), lookup table for fast simulation speed.
Accepts any number of player hands, including unknown hands, as well as a community hand.

## Benchmarks
Computational time spent running simulations increases linearly with total number of hands, as time complexity
of the program is O(N) with regard to the number of simulations.

Including more variable cards (less community cards or more random hands) will require more random card generation, 
creating additional time delay. While significant, the delay should still be less than the simulation runtime.

Reasonable inputs for **100k** simulations take between **1-2 sec**. for my (Macbook Pro 2.3 GHz Dual-Core Intel Core i5)

## Usage

Load the Simulator

    #include "simulator.h"
    Simulator sim;

Provide poker hand pairs for each player 

    vector<vector<string>> known_hands = {{"Ad", "Kh"}, {"2c", "7d"}};

Provide between 0-5 cards available in the community hand

    vector<string> comm_hand = {"9c"};

Number of MonteCarlo simulations to run

    int N = 100000;

Last parameter is optionally including more players, whose hands are unknown (random)

    vector<vector<int>> results = sim.compute_probabilities(N, comm_hand, known_hands, 3);
    
Simulating...

|Hand  |  Win %|  Tie %|
|------|-------|-------|
|A♦ K♥ |28.460 |  1.682|
|2♣ 7♦ | 9.287 |  1.977|
|?? ?? |19.075 |  2.564|

^ Repeat last row **3x** for 3 random hands

Time elapsed: 1.77971s
