#include "matrix.h"
#include <iostream>
#include <vector>
#include <optional>
#include <memory>
#include <string>
#include <math.h>
#include <algorithm>
#include <stdexcept>
#include <fstream>

using namespace std;

Matrix::Matrix(int row, int col):row(row),col(col),m(row*col,0.0){
    if (row <= 0 || col <= 0) {

        cout<<"Row cannot be nonpositive! Enter row: "<<endl;
        while(!(cin>>row)||row<=0){
            cout<<"Row cannot be nonpositive!"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }

        cout<<"Enter column: ";
        while(!(cin>>row)||row<=0){
            cout<<"Row cannot be nonpositive!"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
    }
}
Matrix::Matrix(ifstream &readingfromfile)
{
    float var = 0.0f;
    int count = 0;
    int temp = 0;
    while (!readingfromfile.eof()){
        //Read row number
        if (count == 0){
            readingfromfile >> temp;
            row = temp;
            this->row = row;
            count++;
            continue;
        }
        //Read column number
        if (count == 1){
            readingfromfile >> temp;
            col = temp;
            this->col = col;
            count++;
            continue;
        }

        readingfromfile >> var;
        count++;
        m.push_back(var);
    }
    if (count - 2 != row * col){
        cout << "Number of entered entries do not match the row x col!" << endl;
        if (count - 2 < row * col){
            for (int i = count - 2; i < row * col; i++){
                m.push_back(0.0f);
            }
        }
    }
}
Matrix::Matrix()
{
    cout << "Enter row number: " << endl;
    while (!(cin >> row) || row <= 0){
        cout << "Row cannot be nonpositive!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter column number: " << endl;
    while (!(cin >> col) || col <= 0){
        cout << "Column cannot be nonpositive!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    m.resize(row * col);

    for (int i = 0; i < row * col; i++){
        float temp;
        cout << "Row: " << floor(i / row) + 1 << " Column: " << i % row + 1 << endl;
        cin >> temp;
        m[i] = temp;
    }
}
Matrix::~Matrix(){};
Matrix Matrix::operator+(const Matrix &A) const {
    if(A.row != row || A.col != col){
        cerr<<"Rows and columns numbers must be same!";
        exit(EXIT_FAILURE);
    }

    Matrix output(A.row, A.col);
    transform(A.m.begin(),A.m.end(),m.begin(),output.m.begin(),plus<float>());
    return output;
}
Matrix Matrix::operator-(const Matrix &A) const {
    if(A.row != row || A.col != col){
        cerr<<"Rows and columns numbers must be same!";
        exit(EXIT_FAILURE);
    }

    Matrix output(A.row, A.col);
    transform(m.begin(),m.end(),A.m.begin(),output.m.begin(),minus<float>());
    return output;
}
Matrix Matrix::operator* (const Matrix &A) const {
    if (col != A.row) {
        //throw invalid_argument("Column of A must be equal to row of B");
        cerr<<"Column of A must be equal to row of B";
        exit(EXIT_FAILURE);
    }
    Matrix output(row, A.col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < A.row; j++) {
            for (int k = 0; k < col; k++) {
                output.m[i * output.col + j] += m[i * col + k] * A.m[k * A.col + j];
            }
        }
    }
    return output;
}
ostream& operator<<(ostream& os, const Matrix &A){
    int count = 0;
    for(int i = 0; i < A.row * A.col; i++){
        os << A.m[i] << "   ";
        count++;
        if(count == A.col){
            cout << endl;
            count = 0;
        }
    }
    return os;
}
bool Matrix::operator==(const Matrix &A) const {
    if (col != A.row) {
        //throw invalid_argument("Column of A must be equal to row of B");
        cerr<<"Column of A must be equal to row of B";
        exit(EXIT_FAILURE);
    }
    Matrix testing(row, A.col);
    transform(m.begin(), m.end(), A.m.begin(), testing.m.begin(), minus<float>());
    for(auto &w : testing.m){
        if(abs(w) > EPS ) return false;
    }
    return true;
}
bool Matrix::operator!=(const Matrix &A) const {
    if (col != A.row) {
        //throw invalid_argument("Column of A must be equal to row of B");
        cerr<<"Column of A must be equal to row of B";
        exit(EXIT_FAILURE);
    }
    Matrix testing(row, A.col);
    transform(m.begin(), m.end(), A.m.begin(), testing.m.begin(), minus<float>());
    for(auto &w : testing.m){
        if(abs(w) > EPS ) return true;
    }
    return false;
}
vector<float> Matrix::get_column(int j) const {
    if( j <0 || j > col)
    {
        cerr<<"Invalid column!";
        exit(EXIT_FAILURE);
    }
    vector<float> output;
    for(int i = 0; i < row; i++){
        output.push_back(m[i * col + j]);
    }
    return output;
}
float Matrix::trace() const {
    float sum = 0;
    for (int i = 0; i < row; i++) {
        sum += m[i * col + i];
    }
    return sum;
}
void Matrix::change_rows(int row1, int row2){
    
    if(row1 < 1 || row2 < 1 || row1 > row || row2 > row){
        cerr<<("Invalid row inputs! ");
    }
    if(row1 != row2){

        row1--; row2--;

        for(int i = 0; i < col; i++)
        {
            swap(m[row1 * col + i], m[row2 * col +i]);

        }
    }
}
void Matrix::change_cols(int col1, int col2){
    if(col1 < 1 || col2 < 1 || col1 > col || col2 > col){
        cerr<<("Invalid col inputs! ");
    }
    if(col1 != col2){

        col1--; col2--;

        for(int i = 0; i < row; i++)
        {
            swap(m[col * i + col1], m[col * i + col2]);

        }
    }
}
void Matrix::print_matrix() const {
    int count_col = 0;
    for (int i = 0; i < row * col; i++)
    {
        cout<< m[i]<<"  ";
        count_col++;
        if(count_col == col)
        {
            cout<<endl;
            count_col = 0;
        }
    }
}
float Matrix::determinant() const {
    if(row != col){
        cerr<<("Matrix must be square to calculate determinant.");
        exit(EXIT_FAILURE);
    }
    if(row == 1)
    {
        return m[0];
    }
    if(row == 2){
        return m[0] * m[3] - m[1] * m[2];
    }
    float det = 0.0f;
    for(int i = 0; i < col; i++){
        Matrix subMatrix(row-1, col-1);
        for(int j = 1; j < row; j++){

            int subMatrixColCount = 0;
            for(int k = 0; k < row; k++){

                if(k == i){
                    continue;
                }
                subMatrix.m[(row -1)*(j-1) + subMatrixColCount] = m[j * col + k];
                subMatrixColCount++;
            }
        }
        //float temp = determinant(subMatrix);
        //cout<<"asdf: "<<pow(-1, i) * A.m[i] * temp<<endl;
        det += pow(-1, i) * m[i] * (subMatrix.determinant());
        //cout<<det<<endl;
    }

    return det;
}
void Matrix::mult_by_const(float c){
    for(auto &v: m){
        v *= c;
    }
}
Matrix transpose(Matrix const &A){
    Matrix output = Matrix(A.col, A.row);
    for(int j=0; j<output.row; j++){
        for(int i=0; i<output.col; i++){
            output.m[j * output.col + i] = A.m[i * A.col + j];
        }
    }
    return output;
}

float Matrix::sum_of_abs_elem() const{
    float count = 0.0f;
    for(auto &v : m){
        count += abs(v);
    }
    return count;
}
