#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>
#include <SFML/System/Vector2.hpp>

using namespace std;

class Graph {
private:
    unordered_map<string, vector<pair<string, int>>> graphData;
    unordered_map<string, sf::Vector2f> cityPositions;

public:
    void addGraphEdge(const string& city1, const string& city2, int distance);
    void printGraph();
    unordered_map<string, int> Dijkstra(const string& start);
    vector<pair<string, int>> getNeighbours(const string& city) const {
        return graphData.at(city);
    }
    void loadFromFile(const string& filename);
    void printShortestPaths(const unordered_map<string, int>& distances, const string& start);
    vector<string> getAllCities() const;
    void setCityPosition(const string& city, const sf::Vector2f& position);
    sf::Vector2f getCityPosition(const string& city) const;
};

#endif
