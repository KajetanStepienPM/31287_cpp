#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class Graph{
    private:
        unordered_map<string, vector<pair<string, int>>> graphData;
    public:
        void addGraphEdge(const string& city1, const string& city2, int distance); //wskazniki, poniewaz uzywam nazw miast zamiast np. ich ID
        void printGraph(); //funkcja, ktora docelowo bedzie drukowala cala liste sasiedztwa dla miasta
        void Djikstra(const string& start);
        vector<pair<string, int>> getNeighbours(const string& city) {
            return graphData[city];
        }
        };