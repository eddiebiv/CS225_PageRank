#include <vector>
#include <string>

// Linear Algebra functions
std::vector<double> colMatrixMult(std::vector<std::vector<double>>& A, std::vector<double>& B);
void scalarMult(std::vector<std::vector<double>>& A, double scalar);
double columnSum(std::vector<std::vector<double>>& A, unsigned col);
std::vector<std::vector<double>> matrixAddition(std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& B);

class WebGraph
{
    public:
        WebGraph(std::string input, int searchIndex);
        
        // Graph Conversion algorithms
        void convertToAdjacency(std::string& text);
        void convertToMarkov();
        void computePageRank();

        // Getters
        std::vector<std::vector<double>> getMat();
        std::vector<double> getPageRank();
        unsigned getNumberofNodes();

    private:
        void powerIteration(std::vector<std::vector<double>>& A, std::vector<double>& vect);
        bool vectorEqual(std::vector<double>& a, std::vector<double>& b);
        // Helper function to process .CSV files
        std::string processInput(std::string& input, int& row);

        std::vector<std::vector<double>> matrix;
        std::vector<double> rankedList;

        unsigned numberOfNodes;
        double damp_fact = .85;
};