package cayci_hw8;

/**
 * An interface to specify Graph ADT.
 */

public interface DynamicGraph extends Graph{
    /**
     * Generates a new vertex by given parameters.
     * @param label Name of the Vertex.
     * @param weight Weight of the Vertex.
     * @return Returns the vertex.
     */
    Vertex newVertex (String label, double weight);

    /**
     * Filter the vertices by the given user-defined property and returns a subgraph of the graph.
     * @param key Key value of a pair.
     * @param filter Filter value of a pair.
     * @return Returns the subgraph which consists of vertices which contains given key value pairs.
     */
    MyGraph filterVertices(String key, String filter);

    /**
     * Generate the adjacency matrix representation of the graph and returns the matrix.
     * @return Returns the matrix representation of the graph.
     */
    double[][] exportMatrix();

    /**
     * Add the given vertex to the graph.
     * @param vertex Gets the vertex which will be added.
     */
    void addVertex(Vertex vertex);

    /**
     * Add an edge between the given two vertices in the graph.
     * @param source ID of the source vertex.
     * @param destination ID of the destination vertex.
     * @param weight Weight of the edge.
     */
    void addEdge(int source, int destination, double weight);

    /**
     * Remove the edge between the given two vertices.
     * @param source ID of the Source vertex.
     * @param destination ID of the destination vertex.
     */
    void removeEdge(int source, int destination);

    /**
     * Remove the vertex from the graph with respect to the given vertex id.
     * @param vertexID ID of the vertex which will be removed.
     */
    void removeVertex(int vertexID);

    /**
     * Remove the vertex from the graph with respect to the given vertex label.
     * @param label Label of the vertex which will be removed.
     */
    void removeVertex(String label);

    /**
     * Print the graph in adjacency list format.
     */
    void printGraph();
}