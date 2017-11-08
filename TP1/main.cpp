#include "ImageBase.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
//#include <complexe>

int num = 0;
int taille;

//calcul du PSNR
/*double PSNR(const ImageBase& imgBase, const ImageBase& imgFinal)
{
    double EQM = 0;
    double divpix = 1.0 / static_cast<double>(imgBase.getWidth() * imgBase.getHeight() * 3);
    for(int i = 0; i < imgBase.getWidth(); ++i)
    {
        for(int j = 0; j < imgBase.getHeight(); ++j)
        {
            EQM += divpix * std::pow(imgBase(i,j, Layer::RED) - imgFinal(i,j, Layer::RED), 2);
            EQM += divpix * std::pow(imgBase(i,j, Layer::GREEN) - imgFinal(i,j, Layer::GREEN), 2);
            EQM += divpix * std::pow(imgBase(i,j, Layer::BLUE) - imgFinal(i,j, Layer::BLUE), 2);
        }
    }

    return 10.0 * std::log10(65025.0 / EQM);
}*/

//fonction qui calcule la distance entre 2 couleurs
float distance(int R, int G, int B, int R2, int G2, int B2)
{
	return sqrt(pow(R-R2,2)+pow(G-G2,2)+pow(B-B2,2));
}

bool Check_KMeans(int tabPixel[256][3], int tabSommePixelGroupe[256][3])
{
	bool resultat = false;

	num++;

	printf("boucle numéro %d\n", num);

	for (int i = 0; i < taille; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if(tabPixel[i][j] != tabSommePixelGroupe[i][j])
			{
				tabPixel[i][j] = tabSommePixelGroupe[i][j];
				resultat = true;
			}
		}
	}

	return resultat;
}

