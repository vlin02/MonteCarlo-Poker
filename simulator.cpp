//
// Created by Victor on 5/21/20.
//

#include <vector>
#include <iostream>
#include "simulator.h"
#include "tools.h"
#include "cards.h"
#include "samples.h"

using namespace std;

void Simulator::load_table(){
    c_table = gen_combo_table(52, 5);
    table = read_vect("lookup_tablev3.bin");
}

int Simulator::to_ckey(const vector<int> &hand){
    int key = 0;
    for (int i = 0; i < hand.size(); ++i) {
        key += c_table[(i + 1) * 53 + hand[i]];
    }
    return key;
}

vector<int> Simulator::get_remaining(){
    vector<int> remaining;
    vector<int> filled(52);

    for(int card : comm_hand){ filled[card] = 1; }
    for(int card : my_hand){ filled[card] = 1; }

    for (int i = 0; i < 52; ++i) {
        if (! filled[i]) {
            remaining.push_back(i);
        }
    }
    return remaining;
}

vector<vector<int>> Simulator::fill_empty(int N){
    vector<int> remaining = get_remaining();
    int c = players * 2 + 5 - comm_hand.size();
    vector<vector<int>> samples = gen_samples(N, c, remaining.size());

    for(vector<int> &sample : samples){
        for (int i = 0; i < c; ++i) {
            sample[i] = remaining[sample[i]];
        }
    }

    return samples;
}

int Simulator::evaluate_selection(vector<int> selection){
    sort(selection.begin(), selection.end());
    vector<int> hand (5);
    for (int i = 0; i < 5; ++i) {
        hand[i] = selection[i+2];
    }

    int key = to_ckey(hand);
    int max_score = table[key];

    for (int j = 0; j < 40; j+=2) {
        int ix_k = (replace[j] + 1) * 53;
        key += c_table[ix_k + selection[replace[j+1]]] - c_table[ix_k + hand[replace[j]]];

        hand[replace[j]] = selection[replace[j+1]];
        max_score = max(max_score, table[key]);
    }
    return max_score;
}

double Simulator::simulate(int N) {
    clock_t start = clock();
    int s_comm = 5 - (int) comm_hand.size();
    vector<vector<int>> samples = fill_empty(N);
    vector<int> selection(7);

    for (int i = 0; i < comm_hand.size(); ++i) { selection[i] = comm_hand[i];}

    int wins = 0;
    for (vector <int> sample : samples){

        for (int i = 0; i < s_comm; ++i) {
            selection[4 - i] = sample[i];
        }

        selection[5] = my_hand[0]; selection[6] = my_hand[1];
        int my_val = evaluate_selection(selection);
        int j = 0;
        for ( ; j < players; ++j) {
            selection[5] = sample[s_comm + j * 2]; selection[6] = sample[s_comm + 1 + j * 2];
            if (my_val <= evaluate_selection(selection)){ break;}
        }

        wins += j == players ? 1 : 0;
    }
    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("\nTime elapsed: %.5f\n", elapsed);
    return (double) wins / N;
}