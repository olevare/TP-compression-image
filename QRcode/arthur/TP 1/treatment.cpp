#include <cmath>

#include "treatment.hpp"

void NoirEtBlanc(ImageBase& src, ImageBase& dest) {
    for (int i = 0, h = src.getHeight(); i < h; i++) {
        for (int j = 0, w = src.getWidth(); j < w; j++) {
            dest[i][j] = (unsigned char)(
                            (unsigned int)src[i * 3][j * 3] * 0.3 +
                            (unsigned int)src[i * 3][j * 3 + 1] * 0.59 +
                            (unsigned int)src[i * 3][j * 3 + 2] * 0.11);
        }
    }
}

unsigned char BinarisationGlobal(ImageBase& src, ImageBase& dest) {
    unsigned char min_value = 255, max_value = 0;
    for (int i = 0, h = src.getHeight(); i < h; i++) {
        for (int j = 0, w = src.getWidth(); j < w; j++) {
            if (min_value > src[i][j])
                min_value = src[i][j];
            if (max_value < src[i][j])
                max_value = src[i][j];
        }
    }
    unsigned char seuil = (max_value - min_value) / 2;
    for (int i = 0, h = src.getHeight(); i < h; i++) {
        for (int j = 0, w = src.getWidth(); j < w; j++) {
            if (src[i][j] <= seuil)
                dest[i][j] = 0;
            else
                dest[i][j] = 255;
        }
    }
    return seuil;
}

unsigned char BinarisationMajoritaire(ImageBase& src, ImageBase& dest, unsigned int size) {
    unsigned char min_value = 255, max_value = 0;
    for (int i = 0, h = src.getHeight(); i < h; i++) {
        for (int j = 0, w = src.getWidth(); j < w; j++) {
            if (min_value > src[i][j])
                min_value = src[i][j];
            if (max_value < src[i][j])
                max_value = src[i][j];
        }
    }
    unsigned char seuil = (max_value - min_value) / 2;
    unsigned char _blanc, _noir, _color;
    for (int i = 0, h = src.getHeight() / size; i < h; i++) {
        for (int j = 0, w = src.getWidth() / size; j < w; j++) {
            _blanc = _noir = 0;
            for (int _i = 0; _i < size; _i++) {
                for (int _j = 0; _j < size; _j++) {
                    if (src[i * size + _i][j * size + _j] <= seuil)
                        _noir++;
                    else
                        _blanc++;
                }
            }
            _color = _blanc > _noir ? 255 : 0;
            for (int _i = 0; _i < size; _i++) {
                for (int _j = 0; _j < size; _j++) {
                    dest[i * size + _i][j * size + _j] = _color;
                }
            }
        }
    }
    return seuil;
}

void BinarisationNiblack(ImageBase& src, ImageBase& dest, unsigned int size, float k) {
    float moyenne, ecart_type;
    unsigned int count;
    for (int i = 0, h = src.getHeight(); i < h; i++) {
        for (int j = 0, w = src.getWidth(); j < w; j++) {
            moyenne = ecart_type = 0.f;
            count = 0;
            for (int _i = i - size / 2, _imax = i + size / 2; _i <= _imax; _i++) {
                if (_i < 0 || _i >= h) continue;
                for (int _j = j - size / 2, _jmax = j + size / 2; _j <= _jmax;  _j++) {
                    if (_j < 0 || _j >= w) continue;
                    moyenne += (float)src[_i][_j];
                    count++;
                }
            }
            moyenne /= (float)count;
            for (int _i = i - size / 2, _imax = i + size / 2; _i <= _imax; _i++) {
                if (_i < 0 || _i >= h) continue;
                for (int _j = j - size / 2, _jmax = j + size / 2; _j <= _jmax;  _j++) {
                    if (_j < 0 || _j >= w) continue;
                    ecart_type += std::pow((float)src[_i][_j] - moyenne, 2);
                }
            }
            ecart_type = std::sqrt(ecart_type / (float)count);
            if (src[i][j] <= (unsigned char)(moyenne + k * ecart_type))
                dest[i][j] = 0;
            else
                dest[i][j] = 255;
        }
    }
}

void BinarisationMixte(ImageBase& src, ImageBase& dest, unsigned int size, float k) {
    unsigned char min_value = 255, max_value = 0;
    for (int i = 0, h = src.getHeight(); i < h; i++) {
        for (int j = 0, w = src.getWidth(); j < w; j++) {
            if (min_value > src[i][j])
                min_value = src[i][j];
            if (max_value < src[i][j])
                max_value = src[i][j];
        }
    }
    unsigned char seuil = (max_value - min_value) / 2;
    float moyenne, ecart_type;
    unsigned int count;
    unsigned char tmp_seuil;
    for (int i = 0, h = src.getHeight(); i < h; i++) {
        for (int j = 0, w = src.getWidth(); j < w; j++) {
            moyenne = ecart_type = 0.f;
            count = 0;
            for (int _i = i - size / 2, _imax = i + size / 2; _i <= _imax; _i++) {
                if (_i < 0 || _i >= h) continue;
                for (int _j = j - size / 2, _jmax = j + size / 2; _j <= _jmax;  _j++) {
                    if (_j < 0 || _j >= w) continue;
                    moyenne += (float)src[_i][_j];
                    count++;
                }
            }
            moyenne /= (float)count;
            for (int _i = i - size / 2, _imax = i + size / 2; _i <= _imax; _i++) {
                if (_i < 0 || _i >= h) continue;
                for (int _j = j - size / 2, _jmax = j + size / 2; _j <= _jmax;  _j++) {
                    if (_j < 0 || _j >= w) continue;
                    ecart_type += std::pow((float)src[_i][_j] - moyenne, 2);
                }
            }
            ecart_type = std::sqrt(ecart_type / (float)count);
            tmp_seuil = (unsigned char)(moyenne + k * ecart_type);
            if (src[i][j] <= tmp_seuil || src[i][j] <= seuil)
                dest[i][j] = 0;
            else
                dest[i][j] = 255;
        }
    }
}