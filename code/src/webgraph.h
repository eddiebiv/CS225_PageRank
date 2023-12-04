#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

/**
 * Performs matrix multiplication (via linear combination method) where A is 
 * an n by n matrix and B is a simple column vector.
 * 
 * @param A n x n matrix 
 * @param B column vector with R^n
 * 
 * @return resultant matrix product as column vector in R^n 
 */
std::vector<double> colMatrixMult(std::vector<std::vector<double>>& A, std::vector<double>& B);

/**
 * Performs simple scalar multiplication on a matrix and saves it in the 
 * original matrix.
 * 
 * @param A any matrix
 * @param scalar real number
 */
void scalarMult(std::vector<std::vector<double>>& A, double scalar);

/**
 * Sums all the given entries in a column and returns the result.
 * 
 * @param A any matrix
 * @param col a valid column index (zero-based) within A 
 */
double columnSum(std::vector<std::vector<double>>& A, unsigned col);

/**
 * Performs matrix addition between two matrices A and B (of equal size) and 
 * returns the resultant matrix;
 * 
 * @param A the first matrix in A+B
 * @param B the second matrix in A+B
 *
 * @return matrix where each entry is a sum of the respective entries of A and B
 */
std::vector<std::vector<double>> matrixAddition(std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& B);

class WebGraph
{
    public:
        /**
         * Graph constructor.
         * Initiailzes the graph and creates an adjacency matrix
         * 
         * @param infile the working directory to the raw csv file
         * @param searchIndex specific graph (row in .csv) we want to create
         */
        WebGraph(std::string infile, int searchIndex);

        /**
         * Takes in the a .csv file directory + a row index and returns the 
         * the outgoing links for each node seperated by commas.
         * 
         * @param input: a directory of an existing csv file
         * @param row: specified row corresponding to one in the .csv file
         * 
         * @return the corresponding text of the row where each node is 
         * seperated by a comma
         */
        std::string processInput(std::string& input, int& row);

        /**
         * A helper for processInput()
         * 
         * @param str const reference to a string
         * 
         * @return the original string but with leading and trailing 
         * whitespace removed
         */
        std::string trimWhitespace(const std::string& str);

        /**
         * Using the processed text information, this function creates an 
         * n x n directed graph represented through an adjacency matrix stored in `matrix`.
         * 
         * @param text comma seperated nodes
         */
        void convertToAdjacency(std::string& text);

        /**
         * For the current `matrix` (should be an adjacency matrix) convert it 
         * into a markov matrix where each column is normalized. If a column 
         * (i.e. webpage) has no outgoing links then set each entry in that 
         * column to be 1 / N where N is the number of web pages. Otherwise,
         * normalize it to ensure it maintains the properties of a Markov Matrix.
         */
        void convertToMarkov();

        /**
         * For the current `matrix` (should be a markov matrix when called) 
         * convert it into the final PageRank matrix taking into account for damping.
         * 
         * Then obtain the steady-state eigenvector (with eigenvalue 1) through power
         * iteration.
         */
        void computePageRank();

        // Getters
        std::vector<std::vector<double>> getMat();
        std::vector<double> getPageRank();
        unsigned getNumberofNodes();

    private:
        /**
         * Performs power iteration on `vect` by iterating through the limit
         * (https://en.wikipedia.org/wiki/Power_iteration)
         * 
         * @param A reference to a markov matrix with entires all > 0 (necessary for unique convergence)
         * @param vect reference to an existing normalized vector
         */
        void powerIteration(std::vector<std::vector<double>>& A, std::vector<double>& vect);

        /**
         * A simple helper function used to compare two vectors.
         * 
         * @param a: a vector containing numbers
         * @param b: another vector containing numbers
         * 
         * @return whether each respective entries for a and b match
         */
        bool vectorEqual(std::vector<double>& a, std::vector<double>& b);

        std::vector<std::vector<double>> matrix;
        std::vector<double> rankedList;

        unsigned numberOfNodes;
        double damp_fact = .85;
};