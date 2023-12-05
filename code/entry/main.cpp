#include "../src/webgraph.h"
#include <chrono>

std::string file = "../../data/10vertices.csv";
int row = 2;

/**
 * Writes the elements of a vector to a text file, separated by new lines.
 * Will create a new text file if one doesn't already exist.
 *
 * @param v A vector
 * @param f Filename directory.
 */
void writeToFile(std::vector<double>& v, std::string f) 
{
    std::ofstream outputFile(f, std::ios::trunc);

    for (double& elem : v) 
    {
        outputFile << elem << "\n";
    }
    outputFile.close();
}


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

    writeToFile(ranked, "../../results/" + std::to_string(graph.getNumberofNodes()) + "_row"
                       + std::to_string(row) + "_vertices_res.txt");

    return 0;
}