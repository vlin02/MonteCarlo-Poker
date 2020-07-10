//
// Created by Victor on 5/21/20.
//

#ifndef TOOLS_H
#define TOOLS_H
#include <vector>

using namespace std;

void print(vector<int> const &input);
void print_score(int score);
void write_vect(vector<int> vect, string name);
vector<int> read_vect(const char *name);

#endif
