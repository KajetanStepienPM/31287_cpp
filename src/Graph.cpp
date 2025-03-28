#include "Graph.h"
#include <iostream>

using namespace std;

void Graph::addGraphEdge(string u, string v, int distance){
    graphData[u].push_back({v, distance});
    graphData[v].push_back({u, distance});
}