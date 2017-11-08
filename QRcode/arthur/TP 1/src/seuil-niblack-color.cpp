#include <iostream>

#include "ImageBase.h"
#include "treatment.hpp"

int main(int argc, char * argv[]) {
    if (argc < 3) {
        std::cerr << "usage : " << argv[1] << " <entree.pgm> <sortie.pgm>" << std::endl;
        return -1;
    }

    ImageBase imIn;
    imIn.load(argv[1]);
    ImageBase imOut(imIn.getWidth(), imIn.getHeight(), false);
    NoirEtBlanc(imIn, imIn);
    BinarisationNiblack(imIn, imOut, 20);
    imOut.save(argv[2]);

    return 0;
}