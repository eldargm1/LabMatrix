#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class TVector {
protected:
    T* pMem;
    size_t sz;
    size_t cap;

public:
    TVector(size_t size = 0) : sz(size), cap(size) {
        if (sz == 0) {
            pMem = nullptr;
        }
        else {
            pMem = new T[cap]();
        }
    }

    TVector(const TVector& v) : sz(v.sz), cap(v.cap) {
        if (cap == 0) {
            pMem = nullptr;
        }
        else {
            pMem = new T[cap];
            for (size_t i = 0; i < sz; ++i) {
                pMem[i] = v.pMem[i];
            }
        }
    }

    TVector(TVector&& v) noexcept : pMem(v.pMem), sz(v.sz), cap(v.cap) {
        v.pMem = nullptr;
        v.sz = 0;
        v.cap = 0;
    }

    virtual ~TVector() {
        delete[] pMem;
    }

    TVector& operator=(const TVector& v) {
        if (this != &v) {
            if (cap < v.sz) {
                delete[] pMem;
                cap = v.sz;
                pMem = new T[cap];
            }
            sz = v.sz;
            for (size_t i = 0; i < sz; ++i) {
                pMem[i] = v.pMem[i];
            }
        }
        return *this;
    }

    TVector& operator=(TVector&& v) noexcept {
        if (this != &v) {
            delete[] pMem;
            pMem = v.pMem;
            sz = v.sz;
            cap = v.cap;
            v.pMem = nullptr;
            v.sz = 0;
            v.cap = 0;
        }
        return *this;
    }

    size_t size() const noexcept { return sz; }
    size_t capacity() const noexcept { return cap; }

    T& operator[](size_t index) { return pMem[index]; }
    const T& operator[](size_t index) const { return pMem[index]; }

    T& at(size_t index) {
        if (index >= sz) throw std::out_of_range("Index out of range");
        return pMem[index];
    }
    const T& at(size_t index) const {
        if (index >= sz) throw std::out_of_range("Index out of range");
        return pMem[index];
    }

    void shrink_to_fit() {
        if (cap > sz) {
            if (sz == 0) {
                delete[] pMem;
                pMem = nullptr;
                cap = 0;
            }
            else {
                T* newMem = new T[sz];
                for (size_t i = 0; i < sz; ++i) {
                    newMem[i] = pMem[i];
                }
                delete[] pMem;
                pMem = newMem;
                cap = sz;
            }
        }
    }

    class Iterator {
    private:
        T* ptr;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(T* p = nullptr) : ptr(p) {}

        T& operator*() const { return *ptr; }
        T* operator->() { return ptr; }

        Iterator& operator++() { ++ptr; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; ++ptr; return tmp; }

        Iterator& operator--() { --ptr; return *this; }
        Iterator operator--(int) { Iterator tmp = *this; --ptr; return tmp; }

        Iterator operator+(difference_type n) const { return Iterator(ptr + n); }
        Iterator operator-(difference_type n) const { return Iterator(ptr - n); }

        difference_type operator-(const Iterator& other) const { return ptr - other.ptr; }

        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };

    Iterator begin() noexcept { return Iterator(pMem); }
    Iterator end() noexcept { return Iterator(pMem + sz); }
};