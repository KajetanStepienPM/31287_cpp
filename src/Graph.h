#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class Graph{
    private:
        unordered_map<string, vector<pair<string, int>>> graphData;
    public:
        void addGraphEdge(const string& city1, const string& city2, int distance);
        void printGraph();
        unordered_map<string, int> Dijkstra(const string& start);
        vector<pair<string, int>> getNeighbours(const string& city) {
            return graphData[city];
        }
        void loadFromFile(const string& filename);
        void printShortestPaths(const unordered_map<string, int>& distances, const string& start);
        };