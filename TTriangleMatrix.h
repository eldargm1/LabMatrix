#pragma once
#include "TVector.h"

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
