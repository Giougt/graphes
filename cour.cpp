// manipuler des vecteurs 
#include <iostream>
#include <vector>

void affichage(const std:vector<std::vector<int>>& matrice){
  for (const auto& elem: matrice){
    for (const auto& value : elem){
      std::cout <<value << " ";
    }
    std::cout << std::endl;
  }
}

int main(){
  std::vector<std::vector<int>>
  matrice(10, std::vector<int>(20, 0));

  matrice[0][1] = 1;
  matrice[3][2] = 1;

  affichage(matrice);
  return 0;
}
