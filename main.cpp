#include <iostream>
#include "TVector.h"
#include "TMatrix.h"
#include "TTriangleMatrix.h"

int main() {
    TVector<int> my_vec(8);
    int val = 1;

    for (auto it = my_vec.begin(); it != my_vec.end(); ++it) {
        *it = val++;
    }

    for (auto it = my_vec.begin(); it != my_vec.end(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << std::endl;

    return 0;
}