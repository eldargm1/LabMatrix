#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
class TVector {
protected:
    size_t sz;
    size_t cap;
    T* pMem;

public:
    TVector(size_t size = 0) : sz(size), cap(size) {
        if (sz > 0) {
            pMem = new T[cap]();
        }
        else {
            pMem = nullptr;
        }
    }

    TVector(const TVector& v) : sz(v.sz), cap(v.cap) {
        if (sz > 0) {
            pMem = new T[cap];
            for (size_t i = 0; i < sz; ++i) {
                pMem[i] = v.pMem[i];
            }
        }
        else {
            pMem = nullptr;
        }
    }

    virtual ~TVector() {
        delete[] pMem;
    }

    size_t size() const { return sz; }
    size_t capacity() const { return cap; }

    T& operator[](size_t pos) {
        if (pos >= sz) throw std::out_of_range("Index out of range");
        return pMem[pos];
    }

    const T& operator[](size_t pos) const {
        if (pos >= sz) throw std::out_of_range("Index out of range");
        return pMem[pos];
    }

    TVector& operator=(const TVector& v) {
        if (this == &v) return *this;
        delete[] pMem;
        sz = v.sz;
        cap = v.cap;
        if (sz > 0) {
            pMem = new T[cap];
            for (size_t i = 0; i < sz; ++i) {
                pMem[i] = v.pMem[i];
            }
        }
        else {
            pMem = nullptr;
        }
        return *this;
    }

    template <typename Type>
    class Iterator {
    private:
        Type* ptr;
    public:
        Iterator(Type* p = nullptr) : ptr(p) {}
        Iterator(const Iterator& it) : ptr(it.ptr) {}

        Iterator& operator=(Type* p) {
            ptr = p;
            return *this;
        }

        Iterator& operator=(const Iterator& it) {
            ptr = it.ptr;
            return *this;
        }

        bool operator==(const Iterator& it) const { return ptr == it.ptr; }
        bool operator!=(const Iterator& it) const { return ptr != it.ptr; }

        Iterator& operator++() {
            ptr++;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp(*this);
            ptr++;
            return tmp;
        }

        Iterator& operator--() {
            ptr--;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp(*this);
            ptr--;
            return tmp;
        }

        Iterator operator+(ptrdiff_t n) const { return Iterator(ptr + n); }
        Iterator operator-(ptrdiff_t n) const { return Iterator(ptr - n); }

        ptrdiff_t operator-(const Iterator& it) const { return ptr - it.ptr; }

        Iterator& operator+=(ptrdiff_t n) {
            ptr += n;
            return *this;
        }

        Iterator& operator-=(ptrdiff_t n) {
            ptr -= n;
            return *this;
        }

        Type& operator*() const { return *ptr; }
        Type* operator->() const { return ptr; }
    };

    typedef Iterator<T> iterator;
    typedef Iterator<const T> const_iterator;

    iterator begin() { return iterator(pMem); }
    iterator end() { return iterator(pMem + sz); }

    const_iterator begin() const { return const_iterator(pMem); }
    const_iterator end() const { return const_iterator(pMem + sz); }

    const_iterator cbegin() const { return const_iterator(pMem); }
    const_iterator cend() const { return const_iterator(pMem + sz); }
};