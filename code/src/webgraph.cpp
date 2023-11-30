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

std::vector<double> WebGraph::getPageRank()
{
    return rankedList;
}

unsigned WebGraph::getNumberofNodes()
{
    return numberOfNodes;
}

std::string WebGraph::processInput(std::string& input, int& row)
{
    return std::string();
}

/* Graph Conversion */
void WebGraph::convertToAdjacency(std::string& text)
{

}

// Assumes current matrix is an adjacency matrix
void WebGraph::convertToMarkov()
{
    std::vector<std::vector<double>> markov = matrix;

    for (unsigned i = 0; i < markov.size(); i++)
    {
        for (unsigned j = 0; j < markov[0].size(); j++)
        {
            // No outgoing links case
            if (columnSum(matrix, j) == 0)
            {
                markov[i][j] = 1 / numberOfNodes;
                continue;
            }

            markov[i][j] = matrix[i][j] / columnSum(matrix, j);
        }
    }

    matrix = markov;
}

// Assumes current matrix is a markov matrix with all entries > 0
void WebGraph::computePageRank()
{
    // Convert into final "PageRank" matrix
    std::vector<std::vector<double>> ones (numberOfNodes, std::vector<double>(numberOfNodes, 1));
    std::vector<std::vector<double>> M = matrix;
    scalarMult(M, damp_fact);
    scalarMult(ones, (1-damp_fact)/numberOfNodes);
    matrix = matrixAddition(M, ones);

    // Obtain stationary vector through power iteration
    std::vector<double> initialGuess (numberOfNodes, 0);
    initialGuess[0] = 1;

    powerIteration(matrix, initialGuess);
}

// Assumes vect is a normalized guess (i.e. all elements sum to 1)
void WebGraph::powerIteration(std::vector<std::vector<double>>& A, std::vector<double>& vect)
{
    std::vector<double> nextIteration = colMatrixMult(matrix, vect);
    while (!vectorEqual(nextIteration, vect))
    {
        vect = nextIteration;
        nextIteration = colMatrixMult(matrix, nextIteration);
    }

    rankedList = nextIteration;
}

bool WebGraph::vectorEqual(std::vector<double>& a, std::vector<double>& b)
{
    if (a.size() != b.size())
        return false;

    for (unsigned i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
            return false;
    }

    return true;
}

/* Linear Algebra */
std::vector<double> colMatrixMult(std::vector<std::vector<double>>& A, std::vector<double>& B)
{
    int n = A.size();
    std::vector<double> result(n, 0.0);

    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            result[i] += A[i][j] * B[j];
        }
    }

    return result;
}

void scalarMult(std::vector<std::vector<double>>& A, double scalar)
{
    int rows = A.size();
    int cols = A[0].size();

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            A[i][j] *= scalar;
        }
    }
}

double columnSum(std::vector<std::vector<double>>& A, unsigned col)
{
    double sum = 0.0;

    for (const auto& row : A) 
    {
        if (col < row.size()) 
        {
            sum += row[col];
        } 
        else 
        {
            return 0.0; // invalid
        }
    }

    return sum;
}

std::vector<std::vector<double>> matrixAddition(std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& B)
{
    if (A.size() != B.size() || A[0].size() != B[0].size())
    {
        return std::vector<std::vector<double>>(); // invalid
    }

    int rows = A.size();
    int cols = A[0].size();

    std::vector<std::vector<double>> ret (A.size(), std::vector<double>(A[0].size(), 0));
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            ret[i][j] = A[i][j] + B[i][j];
        }
    }

    return ret;
}
