#include "ImageBase.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>


int main(int argc, char **argv)
{
	char cNomImgLue[250];
	char cNomImgLuere[250];
  
	if (argc != 3) 
	{
		printf("Usage: ImageIn.ppm Decompression.ppm\n"); 
		return 1;
	}
	sscanf (argv[1],"%s",cNomImgLue);
	sscanf (argv[2],"%s",cNomImgLuere);
	
	//lecture de l'image
	ImageBase imIn;
	ImageBase Image_Finale;
	imIn.load(cNomImgLue);
	Image_Finale.load(cNomImgLuere);


	//calcul du PSNR (luminance)
	float som = 0;
    for(int x = 0; x < imIn.getHeight(); x++)//hauteur
	{
        for(int y = 0; y < imIn.getWidth(); y++)//largeur
        {
            float lumOut = (0.3 * Image_Finale[x*3][y*3+0]) + (0.6 * Image_Finale[x*3][y*3+1]) + (0.1 * Image_Finale[x*3][y*3+2]);
            float lumIn = (0.3 * imIn[x*3][y*3+0]) + (0.6 * imIn[x*3][y*3+1]) + (0.1 * imIn[x*3][y*3+2]);

            som += pow( lumIn - lumOut, 2);
        }
    }
    float EQM = som / (imIn.getHeight() * imIn.getWidth());
    float PSNR = 10 * log10((255*255)/EQM);
    std::cout << "PSNR (en luminance) = " << PSNR << std::endl;


   	//calcul du PSNR (luminance)
	float Somme_Rouge = 0;
	float Somme_Vert = 0;
	float Somme_Bleu = 0;

    for(int x = 0; x < imIn.getHeight(); x++)//hauteur
	{
        for(int y = 0; y < imIn.getWidth(); y++)//largeur
        {
            Somme_Rouge += pow(imIn[x * 3][y * 3] - Image_Finale[x * 3][y * 3], 2);
            Somme_Vert += pow(imIn[x * 3][(y * 3) + 1] - Image_Finale[x * 3][(y * 3) + 1], 2);
            Somme_Bleu += pow(imIn[x * 3][(y * 3) + 2] - Image_Finale[x * 3][(y * 3) + 2], 2);
        }
    }

    float EQM_Rouge = Somme_Rouge / (imIn.getHeight() * imIn.getWidth());
    float EQM_Vert = Somme_Vert / (imIn.getHeight() * imIn.getWidth());
    float EQM_Bleu = Somme_Bleu / (imIn.getHeight() * imIn.getWidth());
    EQM = EQM_Rouge + EQM_Vert + EQM_Bleu;
    PSNR = 10 * log10((3 * pow(255, 2))/EQM);
    std::cout << "PSNR (en couleur) = " << PSNR << std::endl;


	return 0;
}
