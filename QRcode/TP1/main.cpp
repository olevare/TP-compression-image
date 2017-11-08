// pour compiler:
//		g++ main.cpp ImageBase.cpp -o test

//pour executer(exemple):
//		./test QrCode_phone_03_1280_720_3.data 1280 720 3

//L'image de sortie s'appellera out.pgm

//questions 6 et 7 non effectué !!!



#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "ImageBase.h"

using namespace std;

//parcours tous le buffer à la recherche de la valeur minimum
int Minimum(unsigned char *Buffer, int lSize[3])
{
	int min = 2500;

	for(int i = 0; i < lSize[0] * lSize[1]; i++)
	{
		//si c'est une image en noir et blanc
		if(lSize[2] == 1)
		{
			if(min > Buffer[i])
				min = Buffer[i];
		}
		//si c'est une image couleur
		else
		{
			//on convertie le pixel couleur en noir et blanc
			int test = 0.3*(int)Buffer[i*3] + 0.6*(int)Buffer[i*3+1] + 0.1*(int)Buffer[i*3+2];
			if(min > test)
				min = test;
		}
	}

	return min;
}

//parcours tous le buffer à la recherche de la valeur maximum
int Maximum(unsigned char *Buffer, int lSize[3])
{
	int max = 0;

	for(int i = 0; i < lSize[0] * lSize[1]; i++)
	{
		//si c'est une image en noir et blanc
		if(lSize[2] == 1)
		{
			if(max < Buffer[i])
				max = Buffer[i];
		}
		//si c'est une image couleur
		else
		{
			//on convertie le pixel couleur en noir et blanc
			int test = 0.3*(int)Buffer[i*3] + 0.6*(int)Buffer[i*3+1] + 0.1*(int)Buffer[i*3+2];
			if(max < test)
				max = test;
		}
	}
		
	return max;
}

//parcours l'image seuiller block par block
int Majoritaire(int TailleBlock, ImageBase &out)
{
	//parcours de toute l'image
	for(int i = 0; i < out.getHeight() - TailleBlock; i = i + TailleBlock)
	{
		for(int j = 0; j < out.getWidth() - TailleBlock; j = j + TailleBlock)
		{
			int blancs = 0;
			int noirs = 0;

			//parcours de l'image en block
			//pour compter les blancs et les noirs
			for(int k = i; k < i + TailleBlock; k++)
			{
				for(int l = j; l < j + TailleBlock; l++)
				{
					if (out[k][l] < 125)
						noirs++;
					else
						blancs++;
				}
			}

			//parcours de l'image en block
			//pour modifier les pixels et les mettres soit
			//noir soit blanc
			for(int k = i; k < i + TailleBlock; k++)
			{
				for(int l = j; l < j + TailleBlock; l++)
				{
					if (noirs > blancs)
						out[k][l] = 0;
					else
						out[k][l] = 255;
				}
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	char cNomImgLue[250]; //nom de l'image lu en entrée

	//code du prof
	unsigned char *Buffer, *Buffer2;
	FILE* File;
	int lSize[3];

	if (argc != 5) 
	{
		printf("Usage: fichier à lire, colonnes, ligne, canaux \n"); 
		return -1;
	}
	//on enregistre les données passé en paramètre
	sscanf (argv[1], "%s", cNomImgLue);
	sscanf (argv[2], "%d", &lSize[0]); //colonnes
	sscanf (argv[3], "%d", &lSize[1]); //lignes
	sscanf (argv[4], "%d", &lSize[2]); //canaux

	//on ouvre le fichier
	File = fopen(cNomImgLue, "rb");

	//on charge le fichier dans le buffer
	Buffer = new unsigned char[lSize[0] * lSize[1] * lSize[2]];
	Buffer2 = new unsigned char[lSize[0] * lSize[1]];
	int read = fread(Buffer, sizeof(unsigned char), lSize[0] * lSize[1] * lSize[2], File);

	//on ferme le fichier
	fclose(File);

	//on crée une image de sortie
	ImageBase out(lSize[0], lSize[1], false);

	//question 2
	int min = Minimum(Buffer, lSize);
	int max = Maximum(Buffer, lSize);

	int Seuil = (max + min) / 2;

	//on applique le seuil à l'image dans le buffer
	for(int i = 0; i < lSize[0] * lSize[1]; i++)
	{
		//si c'est une image en noir et blanc
		if(lSize[2] == 1)
		{
			if (Buffer[i] > Seuil) 
				Buffer[i] = 255;
			else
				Buffer[i] = 0;
		}
		//si c'est une image couleur
		else
		{
			//on convertie le pixel couleur en noir et blanc
			Buffer2[i] = 0.3*(int)Buffer[i*3] + 0.6*(int)Buffer[i*3+1] + 0.1*(int)Buffer[i*3+2];
			if (Buffer2[i] > Seuil) 
				Buffer2[i] = 255;
			else
				Buffer2[i] = 0;
		}
	}

	//variable utilisé pour incrémenté la position dans le buffer
	//lors de la création de l'image pendant le parcours en hauteur et largeur
	int k = 0;

	//création de l'image de sortie
	for(int i = 0 ; i < out.getHeight(); i++)
	{
		for(int j = 0 ; j < out.getWidth(); j++)
		{
			//si c'est une image en noir et blanc
			if(lSize[2] == 1)
			{
				if (Buffer[k] > Seuil)
					out[i][j] = 255;
				else
					out[i][j] = 0;
			}
			//si c'est une image couleur
			else
			{
				if (Buffer2[k] > Seuil)
					out[i][j] = 255;
				else
					out[i][j] = 0;
			}

			k++;
		}
	}

	//question 4
	Majoritaire(100, out);

	//on enregistre l'image de sortie
	out.save("out.pgm");

	return 0;
}