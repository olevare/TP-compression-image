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


	//on applique le seuil à l'image dans le buffer
	for(int i = 0; i < lSize[0] * lSize[1]; i++)
	{
			//on convertie le pixel couleur en noir et blanc
			Buffer2[i] = 0.3*(int)Buffer[i*3] + 0.6*(int)Buffer[i*3+1] + 0.1*(int)Buffer[i*3+2];
	}

	//variable utilisé pour incrémenté la position dans le buffer
	//lors de la création de l'image pendant le parcours en hauteur et largeur
	int k = 0;

	//création de l'image de sortie
	for(int i = 0 ; i < out.getWidth(); i++)
	{
		for(int j = 0 ; j < out.getHeight(); j++)
		{
			out[i][j] = Buffer2[k];

			k++;
		}
	}

	//on enregistre l'image de sortie
	out.save("out.pgm");

	return 0;
}