#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H
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


// Utility functions
// Helps a lot in some calculations, sometimes I need to just some vector rather than Matrix object

vector<float> mult_by_const_vec(vector<float> v, float c); // Multiply vector v with a constant
float inner_product(Matrix const &A, Matrix const &B); // Euclidian inner product of two matrices (both are tuples)
float inner_product_vector(vector<float> const &v, vector<float> const &u); // Euclidian inner product of two vectors
Matrix projection(Matrix u, Matrix a); // Orthogonal projection of a to onto u
vector<float> projection_vector(vector<float> &u, vector<float> &a); // Orthogonal projection of a to onto u
vector<float> get_column_vec(vector<vector<float>> v, int i); // Get i^th column of vector-matrix of v
#endif