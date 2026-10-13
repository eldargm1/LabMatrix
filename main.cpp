#include <iostream>
#include "TMatrix.h"
#include "TTriangleMatrix.h"

void showMenu() {
    std::cout << "\n=== MATRIX CALCULATOR ===" << std::endl;
    std::cout << "1. Add two square matrices" << std::endl;
    std::cout << "2. Subtract two square matrices" << std::endl;
    std::cout << "3. Multiply square matrix by scalar" << std::endl;
    std::cout << "4. Triangle matrix demo" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Select action: ";
}

int main() {
    int choice = -1;

    while (choice != 0) {
        showMenu();
        std::cin >> choice;

        if (choice == 1) {
            size_t n;
            std::cout << "Enter matrix size N: ";
            std::cin >> n;

            TMatrix<double> A(n), B(n);
            std::cout << "Enter elements for matrix A (" << n << "x" << n << "):\n";
            std::cin >> A;
            std::cout << "Enter elements for matrix B (" << n << "x" << n << "):\n";
            std::cin >> B;

            std::cout << "\nResult A + B:\n" << (A + B) << std::endl;
        }
        else if (choice == 2) {
            size_t n;
            std::cout << "Enter matrix size N: ";
            std::cin >> n;

            TMatrix<double> A(n), B(n);
            std::cout << "Enter elements for matrix A:\n";
            std::cin >> A;
            std::cout << "Enter elements for matrix B:\n";
            std::cin >> B;

            std::cout << "\nResult A - B:\n" << (A - B) << std::endl;
        }
        else if (choice == 3) {
            size_t n;
            double val;
            std::cout << "Enter matrix size N: ";
            std::cin >> n;

            TMatrix<double> A(n);
            std::cout << "Enter elements for matrix A:\n";
            std::cin >> A;

            std::cout << "Enter scalar value: ";
            std::cin >> val;

            std::cout << "\nResult A * " << val << ":\n" << (A * val) << std::endl;
        }
        else if (choice == 4) {
            std::cout << "\n--- Creating triangle matrix 3x3 ---\n";
            TTriangleMatrix<int> tri(3);
            tri[0][0] = 3; tri[0][1] = 4; tri[0][2] = 5;
            tri[1][1] = 8; tri[1][2] = 2;
            tri[2][2] = 1;

            std::cout << "Matrix output:\n" << tri << std::endl;
            std::cout << "Accessing subdiagonal element tri[2][0]: " << tri[2][0] << std::endl;
        }
    }

    return 0;
}