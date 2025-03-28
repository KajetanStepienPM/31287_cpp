#include "Graph.h"

using namespace std;

int main(){
    Graph g;

    g.addGraphEdge("Warszawa", "Kraków", 300);
    g.addGraphEdge("Warszawa", "Gdańsk", 350);
    g.addGraphEdge("Kraków", "Gdańsk", 550);
    g.addGraphEdge("Kraków", "Wrocław", 270);
    g.printGraph();
    return 0;
}