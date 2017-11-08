#include <iostream>
#include <cmath>

#include "ImageBase.h"

int main_grey(int argc, char * argv[]) {
    ImageBase imIn, imTatoo;
    imIn.load(argv[1]);
    imTatoo.load(argv[2]);
    ImageBase imOut(imIn.getWidth(), imIn.getHeight(), false);

    for (int i = 0, h = imIn.getHeight(), hT = imTatoo.getHeight(); i < h; i++) {
        for (int j = 0, w = imIn.getWidth(), wT = imTatoo.getWidth(); j < w; j++) {
            if (imIn[i][j] < 128) {
                // B Y (i,j) = min{ C Y (i,j), τ l }
                imOut[i][j] = std::min((int)imTatoo[i][j], (int)100);
            }
            else {
                // B Y (i,j) = max{ C Y (i,j), τ u }
                imOut[i][j] = std::max((int)imTatoo[i][j], (int)200);
            }
        }
    }

    imOut.save(argv[3]);

    return 0;
}
