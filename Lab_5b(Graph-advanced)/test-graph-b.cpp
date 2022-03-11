#include "graph-b.h"

int main() {
    // vector<vector<int>> graph{
    //     {1, 2},
    //     {2, 3},
    //     {3, 4},
    //     {4},
    //     {}
    // };

    // vector<vector<int>> graph{
    //     {2},
    //     {0, 2},
    //     {3, 4},
    //     {},
    //     {1, 8},
    //     {10},
    //     {5},
    //     {1, 5},
    //     {9},
    //     {8},
    //     {6, 7},
    // };

    // vector<vector<int>> graph{
    //     {1, 3},
    //     {0, 5, 6},
    //     {6},
    //     {0, 4},
    //     {3, 7},
    //     {1, 6},
    //     {1, 2, 5},
    //     {4}
    // };

    vector<vector<int>> graph{
        {1, 3, 4, 4},
        {0, 2, 3, 4},
        {1, 3},
        {0, 1, 2, 4},
        {0, 1, 3, 0}
    };

    for(int i = 0; i < graph.size(); i++) {         //show graph
        cout << "{ ";
        for(int j = 0; j < graph[i].size(); j++) {
            cout << graph[i][j] << " ";
        }
        cout << "}" << endl;
    }

    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_Kosaraju-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    
    vector<vector<int>> reverse_graph = reverse(graph);
    
    kosaraju_algo(reverse_graph);

    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_Tarian-_-_-_-_-_-_-_-_-_-_-_-_-_-_

    tarian_algo(graph);

    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_Fleri-_-_-_-_-_-_-_-_-_-_-_-_-_-_

    fleri_algo(graph, reverse_graph);

    //-_-_-_-_-_-_-_-_-_-_-_-_-_-_Euler cycle another realisation-_-_-_-_-_-_-_-_-_-_-_-_-_-_
/*
    used.assign(graph.size(), 0);
    sorted.clear();
    order.clear();

    cout << "\n\n-_-_-_Euler cycle another realisation-_-_-_\n\nCycles:" << endl;
    vector<vector<int>> cycle;
    for(int i = 0; i < graph.size(); i++) {     //check if all graph is not a strong connectuion component
        if(!used[order[i]]) {
            dfs_list(reverse_graph, used, sorted, order[i]);
            cycles_dfs(sorted, used, cycle, i);
            for(int i = sorted.size() - 1; i >= 0; i--) {
                cout << sorted[i] << " ";
            }
            cout << endl;
        }
    }
*/
}