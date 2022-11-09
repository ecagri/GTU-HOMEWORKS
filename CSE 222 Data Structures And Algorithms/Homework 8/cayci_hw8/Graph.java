package cayci_hw8;

import java.util.Iterator;

/**
 * An interface to specify Graph ADT.
 */
public interface Graph{
    /**
     * Finds the number of vertices on Graph.
     * @return Returns the number of vertices on Graph.
     */
    int getVerticesNumber();

    /**
     * Check whether graph is directed or not.
     * @return Returns true if the Graph is directed, otherwise false.
     */
    boolean isDirected();

    /**
     * Inserts an edge to the Graph.
     * @param edge Gets an edge which will be inserted on the Graph.
     */
    void insert(Edge edge);

    /**
     * Checks whether an edge exists or not.
     * @param source ID of the source vertex.
     * @param destination ID of destination vertex.
     * @return Returns true if the edge exists, otherwise false.
     */
    boolean isEdge(int source, int destination);

    /**
     * Gets the edge between two vertices.
     * @param source ID of the source vertex.
     * @param destination ID of the destination vertex.
     * @return Returns the edge between two vertices.
     */
    Edge getEdge(int source, int destination);

    /**
     * Return an iterator to the edges connected to a given vertex.
     * @param source ID of the source vertex.
     * @return An edge iterator to the vertices connected to source.
     */
    Iterator<Edge> edgeIterator(int source);
}
