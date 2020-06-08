//
// Created by Victor on 5/21/20.
//

#ifndef SIMULATOR_H
#define SIMULATOR_H
#include "sparsepp/spp.h"
#include <vector>
using namespace std;

class Simulator {
public:
    vector<int> c_table;
    vector<int> table;
    vector<int> my_hand;
    vector<int> comm_hand;
    int players = 2;
    vector<int> replace = {0,1,1,2,2,3,3,4,4,5,0,0,4,6,3,5,2,4,1,3,1,1,2,3,3,4,4,5,2,2,4,6,3,5,3,3,4,5,4,4};
    vector<int> pow52 = {1, 52, 52 * 52, 52 * 52 * 52, 52 * 52 * 52 * 52};

    void load_table();
    vector<int> get_remaining();
    vector<vector<int>> fill_empty(int N);
    int evaluate_selection(vector<int> selection);
    double simulate(int N);
    int to_ckey(const vector<int> &hand);
};

#endif
