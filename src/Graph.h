#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class Graph{
    private:
        unordered_map<string, vector<pair<string, int>>> graphData;
    public:
        void addGraphEdge(string u, string v, int distance);
        void printGraph();
};