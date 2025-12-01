#include "Graph.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace separation {

Graph::Graph() : nextCityId(1) {}

int Graph::addCity(const std::string &name) {
    if (name.empty()) return -1;
    for (auto &p : cities) if (p.second.name == name) return p.first;
    int id = nextCityId++;
    cities[id] = City(name);
    return id;
}

void Graph::addEdge(int u, int v, int w, bool direction) {
    if (u == v) return;
    // simple duplicates check
    for (auto &r : adj[u]) if (r.neighbor == v) return;
    adj[u].push_back(Route(v,w));
    if (!direction) adj[v].push_back(Route(u,w));
}

void Graph::blockRoute(int u, int v) {
    for (auto &r : adj[u]) if (r.neighbor == v) r.isBlocked = true;
}
void Graph::unblockRoute(int u, int v) {
    for (auto &r : adj[u]) if (r.neighbor == v) r.isBlocked = false;
}

void Graph::setTraffic(int u, int v, int level) {
    for (auto &r : adj[u]) if (r.neighbor == v) r.traffic = level;
}

void Graph::displayCities() const {
    std::cout << "=== Cities ===\n";
    for (auto &p : cities) std::cout << p.first << ": " << p.second.name << "\n";
}

void Graph::displayGraph() const {
    std::cout << "=== Graph ===\n";
    for (auto &p : cities) {
        std::cout << p.second.name << " (" << p.first << ") -> ";
        auto it = adj.find(p.first);
        if (it == adj.end()) { std::cout << "<no edges>\n"; continue; }
        bool first = true;
        for (auto &r : it->second) {
            if (!first) std::cout << ", "; first = false;
            std::cout << "(" << r.neighbor << ", d=" << r.distance << ", t=" << r.traffic << (r.isBlocked?", blocked":"") << ")";
        }
        std::cout << "\n";
    }
}

int Graph::calculateEffectiveCost(int distance, int traffic) const {
    return distance + (distance * traffic / 10);
}

void Graph::dijkstra(int src, int dest) const {
    if (cities.empty()) { std::cout << "empty graph\n"; return; }
    if (cities.find(src) == cities.end() || cities.find(dest) == cities.end()) { std::cout << "src/dest not found\n"; return; }
    if (src == dest) { std::cout << "same node\n"; return; }

    std::unordered_map<int,int> parents;
    std::unordered_map<int,int> distances;
    MinHeap heap;

    for (auto &p : cities) distances[p.first] = INT_MAX;
    distances[src] = 0; parents[src] = src; heap.push(0, src);

    while (!heap.empty()) {
        auto cur = heap.top(); heap.pop();
        int node = cur.second, d = cur.first;
        if (d > distances[node]) continue;
        for (auto &r : adj.at(node)) {
            if (r.isBlocked) continue;
            int cost = calculateEffectiveCost(r.distance, r.traffic);
            if (distances[node] + cost < distances[r.neighbor]) {
                distances[r.neighbor] = distances[node] + cost;
                parents[r.neighbor] = node;
                heap.push(distances[r.neighbor], r.neighbor);
            }
        }
    }

    if (distances.at(dest) == INT_MAX) { std::cout << "no path\n"; return; }

    std::vector<int> path;
    for (int cur = dest; cur != src; cur = parents[cur]) path.push_back(cur);
    path.push_back(src);

    std::cout << "path: ";
    for (int i = (int)path.size()-1; i >= 0; --i) {
        std::cout << cities.at(path[i]).name;
        if (i) std::cout << " -> ";
    }
    std::cout << "\ncost: " << distances.at(dest) << "\n";
}

void Graph::loadSampleData() {
    addCity("City1"); addCity("City2"); addCity("City3"); addCity("City4");
    addCity("City5"); addCity("City6"); addCity("City7"); addCity("City8");
    addEdge(1, 3, 2, false);
    addEdge(2, 3, 4, false);
    addEdge(3, 5, 6, false);
    addEdge(3, 4, 3, false);
    addEdge(4, 6, 2, false);
    addEdge(5, 6, 1, false);
    addEdge(7, 8, 1, false);
}

void Graph::saveToFile(const std::string &filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) return;
    out << "NEXT_ID " << nextCityId << "\n";
    out << "CITIES " << cities.size() << "\n";
    for (auto &p : cities) out << p.first << " " << p.second.name << "\n";
    int edgeCount = 0;
    for (auto &e : adj) edgeCount += (int)e.second.size();
    out << "EDGES " << edgeCount << "\n";
    for (auto &e : adj) {
        for (auto &r : e.second) {
            out << e.first << " " << r.neighbor << " " << r.distance << " " << r.traffic << " " << (r.isBlocked?1:0) << "\n";
        }
    }
}

void Graph::loadFromFile(const std::string &filename) {
    std::ifstream in(filename);
    if (!in.is_open()) return;
    cities.clear(); adj.clear();
    std::string tag; int val;
    if (!(in >> tag >> val)) return; // NEXT_ID
    nextCityId = val;
    if (!(in >> tag >> val)) return; // CITIES
    for (int i = 0; i < val; ++i) {
        int id; std::string name;
        in >> id >> name; cities[id] = City(name);
    }
    if (!(in >> tag >> val)) return; // EDGES
    for (int i = 0; i < val; ++i) {
        int u, v, d, t, b; in >> u >> v >> d >> t >> b;
        Route r(v, d); r.traffic = t; r.isBlocked = (b!=0);
        adj[u].push_back(r);
    }
}

void Graph::clearGraph() { cities.clear(); adj.clear(); nextCityId = 1; }

} // namespace separation
