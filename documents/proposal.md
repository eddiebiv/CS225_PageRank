## Academic Reference

Our proposed algorithm is the notorious PageRank intially used by Google.
The following link goes quite in depth of possible implementations for PageRank (https://mathweb.ucsd.edu/~fan/wp/pagerank.pdf).

For our intended purposes, we will be implementing the generic algorithm as detailed in the following Wikipedia Page (https://en.wikipedia.org/wiki/PageRank) and as explained below.

## Algorithm Summary

Given a set of web pages and the respective links associated with each page, this algorithm returns a vector ranking of the websites concerning their popularity/importance. Here, importance is roughly defined as the number of links to a page, however, not all links are weighed the same (those with fewer outgoing links and a higher ranking will be more significant). We based our algorithm on the random-surfer model where the surfer starts on any initial website and arbitrarily visits websites. While this process is ongoing there is a damping factor (.85) which determines the chance of our surfer "being reset" (i.e. a 15% chance if .85 is our damping factor) where we place the surfer on some random page. Also, as discovered by Larry Page and Sergey Brin, if a page has no outgoing links, our surfer will have an equal probability of visiting any page which is modeled by 1 / N where N is the total number of pages. Eventually, after many iterations, the vector of visited pages will converge towards a stationary probability vector (whose eigenvalue is 1) from which we can easily rank the web pages.

## Function I/O

