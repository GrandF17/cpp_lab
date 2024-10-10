#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

// ...0 ~ white, 1 ~ grey, 2 ~ black...

vector<int> sorted;
vector<int> order;
vector<int> used;

void tarian_algo(const vector<vector<int>>& graph, vector<int>& used, vector<int>& sorted, int current_vertex) {
    used[current_vertex] = 1;//grey

    for(int i = 0; i < graph[current_vertex].size(); i++) {
        int adjacent_vertex = graph[current_vertex][i];
        if(used[adjacent_vertex] == 1 && adjacent_vertex != current_vertex) {
            throw exception();
        }
        if(used[adjacent_vertex] == 0) {
            tarian_algo(graph, used, sorted, adjacent_vertex);
        }
    }
    sorted.push_back(current_vertex);
    used[current_vertex] = 2;   
}

void dfs_list(const vector<vector<int>>& graph, vector<int>& used, vector<int>& order, int current_vertex) {
    used[current_vertex] = 1;

    for(int i = 0; i < graph[current_vertex].size(); i++) {
        int adjacent_vertex = graph[current_vertex][i];
        if(used[adjacent_vertex] == 0) {
            dfs_list(graph, used, order, adjacent_vertex);
        }
    }
    order.push_back(current_vertex);
}

void dfs(const vector<vector<int>>& graph, map<pair<int, int>, int>& edges, vector<int>& cycle, int current_vertex) {
    for(int i = 0; i < graph[current_vertex].size(); i++) {
        int adjacent_vertex = graph[current_vertex][i];
        int a = current_vertex;
        int b = adjacent_vertex;
        if(a > b)
            swap(a, b);
        if(edges[{a, b}] != 0) {
            edges[{a, b}]--;
            dfs(graph, edges, cycle, adjacent_vertex);
        }
    }
    cycle.push_back(current_vertex);
}

void find_euler_cycle(vector<vector<int>>& graph, vector<int>& cycle, int current_vertex) {
    if(graph.empty()) { return; }
    for(int i = 0; i < graph[current_vertex].size(); i++) {
        int next = graph[current_vertex][i];
        graph[current_vertex].erase(graph[current_vertex].begin() + i);
        for(int k = 0; k < graph[next].size(); k++) {
            if(current_vertex == graph[next][k]) { 
                graph[next].erase(graph[next].begin() + k);
                break;
            }
        }
        find_euler_cycle(graph, cycle, next);
    }
    cycle.push_back(current_vertex);
}

vector<vector<int>> reverse(vector<vector<int>>& graph) {
    used.resize((graph.size()));
    vector<vector<int>> reverse_graph(graph.size());

    for(int i = 0; i < graph.size(); i++) {
        if(!used[i]) {
            dfs_list(graph, used, order, i);
        }
    }
    for(int i = 0; i < order.size()/2; i++) {
        swap(order[i], order[order.size() - i - 1]);
    }
    
    for(int i = 0; i < graph.size(); i++) {         //reverse our graph
        for(int j = 0; j < graph[i].size(); j++) {
            reverse_graph[graph[i][j]].push_back(i);
        }
    }
    return reverse_graph;
}

void kosaraju_algo(const vector<vector<int>>& reverse_graph) {
    cout << "\n\n-_-_-_Kosaraju-_-_-_\n\nStrong connection components: " << endl;

    used.assign(reverse_graph.size(), 0);
    for(int i = 0; i < order.size(); i++) {
        if(!used[order[i]]) {
            dfs_list(reverse_graph, used, sorted, order[i]);
            for(int i = 0; i < sorted.size(); i++) {
                cout << sorted[i] << " ";
            }
            cout << endl;
            sorted.clear();
        }
    }
}

void tarian_algo(const vector<vector<int>>& graph) {
    cout << "\n\n-_-_-_Tarian search algo-_-_-_\n\nSorted array: " << endl;

    try {
        tarian_algo(graph, used, sorted, 0);
        for(int i = sorted.size() - 1; i >= 0; i--) {
            cout << sorted[i] << " ";
        }
    } catch (exception) { cout << "Graph has cycles, topo-sort is impossible!" << '\n'; }
}

bool continue_algo(const vector<vector<int>>& graph, const vector<vector<int>>& reverse_graph) {
    for(int i = 0; i < graph.size(); i++) {     //check if all graph is a strong connection component
        if(graph[i].size() % 2 == 1) { return false; }  //if deg of some vertex is odd
        if(!used[order[i]]) {
            dfs_list(reverse_graph, used, sorted, order[i]);
            if(sorted.size() != graph.size()) { return false; } 
        }
    }
    return true;
}

void fleri_algo(const vector<vector<int>>& graph, const vector<vector<int>>& reverse_graph) {
    if(!continue_algo(graph, reverse_graph)) { return; }

    cout << "\n\n-_-_-_Fleri-_-_-_\n\nCycle: ";
    vector<int> cycle;
    map<pair<int, int>, int> edges;
    for(int i = 0; i < graph.size(); i++) {
        for(int j = 0; j < graph[i].size(); j++) {
            if(i < graph[i][j]) {
                edges[{i, graph[i][j]}]++;
            }
        }
    }

    dfs(graph, edges, cycle, 0);

    for(int i = 0; i < cycle.size(); i++) { cout << cycle[i] + 1 << " "; } 
    cout << endl;
}

void cycle_algo(vector<vector<int>>& graph, const vector<vector<int>>& reverse_graph) {
    if(!continue_algo(graph, reverse_graph)) { return; }

    cout << "\n\n-_-_-_Euler cycle from other cycles-_-_-_\n\nCycle: ";
    vector<int> cycle;

    find_euler_cycle(graph, cycle, 0);

    for(int i = 0; i < cycle.size(); i++) { cout << cycle[i] + 1 << " "; } 
    cout << endl;
}