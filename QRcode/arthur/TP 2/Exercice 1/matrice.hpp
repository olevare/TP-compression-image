#ifndef _MATRICE_HPP
#define _MATRICE_HPP

#include <iostream>
#include <array>

// Classe générique de matrices
template <typename T, unsigned char N, unsigned char M>
class Matrice {

    std::array<std::array<T, M>, N> data;

public:

    Matrice() {}
    Matrice(const Matrice<T, N, M>& x) {
        for (unsigned char i = 0; i < N; i++) {
            for (unsigned char j = 0; j < M; j++) {
                this->data[i][j] = x.data[i][j];
            }
        }
    }

    template <unsigned char _M>
    Matrice<T, N, _M> operator*(const Matrice<T, M, _M>& x) const {
        Matrice<T, N, _M> res;
        for (unsigned char i = 0; i < N; i++) {
            for (unsigned char j = 0; j < _M; j++) {
                res[i][j] = 0;
                for (unsigned char k = 0; k < M; k++) {
                    res[i][j] += this->data[i][k] * x[k][j];
                }
            }
        }
        return res;
    }

    std::array<T, M>& operator[](unsigned int i) {
        return this->data[i];
    }
    const std::array<T, M>& operator[](unsigned int i) const {
        return this->data[i];
    }

};

template <typename T, unsigned char N, unsigned char M>
std::ostream& operator<<(std::ostream& stream, const Matrice<T, N, M>& m) {
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < M; j++) {
            stream << m[i][j] << " ";
        }
        stream << std::endl;
    }
    return stream;
}

#endif