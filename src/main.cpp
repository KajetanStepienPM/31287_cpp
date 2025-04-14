#include "Graph.h"
#include <iostream>

using namespace std;

int main() {
    Graph g;
    int choice;

    cout << "1. Wczytaj dane z pliku" << endl;
    cout << "2. Wprowadź dane ręcznie" << endl;
    cout << "Wybierz opcję: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        string filename;
        cout << "Podaj nazwę pliku: ";
        getline(cin, filename);
        g.loadFromFile(filename);
    } else if (choice == 2) {
        int cityCount;
        cout<<"Ile miast chcesz wprowadzić?: ";
        cin >> cityCount;
        cin.ignore();
        for(int i = 0; i<cityCount; i++){
            string firstCity, secondCity;
            int distance;
            cout<<"Podaj pierwsze miasto: ";
            getline(cin, firstCity);

            cout<<"Podaj drugie miasto: ";
            getline(cin, secondCity);

            cout<<"Podaj dystans: ";
            cin>>distance;
            cin.ignore();

            g.addGraphEdge(firstCity, secondCity, distance);
        }
    } else {
        cout << "Nieprawidłowy wybór" << endl;
        return 1;
    }

    g.printGraph();

    string startCity;
    cout << "\nPodaj miasto startowe: ";
    getline(cin, startCity);

    unordered_map<string, int> distances = g.Dijkstra(startCity);
    g.printShortestPaths(distances, startCity);

    return 0;
}

