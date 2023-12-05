#include "../src/webgraph.h"
#include <chrono>

std::string file = "../../data/250vertices.csv";
int row = 3;

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    WebGraph graph (file, row);

    graph.convertToMarkov();
    graph.computePageRank();

    std::vector<double> ranked = graph.getPageRank();
    unsigned highestRanked = std::distance(ranked.begin(), std::max_element(ranked.begin(), ranked.end()));

    std::cout << "Total Nodes: " << graph.getNumberofNodes() << std::endl;
    std::cout << "Node " << highestRanked+1 << " has the highest PageRank!"<< std::endl << std::endl;   


    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Total time: " << duration_ms << " ms."<< std::endl;

    return 0;
}