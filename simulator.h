//
// Created by Victor on 5/21/20.
//

#ifndef SIMULATOR_H
#define SIMULATOR_H
#include "cards.h"
#include "tools.h"
#include <vector>

using namespace std;

class Simulator {
private:
    vector<int> get_remaining(vector<int> &comm_hand, vector<vector<int>> &known_hands);
    vector<vector<int>> fill_empty(int N, vector<int> &comm_hand, vector<vector<int>> &known_hands, int players_unknown);
    int evaluate_selection(vector<int> selection);
    void update_winners(int my_val, int &max_val, int ix, vector<int> &winners);
    void format_result(int N, vector<int> result);
public:
    vector<int> c_table = gen_combo_table(52, 5);
    vector<int> table = read_vect("lookup_tablev3.bin");
    vector<int> replace = {0,1,1,2,2,3,3,4,4,5,0,0,4,6,3,5,2,4,1,3,1,1,2,3,3,4,4,5,2,2,4,6,3,5,3,3,4,5,4,4};
    int to_ckey(const vector<int> &hand);
    vector<int> simulate(vector<int> &selection, vector<vector<int>> &known_hands, vector<int> &sample, int start);
    vector<vector<int>> compute_probabilities(int N, vector<string> comm_hand_str, vector<vector<string>> known_hands_str, int players_unknown);
    void print_results(int N, vector<vector<int>> hands, vector<vector<int>> results);
    vector<vector<int>> calculate(int N, vector<int>comm_hand, vector<vector<int>>known_hands, int players_unknown);
};

#endif
