/*graph-b.h*/

#ifndef GRAPH_B_H
#define GRAPH_B_H

#include <iostream>
#include <vector>
#include <map>

using namespace std;

void fleri_algo(const vector<vector<int>>&, const vector<vector<int>>&);

void kosaraju_algo(const vector<vector<int>>&);

void tarian_algo(const vector<vector<int>>&);

//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_

vector<vector<int>> reverse(vector<vector<int>>&);

#endif