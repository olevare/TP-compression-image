#include "ImageBase.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>


ImageBase *Compression(int iteration, ImageBase *imIn)
{
	ImageBase *Composante_BF = new ImageBase((*imIn).getWidth() / 2, (*imIn).getHeight() / 2, (*imIn).getColor());
	ImageBase Composante_FV((*imIn).getWidth() / 2, (*imIn).getHeight() / 2, (*imIn).getColor());
	ImageBase Composante_FH((*imIn).getWidth() / 2, (*imIn).getHeight() / 2, (*imIn).getColor());
	ImageBase Composante_HF((*imIn).getWidth() / 2, (*imIn).getHeight() / 2, (*imIn).getColor());
	ImageBase *Out = new ImageBase((*imIn).getWidth(), (*imIn).getHeight(), (*imIn).getColor());


	ImageBase H_X((*imIn).getWidth() / 2, (*imIn).getHeight(), (*imIn).getColor());
	for(int x = 0; x < H_X.getHeight(); x++)//hauteur
	{
		for(int y = 0; y < H_X.getWidth(); y++)//largeur
		{
			H_X[x * 3][y * 3] = ((*imIn)[x * 3][(y * 2) * 3] + (*imIn)[x * 3][((y * 2) + 1) * 3]) / 2;
			H_X[x * 3][y * 3 + 1] = ((*imIn)[x * 3][(y * 2) * 3 + 1] + (*imIn)[x * 3][((y * 2) + 1) * 3 + 1]) / 2;
			H_X[x * 3][y * 3 + 2] = ((*imIn)[x * 3][(y * 2) * 3 + 2] + (*imIn)[x * 3][((y * 2) + 1) * 3 + 2]) / 2;
		}
	}


	//Composante_BF
	for(int x = 0; x < (*Composante_BF).getHeight(); x++)//hauteur
	{
		for(int y = 0; y < (*Composante_BF).getWidth(); y++)//largeur
		{
			(*Composante_BF)[x * 3][y * 3] = (H_X[(x * 2) * 3][y * 3] + H_X[((x * 2) + 1) * 3][y * 3]) / 2;
			(*Composante_BF)[x * 3][y * 3 + 1] = (H_X[(x * 2) * 3][y * 3 + 1] + H_X[((x * 2) + 1) * 3][y * 3 + 1]) / 2;
			(*Composante_BF)[x * 3][y * 3 + 2] = (H_X[(x * 2) * 3][y * 3 + 2] + H_X[((x * 2) + 1) * 3][y * 3 + 2]) / 2;
		}
	}
	//Composante_BF.save("Composante_BF.ppm");


	//Composante_FV
	for(int x = 0; x < Composante_FV.getHeight(); x++)//hauteur
	{
		for(int y = 0; y < Composante_FV.getWidth(); y++)//largeur
		{
			int comp1 = H_X[(x * 2) * 3][y * 3] - H_X[((x * 2) + 1) * 3][y * 3] + 128;
			int comp2 = H_X[(x * 2) * 3][y * 3 + 1] - H_X[((x * 2) + 1) * 3][y * 3 + 1] + 128;
			int comp3 = H_X[(x * 2) * 3][y * 3 + 2] - H_X[((x * 2) + 1) * 3][y * 3 + 2] + 128;

			Composante_FV[x * 3][y * 3] = (comp1 >= 0) ? ((comp1 <= 255) ? comp1 : 255) : 0;
			Composante_FV[x * 3][y * 3 + 1] = (comp2 >= 0) ? ((comp2 <= 255) ? comp2 : 255) : 0;
			Composante_FV[x * 3][y * 3 + 2] = (comp3 >= 0) ? ((comp3 <= 255) ? comp3 : 255) : 0;


		}
	}
	//Composante_FV.save("Composante_FV.ppm");


	ImageBase G_X((*imIn).getWidth() / 2, (*imIn).getHeight(), (*imIn).getColor());
	for(int x = 0; x < G_X.getHeight(); x++)//hauteur
	{
		for(int y = 0; y < G_X.getWidth(); y++)//largeur
		{
			int comp1 = (*imIn)[x * 3][(y * 2) * 3] - (*imIn)[x * 3][((y * 2) + 1) * 3] + 128;
			int comp2 = (*imIn)[x * 3][(y * 2) * 3 + 1] - (*imIn)[x * 3][((y * 2) + 1) * 3 + 1] + 128;
			int comp3 = (*imIn)[x * 3][(y * 2) * 3 + 2] - (*imIn)[x * 3][((y * 2) + 1) * 3 + 2] + 128;

			G_X[x * 3][y * 3] = (comp1 >= 0) ? ((comp1 <= 255) ? comp1 : 255) : 0;
			G_X[x * 3][y * 3 + 1] = (comp2 >= 0) ? ((comp2 <= 255) ? comp2 : 255) : 0;
			G_X[x * 3][y * 3 + 2] = (comp3 >= 0) ? ((comp3 <= 255) ? comp3 : 255) : 0;
		}
	}


	//Composante_FH
	for(int x = 0; x < Composante_FH.getHeight(); x++)//hauteur
	{
		for(int y = 0; y < Composante_FH.getWidth(); y++)//largeur
		{
			Composante_FH[x * 3][y * 3] = (G_X[(x * 2) * 3][y * 3] + G_X[((x * 2) + 1) * 3][y * 3]) / 2;
			Composante_FH[x * 3][y * 3 + 1] = (G_X[(x * 2) * 3][y * 3 + 1] + G_X[((x * 2) + 1) * 3][y * 3 + 1]) / 2;
			Composante_FH[x * 3][y * 3 + 2] = (G_X[(x * 2) * 3][y * 3 + 2] + G_X[((x * 2) + 1) * 3][y * 3 + 2]) / 2;
		}
	}
	//Composante_FH.save("Composante_FH.ppm");


	//Composante_HF
	for(int x = 0; x < Composante_HF.getHeight(); x++)//hauteur
	{
		for(int y = 0; y < Composante_HF.getWidth(); y++)//largeur
		{
			int comp1 = (G_X[(x * 2) * 3][y * 3] - G_X[((x * 2) + 1) * 3][y * 3]) + 128;
			int comp2 = (G_X[(x * 2) * 3][y * 3 + 1] - G_X[((x * 2) + 1) * 3][y * 3 + 1]) + 128;
			int comp3 = (G_X[(x * 2) * 3][y * 3 + 2] - G_X[((x * 2) + 1) * 3][y * 3 + 2]) + 128;

			Composante_HF[x * 3][y * 3] = (comp1 >= 0) ? ((comp1 <= 255) ? comp1 : 255) : 0;
			Composante_HF[x * 3][y * 3 + 1] = (comp2 >= 0) ? ((comp2 <= 255) ? comp2 : 255) : 0;
			Composante_HF[x * 3][y * 3 + 2] = (comp3 >= 0) ? ((comp3 <= 255) ? comp3 : 255) : 0;
		}
	}
	//Composante_HF.save("Composante_HF.ppm");


	if(iteration > 0)
	{
		Composante_BF = Compression(iteration - 1, Composante_BF);

		for(int x = 0; x < (*Out).getHeight(); x++)//hauteur
		{
			if(x < (*Composante_BF).getHeight())
			{
				for(int k = 0; k < (*Composante_BF).getWidth(); k++)//largeur
				{
					(*Out)[x * 3][k * 3] = (*Composante_BF)[x * 3][k * 3];
					(*Out)[x * 3][k * 3 + 1] = (*Composante_BF)[x * 3][k * 3 + 1];
					(*Out)[x * 3][k * 3 + 2] = (*Composante_BF)[x * 3][k * 3 + 2];
				}

				int i = 0;

				for(int k = (*Composante_BF).getWidth(); k < (*Out).getWidth(); k++)//largeur
				{
					(*Out)[x * 3][k * 3] = Composante_FV[x * 3][i * 3];
					(*Out)[x * 3][k * 3 + 1] = Composante_FV[x * 3][i * 3 + 1];
					(*Out)[x * 3][k * 3 + 2] = Composante_FV[x * 3][i * 3 + 2];

					i++;
				}
			}
			else
			{
				for(int k = 0; k < Composante_FH.getWidth(); k++)//largeur
				{
					(*Out)[x * 3][k * 3] = Composante_FH[(x % Composante_FH.getHeight()) * 3][k * 3];
					(*Out)[x * 3][k * 3 + 1] = Composante_FH[(x % Composante_FH.getHeight()) * 3][k * 3 + 1];
					(*Out)[x * 3][k * 3 + 2] = Composante_FH[(x % Composante_FH.getHeight()) * 3][k * 3 + 2];
				}

				int i = 0;
				for(int k = Composante_FH.getWidth(); k < (*Out).getWidth(); k++)//largeur
				{
					(*Out)[x * 3][k * 3] = Composante_HF[(x % Composante_FH.getHeight()) * 3][i * 3];
					(*Out)[x * 3][k * 3 + 1] = Composante_HF[(x % Composante_FH.getHeight()) * 3][i * 3 + 1];
					(*Out)[x * 3][k * 3 + 2] = Composante_HF[(x % Composante_FH.getHeight()) * 3][i * 3 + 2];

					i++;
				}
			}
		}

	}
	else
	{
		for(int x = 0; x < (*Out).getHeight(); x++)//hauteur
		{
			if(x < (*Composante_BF).getHeight())
			{
				for(int k = 0; k < (*Composante_BF).getWidth(); k++)//largeur
				{
					(*Out)[x * 3][k * 3] = (*Composante_BF)[x * 3][k * 3];
					(*Out)[x * 3][k * 3 + 1] = (*Composante_BF)[x * 3][k * 3 + 1];
					(*Out)[x * 3][k * 3 + 2] = (*Composante_BF)[x * 3][k * 3 + 2];
				}

				int i = 0;

				for(int k = (*Composante_BF).getWidth(); k < (*Out).getWidth(); k++)//largeur
				{
					(*Out)[x * 3][k * 3] = Composante_FV[x * 3][i * 3];
					(*Out)[x * 3][k * 3 + 1] = Composante_FV[x * 3][i * 3 + 1];
					(*Out)[x * 3][k * 3 + 2] = Composante_FV[x * 3][i * 3 + 2];

					i++;
				}
			}
			else
			{
				for(int k = 0; k < Composante_FH.getWidth(); k++)//largeur
				{
					(*Out)[x * 3][k * 3] = Composante_FH[(x % Composante_FH.getHeight()) * 3][k * 3];
					(*Out)[x * 3][k * 3 + 1] = Composante_FH[(x % Composante_FH.getHeight()) * 3][k * 3 + 1];
					(*Out)[x * 3][k * 3 + 2] = Composante_FH[(x % Composante_FH.getHeight()) * 3][k * 3 + 2];
				}

				int i = 0;
				for(int k = Composante_FH.getWidth(); k < (*Out).getWidth(); k++)//largeur
				{
					(*Out)[x * 3][k * 3] = Composante_HF[(x % Composante_FH.getHeight()) * 3][i * 3];
					(*Out)[x * 3][k * 3 + 1] = Composante_HF[(x % Composante_FH.getHeight()) * 3][i * 3 + 1];
					(*Out)[x * 3][k * 3 + 2] = Composante_HF[(x % Composante_FH.getHeight()) * 3][i * 3 + 2];

					i++;
				}
			}
		}
	}

	delete Composante_BF;
	delete imIn;

	return Out;
}

