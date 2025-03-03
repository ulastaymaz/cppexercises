#include <iostream>
#include <vector>
#include <optional>
#include <memory>
#include <string>
#include <math.h>
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include "matrix.cpp"
#include "utility_functions.cpp"
using namespace std;

#define RL_BUFSIZE 1024

void LU_decomp(Matrix A, Matrix &L, Matrix &U){
    ///Not finished
    //if (A.row != A.col) {
    //    throw invalid_argument("Matrix must be square for LU decomposition.");
    //}
    for(int i = 0; i < A.col-1; i++){
        //Choose maximum element of i^th column
        //int max_index = i * A.col + i;
        int max_index = i;
        float max_temp = abs(A.m[max_index]);

        for(int t = i; t < A.row; t++){
            if (abs(A.m[t * A.col + i]) > max_temp){
                max_index = t;
                max_temp = abs(A.m[t * A.col + i]);
            }
        }

        if(max_temp == 0){
            break;
        }
        A.change_rows(max_index + 1, i + 1);

        for (int t = i + 1; t < A.row; t++){
            A.m[t * A.col + i] /= A.m[i * A.col + i];
        }

        for (int t = i + 1; t < A.row; t++){
            for (int j = i + 1; j < A.col; j++){
                A.m[t * A.col + j] -= A.m[t * A.col + i] * A.m[i * A.col + j];
            }
        }
    }

    //Upper matrix
    for(int i = 0; i < A.row; i++){
        //for(int j = i; j < A.col; j++ ){
        for(int j = i; j < A.col; j++ ){
            U.m[i * U.col + j] = A.m[i * U.col + j];
        }
    }
    //Lower matrix
    /*
    for(int i = 0; i < A.row; i++){
        for(int j = 0; j <= i; j++ ){
            if(i == j)
            {
                L.m[i * L.col + i] = 1;
                continue;
            }
            L.m[i * L.col + j] = A.m[i * L.col + j];
        }
    }
    */
    for(int i = 0; i < A.row; i++){
        for(int j = 0; j <= i; j++ ){
            if(i == j)
            {
                L.m[i * L.col + i] = 1;
                continue;
            }
            L.m[i * L.col + j] = A.m[i * L.col + j];
        }
    }
    //return A;
}

void QR_decomp(Matrix A, Matrix &Q, Matrix &R)
{
    // Tested for some matrices, should test for extreme cases
    /////////////////////////////////////
    // Initialize u vectors
    vector<vector<float>> u(A.row, vector<float>(A.col, 0.0f));

    // Initialize Q and R matrices
    // When I don't do that, it breaks, don't know why tho.
    Q = Matrix(A.row, A.col);
    R = Matrix(A.col, A.col);

    // Enter u_1 = a_1
    for (int i = 0; i < A.row; i++)
    {
        u[i][0] = A.m[i * A.col];
    }

    for (int i = 0; i < A.col; i++)
    {
        // Get a_i
        vector<float> column_i_of_A = A.get_column(i);
        // I will use temp vector for calculation
        vector<float> temp = column_i_of_A;

        for (int j = 0; j < i; j++)
        {
            // To separate j^th column, construct u_j vector
            vector<float> u_j(A.row);
            for (int k = 0; k < A.row; k++)
            {
                u_j[k] = u[k][j];
            }
            // to_subs vector is created to use in transform function
            vector<float> to_subs = projection_vector(u_j, column_i_of_A);
            transform(temp.begin(), temp.end(), to_subs.begin(), temp.begin(), minus<float>());
        }

        // Enter new column of u, u_i
        for (int k = 0; k < A.row; k++)
        {
            u[k][i] = temp[k];
        }
        // Calculate Q
        float norm_i = sqrt(inner_product_vector(temp, temp));
        for (int k = 0; k < A.row; k++)
        {
            Q.m[k * Q.col + i] = u[k][i] / norm_i;
        }
    }

    // Calculate R
    for (int i = 0; i < A.col; i++)
    {
        for (int j = i; j < A.col; j++)
        {
            R.m[i * R.col + j] = inner_product_vector(Q.get_column(i), A.get_column(j));
        }
    }
}


int main(int argc, char **argv){

    string name = "matrix_a.txt";
    ifstream readfromfileA(name);
    if (!readfromfileA) {
        cerr << "Error opening file" << endl;
        return EXIT_FAILURE;
    }
    Matrix A(readfromfileA);
    
    readfromfileA.close();
    ifstream readfromfileB("matrix_b.txt");
    if (!readfromfileB) {
        cerr << "Error opening file" << endl;
        return EXIT_FAILURE;
    }
    //readfromfileB.open();
    Matrix B(readfromfileB);
    A.print_matrix();
    Matrix Q(A.row, A.row);
    Matrix R(A.row, A.col);
    QR_decomp(A, Q, R);
    Matrix deneme = A-Q*R;


    
}
