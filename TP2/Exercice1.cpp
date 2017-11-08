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


	ImageBase Composante_Rouge(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	ImageBase Composante_Vert(imIn.getWidth()/2, imIn.getHeight()/2, imIn.getColor());
	ImageBase Composante_Vert_Out(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	ImageBase Composante_Bleu(imIn.getWidth()/2, imIn.getHeight()/2, imIn.getColor());
	ImageBase Composante_Bleu_Out(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	ImageBase Image_Finale(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	//on conserve le canal Rouge
	for(int x = 0; x < imIn.getHeight(); x++)//hauteur
	{
		for(int y = 0; y < imIn.getWidth(); y++)//largeur
		{
			Composante_Rouge[x * 3][y * 3] = imIn[x * 3][y * 3]; // R
			Composante_Rouge[x * 3][(y * 3) + 1] = 0; // G
			Composante_Rouge[x * 3][(y * 3) + 2] = 0; // B
		}
	}

	Composante_Rouge.save("Composante_Rouge.ppm");

	//on diminue la taille des canaux Vert et Bleu
	for(int x = 0; x < Composante_Vert.getHeight(); x++)//hauteur
	{
		for(int y = 0; y < Composante_Vert.getWidth(); y++)//largeur
		{
			Composante_Vert[x * 3][y * 3] = 0; // R
			Composante_Vert[x * 3][(y * 3) + 1] = imIn[(x * 2) * 3][((y * 2) * 3) + 1]; // G
			Composante_Vert[x * 3][(y * 3) + 2] = 0; // B

			Composante_Bleu[x * 3][y * 3] = 0; // R
			Composante_Bleu[x * 3][(y * 3) + 1] = 0; // G
			Composante_Bleu[x * 3][(y * 3) + 2] = imIn[(x * 2) * 3][((y * 2) * 3) + 2]; // B
		}
	}

	Composante_Vert.save("Composante_Vert.ppm");
	Composante_Bleu.save("Composante_Bleu.ppm");

	int y_bis = 0;

	//on agrandit de nouveau les canaux Vert et Bleu
	for(int x = 0; x < Composante_Vert.getHeight(); x++)//hauteur
	{
		for(int y = 0; y < Composante_Vert.getWidth(); y++)//largeur
		{
			if(y_bis == (imIn.getWidth()-1))
				y_bis = 0;

			//composante verte
			Composante_Vert_Out[x * 3][y_bis * 3] = 0; // R
			Composante_Vert_Out[x * 3][(y_bis * 3) + 1] = Composante_Vert[x * 3][(y * 3) + 1]; // G
			Composante_Vert_Out[x * 3][(y_bis * 3) + 2] = 0; // B

			Composante_Vert_Out[x * 3][(y_bis + 1) * 3] = 0; // R
			Composante_Vert_Out[x * 3][((y_bis + 1) * 3) + 1] = Composante_Vert[x * 3][(y * 3) + 1]; // G
			Composante_Vert_Out[x * 3][((y_bis + 1) * 3) + 2] = 0; // B

			Composante_Vert_Out[(x + 1) * 3][y_bis * 3] = 0; // R
			Composante_Vert_Out[(x + 1) * 3][(y_bis * 3) + 1] = Composante_Vert[x * 3][(y * 3) + 1]; // G
			Composante_Vert_Out[(x + 1) * 3][(y_bis * 3) + 2] = 0; // B

			Composante_Vert_Out[(x + 1) * 3][(y_bis + 1) * 3] = 0; // R
			Composante_Vert_Out[(x + 1) * 3][((y_bis + 1) * 3) + 1] = Composante_Vert[x * 3][(y * 3) + 1]; // G
			Composante_Vert_Out[(x + 1) * 3][((y_bis + 1) * 3) + 2] = 0; // B

			//composante bleu
			Composante_Bleu_Out[x * 3][y_bis * 3] = 0; // R
			Composante_Bleu_Out[x * 3][(y_bis * 3) + 1] = 0; // G
			Composante_Bleu_Out[x * 3][(y_bis * 3) + 2] = Composante_Bleu[x * 3][(y * 3) + 2]; // B

			Composante_Bleu_Out[x * 3][(y_bis + 1) * 3] = 0; // R
			Composante_Bleu_Out[x * 3][((y_bis + 1) * 3) + 1] = 0; // G
			Composante_Bleu_Out[x * 3][((y_bis + 1) * 3) + 2] = Composante_Bleu[x * 3][(y * 3) + 2]; // B

			Composante_Bleu_Out[(x + 1) * 3][y_bis * 3] = 0; // R
			Composante_Bleu_Out[(x + 1) * 3][(y_bis * 3) + 1] = 0; // G
			Composante_Bleu_Out[(x + 1) * 3][(y_bis * 3) + 2] = Composante_Bleu[x * 3][(y * 3) + 2]; // B

			Composante_Bleu_Out[(x + 1) * 3][(y_bis + 1) * 3] = 0; // R
			Composante_Bleu_Out[(x + 1) * 3][((y_bis + 1) * 3) + 1] = 0; // G
			Composante_Bleu_Out[(x + 1) * 3][((y_bis + 1) * 3) + 2] = Composante_Bleu[x * 3][(y * 3) + 2]; // B


			y_bis = y_bis + 2;
		}
	}

	Composante_Vert_Out.save("Composante_Vert_Out.ppm");
	Composante_Bleu_Out.save("Composante_Bleu_Out.ppm");

	//fusion des 3 canaux
	for(int x = 0; x < Image_Finale.getHeight(); x++)//hauteur
	{
		for(int y = 0; y < Image_Finale.getWidth(); y++)//largeur
		{
			Image_Finale[x * 3][y * 3] = Composante_Rouge[x * 3][y * 3]; // R
			Image_Finale[x * 3][(y * 3) + 1] = Composante_Vert_Out[x * 3][(y * 3) + 1]; // G
			Image_Finale[x * 3][(y * 3) + 2] = Composante_Bleu_Out[x * 3][(y * 3) + 2]; // B
		}
	}

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
