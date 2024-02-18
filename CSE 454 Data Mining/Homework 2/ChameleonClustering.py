import numpy as np
import networkx as nx
import community 
import matplotlib.pyplot as plt
from sklearn.metrics.pairwise import cosine_similarity

def K_Nearest_Neighbor(dataset, k): # Creates a graph with connecting a vertex with k-nearest neighbours. 
    graph = nx.Graph()
    for i in range(len(dataset)):
        graph.add_node(i) # Adds each node. 
    for i in range(len(dataset)):

        distances = np.sqrt(np.sum((dataset - dataset[i])**2, axis=1)) # Calculates euclidian distances. 

        k_smallest_indices = np.argpartition(distances, k + 1)[0: k + 1] # Finds smallest k element indices.

        k_smallest_indices = k_smallest_indices[k_smallest_indices != i] # Excludes the vertex itself.

        for vertex in k_smallest_indices:
            graph.add_edge(i, vertex, weight= 1 / (distances[vertex] + 0.0001)) # Create an edge between the vertex and its neighbour with (1 / distance) weight.
    return graph

def similarity(x, y):
    sum_x = np.sum(dataset[x], axis=0) / len(x)
    sum_y = np.sum(dataset[y], axis=0) / len(y)

    return 100 / np.linalg.norm(sum_x - sum_y)

def AgglomerativeClustering(clusters, threshold):
    while(len(clusters) > 1):
        merge = []
        for i in range(len(clusters)):
            for j in range(len(clusters)):
                if(i != j and similarity(clusters[i], clusters[j]) > threshold):
                    merge.append(i)
                    merge.append(j)
                    break
            if(len(merge) > 0):
                break
        if(len(merge) == 0):
            break
        else:
            clusters.append(clusters[merge[0]] + clusters[merge[1]])
            clusters.remove(clusters[merge[0]])
            clusters.remove(clusters[merge[0]])
    return clusters


dataset = []

with open('worms/worms_2d.txt', "r") as file:
    for line in file:
        numbers = line.split()
        point = np.array([float(num) for num in numbers])
        dataset.append(point)

dataset = np.array(dataset)

print("KNN Graph is applying...")

graph = K_Nearest_Neighbor(dataset, 3)

print("KNN Graph is created.\nPartition is applying...")

partition = community.best_partition(graph)

clusters = {}
for key, value in partition.items():
    if value not in clusters:
        clusters[value] = [key]
    else:
        clusters[value].append(key)

clusters = list(clusters.values())

print("Partition is applied.\nAgglomerative Clustering is applying...", len(clusters))

clusters = AgglomerativeClustering(clusters, 0.7)

print("Agglomerative Clustering is applied.\nPlotting the graph...", len(clusters))


for cluster in clusters:
    plt.scatter(dataset[cluster][:,0], dataset[cluster][:, 1])

plt.savefig("result.png")
