#include "webgraph.h"

#include <vector>
#include <string>
#include <iostream>


/* Constructing */
WebGraph::WebGraph(std::string input, int searchIndex){

}

std::string processInput(std::string& input, int& row){

}

std::vector<double> getPageRank(){

}


/* Graph Conversion */
void convertToAdjacency(std::string& text){

}

void convertToMarkov(){

}

void computePageRank(){

}


/* Linear Algerbra */
std::vector<double> colMatrixMult(std::vector<std::vector<double>>& A, std::vector<double>& B){
    int n = A.size();
    std::vector<double> result(n, 0.0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i] += A[i][j] * B[j];
        }
    }

    return result;
}

std::vector<std::vector<double>> scalarMult(std::vector<std::vector<double>>& A, double scalar){
    int rows = A.size();
    int cols = A[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            A[i][j] *= scalar;
        }
    }
}

double columnSum(std::vector<std::vector<double>>& A, unsigned col){
    double sum = 0.0;

    for (const auto& row : A) {
        if (col < row.size()) {
            sum += row[col];
        } 
        else {
            return 0.0; // invalid
        }
    }

    return sum;
}