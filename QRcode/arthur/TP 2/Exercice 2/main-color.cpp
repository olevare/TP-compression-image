#include <iostream>
#include <cmath>

#include "ImageBase.h"

int main(int argc, char * argv[]) {
    ImageBase imIn, imTatoo;
    imIn.load(argv[1]);
    imTatoo.load(argv[2]);
    ImageBase imOut(imIn.getWidth(), imIn.getHeight(), true);

    for (int i = 0, h = imIn.getHeight(), hT = imTatoo.getHeight(); i < h; i++) {
        for (int j = 0, w = imIn.getWidth(), wT = imTatoo.getWidth(); j < w; j++) {
            if (imIn[i][j] < 128) {
                // B Y (i,j) = min{ C Y (i,j), τ l }
                imOut[i * 3][j * 3] = std::min((int)imTatoo[i * 3][j * 3], (int)100);
                imOut[i * 3][j * 3 + 1] = std::min((int)imTatoo[i * 3][j * 3 + 1], (int)100);
                imOut[i * 3][j * 3 + 2] = std::min((int)imTatoo[i * 3][j * 3 + 2], (int)100);
            }
            else {
                // B Y (i,j) = max{ C Y (i,j), τ u }
                imOut[i * 3][j * 3] = std::max((int)imTatoo[i * 3][j * 3], (int)100);
                imOut[i * 3][j * 3 + 1] = std::max((int)imTatoo[i * 3][j * 3 + 1], (int)100);
                imOut[i * 3][j * 3 + 2] = std::max((int)imTatoo[i * 3][j * 3 + 2], (int)100);
            }
        }
    }

    imOut.save(argv[3]);

    return 0;
}