#pragma once
#include "TVector.h"
#include <iostream>

template <typename T>
class TTriangleMatrix : public TVector<TVector<T>> {
public:
    TTriangleMatrix(size_t size = 0) : TVector<TVector<T>>(size) {
        for (size_t i = 0; i < size; ++i) {
            this->pMem[i] = TVector<T>(size - i);
        }
    }

    TTriangleMatrix(const TTriangleMatrix& m) : TVector<TVector<T>>(m) {}

    TTriangleMatrix operator+(const TTriangleMatrix& m) const {
        if (this->sz != m.sz) throw std::invalid_argument("Matrix sizes must match");
        TTriangleMatrix res(this->sz);
        for (size_t i = 0; i < this->sz; ++i) {
            for (size_t j = 0; j < this->sz - i; ++j) {
                res[i][j] = (*this)[i][j] + m[i][j];
            }
        }
        return res;
    }

    TTriangleMatrix operator-(const TTriangleMatrix& m) const {
        if (this->sz != m.sz) throw std::invalid_argument("Matrix sizes must match");
        TTriangleMatrix res(this->sz);
        for (size_t i = 0; i < this->sz; ++i) {
            for (size_t j = 0; j < this->sz - i; ++j) {
                res[i][j] = (*this)[i][j] - m[i][j];
            }
        }
        return res;
    }

    TTriangleMatrix operator*(const T& val) const {
        TTriangleMatrix res(this->sz);
        for (size_t i = 0; i < this->sz; ++i) {
            for (size_t j = 0; j < this->sz - i; ++j) {
                res[i][j] = (*this)[i][j] * val;
            }
        }
        return res;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const TTriangleMatrix<T>& matrix) {
    size_t n = matrix.size();
    for (size_t i = 0; i < n; ++i) {
        out << "[ ";
        for (size_t j = 0; j < n; ++j) {
            if (j >= i && (j - i) < matrix[i].size()) {
                out << matrix[i][j - i] << " ";
            }
            else {
                out << T() << " ";
            }
        }
        out << "]" << std::endl;
    }
    return out;
}