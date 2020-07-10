# MonteCarlo-Poker
Flexible Texas Holdem Poker algorithm for calculating winning probabilities using fast Monte Carlo Simulation.

## About
Currently an exculsively Texas Holdem probability calculator, using random (MonteCarlo) simulation. 
Takes advantage of a comprehensive, but compact (10MB), lookup table for fast simulation speed.
Accepts any number of player hands, including unknown hands, as well as a community hand. A more detailed
explanation of the inner-workings is at the bottom if you're **really** curious.

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


# How the numbers are CRUNCHED
Fast poker simulations depend on two variables 1) time spent generating random samples 2) time spent evaluating winner of each sample.
MonteCarlo-poker acheives both at linear time.

## Random hand generation
For a single simulation, random cards fill in the remaining community cards and random hands. Thus, it boils down to being able to efficiently
generating random n (52 - cards from community and holes) choose k (# of random cards needed) combinatorials with no replacement. 

Unfortunately I found no online solution, so I created my own. The procedure involves taking enough repitition of each of the n available cards
and shuffling them into a random sequence. MonteCarlo Poker then iterates along the sequence to generate the samples, keeping track of the placement 
of each of the n unique  cards to ensure each samples contains unique cards.

### Some math...
The efficiency of this sequence-based algorithm is mostly because length of the sequence is barely greater than, but still suffices, to carry out
the procedure above (for large N). In particular, if L = ceil(N * k) /n, MonteCarlo-Poker generates a (L * n)-length random sequence.

## Hand Evaluations
MonteCarlo poker only needs to do 21 lookups (7 choose 5 cards) to determine the strength of a hand. Transitions between each 5 card combination
are also optimized, with inspiration from Heap's algorithm.

The lookup table itself is a single array of size 2.6M (52 choose 5 cards), mapping every 5 card combination to a unique "score". A combinatorial 
number system is leveraged, allowing for a dense one-to-one mapping of each combinations to a unique index in the table up to (52 choose 5). For the geeks,
some basic DP using pascal's triangle was used to quickly create a combinatorial lookup table to convert each combination to a vector index :).

Each score is calculated such that the lowest score represents the worst hand all the way ranging to the highest score representing the best hand. 
Thus, these scores can be used to quickly determine the best 5 card combination of the hand. The score-space is approximately 260M, so even the 
largest score fits in an int32.

That's it folks!





