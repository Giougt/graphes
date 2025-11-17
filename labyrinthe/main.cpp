#include "Maze.h"
#include <iostream>
#include <exception>

int main() {
    try {
        Maze m("file path");   
        m.draw();              

        if (m.solveBFS()) {
            std::cout << "Chemin trouvé !" << std::endl;
        }
        else {
            std::cout << "Pas de chemin possible." << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}
