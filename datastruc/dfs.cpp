#include <iostream>
#include <vector>
using namespace std;

void DFSRec(vector<vector<int> > &adj, vector<bool> &visited, int s){
    visited[s] = true;
    cout << s << " ";

    for (vector<int>::iterator it = adj[s].begin(); it != adj[s].end(); ++it) {
        int i = *it;
        if (visited[i] == false)
            DFSRec(adj, visited, i);
    }
}

void DFS(vector<vector<int> > &adj, int s){
    vector<bool> visited(adj.size(), false);
    DFSRec(adj, visited, s);
}

void addEdge(vector<vector<int> > &adj, int s, int t){
    adj[s].push_back(t); 
    adj[t].push_back(s); 
}

int main(){
    int V = 5; 
    vector<vector<int> > adj(V);
  
    vector<pair<int, int>> edges = {{1, 2}, {1, 0}, {2, 0}, {2, 3}, {2, 4}};
    for (int i = 0; i < edges.size(); ++i) {
        addEdge(adj, edges[i].first, edges[i].second);
    }

    int s = 1;
    cout << "DFS from source: " << s << endl;
    DFS(adj, s);

    return 0;
}