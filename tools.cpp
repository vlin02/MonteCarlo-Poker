//
// Created by Victor on 5/21/20.
//

#include "tools.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "sparsepp/spp.h"

using namespace std;
const string BASE = "/Users/5apphire/Desktop/Programs/C++/MonteCarloPoker/";

void print(vector<int> const &input) {
std::copy(input.begin(),
        input.end(),
        std::ostream_iterator<int>(std::cout, " "));
}

ifstream::pos_type filesize(const char* filename)
{
    ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    ifstream::pos_type ret =  in.tellg();
    return ret;
}

void write_vect(vector<int> vect, string name){
    fstream f;
    int* arr = &vect[0];
    f.open(BASE + name, ios::out|ios::binary);
    if (f){
        f.write(reinterpret_cast<char*>(arr), vect.size() * 4);
        f.close();
    } else {
        cout << "Error" << endl;
    }
}

vector<int> read_vect(const char *name){
    fstream f;
    string loc = BASE + name;
    f.open(loc, ios::in|ios::binary);
    int fsize = filesize(loc.c_str());
    vector<int> vect(fsize/4);
    int* arr = &vect[0];
    if(f){
        f.read(reinterpret_cast<char*>(arr), fsize);
        f.close();
    }
    return vect;
}

vector<int> map_to_vect(const spp::sparse_hash_map<int, int> &table){
    vector<int> ret(table.size() * 2, 0);
    int ix = 0;
    for (const auto& [key, value]: table)
    {
        ret[ix] = key;
        ret[ix + 1] = value;
        ix += 2;
    }
    return ret;
}

spp::sparse_hash_map<int, int> vect_to_map(vector<int> vect){
    spp::sparse_hash_map<int, int> table;
    for (int i = 0; i < vect.size(); i += 2) {
        table[vect[i]] = vect[i+1];
    }
    return table;
}
