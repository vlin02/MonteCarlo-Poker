#include <iostream>
#include "samples.h"
#include "simulator.h"
#include "tables.h"
#include "tools.h"
#include "cards.h"
#include "math.h"
using namespace std;

int main() {
    Simulator sim;

    vector<vector<string>> known_hands = {{"Ad", "Kh"}}; // Poker hand pairs for each player 
    vector<string> comm_hand = {"Ac", "Ah", "3d", "4h", "9c"}; // Between 0-5 cards available in the community hand

    int N = 100000; // Number of simulations to run

    cout << "Simulating..." << endl;

    // Last parameter is optionally including more players, whose hands are unknown (random)
    vector<vector<int>> results = sim.compute_probabilities(N, comm_hand, known_hands, 2);
}