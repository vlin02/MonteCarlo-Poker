#include <iostream>
#include "samples.h"
#include "simulator.h"
#include "tables.h"
#include "tools.h"
#include "cards.h"
#include "math.h"
using namespace std;


bool sortcol( const vector<double>& v1,
              const vector<double>& v2 ) {
    return v1[0] > v2[0];
}

//vector<string> suit = {"♣️1", "♦️2", "♥️3", "♠️4"};
int main() {
    Simulator sim;
    sim.load_table();

    vector<int> my_hand = {142, 133};
    vector<int> comm_hand = {141, 143, 32, 43, 91};
    sim.my_hand = convert_hand(my_hand);
    sim.comm_hand = convert_hand(comm_hand);
    int N = 100000;

    cout << "Simulating..." << endl;
    double prop = sim.simulate(N);
    double error = calc_error(prop, N);
    printf("%.3f±%.3f%% chance of winning.\n", prop * 100, error * 100);
}