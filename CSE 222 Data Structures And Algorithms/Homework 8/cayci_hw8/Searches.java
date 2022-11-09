package cayci_hw8;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;

/**
 * A class to use search algorithms on a graph.
 */
public class Searches {
    /**
     * Finds the root vertex of the graph. The first vertex which has edge.
     * @param myGraph Gets a graph object.
     * @return Returns the index of the first vertex which has edge.
     */
    private static int findRootVertex(MyGraph myGraph){
        if(myGraph == null)
            return -1;
        int start = -1;
        for(int index = 0; index < myGraph.getVerticesNumber() && start == -1; index++){ /* Starts from beginning and find first non-empty vertex. */
            if(myGraph.getVertex(index) != null && myGraph.getVertex(index).getEdges().size() != 0){
                start = index;
            }
        }
        return start;
    }

    /**
     * Applies Breadth First Search algorithm on a graph.
     * @param myGraph Gets a graph object.
     * @param visited An array to know which vertex is already visited.
     * @param start Index of the vertex where the algorithm starts.
     * @return Returns the total distance of the Breadth First Search algorithm.
     */
    private static double breadthFirstSearch(MyGraph myGraph, boolean[] visited, int start){
        Queue<Integer> queue = new LinkedList<Integer>(); /* Creates a queue. */
        double totalDistance = 0;
        queue.offer(start); /* Adds first vertex ID to the queue. */
        visited[start] = true; /* Sets the vertex as visited. */
        while(!queue.isEmpty()){ /* Continues until queue is empty. */
            start = queue.poll(); /* Gets first item of the queue. */
            Iterator<Edge> iterator = myGraph.edgeIterator(start);
            while(iterator.hasNext()){ /* Visits its edges which are not visited. */
                Edge edge = iterator.next();
                if(!visited[edge.getDestination()]){
                    totalDistance = totalDistance + edge.getWeight(); /* Adds the distance of the edge to the total distance. */
                    queue.offer(edge.getDestination()); /* Adds the destination of the edge to the queue. */
                    visited[edge.getDestination()] = true; /* Sets the vertex whose ID is equals to destination as true. */
                }
            }
        }
        return totalDistance;
    }

    /**
     * Applies Depth First Search algorithm on a graph.
     * @param myGraph Gets a graph object.
     * @param visited An array to know which vertex is already visited.
     * @param start Index of the vertex where the algorithm starts.
     * @return Returns the total distance of the Depth First Search algorithm.
     */
    private static double depthFirstSearch(MyGraph myGraph, boolean[] visited, int start){
        int number_of_unvisited = 0;
        double distance = Double.POSITIVE_INFINITY;
        int next = 0;
        visited[start] = true; /* Sets the start vertex as visited. */
        Iterator<Edge> iterator = myGraph.edgeIterator(start);
        while (iterator.hasNext()) {
            Edge edge = iterator.next();
            if (!visited[edge.getDestination()]) { /* Finds the vertex which is closest to the current vertex. */
                if (edge.getWeight() < distance) {
                    distance = edge.getWeight();
                    next = edge.getDestination();
                }
                number_of_unvisited = number_of_unvisited + 1; /* Increases the number of unvisited vertex by one. */
            }
        }
        if(number_of_unvisited != 0){ /* If the number of unvisited vertex is not equal to 0, recursively call the function. */
            return distance + depthFirstSearch(myGraph, visited, next)  + depthFirstSearch(myGraph, visited, start);
        }
        return 0;
    }

    /**
     * Applies Dijkstra First Search algorithm on a graph. Prints the shortest distance of the all vertices to the start vertices.
     * @param myGraph Gets a graph object.
     * @param start Index of the vertex where the algorithm starts.
     */
    public static void dijkstraSearch(MyGraph myGraph, int start){
        if(myGraph.getVerticesNumber() <= start || start < 0 || myGraph.getVertex(start) == null)
            return;

        boolean[] visited = new boolean[myGraph.getVerticesNumber()]; /* Creates a boolean array to check a vertex is visited. */

        double[] distances = new double[myGraph.getVerticesNumber()]; /* Creates a double array to keep distances of the vertex to the start vertex. */

        for(int i = 0; i < myGraph.getVerticesNumber(); i++){ /* Sets all vertex as unvisited, and sets all distances as infinity. */
            visited[i] = false;
            distances[i] = Double.POSITIVE_INFINITY;
        }

        distances[start] = 0; /* Distance of the start vertex to the start vertex is 0. */

        for(int step = 0; step < myGraph.getVerticesNumber(); step++) {
            double min = Double.POSITIVE_INFINITY;
            int shortest_path = -1;
            for(int index = 0; index < distances.length; index++){ /* Searches the distances array to find the unvisited vertex which has minimum distance. */
                if(!visited[index] && distances[index] < min){
                    min = distances[index];
                    shortest_path = index;
                }
            }
            if(shortest_path != -1) {
                visited[shortest_path] = true; /* Sets the vertex as visited. */
                Iterator<Edge> iterator = myGraph.edgeIterator(shortest_path);
                while (iterator.hasNext()) { /* Checks every neighbour of the vertex and updates their distances. */
                    Edge edge = iterator.next();
                    if (shortest_path == start){
                        if (!visited[edge.getDestination()] && distances[shortest_path] + edge.getWeight() < distances[edge.getDestination()]) {
                            distances[edge.getDestination()] = distances[shortest_path] + edge.getWeight();
                        }
                    }
                    else{
                        if (!visited[edge.getDestination()] && distances[shortest_path] + edge.getWeight() - myGraph.getVertex(shortest_path).getBoosting() < distances[edge.getDestination()]) {
                            distances[edge.getDestination()] = distances[shortest_path] + edge.getWeight() - myGraph.getVertex(shortest_path).getBoosting();
                        }
                    }
                }
            }
        }
        for(int j = 0; j < myGraph.getVerticesNumber(); j++){
            System.out.println("The distance between " + start + " with " + j + " is: " + distances[j]);
        }
    }

    /**
     * Finds distance difference between Breadth First Search and Depth First Search.
     * @param myGraph Takes a graph object.
     */
    public static void distanceDifference(MyGraph myGraph){
        int start = findRootVertex(myGraph); /* Finds first vertex which has edges. */
        boolean[] visited0 = new boolean[myGraph.getVerticesNumber()]; /* Creates a boolean array to check a vertex is visited. */
        boolean[] visited1 = new boolean[myGraph.getVerticesNumber()]; /* Creates a boolean array to check a vertex is visited. */
        for(int i = 0; i < myGraph.getVerticesNumber(); i++){ /* Sets the vertex as unvisited. */
            visited0[i] = false;
            visited1[i] = false;
        }
        double bfs = (start == -1) ? 0 :  breadthFirstSearch(myGraph, visited0, start); /* Starts Breadth First Search. */
        double dfs = (start == -1) ? 0 :  depthFirstSearch(myGraph, visited1, start); /* Starts Depth First Search. */
        System.out.println("The difference between BFS and DFS is: " + bfs + " - " + dfs + " = " + (bfs - dfs));
    }
}
