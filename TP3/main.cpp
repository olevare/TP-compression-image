#include "ImageBase.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


int main(int argc, char **argv)
{
	char cNomImgLue[250];
  
	if (argc != 2) 
	{
		printf("Usage: ImageIn.pgm\n"); 
		return 1;
	}
	sscanf (argv[1],"%s",cNomImgLue) ;
	
	//lecture de l'image
	ImageBase imIn;
	imIn.load(cNomImgLue);

	ImageBase Prediction(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	//on conserve le canal Rouge
	for(int x = 0; x < imIn.getHeight(); x++)//hauteur
	{
		for(int y = 0; y < imIn.getWidth(); y++)//largeur
		{
			if(x == 0 && y == 0)
			{
				Prediction[x][y] = imIn[x][y];
			}
			else if(x == 0)
			{
				Prediction[x][y] = imIn[imIn.getHeight() - 1][y - 1] - imIn[x][y] + 128;
			}
			else
			{
				Prediction[x][y] = imIn[x - 1][y] - imIn[x][y] + 128;
			}
			
		}
	}

	Prediction.save("Prediction.pgm");

	return 0;
}