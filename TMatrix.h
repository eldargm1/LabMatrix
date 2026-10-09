#pragma once
#include "TVector.h"

template <typename T>
class TMatrix : public TVector<TVector<T>> {
public:
    TMatrix(size_t size = 0) : TVector<TVector<T>>(size) {
        for (size_t i = 0; i < size; ++i) {
            this->pMem[i] = TVector<T>(size);
        }
    }

    TMatrix(const TVector<TVector<T>>& m) : TVector<TVector<T>>(m) {}

    TMatrix operator+(const TMatrix& m) const {
        if (this->sz != m.sz) throw std::invalid_argument("Matrix sizes must match");
        TMatrix res(this->sz);
        for (size_t i = 0; i < this->sz; ++i) {
            for (size_t j = 0; j < this->sz; ++j) {
                res[i][j] = (*this)[i][j] + m[i][j];
            }
        }
        return res;
    }

    TMatrix operator-(const TMatrix& m) const {
        if (this->sz != m.sz) throw std::invalid_argument("Matrix sizes must match");
        TMatrix res(this->sz);
        for (size_t i = 0; i < this->sz; ++i) {
            for (size_t j = 0; j < this->sz; ++j) {
                res[i][j] = (*this)[i][j] - m[i][j];
            }
        }
        return res;
    }

    TMatrix operator*(const TMatrix& m) const {
        if (this->sz != m.sz) throw std::invalid_argument("Matrix sizes must match");
        TMatrix res(this->sz);
        for (size_t i = 0; i < this->sz; ++i) {
            for (size_t j = 0; j < this->sz; ++j) {
                res[i][j] = T();
                for (size_t k = 0; k < this->sz; ++k) {
                    res[i][j] += (*this)[i][k] * m[k][j];
                }
            }
        }
        return res;
    }
};