void K_Means(ImageBase imIn)
{
	//création image couleur de sortie
	ImageBase choisi(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	ImageBase moyenne(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	ImageBase final(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	ImageBase gris(imIn.getWidth(), imIn.getHeight(), false);
	ImageBase palette(taille, 1, imIn.getColor());

	//initialisation aléatoire
	srand (time(NULL));

	//tableau des 256 pixel aléatoire
	int tabPixel[taille][3];

	//prend aléatoirement 256 pixels
	for (int i = 0; i < taille; i++)
	{
		int aleaX1 = rand() % imIn.getWidth(); //largeur
		int aleaY1 = rand() % imIn.getHeight(); //hauteur

		tabPixel[i][0] = imIn[aleaY1 * 3][aleaX1 * 3];
		tabPixel[i][1] = imIn[aleaY1 * 3][(aleaX1 * 3) + 1];
		tabPixel[i][2] = imIn[aleaY1 * 3][(aleaX1 * 3) + 2];
	}

	//nombre de pixel pour chaque groupe
	int groupe[taille] = {0};

	bool first = true;

	bool boucle = true;

	while(boucle)
	{

		for (int i = 0; i < taille; i++)
		{
			groupe[i] = 0;
		}

		//tableau qui somme la valeur des pixel pour chauque groupe
		int tabSommePixelGroupe[taille][3] = {0};


		for(int y = 0; y < imIn.getHeight() - 1; y++)//hauteur
		{
			for(int x = 0; x < imIn.getWidth() - 1; x++)//largeur
			{

				float MinDistance = distance(imIn[y*3][x*3], imIn[y*3][(x*3)+1], imIn[y*3][(x*3)+2], tabPixel[0][0], tabPixel[0][1], tabPixel[0][2]);
				int emplacement = 0;

				for (int i = 1; i < taille; i++)
				{
					//si la distance avec un pixel est plus grande qu'avec l'autre
					if(MinDistance > distance(imIn[y*3][x*3], imIn[y*3][(x*3)+1], imIn[y*3][(x*3)+2], tabPixel[i][0], tabPixel[i][1], tabPixel[i][2]))
					{
						MinDistance = distance(imIn[y*3][x*3], imIn[y*3][(x*3)+1], imIn[y*3][(x*3)+2], tabPixel[i][0], tabPixel[i][1], tabPixel[i][2]);
						emplacement = i;
					}
				}

				groupe[emplacement]++;
				tabSommePixelGroupe[emplacement][0] += imIn[y * 3][x * 3];
				tabSommePixelGroupe[emplacement][1] += imIn[y * 3][(x * 3) + 1];
				tabSommePixelGroupe[emplacement][2] += imIn[y * 3][(x * 3) + 2];
			}
		}

		//on fait la moyenne des pixels de chaque groupe
		for (int i = 0; i < taille; i++)
		{
			tabSommePixelGroupe[i][0] = ((groupe[i] == 0 || tabSommePixelGroupe[i][0] == 0) ? tabSommePixelGroupe[i][0] : tabSommePixelGroupe[i][0] / groupe[i]);
			tabSommePixelGroupe[i][1] = ((groupe[i] == 0 || tabSommePixelGroupe[i][1] == 0) ? tabSommePixelGroupe[i][1] : tabSommePixelGroupe[i][1] / groupe[i]);
			tabSommePixelGroupe[i][2] = ((groupe[i] == 0 || tabSommePixelGroupe[i][2] == 0) ? tabSommePixelGroupe[i][2] : tabSommePixelGroupe[i][2] / groupe[i]);
		}

		//regarde si on a atteint la convergence ou pas
		boucle = Check_KMeans(tabPixel, tabSommePixelGroupe);

		//si c'est la première fois
		//génère l'image avec les couleurs choisi à l'initialisation
		//et la l'image avec la couleir moyenne correspondant
		if(first)
		{
			for(int y = 0; y < imIn.getHeight() - 1; y++)//hauteur
			{
				for(int x = 0; x < imIn.getWidth() - 1; x++)//largeur
				{

					float MinDistance = distance(imIn[y*3][x*3], imIn[y*3][(x*3)+1], imIn[y*3][(x*3)+2], tabPixel[0][0], tabPixel[0][1], tabPixel[0][2]);
					int emplacement = 0;

					for (int i = 1; i < taille; i++)
					{
						//si la distance avec un pixel est plus grande qu'avec l'autre
						if(MinDistance > distance(imIn[y*3][x*3], imIn[y*3][(x*3)+1], imIn[y*3][(x*3)+2], tabPixel[i][0], tabPixel[i][1], tabPixel[i][2]))
						{
							MinDistance = distance(imIn[y*3][x*3], imIn[y*3][(x*3)+1], imIn[y*3][(x*3)+2], tabPixel[i][0], tabPixel[i][1], tabPixel[i][2]);
							emplacement = i;
						}
					}

					choisi[y * 3][x * 3] = tabPixel[emplacement][0];
					choisi[y * 3][(x * 3) + 1] = tabPixel[emplacement][1];
					choisi[y * 3][(x * 3) + 2] = tabPixel[emplacement][2];

					moyenne[y * 3][x * 3] = tabSommePixelGroupe[emplacement][0];
					moyenne[y * 3][(x * 3) + 1] = tabSommePixelGroupe[emplacement][1];
					moyenne[y * 3][(x * 3) + 2] = tabSommePixelGroupe[emplacement][2];

				}
			}

			first = false;

			//sauvegarde de l'image couleur
			choisi.save("Choisi256Means.ppm");
			moyenne.save("Moyenne256Means.ppm");
		}

	}

	printf("oui oui oui\n");

	for(int y = 0; y < imIn.getHeight() - 1; y++)//hauteur
	{
		for(int x = 0; x < imIn.getWidth() - 1; x++)//largeur
		{

			float MinDistance = distance(imIn[y*3][x*3], imIn[y*3][(x*3)+1], imIn[y*3][(x*3)+2], tabPixel[0][0], tabPixel[0][1], tabPixel[0][2]);
			int emplacement = 0;

			for (int i = 1; i < taille; i++)
			{
				//si la distance avec un pixel est plus grande qu'avec l'autre
				if(MinDistance > distance(imIn[y*3][x*3], imIn[y*3][(x*3)+1], imIn[y*3][(x*3)+2], tabPixel[i][0], tabPixel[i][1], tabPixel[i][2]))
				{
					MinDistance = distance(imIn[y*3][x*3], imIn[y*3][(x*3)+1], imIn[y*3][(x*3)+2], tabPixel[i][0], tabPixel[i][1], tabPixel[i][2]);
					emplacement = i;
				}
			}

			gris[y][x] = emplacement;

			final[y * 3][x * 3] = tabPixel[emplacement][0];
			final[y * 3][(x * 3) + 1] = tabPixel[emplacement][1];
			final[y * 3][(x * 3) + 2] = tabPixel[emplacement][2];

		}
	}

	gris.save("Gris256Means.pgm");

	final.save("Final256Means.ppm");

	for (int i = 0; i < taille; i++)
	{
		palette[0][(i * 3)] = tabPixel[i][0];
		palette[0][(i * 3) + 1] = tabPixel[i][1];
		palette[0][(i * 3) + 2] = tabPixel[i][2];
	}

	palette.save("Palette256Means.ppm");
}

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

	std::cout << "quelle taille pour le K_Means ??" << std::endl;

	std::cin >> taille;

	K_Means(imIn);

	return 0;
}
