#include "webgraph.h"

#include <vector>
#include <string>
#include <iostream>


/* Constructing */
WebGraph::WebGraph(std::string input, int searchIndex)
{

}

std::vector<std::vector<double>> WebGraph::getMat()
{
    return matrix;
}

std::vector<double> WebGraph::getRankedList()
{
    return rankedList;
}

std::string WebGraph::processInput(std::string& input, int& row)
{

    return std::string();
}

std::vector<double> WebGraph::getPageRank()
{
    return std::vector<double>();
}

/* Graph Conversion */
void WebGraph::convertToAdjacency(std::string& text)
{

}

void WebGraph::convertToMarkov()
{

}

void WebGraph::computePageRank()
{

}

/* Linear Algerbra */
std::vector<double> colMatrixMult(std::vector<std::vector<double>>& A, std::vector<double>& B)
{
    int n = A.size();
    std::vector<double> result(n, 0.0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i] += A[i][j] * B[j];
        }
    }

    return result;
}

void scalarMult(std::vector<std::vector<double>>& A, double scalar)
{
    int rows = A.size();
    int cols = A[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            A[i][j] *= scalar;
        }
    }
}

double columnSum(std::vector<std::vector<double>>& A, unsigned col)
{
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