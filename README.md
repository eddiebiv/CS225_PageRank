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

## General Organization

The test data (as well the generation script) are all stored in the `data` folder which has sizes ranging from 3 nodes all the way up to 1000 nodes. The bulk of the code written is stored within the `src` folder of the `code` directory. Both the written report and presentation video can be found in the the `documents` directory. 

## Development Progress

All the development logs can be found in the `log.md` file within `documents`.