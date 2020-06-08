//
// Created by Victor on 5/23/20.
//

#include "cards.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

vector<string> hands = {"HIGH CARD", "ONE PAIR", "TWO PAIR", "THREE OF A KIND", "STRAIGHT",
                        "FLUSH", "FULL HOUSE", "FOUR OF A KIND", "STRAIGHT FLUSH", "ROYAL FLUSH"};

vector<string> val = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

vector<string> suit = {"♣️", "♦️", "♥️", "♠️"};

string card_string(int ix) {
    return val[ix % 13] + suit[ix / 13];
}

vector<int> convert_hand(vector<int> &s_hand) {
    vector<int> hand;
    for (int card : s_hand) {
        hand.push_back(13 * ((card % 10) - 1) + card / 10 - 2);
    }
    sort(hand.begin(), hand.end());

    return hand;
}

void print_hand(vector<int> hand) {
    for (int card : hand) {
        cout << card_string(card) << " ";
    }
}

void print_score(int score) {
    score /= pow(13, 5);

    int n2 = score % 13;
    score /= 13;
    int n1 = score % 13;
    score /= 13;
    int m = score;

    printf("%s ", hands[m].c_str());
    if (m == 2 || m == 6) {
        printf("with %s & %s", val[n1].c_str(), val[n2].c_str());
    } else if (!(m > 3 && m != 7)) {
        printf("with %s", val[n1].c_str());
    }
    cout << endl;
}

double calc_error(double prop, int N) {
    return 1.96 * sqrt(prop * (1 - prop) / N);
}

int pascal(vector<int> &table, int N, int k) {
    int combos;
    int ix = 53 * k + N;
    if ( N < k){
        return 0;
    } else if (table[ix] != 0) {
        return table[ix];
    }

    combos = pascal(table, N - 1, k - 1) + pascal(table, N - 1, k);
    table[ix] = combos;
    return combos;
}

vector<int> gen_combo_table(int N, int k) {
    vector<int> c_table((k + 1) * (N + 1));
    for (int m = 0; m <= N; ++m) {
        c_table[m] = 1;
    }

    for (int i = 1; i <= k; ++i) {
        for (int j = i; j <= N; ++j) {
            pascal(c_table, j, i);
        }
    }

    return c_table;
}

