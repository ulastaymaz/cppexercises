#include "utility_functions.h"
#include <iostream>
#include <vector>
#include <optional>
#include <memory>
#include <string>
#include <math.h>
#include <algorithm>
#include <stdexcept>
#include <fstream>
vector<float> mult_by_const_vec(vector<float> v, float c){
    for(auto &w: v){
        w *= c;
    }
    return v;
}
float inner_product(Matrix const &A, Matrix const &B){
    if(A.row * A.col != A.row + A.col -1 || B.row * B.col != B.row + B.col -1){
        cerr<<"For inner product, two tuples must be entered!";
        exit(EXIT_FAILURE);
    }
    float output = 0.0f;
    int dimension = A.row * A.col;
    for (int i = 0; i < dimension; i++){
        output += A.m[i] * B.m[i];
    }
    return output;
}
float inner_product_vector(vector<float> const &v, vector<float> const &u){

    if(v.size() != u.size()){
        cerr<<"For inner product, two vectors must be entered!";
        exit(EXIT_FAILURE);
    }

    float output = 0.0f;
    int dimension = v.size();
    for (int i = 0; i < dimension; i++){
        output += v[i] * u[i];
    }
    return output;
}
Matrix projection(Matrix u, Matrix a){
    //inner product of u and a
    float temp1 = inner_product(u, a);
    //inner product of u and u, hence ||u||^2
    float temp2 = inner_product(u, u);
    u.mult_by_const(temp1/temp2);
    return u;
}
vector<float> projection_vector(vector<float> &u, vector<float> &a){
    float temp1 = inner_product_vector(u, a);
    //inner product of u and u, hence ||u||^2
    float temp2 = inner_product_vector(u, u);
    return mult_by_const_vec(u, temp1/temp2);
}
vector<float> get_column_vec(vector<vector<float>> v, int i){
    if(i < 0 || i>v[0].size()){
        cerr<<"hata";
        exit(EXIT_FAILURE);
    }
    vector<float> output(v.size());
    for(int j = 0; j < v[0].size(); j++){
        output[j] = v[j][i];
    }
    return output;
}