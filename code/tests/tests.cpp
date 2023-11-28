#include <catch2/catch_test_macros.hpp>
#include "../src/webgraph.h"
#include <sstream>


TEST_CASE("Matrix Multiplication (lin. comb.)", "[weight=5]")
{
    std::vector<std::vector<double>> initial_mat1 = {{1, 1},
                                                     {0, 1}};
    std::vector<double> initial_mat2 = {2, 
                                        0};                                           

    std::vector<double> expected_mat = {2,
                                        0};
    std::vector<double> out = colMatrixMult(initial_mat1, initial_mat2);
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

TEST_CASE("Converting to markov matrix (basic, case=3)", "[weight=5]")
{

    // (will be stored in graph.matrix)
    // std::vector<std::vector<double>> initial_mat = {{0, 1, 1},
    //                                                 {1, 0, 1},
    //                                                 {1, 0, 0}};

    std::vector<std::vector<double>> expected_mat = {{0, 1, .5},
                                                    {.5, 0, .5},
                                                    {.5, 0, 0}};

    std::string infile = "../../data/webgraph_variations.csv";
    int search = 2;
	
    WebGraph graph(infile, search);
    graph.convertToMarkov();

    REQUIRE(expected_mat == graph.matrix);
}

/*
 * Reads in the dataset and searches for the data on row 1
 */
TEST_CASE("Case 1: 3 disconnected components", "[weight=5]")
{
    std::vector<double> expected;
    expected.push_back(1/3);
    expected.push_back(1/3);
    expected.push_back(1/3);

    std::string infile = "../../data/webgraph_variations.csv";
    int search = 1;
	
    WebGraph graph(infile, search);
    graph.convertToMarkov();
    graph.computePageRank();
	
    std::vector<double> out = graph.getPageRank();

    REQUIRE(expected == out);
}

/*
 * Reads in the dataset and searches for the data on row 2
 */
TEST_CASE("Case 2: 3 connected components; C is only outgoing", "[weight=5]")
{
	std::vector<double> expected;
    expected.push_back(0.464);
    expected.push_back(0.4865);
    expected.push_back(0.05);

    std::string infile = "../../data/webgraph_variations.csv";
    int search = 2;
	
    WebGraph graph(infile, search);
    graph.convertToMarkov();
    graph.computePageRank();
	
    std::vector<double> out = graph.getPageRank();

    REQUIRE(expected == out);
}

/*
 * Reads in the dataset and searches for the data on row 3
 */
TEST_CASE("Case 3: 3 connected components", "[weight=5]")
{
	std::vector<double> expected;
    expected.push_back(0.433);
    expected.push_back(1/3);
    expected.push_back(0.234);

    std::string infile = "../../data/webgraph_variations.csv";
    int search = 3;
	
    WebGraph graph(infile, search);
    graph.convertToMarkov();
    graph.computePageRank();
	
    std::vector<double> out = graph.getPageRank();

    REQUIRE(expected == out);
}

TEST_CASE("convertToAdjacency", "[weight=5]")
{
    std::vector<std::vector<double>> expected_mat = {{0, 0, 0},
                                                    {0, 0, 1},
                                                    {0, 0, 0}};

    std::string infile = "../../data/3vertices.csv";
    int search = 2;

    WebGraph graph(infile, search);
    std::vector<std::vector<double>> out = graph.matrix;

    REQUIRE(expected == out);
}

TEST_CASE("processInput", "[weight=5]")
{
    std::string expected = "1,0,0,2"

    std::string infile = "../../data/3vertices.csv";
    int row = 2;

    WebGraph graph(infile, search);
    std::string out = graph.processInput(infile, row);

    REQUIRE(expected == out);
}
