#include <vector>
#include <string>

class WebGraph
{
    public:
        WebGraph(std::string input, int searchIndex);

        std::vector<double> getPageRank();

        // Linear Algebra functions
        std::vector<double> colMatrixMult(std::vector<std::vector<double>>& A, std::vector<double>& B);
        std::vector<std::vector<double>> scalarMult(std::vector<std::vector<double>>& A, double scalar);
        double columnSum(std::vector<std::vector<double>>& A, unsigned col);
        
        // Graph Conversion algorithms
        void convertToAdjacency(std::string& text);
        void convertToMarkov();
        void computePageRank();

    private:
        std::string processInput(std::string& input, int& row);

        std::vector<std::vector<double>> matrix;
        std::vector<double> rankedList;
    
        double damp_fact = .85;
};