ImageBase *Decompression(int iteration, ImageBase *imIn)
{
	ImageBase *Composante_BF = new ImageBase((*imIn).getWidth() / 2, (*imIn).getHeight() / 2, (*imIn).getColor());
	ImageBase Composante_FV((*imIn).getWidth() / 2, (*imIn).getHeight() / 2, (*imIn).getColor());
	ImageBase Composante_FH((*imIn).getWidth() / 2, (*imIn).getHeight() / 2, (*imIn).getColor());
	ImageBase Composante_HF((*imIn).getWidth() / 2, (*imIn).getHeight() / 2, (*imIn).getColor());
	ImageBase *Out = new ImageBase((*imIn).getWidth(), (*imIn).getHeight(), (*imIn).getColor());

	int i = 0;
	int j = 0;


	//Composante_BF
	for(int x = 0; x < (*Composante_BF).getHeight(); x++)//hauteur
	{
		for(int y = 0; y < (*Composante_BF).getWidth(); y++)//largeur
		{
			(*Composante_BF)[x * 3][y * 3] = (*imIn)[x * 3][y * 3];
			(*Composante_BF)[x * 3][y * 3 + 1] = (*imIn)[x * 3][y * 3 + 1];
			(*Composante_BF)[x * 3][y * 3 + 2] = (*imIn)[x * 3][y * 3 + 2];
		}
	}
	//(*Composante_BF).save("Composante_BF.ppm");

	if(iteration > 0)
	{
		Composante_BF = Decompression(iteration - 1, Composante_BF);
	}


	//Composante_FV
	for(int x = 0; x <  Composante_FV.getHeight(); x++)//hauteur
	{
		for(int y = Composante_FV.getWidth(); y < (*imIn).getWidth(); y++)//largeur
		{
			Composante_FV[x * 3][j * 3] = (*imIn)[x * 3][y * 3];
			Composante_FV[x * 3][j * 3 + 1] = (*imIn)[x * 3][y * 3 + 1];
			Composante_FV[x * 3][j * 3 + 2] = (*imIn)[x * 3][y * 3 + 2];
			j++;
		}
		j = 0;
	}
	//Composante_FV.save("Composante_FV.ppm");
	j = 0;


	//Composante_FH
	for(int x = Composante_FH.getHeight(); x < (*imIn).getHeight(); x++)//hauteur
	{
		for(int y = 0; y < Composante_FH.getWidth(); y++)//largeur
		{
			Composante_FH[i * 3][y * 3] = (*imIn)[x * 3][y * 3];
			Composante_FH[i * 3][y * 3 + 1] = (*imIn)[x * 3][y * 3 + 1];
			Composante_FH[i * 3][y * 3 + 2] = (*imIn)[x * 3][y * 3 + 2];
		}
		i++;
	}
	//Composante_FH.save("Composante_FH.ppm");
	i = 0;


	//Composante_HF
	for(int x = Composante_HF.getHeight(); x < (*imIn).getHeight(); x++)//hauteur
	{
		for(int y = Composante_HF.getWidth(); y < (*imIn).getWidth(); y++)//largeur
		{
			Composante_HF[i * 3][j * 3] = (*imIn)[x * 3][y * 3];
			Composante_HF[i * 3][j * 3 + 1] = (*imIn)[x * 3][y * 3 + 1];
			Composante_HF[i * 3][j * 3 + 2] = (*imIn)[x * 3][y * 3 + 2];
			j++;
		}
		j = 0;
		i++;
	}
	//Composante_HF.save("Composante_HF.ppm");


	ImageBase H_X((*Composante_BF).getWidth(), (*Composante_BF).getHeight() * 2, (*Composante_BF).getColor());
	for(int x = 0; x < H_X.getHeight(); x += 2)//hauteur
	{
		for(int y = 0; y < H_X.getWidth(); y++)//largeur
		{
			H_X[x * 3][y * 3] = (*Composante_BF)[(x / 2) * 3][y * 3] + (Composante_FV[(x / 2) * 3][y * 3] - 128) / 2;
			H_X[x * 3][y * 3 + 1] = (*Composante_BF)[(x / 2) * 3][y * 3 + 1] + (Composante_FV[(x / 2) * 3][y * 3 + 1] - 128) / 2;
			H_X[x * 3][y * 3 + 2] = (*Composante_BF)[(x / 2) * 3][y * 3 + 2] + (Composante_FV[(x / 2) * 3][y * 3 + 2] - 128) / 2;

			H_X[(x + 1) * 3][y * 3] = (*Composante_BF)[(x / 2) * 3][y * 3] + (128 - Composante_FV[(x / 2) * 3][y * 3]) / 2;
			H_X[(x + 1) * 3][y * 3 + 1] = (*Composante_BF)[(x / 2) * 3][y * 3 + 1] + (128 - Composante_FV[(x / 2) * 3][y * 3 + 1]) / 2;
			H_X[(x + 1) * 3][y * 3 + 2] = (*Composante_BF)[(x / 2) * 3][y * 3 + 2] + (128 - Composante_FV[(x / 2) * 3][y * 3 + 2]) / 2;
		}
	}
	H_X.save("H_X.ppm");


	ImageBase G_X(Composante_FH.getWidth(), Composante_FH.getHeight() * 2, Composante_FH.getColor());
	for(int x = 0; x < G_X.getHeight(); x += 2)//hauteur
	{
		for(int y = 0; y < G_X.getWidth(); y++)//largeur
		{
			G_X[x * 3][y * 3] = Composante_FH[(x / 2) * 3][y * 3] + (Composante_HF[(x / 2) * 3][y * 3] - 128) / 2;
			G_X[x * 3][y * 3 + 1] = Composante_FH[(x / 2) * 3][y * 3 + 1] + (Composante_HF[(x / 2) * 3][y * 3 + 1] - 128) / 2;
			G_X[x * 3][y * 3 + 2] = Composante_FH[(x / 2) * 3][y * 3 + 2] + (Composante_HF[(x / 2) * 3][y * 3 + 2] - 128) / 2;

			G_X[(x + 1) * 3][y * 3] = Composante_FH[(x / 2) * 3][y * 3] + (128 - Composante_HF[(x / 2) * 3][y * 3]) / 2;
			G_X[(x + 1) * 3][y * 3 + 1] = Composante_FH[(x / 2) * 3][y * 3 + 1] + (128 - Composante_HF[(x / 2) * 3][y * 3 + 1]) / 2;
			G_X[(x + 1) * 3][y * 3 + 2] = Composante_FH[(x / 2) * 3][y * 3 + 2] + (128 - Composante_HF[(x / 2) * 3][y * 3 + 2]) / 2;
		}
	}
	G_X.save("G_X.ppm");


	for(int x = 0; x < (*Out).getHeight(); x++)//hauteur
	{
		for(int y = 0; y < (*Out).getWidth(); y += 2)//largeur
		{
			(*Out)[x * 3][y * 3] = H_X[x * 3][(y / 2) * 3] + (G_X[x * 3][(y / 2) * 3] - 128) / 2;
			(*Out)[x * 3][y * 3 + 1] = H_X[x * 3][(y / 2) * 3 + 1] + (G_X[x * 3][(y / 2) * 3 + 1] - 128) / 2;
			(*Out)[x * 3][y * 3 + 2] = H_X[x * 3][(y / 2) * 3 + 2] + (G_X[x * 3][(y / 2) * 3 + 2] - 128) / 2;

			(*Out)[x * 3][(y + 1) * 3] = H_X[x * 3][(y / 2) * 3] + (128 - G_X[x * 3][(y / 2) * 3]) / 2;
			(*Out)[x * 3][(y + 1) * 3 + 1] = H_X[x * 3][(y / 2) * 3 + 1] + (128 - G_X[x * 3][(y / 2) * 3]) / 2;
			(*Out)[x * 3][(y + 1) * 3 + 2] = H_X[x * 3][(y / 2) * 3 + 2] + (128 - G_X[x * 3][(y / 2) * 3]) / 2;
		}
	}

	delete Composante_BF;
	delete imIn;

	return Out;
}


int main(int argc, char **argv)
{
	char cNomImgLue[250];
	int iteration;
  
	if (argc != 2) 
	{
		printf("Usage: ImageIn.ppm\n"); 
		return 1;
	}
	sscanf(argv[1],"%s",cNomImgLue) ;

	std::cout << "Combien d'itération voulez-vous ?" << std::endl;
	std::cin >> iteration;
	
	//lecture de l'image
	ImageBase *imIn = new ImageBase;
	ImageBase *imOut = new ImageBase;

	(*imIn).load(cNomImgLue);

	//imOut = Compression(iteration - 1, imIn);
	//(*imOut).save("Compression.ppm");

	imOut = Decompression(iteration - 1, imIn);
	(*imOut).save("Decompression.ppm");

	delete imOut;

	return 0;
}