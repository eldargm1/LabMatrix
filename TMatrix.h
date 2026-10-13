#pragma once
#include "TVector.h"
#include <iostream>

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

    TMatrix operator*(const T& val) const {
        TMatrix res(this->sz);
        for (size_t i = 0; i < this->sz; ++i) {
            for (size_t j = 0; j < this->sz; ++j) {
                res[i][j] = (*this)[i][j] * val;
            }
        }
        return res;
    }
};

template <typename T>
std::istream& operator>>(std::istream& in, TMatrix<T>& matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            in >> matrix[i][j];
        }
    }
    return in;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const TMatrix<T>& matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        out << "[ ";
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            out << matrix[i][j] << " ";
        }
        out << "]" << std::endl;
    }
    return out;
}