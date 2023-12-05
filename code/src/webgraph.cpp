#include "webgraph.h"

/* Constructing */
WebGraph::WebGraph(std::string input, int searchIndex)
{
    std::string nodeList = processInput(input, searchIndex);
    convertToAdjacency(nodeList);
}

std::vector<std::vector<double>> WebGraph::getMat()
{
    return matrix;
}

std::vector<double> WebGraph::getPageRank()
{
    return rankedList;
}

unsigned WebGraph::getNumberofNodes()
{
    return numberOfNodes;
}

std::string WebGraph::trimWhitespace(const std::string& str) 
{
    // find first non whitespace char (w/ lambda function)
    auto firstNonSpace = std::find_if(str.begin(), str.end(), [](int ch) {
        return !std::isspace(ch);
    });

    // finds last non whitespace char
    auto lastNonSpace = std::find_if(str.rbegin(), str.rend(), [](int ch) {
        return !std::isspace(ch);
    });

    return std::string(firstNonSpace, lastNonSpace.base());
}

std::string WebGraph::processInput(std::string& input, int& row)
{
    std::ifstream inputFile(input);
    std::string graphText;      // text of the row where each cell is seperated by a comma

    if(inputFile.is_open()){
        std::string line;
        int currentRow = 0;

        while(std::getline(inputFile, line)){
            if(currentRow == row)
            {
                // store the line in graphText
                graphText = line;
                break;
            }
            currentRow++;
        }

        inputFile.close();
    } 
    else{
        std::cerr << "Unable to open file." << std::endl;
        return std::string();
    }
    
    // remove all trailing, ending whitespace and remove csv index
    graphText = trimWhitespace(graphText);

    return graphText.substr(2);
}

/* Graph Conversion */

// (ex. text=0,0,2)
// the example signifies that nodes 1 and 2 are not pointing to any nodes whereas node 3 is pointing to node 2

// (ex. text=3,3 1,1 2)
// node 1 ---> nodes 3
// node 2 ---> nodes 3, 1
// node 3 ---> nodes 1, 2

// Store this as a directed adjacency matrix,
// initializing numberOfNodes, matrix
void WebGraph::convertToAdjacency(std::string& text)
{
    std::istringstream commaDelimited(text);
    std::string currBatch;

    // Get total number of nodes
    int numberOfBatches = 0;
    while (std::getline(commaDelimited, currBatch, ','))
    {
        numberOfBatches++;
    }

    numberOfNodes = numberOfBatches;

    // Reset stringstream for another iteration
    commaDelimited.clear();
    commaDelimited.seekg(0, std::ios::beg);

    // Initialize matrix
    matrix = std::vector<std::vector<double>>(numberOfNodes, std::vector<double>(numberOfNodes, 0.0));
    unsigned i = 0;
    while (std::getline(commaDelimited, currBatch, ','))
    {
        std::istringstream batchStream(currBatch);
        unsigned directedNode;
        // Goes through each space seperated number
        while (batchStream >> directedNode) 
        {
            if (directedNode == 0)
            {
                continue;
            }

            directedNode--; // 1 indexed to 0 indexed
            matrix[directedNode][i] = 1.0;
        }
        i++;
    }
}

// Assumes current matrix is an adjacency matrix
void WebGraph::convertToMarkov()
{
    std::vector<std::vector<double>> markov = matrix;

    for (unsigned i = 0; i < markov.size(); i++)
    {
        for (unsigned j = 0; j < markov[0].size(); j++)
        {
            // No outgoing links case
            if (columnSum(matrix, j) == 0)
            {
                markov[i][j] = 1.0 / numberOfNodes;
                continue;
            }

            markov[i][j] = static_cast<double>(matrix[i][j]) / columnSum(matrix, j);
        }
    }

    matrix = markov;
}

// Assumes current matrix is a markov matrix with all entries > 0
void WebGraph::computePageRank()
{
    // Convert into final "PageRank" matrix
    std::vector<std::vector<double>> ones (numberOfNodes, std::vector<double>(numberOfNodes, 1.0));
    std::vector<std::vector<double>> M = matrix;
    scalarMult(M, damp_fact);
    scalarMult(ones, (1.0-damp_fact)/static_cast<double>(numberOfNodes));
    matrix = matrixAddition(M, ones);

    // Obtain stationary vector through power iteration
    std::vector<double> initialGuess (numberOfNodes, 0);
    initialGuess[0] = 1.0;

    powerIteration(matrix, initialGuess);
}

// Assumes vect is a normalized guess (i.e. all elements sum to 1)
void WebGraph::powerIteration(std::vector<std::vector<double>>& A, std::vector<double>& vect)
{
    std::vector<double> nextIteration = colMatrixMult(matrix, vect);
    while (!vectorEqual(nextIteration, vect))
    {
        vect = nextIteration;
        nextIteration = colMatrixMult(matrix, nextIteration);
    }

    rankedList = nextIteration;
}

bool WebGraph::vectorEqual(std::vector<double>& a, std::vector<double>& b)
{
    if (a.size() != b.size())
        return false;

    for (unsigned i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
            return false;
    }

    return true;
}

/* Linear Algebra */
std::vector<double> colMatrixMult(std::vector<std::vector<double>>& A, std::vector<double>& B)
{
    int n = A.size();
    std::vector<double> result(n, 0.0);

    for (int j = 0; j < n; ++j) 
    {
        for (int i = 0; i < n; ++i) 
        {
            result[i] += A[i][j] * B[j];
        }
    }

    return result;
}

void scalarMult(std::vector<std::vector<double>>& A, double scalar)
{
    int rows = A.size();
    int cols = A[0].size();

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            A[i][j] *= scalar;
        }
    }
}

double columnSum(std::vector<std::vector<double>>& A, unsigned col)
{
    double sum = 0.0;

    for (const auto& row : A) 
    {
        if (col < row.size()) 
        {
            sum += row[col];
        } 
        else 
        {
            return 0.0; // invalid
        }
    }

    return sum;
}

std::vector<std::vector<double>> matrixAddition(std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& B)
{
    if (A.size() != B.size() || A[0].size() != B[0].size())
    {
        return std::vector<std::vector<double>>(); // invalid
    }

    int rows = A.size();
    int cols = A[0].size();

    std::vector<std::vector<double>> ret (A.size(), std::vector<double>(A[0].size(), 0.));
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            ret[i][j] = A[i][j] + B[i][j];
        }
    }

    return ret;
}