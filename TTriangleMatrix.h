#pragma once
#include "TVector.h"
#include <iostream>
#include <initializer_list>
#include <stdexcept>

template <typename T>
class TTriangleMatrix : public TVector<TVector<T>> {
public:
    TTriangleMatrix(size_t size = 0) : TVector<TVector<T>>(size) {
        for (size_t i = 0; i < size; ++i) {
            this->pMem[i] = TVector<T>(size - i);
        }
    }

    TTriangleMatrix(const TTriangleMatrix& m) : TVector<TVector<T>>(m) {}

    TTriangleMatrix(std::initializer_list<std::initializer_list<T>> list) {
        this->sz = list.size();
        this->cap = this->sz;
        this->pMem = new TVector<T>[this->cap]();

        size_t i = 0;
        for (auto row : list) {
            size_t actualSize = (this->sz > i) ? (this->sz - i) : 0;
            this->pMem[i] = TVector<T>(actualSize);
            size_t j = 0;
            size_t col = 0;
            for (auto val : row) {
                if (col >= i) {
                    if (j < actualSize) {
                        this->pMem[i][j++] = val;
                    }
                }
                col++;
            }
            i++;
        }
    }

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

    class SafeElementProxy {
    private:
        TTriangleMatrix& matrix;
        size_t row;
        size_t col;
    public:
        SafeElementProxy(TTriangleMatrix& m, size_t r, size_t c) : matrix(m), row(r), col(c) {}

        operator T() const {
            if (row > col || row >= matrix.sz || col >= matrix.sz) return T();
            return matrix.pMem[row][col - row];
        }

        SafeElementProxy& operator=(const T& val) {
            if (row > col) {
                if (val != T()) throw std::out_of_range("Cannot set non-zero value below diagonal");
                return *this;
            }
            if (row >= matrix.sz || col >= matrix.sz) {
                throw std::out_of_range("Index out of range");
            }
            matrix.pMem[row][col - row] = val;
            return *this;
        }
    };

    SafeElementProxy operator()(size_t row, size_t col) {
        return SafeElementProxy(*this, row, col);
    }

    T operator()(size_t row, size_t col) const {
        if (row > col || row >= this->sz || col >= this->sz) return T();
        return this->pMem[row][col - row];
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