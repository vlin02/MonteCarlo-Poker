//
// Created by Victor on 5/21/20.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include "simulator.h"
#include "tools.h"
#include "samples.h"
#include "cards.h"

using namespace std;

int Simulator::to_ckey(const vector<int> &hand)
{
    int key = 0;
    for (int i = 0; i < hand.size(); ++i)
    {
        key += c_table[(i + 1) * 53 + hand[i]];
    }
    return key;
}

vector<int> Simulator::get_remaining(vector<int> &comm_hand, vector<vector<int>> &known_hands){
    vector<int> remaining;
    vector<int> filled(52);

    for (int card : comm_hand){
        filled[card] = 1;
    }

    for (vector<int> known_hand : known_hands){
        for (int card : known_hand){
            filled[card] = 1;
        }
    }

    for (int i = 0; i < 52; ++i){
        if (!filled[i]){
            remaining.push_back(i);
        }
    }

    return remaining;
}

vector<vector<int>> Simulator::fill_empty(int N, vector<int> &comm_hand, vector<vector<int>> &known_hands, int players_unknown){
    vector<int> remaining = get_remaining(comm_hand, known_hands);
    int c = players_unknown * 2 + 5 - comm_hand.size();
    vector<vector<int>> samples = gen_samples(N, c, remaining.size());

    for (vector<int> &sample : samples)
    {
        for (int i = 0; i < c; ++i)
        {
            sample[i] = remaining[sample[i]];
        }
    }

    return samples;
}

int Simulator::evaluate_selection(vector<int> selection){

    sort(selection.begin(), selection.end());
    vector<int> hand(5);

    for (int i = 0; i < 5; ++i){
        hand[i] = selection[i + 2];
    }

    int key = to_ckey(hand);
    int max_score = table[key];

    for (int j = 0; j < 40; j += 2){
        int ix_k = (replace[j] + 1) * 53;
        key += c_table[ix_k + selection[replace[j + 1]]] - c_table[ix_k + hand[replace[j]]];

        hand[replace[j]] = selection[replace[j + 1]];
        max_score = max(max_score, table[key]);
    }
    return max_score;
}

void Simulator::update_winners(int my_val, int &max_val, int ix, vector<int> &winners){
    if (my_val > max_val){
        winners = {ix};
        max_val = my_val;
    }
    else if (my_val == max_val){
        winners.push_back(ix);
    }
}

vector<int> Simulator::simulate(vector<int> &selection, vector<vector<int>> &known_hands, vector<int> &sample, int start){

    vector<int> winners;
    int max_val = 0;

    for (int i = 0; i < known_hands.size(); i++){
        selection[5] = known_hands[i][0];
        selection[6] = known_hands[i][1];

        update_winners(evaluate_selection(selection), max_val, i, winners);
    }

    int opp_max_val = 0;
    int opp_max = 0;

    for (int i = 0; start + i * 2 < sample.size(); i ++){
        selection[5] = sample[start + i * 2];
        selection[6] = sample[start + 1 + i * 2];

        update_winners(evaluate_selection(selection), max_val, known_hands.size() + i, winners);
    }

    return winners;
}

vector<vector<int>> Simulator::calculate(int N, vector<int>comm_hand, vector<vector<int>>known_hands, int players_unknown){

    vector<vector<int>> samples = fill_empty(N, comm_hand, known_hands, players_unknown);
    vector<int> selection(7);
    vector<vector<int>> results(known_hands.size() + players_unknown, vector<int>(2, 0));

    for (int i = 0; i < comm_hand.size(); ++i){
        selection[i] = comm_hand[i];
    }
    
    int s_comm = 5 - (int)comm_hand.size();

    int cnt = 0;
    for (vector<int> sample : samples){
        cnt++;

        for (int i = 0; i < s_comm; ++i){
            selection[4 - i] = sample[i];
        }

        vector<int> winners = simulate(selection, known_hands, sample, s_comm);
        
        if (winners.size() == 1) {
            results[winners[0]][0]++;
        } else {
            for (int winner : winners) {
                results[winner][1]++;
            }
        }
    }

    return results;
}

void Simulator::print_results(int N, vector<vector<int>> hands, vector<vector<int>> results) {
    float known_wins = 0;
    for (int i = 0; i < hands.size(); i++) {
        print_hand(hands[i]);
        format_result(N, results[i]);
        known_wins += results[i][0];
    }

    int unknown = results.size() - hands.size();

    if (unknown > 0) {
        float ties = 0;
        for (int i=hands.size(); i < results.size(); i++){
            ties += results[i][1];
        }

        printf("?? ?? %6.3f  %6.3f (x%d random hands)\n", (N - known_wins)*100/N/unknown, ties*100/N/unknown, unknown);
    }
}

void Simulator::format_result(int N, vector<int> result) {
    printf("%6.3f  %6.3f\n", result[0]*100.0/N, result[1]*100.0/N);
}

vector<vector<int>> Simulator::compute_probabilities(int N, vector<string> comm_hand_str, vector<vector<string>> known_hands_str, int players_unknown){

    clock_t start = clock();
    
    vector<int> comm_hand = convert_hand(comm_hand_str);
    
    vector<vector<int>> known_hands;

    for (vector<string> known_hand_str : known_hands_str) {
        known_hands.push_back(convert_hand(known_hand_str));
    }

    vector<vector<int>> results = calculate(N, comm_hand, known_hands, players_unknown);

    cout << "\nHand   Win %   Tie %\n" << endl;
    print_results(N, known_hands, results);

    clock_t stop = clock();
    double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("\nTime elapsed: %.5fs\n", elapsed);

    return results;
}