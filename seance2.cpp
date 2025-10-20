#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <iostream>

struct Arete {
    int x, y, poids;
};

void dfs(int noeud, int couleur, std::map<int, std::set<int>>& graphe, std::map<int, int>& couleurs) {
    couleurs[noeud] = couleur;
    for (int voisin : graphe[noeud]) {
        if (couleurs.find(voisin) == couleurs.end()) {
            dfs(voisin, couleur, graphe, couleurs);
        }
    }
}

std::string intToLabel(int index) {
    std::string label;
    while (index >= 0) {
        label = char('A' + index % 26) + label;
        index = index / 26 - 1;
    }
    return label;
}


int main() {
    std::vector<Arete> tableau = {
        {1, 2, 1}, {2, 3, 1}, {4, 5, 1},
        {6, 7, 1}, {7, 8, 1}, {7, 9, 1},
        {10, 10, 1}
    };


    std::map<int, std::set<int>> graphe;
    for (const auto& ar : tableau) {
        graphe[ar.x].insert(ar.y);
        graphe[ar.y].insert(ar.x);
    }

    std::map<int, std::string> idToName;
    int i = 0;
    for (const auto& pair : graphe) {
        idToName[pair.first] = intToLabel(i++);
    }

    
    std::map<int, int> couleurs;
    int couleur = 1;
    for (const auto& pair : graphe) {
        int noeud = pair.first;
        if (couleurs.find(noeud) == couleurs.end()) {
            dfs(noeud, couleur, graphe, couleurs);
            couleur++;
        }
    }

    std::cout << "Composantes connexes colorées :\n";
    for (const auto& pair : couleurs) {
        std::string nomNoeud = idToName[pair.first];
        int col = pair.second;
        std::cout << "Noeud " << nomNoeud << " → Couleur " << col << "\n";
    }

    return 0;
}
