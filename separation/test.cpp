#include "Graph.h"
#include <iostream>

int main() {
    separation::Graph g;
    g.loadSampleData();
    g.displayCities();
    g.displayGraph();
    std::cout << "Running dijkstra from 1 to 6:\n";
    g.dijkstra(1, 6);
    return 0;
}
