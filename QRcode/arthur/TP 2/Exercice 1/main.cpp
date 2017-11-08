#include <iostream>
#include <array>
#include <vector>

#include "matrice.hpp"

// Convertie une chaine de caractères en tableaux de 4 bits
std::vector<std::array<bool, 4>> Convert4Bit(const char * msg) {
    std::vector<std::array<bool, 4>> res;
    for (unsigned int i = 0; msg[i] != '\0'; i++) {
        res.push_back(std::array<bool, 4>({ (msg[i] >> 7) & 0x1, (msg[i] >> 6) & 0x1, (msg[i] >> 5) & 0x1, (msg[i] >> 4) & 0x1 }));
        res.push_back(std::array<bool, 4>({ (msg[i] >> 3) & 0x1, (msg[i] >> 2) & 0x1, (msg[i] >> 1) & 0x1, (msg[i] >> 0) & 0x1 }));
    }
    return res;
}

// Convertie une chaine de caractères en matrices 4x1
std::vector<Matrice<short, 4, 1>> ConvertMatrix(const char * msg) {
    std::vector<Matrice<short, 4, 1>> res;
    std::vector<std::array<bool, 4>> bits = Convert4Bit(msg);
    for (unsigned int i = 0, sz = bits.size(); i < sz; i++) {
        Matrice<short, 4, 1> m;
        for (unsigned int k = 0; k < 4; k++)
            m[k][0] = bits[i][k];
        res.push_back(m);
    }
    return res;
}

int main(int argc, char * argv[]) {
    // Matrice génératrice
    Matrice<short, 7, 4> matrice;
    // Ligne 0
    matrice[0][0] = 1;
    matrice[0][1] = 1;
    matrice[0][2] = 0;
    matrice[0][3] = 1;
    // Ligne 1
    matrice[1][0] = 1;
    matrice[1][1] = 0;
    matrice[1][2] = 1;
    matrice[1][3] = 1;
    // Ligne 2
    matrice[2][0] = 1;
    matrice[2][1] = 0;
    matrice[2][2] = 0;
    matrice[2][3] = 0;
    // Ligne 3
    matrice[3][0] = 0;
    matrice[3][1] = 1;
    matrice[3][2] = 1;
    matrice[3][3] = 1;
    // Ligne 4
    matrice[4][0] = 0;
    matrice[4][1] = 1;
    matrice[4][2] = 0;
    matrice[4][3] = 0;
    // Ligne 5
    matrice[5][0] = 0;
    matrice[5][1] = 0;
    matrice[5][2] = 1;
    matrice[5][3] = 0;
    // Ligne 6
    matrice[6][0] = 0;
    matrice[6][1] = 0;
    matrice[6][2] = 0;
    matrice[6][3] = 1;

    std::cout << "Matrice generatrice :" << std::endl;
    std::cout << matrice << std::endl;

    std::vector<Matrice<short, 4, 1>> msg = ConvertMatrix("HMIN322 - Codes graphiques");
    std::cout << "Resultats :" << std::endl << std::endl;
    for (unsigned int i = 0, sz = msg.size(); i < sz; i++) {
        Matrice<short, 7, 1> m = matrice * msg[i];
        for (unsigned int k = 0; k < 7; k++)
            std::cout << m[k][0] << " ";
        std::cout << std::endl;
    }

    return 0;
}