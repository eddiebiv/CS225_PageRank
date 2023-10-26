#include <catch2/catch_test_macros.hpp>

#include "../src/webgraph.h"

#include <sstream>

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
