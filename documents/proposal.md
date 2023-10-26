## Academic Reference

Our proposed algorithm is the notorious PageRank intially used by Google.
The following link goes quite in depth of possible implementations for PageRank (https://mathweb.ucsd.edu/~fan/wp/pagerank.pdf).

For our intended purposes, we will be implementing the generic algorithm as detailed in the following Wikipedia Page (https://en.wikipedia.org/wiki/PageRank) and as explained below.

## Algorithm Summary

Given a set of web pages and the respective links associated with each page, this algorithm returns a vector ranking of the websites concerning their popularity/importance. Here, importance is roughly defined as the number of links to a page, however, not all links are weighed the same (those with fewer outgoing links and a higher ranking will be more significant). We based our algorithm on the random-surfer model where the surfer starts on any initial website and arbitrarily visits websites. While this process is ongoing there is a damping factor (.85) which determines the chance of our surfer "being reset" (i.e. a 15% chance if .85 is our damping factor) where we place the surfer on some random page. Also, as discovered by Larry Page and Sergey Brin, if a page has no outgoing links, our surfer will have an equal probability of visiting any page which is modeled by 1 / N where N is the total number of pages. Eventually, after many iterations, the vector of visited pages will converge towards a stationary probability vector (whose eigenvalue is 1) from which we can easily rank the web pages.

## Function I/O 

To first create a web graph, we pass our CSV input to our constructor.

`WebGraph::WebGraph(std::string infile, int searchIndex)`
```
@param infile: the working directory to the raw csv file
@param searchIndex: specific graph (row in .csv) we want to create
```

This constructor will take in the csv file and specific row index in the csv file enabling us to select a specific type of web graph. The actual constructing of the graph will be done using the helper functions: 
`processInput()` and `convertToAdjacency()` which are described below. The end result will be an adjacency matrix for a graph stored as a private member in `matrix` of type `std::vector<std::vector<double>>`.

`std::string processInput(std::string& input, int& row)`
```
@param input: a directory of an existing csv file
@param row: specified row corresponding to one in the .csv file

@return the corresponding text of the row where each cell is seperated by a comma
```

This helper function takes in the row index and a .csv file and returns the nodes as well as their outgoing links seperated by commas. By doing so, it effectively processes the csv file.


`void convertToAdjacency(std::string& text)`
```
@param text: comma seperated nodes
```

Using the processed text information, this function creates an n x n directed graph represented through an adjacency matrix stored in `matrix`.

`void convertToMarkov()`

For the current `matrix` (should be an adjacency matrix when called) convert it into a markov matrix where each column is normalized. If a column (i.e. webpage) has no outgoing links then set each entry in that column to be 1 / N where N is the number of web pages. Otherwise, normalize it to ensure it maintains the properties of a Markov Matrix.

`void computePageRank()`

For the current `matrix` (should be a markov matrix when called) convert it into the final PageRank matrix taking into account for damping according to the following formula:
$\textbf{P} =  d\textbf{M} + (1 - d) \frac{1}{N} \textbf{1}$
where $\textbf{M}$ is the markov matrix, $d$ is the damping factor, $N$ is the total number of web pages, and $\textbf{1}$ is an n x n matrix filled with 1s.

Then obtain the steady-state eigenvector (with eigenvalue 1) through power iteration

`void powerIteration(std::vector<std::vector<double>>& A, std::vector<double>& vect)`
```
@param A: reference to a markov matrix with entires all > 0 (necessary for unique convergence)
@param vect: reference to an existing normalized vector
```
This function iterates through this limit $\lim\limits_{n\to\infty} A^k v$ and then stores the end resultant converged vector back into `vect`. 

`std::vector<double> getPageRank();`
```
@return The ranked vectors (in terms of their probabilities)
```
Getter function which fetches and returns the private variable `rankedList` of type `std::vector<double>` storing the ranks of each respective page after their respective rank is calculated. The values stored in `rankedList` are what gets compared to the expected PageRank vector in the test cases. The expected values in the test cases are calculated manually and allow us to confirm the accuracy of the program's calculations.

`std::vector<std::vector<double>> colMatrixMul(std::vector<std::vector<double>>& A, std::vector<double>& B);`
```
@param A: n x n matrix 
@param B: column vector with R^n

@return resultant matrix product
```
Performs matrix multiplication (via linear combination method) where A is an n by n matrix and B is a simple column vector. The result is as follows: $AB = \vec{a}_1b_1 + \vec{a}_2b_2 + ... + \vec{a}_nb_n$.

`void scalarMult(std::vector<std::vector<double>>& A, double scalar);`
```
@param A: any matrix
@param scalar: real number
```
Performs simple scalar multiplication on a matrix and saves it in the original matrix.

`double columnSum(std::vector<std::vector<double>>& A, unsigned col);`
```
@param A: any matrix
@param col: a valid column index within A 

@return sum of all entries within specified column
```
Sums all the given entries in a column and returns the result.

## Data Description

The dataset used for our test cases was manually constructed in Excel to ensure correctness and to provide a logical increase in complexity as more tests get ran. Each row of the .csv file represents a web of pages with varying connections between sites. We chose to implement the data by row to allow easy distinction between different cases.


