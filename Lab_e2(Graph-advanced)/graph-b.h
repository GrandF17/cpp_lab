/*graph-b.h*/

#ifndef GRAPH_B_H
#define GRAPH_B_H

#include <iostream>
#include <vector>
#include <map>

using namespace std;

void fleri_algo(const vector<vector<int>>&, const vector<vector<int>>&);

void cycle_algo(vector<vector<int>>&, const vector<vector<int>>&);

void kosaraju_algo(const vector<vector<int>>&);

void tarian_algo(const vector<vector<int>>&);

vector<vector<int>> reverse(vector<vector<int>>&);

#endif