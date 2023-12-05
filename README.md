## Project Summary

Our final project implements the PageRank algorithm based on the random surfer model to rank the importance (popularity) of a node in a graph.

## Code

All code files can be found in the `code/` directory. To run the code:

1. Create a `build` directory inside `code/`

2. cd into `build` and run `cmake ..` and `make`.

3. Specify a `file` and `row` in `main.cpp` (in entry folder) to select whichever graph you desire the rankings of.

4. Run using `./main`

To run the test suite:

1. Inside the build folder run either `make` or `make test`

2. Run using `./test`

## Input Data Format and Output

This program expects the data to be formatted as a `.csv` file in a specific manner. Refer to the `#vertices.csv` files in the data folder for an example. 

Looking at `file = "3vertices.csv"` with `row = 1`:

`1,0,0,2`

The first number denotes the number index (namely 1 here) and the rest of the numbers make up the graph. So node nodes 1 and 2 are not pointing to any nodes whereas node 3 is pointing to node 2.

The highest ranking node will be printed on the CLI and in addition, the ranks will be outputted as text files corresponding to the specific file and row. 

## General Organization

The test data (as well the generation script) are all stored in the `data` folder which has sizes ranging from 3 nodes all the way up to 1000 nodes. The bulk of the code written is stored within the `src` folder of the `code` directory. Both the written report and presentation video can be found in the the `documents` directory. Finally, the `results` folder contains the ranked vectors for different files tested within `main.cpp`

## Development Progress

All the development logs can be found in the `log.md` file within `documents`.