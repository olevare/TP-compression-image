#ifndef TREATMENT_HPP
#define TREATMENT_HPP

#include "ImageBase.h"

void NoirEtBlanc(ImageBase& src, ImageBase& dest);

unsigned char BinarisationGlobal(ImageBase& src, ImageBase& dest);

unsigned char BinarisationMajoritaire(ImageBase& src, ImageBase& dest, unsigned int size);

void BinarisationNiblack(ImageBase& src, ImageBase& dest, unsigned int size, float k = 0.2f);

void BinarisationMixte(ImageBase& src, ImageBase& dest, unsigned int size, float k = 0.2f);

#endif