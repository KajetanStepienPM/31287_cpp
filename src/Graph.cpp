#include "Graph.h"
#include <iostream>

using namespace std;

void Graph::addGraphEdge(const string& city1, const string& city2, int distance){
    graphData[city1].push_back(make_pair(city2, distance));
    graphData[city2].push_back(make_pair(city1, distance));
}

void Graph::printGraph(){
    for(auto& [city, neighbours] : graphData){
        cout<<"Miasto "<< city << " jest połączone z: ";
        for(auto& [neighbour, distance] : neighbours){
            cout<<neighbour<<" ("<<distance<<"km) ";
        }
        cout<< endl;
    }
}