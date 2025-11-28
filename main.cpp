#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
#include <vector>
#include <climits>
using namespace std;



class Graph {
public:
    unordered_map<int, list<pair<int, int>>> adj;  // <node, <neighbor, weight>>

    // Add an edge to the graph (u -> v with weight w)
    void addEdge(int u, int v, int w, bool direction) {
        adj[u].push_back({v, w});
        if (!direction) {
            adj[v].push_back({u, w});  // For undirected graph
        }
    }

    void dijkstra(int src, int dest) {
        unordered_map<int,int> parents;
        unordered_map<int,int> distances;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // min heap

        for(auto& i:adj){
            distances[i.first]=INT_MAX;
        }

        distances[src]=0;
        parents[src]=src;
        pq.push({0,src});

        while(!pq.empty()){
            int node = pq.top().second;
            int nodeDist = pq.top().first;

            pq.pop();

            if(nodeDist > distances[node]) continue;
            
            for(auto& neighbor : adj[node]){
                int nbr = neighbor.first;
                int wg = neighbor.second;

                if(wg + distances[node] < distances[nbr]){
                    distances[nbr] = distances[node] + wg;
                    parents[nbr] = node;
                    pq.push({distances[nbr], nbr});
                }
            }
        }
        if (distances[dest] == INT_MAX) {
            cout << "No path exists between " << src << " and " << dest << ".\n";
            return;
        }

        //
        // Reconstruct and print the path
        vector<int> path;
        int currentNode = dest;
        while (currentNode != src) {
            path.push_back(currentNode);
            currentNode = parents[currentNode];
        }
        path.push_back(src);

        // Print the shortest path
        cout << "Shortest Path: ";
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << path[i];
            if (i > 0) cout << " -> ";
        }
        cout << endl;
        cout << "Total Distance: " << distances[dest] << endl;


    }
};

int main() {
    Graph g;
    g.addEdge(1,3,2,false);
    g.addEdge(2,3,4,false);
    g.addEdge(3,5,6,false);
    g.addEdge(3,4,3,false);
    g.addEdge(4,6,2,false);
    g.addEdge(5,6,1,false);
    g.addEdge(7,8,1,false);
    



    int src, dest;
    cout << "Enter source: ";
    cin >> src;
    cout << "Enter destination: ";
    cin >> dest;

    g.dijkstra(src, dest);
}
