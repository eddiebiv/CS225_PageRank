#include <vector>
#include <string>

class WebGraph
{
    public:
        WebGraph(std::string input, int searchIndex);

        void processInput(std::string& infile, int& searchIndex);
        void convertToMarkov();
        void computePageRank();
        std::vector<double> getPageRank(); 

    private:
        std::string processInput(std::string& input, int& row);
        void convertToAdjacency(std::string& text);

        std::vector<std::vector<double>> matrixMult(std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& B);
        void scalarMult(std::vector<std::vector<double>>& A, double scalar);
        double columnSum(std::vector<std::vector<double>>& A, unsigned col);


        std::vector<std::vector<double>> matrix;
        std::vector<double> rankedList;
    
        double damp_fact = .85;
};