#ifndef SEPARATION_GRAPH_H
#define SEPARATION_GRAPH_H

#include "City.h"
#include "Route.h"
#include "MinHeap.h"

#include <unordered_map>
#include <list>
#include <string>

namespace separation {

class Graph {
private:
    int nextCityId;

public:
    std::unordered_map<int, std::list<Route>> adj;
    std::unordered_map<int, City> cities;

    Graph();

    int addCity(const std::string &name);
    void addEdge(int u, int v, int w, bool direction);
    void blockRoute(int u, int v);
    void unblockRoute(int u, int v);
    void setTraffic(int u, int v, int level);
    void displayCities() const;
    void displayGraph() const;
    int calculateEffectiveCost(int distance, int traffic) const;
    void dijkstra(int src, int dest) const;

    void loadSampleData();

    // Save/load
    void saveToFile(const std::string &filename) const;
    void loadFromFile(const std::string &filename);

    void clearGraph();
};

} // namespace separation

#endif // SEPARATION_GRAPH_H
