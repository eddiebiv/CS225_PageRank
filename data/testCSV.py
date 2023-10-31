import csv
import random


num_nodes = 5

num_graphs = 50

output_file = "5vertices.csv"

# Create and write the random directed graphs to the CSV file
with open(output_file, "w", newline='') as csvfile:
    csv_writer = csv.writer(csvfile)

    graph = [['0' for _ in range(num_nodes + 1)] for _ in range(num_graphs + 1)]
    for i in range(0, num_nodes + 1):
            if(i == 0):
                graph[0][i] = ''
                continue
            graph[0][i] = str(i)
            
    for i in range(0, num_graphs + 1):
            if(i == 0):
                graph[i][0] = ''
                continue
            graph[i][0] = str(i)
            
    
    for _ in range(num_graphs + 1):
        for source in range(1, num_graphs + 1):
            for target in range(1, num_nodes + 1):
                if source == target:
                    graph[source][target] = '0'  # no self-pointing edges
                else:
                    # add a random number of digits between 1 and num_nodes (excluding the target)
                    num_edges = random.randint(0, num_nodes - 1)
                    edges = random.sample(range(1, num_nodes + 1), num_edges)
                    if target in edges:
                        edges.remove(target)
                    if source in edges:
                        edges.remove(source)
                    if edges:
                        graph[source][target] = ' '.join(map(str, edges))
                    else:
                        graph[source][target] = '0'
            
    for row in graph:
        csv_writer.writerow(row)
