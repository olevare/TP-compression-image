#include "ImageBase.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>


int main(int argc, char **argv)
{
	char cNomImgLue[250];
  
	if (argc != 2) 
	{
		printf("Usage: ImageIn.ppm\n"); 
		return 1;
	}
	sscanf (argv[1],"%s",cNomImgLue) ;
	
	//lecture de l'image
	ImageBase imIn;
	imIn.load(cNomImgLue);


	ImageBase Composante_Y(imIn.getWidth(), imIn.getHeight(), false);
	ImageBase Composante_CR(imIn.getWidth()/2, imIn.getHeight()/2, false);
	ImageBase Composante_CR_Out(imIn.getWidth(), imIn.getHeight(), false);
	ImageBase Composante_CB(imIn.getWidth()/2, imIn.getHeight()/2, false);
	ImageBase Composante_CB_Out(imIn.getWidth(), imIn.getHeight(), false);
	ImageBase Image_Finale(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	//on conserve le canal Y
	for(int x = 0; x < Composante_Y.getHeight(); x++)//hauteur
	{
		for(int y = 0; y < Composante_Y.getWidth(); y++)//largeur
		{
			Composante_Y[x][y] = (imIn[x * 3][y * 3] * 0.3) + (imIn[x * 3][(y * 3) + 1] * 0.6) + (imIn[x * 3][(y * 3) + 2] * 0.1);
		}
	}

	Composante_Y.save("Composante_Y.ppm");

	//on diminue la taille des canaux CR et CB
	for(int x = 0; x < Composante_CB.getHeight(); x++)//hauteur
	{
		for(int y = 0; y < Composante_CB.getWidth(); y++)//largeur
		{
			Composante_CB[x][y] = -imIn[(x * 2) * 3][(y * 2) * 3] * 0.1687;
			Composante_CB[x][y] += -imIn[(x * 2) * 3][((y * 2) * 3) + 1] * 0.3313;
			Composante_CB[x][y] += imIn[(x * 2) * 3][((y * 2) * 3) + 2] * 0.5;
			Composante_CB[x][y] += 128;

			Composante_CR[x][y] = imIn[(x * 2) * 3][(y * 2) * 3] * 0.5;
			Composante_CR[x][y] += -imIn[(x * 2) * 3][((y * 2) * 3) + 1] * 0.4187;
			Composante_CR[x][y] += -imIn[(x * 2) * 3][((y * 2) * 3) + 2] * 0.0813;
			Composante_CR[x][y] += 128;
		}
	}

	Composante_CR.save("Composante_CR.ppm");
	Composante_CB.save("Composante_CB.ppm");

	int y_bis = 0;

	//on agrandit de nouveau les canaux CR et CB
	for(int x = 0; x < Composante_CB.getHeight(); x++)//hauteur
	{
		for(int y = 0; y < Composante_CB.getWidth(); y++)//largeur
		{
			if(y_bis == (imIn.getWidth()-1))
				y_bis = 0;

			//composante CR
			Composante_CR_Out[x][y_bis] = Composante_CR[x][y];

			Composante_CR_Out[x][y_bis + 1] = Composante_CR[x][y];

			Composante_CR_Out[x + 1][y_bis] = Composante_CR[x][y];

			Composante_CR_Out[x + 1][y_bis + 1] = Composante_CR[x][y];

			//composante CB
			Composante_CB_Out[x][y_bis] = Composante_CB[x][y];

			Composante_CB_Out[x][y_bis + 1] = Composante_CB[x][y];

			Composante_CB_Out[x + 1][y_bis] = Composante_CB[x][y];

			Composante_CB_Out[x + 1][y_bis + 1] = Composante_CB[x][y];


			y_bis = y_bis + 2;
		}
	}

	Composante_CR_Out.save("Composante_CR_Out.ppm");
	Composante_CB_Out.save("Composante_CB_Out.ppm");

	//fusion des 3 canaux
	for(int x = 0; x < Image_Finale.getHeight(); x++)//hauteur
	{
		for(int y = 0; y < Image_Finale.getWidth(); y++)//largeur
		{
			Image_Finale[x * 3][y * 3] = Composante_Y[x][y] + (1.402 * (Composante_CR_Out[x][y] - 128)); // R

			Image_Finale[x * 3][(y * 3) + 1] = Composante_Y[x][y] - (0.34414 * (Composante_CB_Out[x][y] - 128)); // G
			Image_Finale[x * 3][(y * 3) + 1] += -0.714414 * (Composante_CR_Out[x][y] - 128);

			Image_Finale[x * 3][(y * 3) + 2] = Composante_Y[x][y] + (1.772 * (Composante_CB_Out[x][y] - 128)); // B
		}
	}


	/** r = y + 1.402(cr - 128)
	* g = y - 0.34414 (cb - 128) - 0.714414(cr - 128)
	* b = y + 1.772 (cb - 128)*/

	Image_Finale.save("Image_Finale.ppm");

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