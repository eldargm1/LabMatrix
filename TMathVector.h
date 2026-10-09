#pragma once
#include "TVector.h"
#include <cmath>

template <typename T>
class TMathVector : public TVector<T> {
public:
    TMathVector(size_t size = 0) : TVector<T>(size) {}
    TMathVector(const TVector<T>& v) : TVector<T>(v) {}

    TMathVector operator+(const TMathVector& v) const {
        if (this->sz != v.sz) throw std::invalid_argument("Vector sizes must match");
        TMathVector res(this->sz);
        for (size_t i = 0; i < this->sz; ++i) {
            res[i] = (*this)[i] + v[i];
        }
        return res;
    }

    TMathVector operator-(const TMathVector& v) const {
        if (this->sz != v.sz) throw std::invalid_argument("Vector sizes must match");
        TMathVector res(this->sz);
        for (size_t i = 0; i < this->sz; ++i) {
            res[i] = (*this)[i] - v[i];
        }
        return res;
    }

    TMathVector operator*(const T& val) const {
        TMathVector res(this->sz);
        for (size_t i = 0; i < this->sz; ++i) {
            res[i] = (*this)[i] * val;
        }
        return res;
    }

    T operator*(const TMathVector& v) const {
        if (this->sz != v.sz) throw std::invalid_argument("Vector sizes must match");
        T res = T();
        for (size_t i = 0; i < this->sz; ++i) {
            res += (*this)[i] * v[i];
        }
        return res;
    }
};
