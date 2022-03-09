/*graph-a.h*/

#ifndef GRAPH_A_H
#define GRAPH_A_H

#include <iostream>
#include <vector>

using namespace std;

struct edge;

void bfs_list(const vector<vector<int>>&);

void dfs_list(const vector<vector<int>>&, vector<int>&, int);

vector<int> dijkstra(const vector<vector<pair<int, int>>>&, int);

void floyd_warshall(const vector<vector<pair<int, int>>>&);

int prima(vector<vector<pair<int, int>>>&);

int kruskal(vector<vector<pair<int, int>>>&);

#endif