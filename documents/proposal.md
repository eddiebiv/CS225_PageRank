## Academic Reference

Our proposed algorithm is the notorious PageRank intially used by Google.
The following link goes quite in depth of possible implementations for PageRank (https://mathweb.ucsd.edu/~fan/wp/pagerank.pdf).

For our intended purposes, we will be implementing the generic algorithm as detailed in the following Wikipedia Page (https://en.wikipedia.org/wiki/PageRank) and as explained below.

## Algorithm Summary

Given a set of web pages and the respective links associated with each page, this algorithm returns a vector ranking the websites with regard to their popularity/importance. Here, importance is roughly defined as the number of links to a page, however, not all links are weighed the same (those with fewer outgoing links and a higher ranking will be more significant). We based our algorithm on the random-surfer model where the surfer starts on any initial website and randomly chooses to click on websites...
