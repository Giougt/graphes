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
        int noeud = pair.first;
        int col = pair.second;
        std::cout << "Noeud " << noeud << " → Couleur " << col << "\n";
    }

    return 0;
}
