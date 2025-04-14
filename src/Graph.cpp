#include "Graph.h"
#include <limits>
#include <queue>
#include <fstream>
#include <sstream>

using namespace std;

void Graph::addGraphEdge(const string& city1, const string& city2, int distance) {
    graphData[city1].push_back(make_pair(city2, distance));
    graphData[city2].push_back(make_pair(city1, distance));
}

void Graph::printGraph() {
    for (auto& [city, neighbours] : graphData) {
        cout << "Miasto " << city << " jest połączone z: ";
        for (auto& [neighbour, distance] : neighbours) {
            cout << neighbour << " (" << distance << "km) ";
        }
        cout << endl;
    }
}

unordered_map<string, int> Graph::Dijkstra(const string& start) {
    unordered_map<string, int> distances;
    unordered_map<string, bool> visited;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

    for (auto& [city, _] : graphData) {
        distances[city] = numeric_limits<int>::max();
        visited[city] = false;
    }
    distances[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [current_dist, current_city] = pq.top();
        pq.pop();

        if (visited[current_city]) continue;
        visited[current_city] = true;

        for (auto& [neighbour, distance] : graphData[current_city]) {
            if (!visited[neighbour] && current_dist + distance < distances[neighbour]) {
                distances[neighbour] = current_dist + distance;
                pq.push({distances[neighbour], neighbour});
            }
        }
    }

    return distances;
}

void Graph::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Nie można otworzyć pliku: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string city1, city2;
        int distance;

        if (getline(ss, city1, ';') && getline(ss, city2, ';') && (ss >> distance)) {
            addGraphEdge(city1, city2, distance);
        }
    }
    file.close();
}

void Graph::printShortestPaths(const unordered_map<string, int>& distances, const string& start) {
    cout << "Najkrótsze odległości od " << start << ":" << endl;
    for (const auto& [city, distance] : distances) {
        if (distance == numeric_limits<int>::max()) {
            cout << "Do " << city << ": brak połączenia" << endl;
        } else {
            cout << "Do " << city << ": " << distance << " km" << endl;
        }
    }
}