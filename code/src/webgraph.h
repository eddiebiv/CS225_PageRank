#include <vector>
#include <string>

// Linear Algebra functions
std::vector<double> colMatrixMult(std::vector<std::vector<double>>& A, std::vector<double>& B);
void scalarMult(std::vector<std::vector<double>>& A, double scalar);
double columnSum(std::vector<std::vector<double>>& A, unsigned col);

class WebGraph
{
    public:
        WebGraph(std::string input, int searchIndex);

        std::vector<double> getPageRank();
        
        // Graph Conversion algorithms
        void convertToAdjacency(std::string& text);
        void convertToMarkov();
        void computePageRank();

        // Getters
        std::vector<std::vector<double>> getMat();
        std::vector<double> getRankedList();

    private:
        std::string processInput(std::string& input, int& row);

        std::vector<std::vector<double>> matrix;
        std::vector<double> rankedList;
    
        double damp_fact = .85;
};