#include <iostream>

void ConvertToBin(int n, char *psz)
{
  if(!n)
  	*psz++ = 48;
  else
  {
    while(!(n & 0x80000000)) 
    	n <<= 1;
    while(n)
    {
      *psz++ = (n & 0x80000000) ? 49: 48;
      n <<= 1;
    }
  }
  *psz = 0;
} 

int main(int argc, char * argv[])
{

	char tab[] = "HMIN322 – Codes graphiques";
    char *bin = new char[8];      //8 bits doivent suffirent

    int i = 0;

    while(tab[i] != '\0')
    {
    	ConvertToBin((int)tab[i], bin);      //Conversion

    	char sortie1[4];
    	sortie1[0] = bin[0];
    	sortie1[1] = bin[1];
    	sortie1[2] = bin[2];
    	sortie1[3] = bin[3];

    	char sortie2[4];
    	sortie2[0] = bin[4];
    	sortie2[1] = bin[5];
    	sortie2[2] = bin[6];
    	sortie2[3] = bin[7];

    	char resultante[8] = {0};

    	for

    	printf("%s",bin);   //Affichage du resultat

    	i++;
    }  

	/*int matrice [7][4] = {{1, 1, 0, 1},
						{1, 0, 1, 1},
						{1, 0, 0, 0},
						{0, 1, 1, 1},
						{0, 1, 0, 0},
						{0, 0, 1, 0},
						{0, 0, 0, 1}};*/


    return 0;
}