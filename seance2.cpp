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

// part allegro (bonus)

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

struct Arete {
    int x, y, poids;
};

void dfs(int noeud, int couleur, std::map<int, std::set<int>>& graphe, std::map<int, int>& couleurs) {
    couleurs[noeud] = couleur;
    for (std::set<int>::iterator it = graphe[noeud].begin(); it != graphe[noeud].end(); ++it) {
        int voisin = *it;
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

    if (!al_init()) {
        std::cerr << "Erreur lors de l'initialisation d'Allegro.\n";
        return -1;
    }
    if (!al_init_primitives_addon()) {
        std::cerr << "Erreur lors de l'initialisation des primitives Allegro.\n";
        return -1;
    }

    ALLEGRO_DISPLAY* display = al_create_display(800, 600);
    if (!display) {
        std::cerr << "Erreur : impossible de créer la fenêtre d'affichage.\n";
        return -1;
    }

    al_clear_to_color(al_map_rgb(255, 255, 255));

    std::map<int, std::set<int>> graphe;
    for (std::vector<Arete>::const_iterator it = tableau.begin(); it != tableau.end(); ++it) {
        graphe[it->x].insert(it->y);
        graphe[it->y].insert(it->x);
    }

    std::map<int, std::string> idToName;
    int i = 0;
    for (std::map<int, std::set<int>>::const_iterator it = graphe.begin(); it != graphe.end(); ++it) {
        idToName[it->first] = intToLabel(i++);
    }

    std::map<int, int> couleurs;
    int couleur = 1;
    for (std::map<int, std::set<int>>::const_iterator it = graphe.begin(); it != graphe.end(); ++it) {
        int noeud = it->first;
        if (couleurs.find(noeud) == couleurs.end()) {
            dfs(noeud, couleur, graphe, couleurs);
            couleur++;
        }
    }

    std::map<int, std::pair<float, float>> positions;
    int radius = 20;
    int spacing = 70;
    int row = 0, col = 0;

    for (std::map<int, std::set<int>>::const_iterator it = graphe.begin(); it != graphe.end(); ++it) {
        float x = 100 + col * spacing;
        float y = 100 + row * spacing;
        positions[it->first] = std::make_pair(x, y);
        col++;
        if (col > 5) { col = 0; row++; }
    }

    // Dessiner les arêtes
    for (std::vector<Arete>::const_iterator it = tableau.begin(); it != tableau.end(); ++it) {
        if (it->x == it->y) continue;
        float x1 = positions[it->x].first;
        float y1 = positions[it->x].second;
        float x2 = positions[it->y].first;
        float y2 = positions[it->y].second;
        al_draw_line(x1, y1, x2, y2, al_map_rgb(0, 0, 0), 2);
    }

    // Dessiner les nœuds
    // Dessiner les nœuds
    for (std::map<int, int>::const_iterator it = couleurs.begin(); it != couleurs.end(); ++it) {
        int id = it->first;
        int colIndex = it->second;
        float x = positions[id].first;
        float y = positions[id].second;

        // Couleur basée sur l'indice de composante
        ALLEGRO_COLOR color = al_map_rgb((colIndex * 50) % 255, (colIndex * 80) % 255, (colIndex * 110) % 255);

        // Cercle rempli
        al_draw_filled_circle(x, y, radius, color);

        // Contour noir
        al_draw_circle(x, y, radius, al_map_rgb(0, 0, 0), 2);
    }



    al_flip_display();           // Affiche le contenu dessiné
    al_rest(10.0);                // Attend 5 secondes
    al_destroy_display(display); // Détruit la fenêtre
    return 0;
}
