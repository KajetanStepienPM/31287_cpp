#include "Graph.h"
#include <limits>
#include <queue>

using namespace std;

void Graph::Dijkstra(const string& start){
    unordered_map<string, int> distances;
    unordered_map<string, bool> visited;

    for(auto& [city, _] : graphData){
        distances[city] = INT_MAX;
        visited[city] = false;
    }
    distances[start] = 0;
    
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    pq.push({0, start});


    while(!pq.empty()){
        auto [dist, city] = pq.top();
    }
}