#include <catch2/catch_test_macros.hpp>
#include "../src/webgraph.h"
#include <fstream>
#include <sstream>
#include <iostream>

/* Manual Computation of test cases: */
// https://docs.google.com/document/d/10OpI4VX9kW-kSl4yzQL3XEQ7kBIC0RvtQsqNfrW9dFI/edit?usp=sharing

// Helper to compare matrices up to a certain precision
bool compareMatrices(const std::vector<std::vector<double>>& A,
                     const std::vector<std::vector<double>>& B,
                     unsigned decimalPlaces) 
{
        // std::cerr << "Matrix A:" << std::endl;
        // for (const auto& row : A) 
        // {
        //     for (double value : row) 
        //     {
        //         std::cerr << value << " ";
        //     }
        //     std::cerr << std::endl;
        // }

        // std::cerr << "Matrix B:" << std::endl;
        // for (const auto& row : B) 
        // {
        //     for (double value : row) 
        //     {
        //         std::cerr << value << " ";
        //     }
        //     std::cerr << std::endl;
        // }

    if (A.size() != B.size()) 
    {
        return false;
    }

    for (unsigned i = 0; i < A.size(); i++) 
    {
        if (A[i].size() != B[i].size()) 
        {
            return false;
        }

        for (unsigned j = 0; j < A[i].size(); j++) 
        {
            double roundedA = std::round(A[i][j] * std::pow(10, decimalPlaces));
            double roundedB = std::round(B[i][j] * std::pow(10, decimalPlaces));

            if (roundedA != roundedB) 
            {
                return false;
            }
        }
    }

    return true;
}

// Helper to compare vectors up to a certain precision
bool compareVectors(const std::vector<double>& A,
                    const std::vector<double>& B,
                    unsigned decimalPlaces)
{
        // std::cerr << "Vector A: ";
        // for (const auto& elem : A) {
        //     std::cerr << elem << " ";
        // }
        // std::cerr << std::endl;

        // std::cerr << "Vector B: ";
        // for (const auto& elem : B) {
        //     std::cerr << elem << " ";
        // }
        // std::cerr << std::endl;

    if (A.size() != B.size())
    {
        return false;
    }

    for (unsigned i = 0; i < A.size(); i++)
    {
        double roundedA = std::round(A[i] * std::pow(10, decimalPlaces));
        double roundedB = std::round(B[i] * std::pow(10, decimalPlaces));

        if (roundedA != roundedB) 
        {
            return false;
        }
    }

    return true;
}

TEST_CASE("Matrix Multiplication (lin. comb.)", "[weight=5]")
{
    std::vector<std::vector<double>> initial_A = {{1, 1},
                                                     {0, 1}};
    std::vector<double> initial_B = {2, 
                                        0};                                           

    std::vector<double> expected_mat = {2,
                                        0};
    std::vector<double> out = colMatrixMult(initial_A, initial_B);
    REQUIRE(expected_mat == out);
}

TEST_CASE("Scalar Multiplication", "[weight=5]")
{
    std::vector<std::vector<double>> initial_mat = {{1, 1, 1},
                                                    {1, 1, 0}};
    std::vector<std::vector<double>> expected_mat = {{5, 5, 5},
                                                     {5, 5, 0}};
    scalarMult(initial_mat, 5);
    REQUIRE(expected_mat == initial_mat);
}

TEST_CASE("Column Sum", "[weight=5]")
{
    std::vector<std::vector<double>> initial_mat = {{1, 0, 1},
                                                    {1, 1, 8}};
    double expected = 2;
    double out = columnSum(initial_mat, 0);
    REQUIRE(expected == out);
}


TEST_CASE("convertToAdjacency (row 1) 3vertices", "[weight=5]")
{
    std::vector<std::vector<double>> expected_mat = {{0, 0, 0},
                                                    {0, 0, 1.0},
                                                    {0, 0, 0}};

    std::string infile = "../../data/3vertices.csv";
    int search = 1;

    WebGraph graph(infile, search);
    std::vector<std::vector<double>> out = graph.getMat();

    REQUIRE(expected_mat == out);
}

TEST_CASE("convertToAdjacency (row 2) 10vertices", "[weight=5]")
{
    std::vector<std::vector<double>> expected_mat = {{0, 0, 0, 0, 0, 1., 1., 0, 0, 1.},
                                                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                     {0, 0, 0, 0, 0, 1., 1., 1., 1., 0},
                                                     {0, 0, 0, 0, 0, 1., 1., 1., 0, 0},
                                                     {0, 0, 0, 0, 0, 1., 0, 1., 1., 0},
                                                     {1., 0, 0, 0, 0, 0, 0, 1., 0, 0},
                                                     {1., 0, 1., 0, 0, 0, 0, 0, 0, 1.},
                                                     {1., 0, 1., 0, 0, 1., 1., 0, 0, 0},
                                                     {0, 0, 1., 0, 0, 0, 0, 0, 0, 1.},
                                                     {0, 0, 0, 0, 0, 1., 1., 0, 0, 0}};

    std::string infile = "../../data/10vertices.csv";
    int search = 2;
	
    WebGraph graph(infile, search);

    REQUIRE(expected_mat == graph.getMat());
}

// Assumes convertToAdjacency() is implemented correctly
TEST_CASE("convertToMarkov (row 1) 3vertices", "[weight=5]")
{
    std::vector<std::vector<double>> expected_mat = {{1.0/3, 1.0/3, 0},
                                                     {1.0/3, 1.0/3, 1},
                                                     {1.0/3, 1.0/3, 0}};

    std::string infile = "../../data/3vertices.csv";
    int search = 1;
	
    WebGraph graph(infile, search);

    graph.convertToMarkov();

    REQUIRE(expected_mat == graph.getMat());
}

