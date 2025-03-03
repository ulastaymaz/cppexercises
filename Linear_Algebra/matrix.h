#ifndef MATRIX_H
#define MATRIX_H
#define EPS 0.0000001
#include <iostream>
#include <vector>
#include <optional>
#include <memory>
#include <string>
#include <math.h>
#include <algorithm>
#include <stdexcept>
#include <fstream>
class Matrix{
    public:

        int row, col; // Row and Col number, should be positive
        std::vector<float> m; // Float vector for elements of matrix
        void change_rows(int row1, int row2); // Change two rows of matrix
        void change_cols(int col1, int col2); // Change two columns of matrix
        void print_matrix() const; // It is not important anymore, I implemented operator<< below 
        float trace() const; // Calculate trace
        float determinant() const ; // Calculate determinant, should be improved
        void mult_by_const(float c); // Multiply matrix with a constant float c
        Matrix operator+(const Matrix  &A) const; // Summation of two matrices elementwise
        Matrix operator-(const Matrix  &A) const; // Substraction of twp matrices elementwise
        Matrix operator*(const Matrix  &A) const; // Matrix multiplication of two matrices
        bool operator==(const Matrix  &A) const; // If |a_ij - b_ij| < EPS = 1e-6, for all i,j, two matrices equal
        bool operator!=(const Matrix  &A) const; // If |a_ij - b_ij| >= EPS = 1e-6, for some i,j, two matrices not equal
        friend std::ostream& operator<<(std::ostream& os, const Matrix &A); // Can be used directly for printing the matrix
        std::vector<float> get_column(int j) const; // Get i^th column of matrix
        Matrix(int row, int col); // Creates a zero matrix with given number of row and column
        Matrix(std::ifstream &readingfromfile); // Reads file for creating a matrix. Should be improved
        Matrix(); // User can use this for adding elements of matrix one-by-one 
        };
    #endif // MATRIX_H, EPS