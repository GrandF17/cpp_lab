#include<algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

//-_-_-_-_-_-_-_breadth search-_-_-_-_-_-_-_

void bfs_list(const vector<vector<int>>& graph) {
    int start_vertex = 0;
    vector<int> used(graph.size(), 0);
    used[start_vertex] = 1;
    queue<int> q;
    q.push(start_vertex);
    while(!q.empty()) {
        int current_vertex = q.front();
        cout << current_vertex + 1;
        q.pop();
        for(int i = 0; i < graph[current_vertex].size(); i++) {
            int adjacent_vertex = graph[current_vertex][i];
            if(!used[adjacent_vertex]) {
                q.push(adjacent_vertex);
                used[adjacent_vertex] = 1;
            }
        }
        if(q.empty()) { cout << ";" << endl; }
        else { cout << " --> ";  }
    }
}

//-_-_-_-_-_-_-_depth search-_-_-_-_-_-_-_

void dfs_list(const vector<vector<int>>& graph, vector<int>& used, int current_vertex) {
    used[current_vertex] = 1;

    bool finished = true;
    for(int i = 0; i < used.size(); i++) {
        if(used[i] == 0) {
            finished = false;
            break;
        } 
    }

    if(finished) {
        cout << current_vertex << ";" << endl;
    } else {
        cout << current_vertex << " --> ";
    }

    for(int i = 0; i < graph[current_vertex].size(); i++) {
        int adjacent_vertex = graph[current_vertex][i];
        if(used[adjacent_vertex] == 0) {
            dfs_list(graph, used, adjacent_vertex);
        }
    }
}

//-_-_-_-_-_-_-_dijkstra algo-_-_-_-_-_-_-_

vector<int> dijkstra(const vector<vector<pair<int, int>>>& graph, int start_vertex) {
    const int inf = 1000000;
    vector<int> dist(graph.size(), inf);
    dist[start_vertex] = 0;

    set<pair<int, int>> s;
    s.insert({0, start_vertex});

    while(!s.empty()) {//O(m * log(n))
        int current_vertex = s.begin()->second;
        s.erase(s.begin());

        for(int i = 0; i < graph[current_vertex].size(); i++) {
            int adjacent_vertex = graph[current_vertex][i].first;
            int weight = graph[current_vertex][i].second;
            if(dist[current_vertex] + weight < dist[adjacent_vertex]) {
                s.erase({dist[adjacent_vertex], adjacent_vertex});
                dist[adjacent_vertex] = dist[current_vertex] + weight;
                s.insert({dist[adjacent_vertex], adjacent_vertex});
            }
        }
    }
    return dist;
}

//-_-_-_-_-_-_-floyd-warshall algo-_-_-_-_-_-_-_
vector<vector<int>> FWAfunc(vector<vector<int>>& dist) {
    const int n = dist.size();
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    return dist;
}

void floyd_warshall(const vector<vector<pair<int, int>>>& graph) {
    const int Inf = 1e9 + 7;
    vector<vector<int>> graph3(graph.size(), vector<int>(graph.size(), Inf));

    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph[i].size(); ++j) {
            graph3[i][graph[i][j].first] = graph[i][j].second;
            graph3[graph[i][j].first][i] = graph[i][j].second;
        }
    }
/*
    for(int i = 0; i < graph.size(); ++i) {
        vector<int> dist = dijkstra(graph, i);
        for (int i = 0; i < dist.size(); ++i) {
            cout << dist[i] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
*/

    auto dist = FWAfunc(graph3);
    for (int i = 0; i < dist.size(); ++i) {
        for (int j = 0; j < dist[i].size(); ++j) {
            if (i == j) { cout << 0 << " "; }
            else { cout << dist[i][j] << " "; }
        }
        cout << endl;
    }
}

//-_-_-_-_-_-_-special struct for Prima & Kruskal-_-_-_-_-_-_-_

struct edge {
    int a, b, c;
    bool operator<(const edge& e) { return c < e.c; }
};

//-_-_-_-_-_-_-MST (Prima) algo-_-_-_-_-_-_-_

int PRIMAfunc(vector<vector<pair<int, int>>>& graph, vector<bool> visited, vector<edge> not_visited, int index, int amount) {
    visited[index] = true;  //begin with 0 vertex
/*  
    //to check if all vertices are visited
    cout << "Now in " << index << " vertex" << endl;
    for(int i = 0; i < visited.size(); i++) {
        cout << visited[i] << " ";
    }
    cout << endl;
*/
    for(int i = 0; i < visited.size(); i++) {
        if(!visited[i]) { break; }
        if(i == visited.size() - 1) { return amount; }
    }

    for(int i = 0; i < graph[index].size(); i++) {
        if(!visited[graph[index][i].first]) {
            int k = not_visited.size();
            not_visited.push_back(edge());
            not_visited[k].a = index;
            not_visited[k].b = graph[index][i].first;
            not_visited[k].c = graph[index][i].second;
        }
    }

    int min = 0;
    for(int i = 0; i < not_visited.size(); i++) {
        if(not_visited[min].c > not_visited[i].c) { min = i; }
    }

    cout << not_visited[min].a + 1 << " " << not_visited[min].b + 1 << "\n";
    amount += not_visited[min].c;
    not_visited[min].c = 1e9;

    return PRIMAfunc(graph, visited, not_visited, not_visited[min].b, amount);
}

int prima(vector<vector<pair<int, int>>>& graph) {
    vector<bool> visited (graph.size(), false);
    vector<edge> not_visited;
    return PRIMAfunc(graph, visited, not_visited, 0, 0);
}

//-_-_-_-_-_-_-MST (Kruskal) algo-_-_-_-_-_-_-_
vector<int> parent;
vector<int> sizes;

int find_set(int v) {
    if (v == parent[v]) { return v; }
    return parent[v] = find_set(parent[v]);
}

void union_set(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sizes[a] < sizes[b]) { swap(a, b); }
        parent[b] = a;
        sizes[a] += sizes[b];
    }
}

int kruskal(vector<vector<pair<int, int>>>& graph) {

    //~rebuild our graph~
    vector<edge> edges;
    int k = 0;
    for(int i = 0; i < graph.size(); i++) {
        for(int j = 0; j < graph[i].size(); j++) {
            edges.push_back(edge());
            edges[k].a = i + 1;
            edges[k].b = graph[i][j].first + 1;
            edges[k].c = graph[i][j].second;
            k++;
        }
    }

    for(int i = 0; i < edges.size() - 1; i++) {
        for(int j = i + 1; j < edges.size(); j++) {
            if(edges[i].a == edges[j].b && edges[i].b == edges[j].a) { 
                edges.erase(edges.begin() + j);
            }
        }
    }
    //~rebuild our graph~

/*  
    //to show new graph
    for(int i = 0; i < edges.size(); i++) {
        cout << i + 1 << ") [" << edges[i].a << ", " << edges[i].b << ", " << edges[i].c << "]" << endl;
    }
*/
    parent.resize(edges.size() + 1);
    sizes.resize(edges.size() + 1);

    for(int i = 0; i < sizes.size(); i++) {
        parent[i] = i;
        sizes[i] = 1;
    }

    sort(edges.begin(), edges.end());
    int all_cost = 0;

    for(int i = 0; i < edges.size(); i++) {
        int a = edges[i].a;
        int b = edges[i].b;
        int c = edges[i].c;
        if(find_set(a) != find_set(b)) {
            cout << a << " " << b << "\n";
            all_cost += c;
            union_set(a, b);
        }
    }
    return all_cost;
}
