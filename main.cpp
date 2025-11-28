#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
#include <vector>
#include <climits>
using namespace std;

class City {
public:
    int distance;
    string name;

    City(string name, int distance = INT_MAX) {
        this->name = name;
        this->distance = distance;
    }
};

class Graph {
public:
    unordered_map<int, list<pair<int, int>>> adj;  // <node, <neighbor, weight>>
    unordered_map<int, City> cities;  // Map to store the city objects

    // Add a city to the graph
    void addCity(int id, const string& name) {
        cities[id] = City(name);
    }

    // Add an edge to the graph (u -> v with weight w)
    void addEdge(int u, int v, int w, bool direction) {
        adj[u].push_back({v, w});
        if (!direction) {
            adj[v].push_back({u, w});  // For undirected graph
        }
    }

    void dijkstra(int src, int dest) {
        unordered_map<int, int> parents;  // To reconstruct the shortest path
        unordered_map<int, int> distances;  // Stores shortest distance from src to each node
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Min heap

        // Initialize all distances to infinity
        for (auto& city : cities) {
            distances[city.first] = INT_MAX;
        }

        distances[src] = 0;  // Distance from source to source is 0
        parents[src] = src;  // The parent of source is itself
        pq.push({0, src});  // Push source into the priority queue with distance 0

        while (!pq.empty()) {
            int node = pq.top().second;
            int nodeDist = pq.top().first;
            pq.pop();

            if (nodeDist > distances[node]) continue;

            for (auto& neighbor : adj[node]) {
                int nbr = neighbor.first;
                int wg = neighbor.second;

                if (wg + distances[node] < distances[nbr]) {
                    distances[nbr] = distances[node] + wg;
                    parents[nbr] = node;
                    pq.push({distances[nbr], nbr});
                }
            }
        }

        // If destination is unreachable
        if (distances[dest] == INT_MAX) {
            cout << "No path exists between " << cities[src].name << " and " << cities[dest].name << ".\n";
            return;
        }

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
            cout << cities[path[i]].name;
            if (i > 0) cout << " -> ";
        }
        cout << endl;
        cout << "Total Distance: " << distances[dest] << endl;
    }
};

int main() {
    Graph g;

    // Add cities (nodes)
    g.addCity(1, "City1");
    g.addCity(2, "City2");
    g.addCity(3, "City3");
    g.addCity(4, "City4");
    g.addCity(5, "City5");
    g.addCity(6, "City6");
    g.addCity(7, "City7");
    g.addCity(8, "City8");

    // Add edges (routes)
    g.addEdge(1, 3, 2, false);
    g.addEdge(2, 3, 4, false);
    g.addEdge(3, 5, 6, false);
    g.addEdge(3, 4, 3, false);
    g.addEdge(4, 6, 2, false);
    g.addEdge(5, 6, 1, false);
    g.addEdge(7, 8, 1, false);

    // Input source and destination cities
    int src, dest;
    cout << "Enter source (ID): ";
    cin >> src;
    cout << "Enter destination (ID): ";
    cin >> dest;

    // Find and print the shortest path
    g.dijkstra(src, dest);

    return 0;
}