TEST_CASE("convertToMarkov (row 2) 10vertices", "[weight=5]")
{
    std::vector<std::vector<double>> expected_mat = {{0,    1./10, 0,    1./10, 1./10, 1./6, 1./5, 0,    0,     1./3},
                                                     {0,    1./10, 0,    1./10, 1./10, 0,    0,    0,    0,     0},
                                                     {0,    1./10, 0,    1./10, 1./10, 1./6, 1./5, 1./4, 1./2,  0},
                                                     {0,    1./10, 0,    1./10, 1./10, 1./6, 1./5, 1./4, 0,     0},
                                                     {0,    1./10, 0,    1./10, 1./10, 1./6, 0,    1./4, 1./2,  0},
                                                     {1./3, 1./10, 0,    1./10, 1./10, 0,    0,    1./4, 0,     0},
                                                     {1./3, 1./10, 1./3, 1./10, 1./10, 0,    0,    0,    0,     1./3},
                                                     {1./3, 1./10, 1./3, 1./10, 1./10, 1./6, 1./5, 0,    0,     0},
                                                     {0,    1./10, 1./3, 1./10, 1./10, 0,    0,    0,    0,     1./3},
                                                     {0,    1./10, 0,    1./10, 1./10, 1./6, 1./5, 0,    0,     0}};

    std::string infile = "../../data/10vertices.csv";
    int search = 2;
	
    WebGraph graph(infile, search);

    graph.convertToMarkov();

    REQUIRE(expected_mat == graph.getMat());
}

// Assumes convertToMarkov() is implemented correctly
// Final end result
TEST_CASE("computePageRank (row 1) 3vertices", "[weight=5]")
{
    std::vector<std::vector<double>> expected_mat = {{1.0/3, 1.0/3, 0.05},
                                                     {1.0/3, 1.0/3, 0.9},
                                                     {1.0/3, 1.0/3, 0.05}};

    std::vector<double> expected_rank = {0.25974026, 0.48051948, 0.25974026};

    std::string infile = "../../data/3vertices.csv";
    int search = 1;
	
    WebGraph graph(infile, search);
    graph.convertToMarkov();

    graph.computePageRank();

    REQUIRE(compareMatrices(expected_mat, graph.getMat(), 10)); // up to 10 decimal places
    REQUIRE(compareVectors(expected_rank, graph.getPageRank(), 8)); // up to 8 decimal places
}

TEST_CASE("computePageRank (row 2) 10vertices", "[weight=5]")
{
    std::vector<std::vector<double>> expected_mat = {
        {0.015, 0.1, 0.015, 0.1, 0.1, 0.15666667, 0.185, 0.015, 0.015, 0.29833333},
        {0.015, 0.1, 0.015, 0.1, 0.1, 0.015, 0.015, 0.015, 0.015, 0.015},
        {0.015, 0.1, 0.015, 0.1, 0.1, 0.15666667, 0.185, 0.2275, 0.44, 0.015},
        {0.015, 0.1, 0.015, 0.1, 0.1, 0.15666667, 0.185, 0.2275, 0.015, 0.015},
        {0.015, 0.1, 0.015, 0.1, 0.1, 0.15666667, 0.015, 0.2275, 0.44, 0.015},
        {0.29833333, 0.1, 0.015, 0.1, 0.1, 0.015, 0.015, 0.2275, 0.015, 0.015},
        {0.29833333, 0.1, 0.29833333, 0.1, 0.1, 0.015, 0.015, 0.015, 0.015, 0.29833333},
        {0.29833333, 0.1, 0.29833333, 0.1, 0.1, 0.15666667, 0.185, 0.015, 0.015, 0.015},
        {0.015, 0.1, 0.29833333, 0.1, 0.1, 0.015, 0.015, 0.015, 0.015, 0.29833333},
        {0.015, 0.1, 0.015, 0.1, 0.1, 0.15666667, 0.185, 0.015, 0.015, 0.015}
    };

    std::vector<double> expected_rank = {0.09018786, 0.03667581, 0.13997215, 0.09906751, 0.11926625,
                                         0.0910203, 0.12179942, 0.13548826, 0.09624619, 0.07027626};

    std::string infile = "../../data/10vertices.csv";
    int search = 2;
	
    WebGraph graph(infile, search);
    graph.convertToMarkov();

    graph.computePageRank();

    REQUIRE(compareMatrices(expected_mat, graph.getMat(), 7)); // up to 7 decimal places
    REQUIRE(compareVectors(expected_rank, graph.getPageRank(), 6)); // up to 6 decimal places
}

// TEST_CASE("processInput (row 1) 3vertices", "[weight=5]")
// {
//     std::string expected = "0,0,2";
//     // expected.erase(std::remove_if(expected.begin(), expected.end(), ::isspace), expected.end()); // remove whitespace

//     std::string infile = "../../data/3vertices.csv";
//     int search = 1;

//     WebGraph graph(infile, search);
//     std::string out = graph.processInput(infile, search);

//     REQUIRE(expected == out);
// }

// TEST_CASE("processInput (row 2) 10vertices", "[weight=5]")
// {
//     std::string expected = "7 6 8,0,7 8 9,0,0,5 3 4 1 10 8,1 10 8 4 3,4 5 3 6,3 5,7 9 1";
//     // expected.erase(std::remove_if(expected.begin(), expected.end(), ::isspace), expected.end()); // remove whitespace

//     std::string infile = "../../data/10vertices.csv";
//     int search = 2;

//     WebGraph graph(infile, search);
//     std::string out = graph.processInput(infile, search);

//         // std::cerr << "expected: " << expected.size() << std::endl;
//         // std::cerr << "output: " << out.size() << std::endl;

//     REQUIRE(expected == out);
// }
