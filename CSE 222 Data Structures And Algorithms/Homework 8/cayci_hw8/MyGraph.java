package cayci_hw8;

import java.util.HashMap;
import java.util.Iterator;

/**
 * A Graph uses array to represent vertex.
 */
public class MyGraph implements DynamicGraph{

    /**
     * The number of vertices.
     */
    private int size = 0;

    /**
     * The number of deleted vertices.
     */
    private int deleted = 0;

    /**
     * The capacity of the vertex array.
     */
    private int capacity = 1;

    /**
     * Vertex array to keep vertices.
     */
    private Vertex vertices[];

    /**
     * True if this is a directed graph.
     */
    private boolean isDirected;

    /**
     * One parameter constructor.
     * @param isDirected The directed flag.
     */
    public MyGraph(boolean isDirected){
        this.isDirected = isDirected;
        vertices = new Vertex[capacity];
    }

    /**
     * Generates a new vertex by given parameters.
     * @param label Name of the Vertex.
     * @param weight Weight of the Vertex.
     * @return Returns the vertex.
     */
    @Override
    public Vertex newVertex(String label, double weight) {
        return new Vertex(label, weight);
    }

    /**
     * Filter the vertices by the given user-defined property and returns a subgraph of the graph.
     * @param key Key value of a pair.
     * @param filter Filter value of a pair.
     * @return Returns the subgraph which consists of vertices which contains given key value pairs.
     */
    @Override
    public MyGraph filterVertices(String key, String filter) {
        MyGraph subgraph = new MyGraph(isDirected);

        for(int i = 0; i < size; i++){
            subgraph.addVertex(vertices[i]); /* Adds all vertex to the subgraph. */
        }

        for(int i = 0; i < size; i++) {
            if (vertices[i] != null){
                HashMap<String, String> pairs = vertices[i].getPairs();
                String value = pairs.get(key);
                if (value == null || value.compareTo(filter) != 0){
                    subgraph.removeVertex(i); /* If the vertex does not contain the key-filter pair, removes it from graph. */
                }
            }
        }
        return subgraph;
    }

    /**
     * Generate the adjacency matrix representation of the graph and returns the matrix.
     * @return Returns the matrix representation of the graph.
     */
    @Override
    public double[][] exportMatrix() {
        double[][] matrix = new double[size][size]; /* Creates a 2D double array. */
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                matrix[i][j] = Double.POSITIVE_INFINITY; /* Fills it with infinity. */
            }
            if(vertices[i] != null) {
                Iterator<Edge> iterator = vertices[i].edgeIterator();
                while (iterator.hasNext()) {
                    Edge edge = iterator.next();
                    matrix[i][edge.getDestination()] = edge.getWeight(); /* Assign weight of the edge to source-destination position on array. */
                }
            }
        }
        return matrix;
    }

    /**
     * Adds the given vertex to the graph.
     * @param vertex Gets the vertex which will be added.
     */
    @Override
    public void addVertex(Vertex vertex) {
        if(size >= capacity) /* If the size is equal to or bigger than the capacity, reallocates the vertex array. */
            reallocate();
        if(vertex != null) vertex.setID(size); /* Sets its ID. */
        for(int index = 0; index < size; index++){ /* Checks the graph, if the same vertex is already on the graph, it will not be added. */
            if(vertices[index] != null  && vertices[index].equals(vertex))
                return;
        }
        vertices[size] = vertex; /* Adds the vertex to its position. */
        size = size + 1; /* Increases the size by one. */
    }

    /**
     * Adds the pairs to the given vertex.
     * @param pairs Pairs of String.
     * @param source ID of the vertex.
     */
    public void addPairs(HashMap<String, String> pairs, int source){
        if(source < 0 || size <= source || vertices[source] == null)
            return;
        vertices[source].setPairs(pairs); /* Adds pairs to the source vertex. */
    }

    /**
     * Remove the vertex from the graph with respect to the given vertex id.
     * @param vertexID ID of the vertex which will be removed.
     */
    @Override
    public void removeVertex(int vertexID) {
        vertexRemoval(vertexID);
    }

    /**
     * Remove the vertex from the graph with respect to the given vertex label.
     * @param label Label of the vertex which will be removed.
     */
    @Override
    public void removeVertex(String label){
        for(int i = 0; i < size; i++){ /* Searches a vertex with its label, remove it if it is found. */
            if(vertices[i] != null && vertices[i].getLabel().compareTo(label) == 0) {
                vertexRemoval(i);
                return;
            }
        }
    }

    /**
     * Add an edge between the given two vertices in the graph.
     * @param source ID of the source vertex.
     * @param destination ID of the destination vertex.
     * @param weight Weight of the edge.
     */
    @Override
    public void addEdge(int source, int destination, double weight) {
        if(0 <= source && source < size && 0 <= destination && destination < size && vertices[source] != null && vertices[destination] != null){
            vertices[source].add(new Edge(source, destination, weight)); /* Adds the edge to the source vertex. */
            if(!isDirected){
                vertices[destination].add(new Edge(destination, source, weight)); /* Adds the edge to the destination vertex if the graph is not directed. */
            }
        }
    }

    /**
     * Remove the edge between the given two vertices.
     * @param source ID of the Source vertex.
     * @param destination ID of the destination vertex.
     */
    @Override
    public void removeEdge(int source, int destination){
        if(0 <= source && source < size && 0 <= destination  && destination < size && vertices[source] != null && vertices[destination] != null){
            vertices[source].remove(new Edge(source, destination)); /* Removes the edge from the source vertex. */
            if(!isDirected){
                vertices[destination].remove(new Edge(destination, source)); /* Removes the edge from the destination vertex if the graph is not directed. */
            }
        }
    }

    /**
     * Print the graph in adjacency list format.
     */
    @Override
    public void printGraph() {
        System.out.println("****************************************************");
        for(int i = 0; i < size; i++){
            if(vertices[i] != null){ /* If the vertex is not null, prints the vertex and its edges. */
                System.out.print(vertices[i] + ": ");
                Iterator<Edge> iterator = vertices[i].edgeIterator();
                while (iterator.hasNext()) {
                    System.out.print(iterator.next());
                    System.out.print("--->");
                }
                System.out.println();
            }
        }
        System.out.println("****************************************************");
    }

    /**
     * Finds the number of vertices on Graph.
     * @return Returns the number of vertices on Graph.
     */
    @Override
    public int getVerticesNumber() {
        return size;
    }

    /**
     * Gets the number of deleted vertex.
     * @return Returns the number of deleted vertex.
     */
    public int getDeleted(){
        return deleted;
    }

    /**
     * Check whether graph is directed or not.
     * @return Returns true if the Graph is directed, otherwise false.
     */
    @Override
    public boolean isDirected() {
        return isDirected;
    }

    /**
     * Inserts an edge to the Graph.
     * @param edge Gets an edge which will be inserted on the Graph.
     */
    @Override
    public void insert(Edge edge) {
        addEdge(edge.getSource(), edge.getDestination(), edge.getWeight()); /* Calls addEdge method to add an element to the graph. */
    }

    /**
     * Checks whether an edge exists or not.
     * @param source ID of the source vertex.
     * @param destination ID of destination vertex.
     * @return Returns true if the edge exists, otherwise false.
     */
    @Override
    public boolean isEdge(int source, int destination) {
        if(source < 0 || size <= source || vertices[source] == null) /* Returns false if there is no vertex which has the source ID. */
            return false;
        return vertices[source].contains(new Edge(source, destination)); /* Returns true if the vertex has the edge, otherwise false. */
    }

    /**
     * Gets the edge between two vertices.
     * @param source ID of the source vertex.
     * @param destination ID of the destination vertex.
     * @return Returns the edge between two vertices.
     */
    @Override
    public Edge getEdge(int source, int destination) {
        if(source < 0 || size <= source || vertices[source] == null) /* Returns null if there is no vertex which has the source ID. */
            return null;
        Iterator<Edge> iterator = vertices[source].edgeIterator();
        while(iterator.hasNext()){
            Edge edge = iterator.next();
            if(edge.equals(new Edge(source, destination))) /* Checks every edge on the source vertex. */
                return edge; /* If there is a vertex whose source is equal to source, and destination is equal to destination, returns it. */
        }
        return null; /* If the edge is not found, returns null. */
    }

    /**
     * Gets the vertex which has given ID.
     * @param source ID of the vertex.
     * @return Returns the vertex has the given ID if it is found, otherwise null.
     */
    public Vertex getVertex(int source){
        if(source < 0 || size <= source || vertices[source] == null) /* Returns null if there is no vertex which has the source ID. */
            return null;
        return vertices[source]; /* Returns the vertex. */
    }

    /**
     * Return an iterator to the edges connected to a given vertex.
     * @param source ID of the source vertex.
     * @return An edge iterator to the vertices connected to source.
     */
    @Override
    public Iterator<Edge> edgeIterator(int source) {
        if(source < 0 || size <= source || vertices[source] == null) /* Returns null if there is no vertex which has the source ID. */
            return null;
        return vertices[source].edgeIterator(); /* Returns the edge iterator. */
    }

    /**
     * Reallocates vertex array dynamically.
     */
    private void reallocate(){
        Vertex[] temp = new Vertex[2 * size]; /* Creates a temp vertex array which has double capacity. */
        for(int i = 0; i < size; i++) { /* Fills first size element of the temp array with vertices. */
            temp[i] = vertices[i];
        }
        capacity = capacity * 2; /* Doubles the capacity. */
        vertices = temp; /* Assigns the temp to the vertex array. */
    }

    /**
     * Remove a vertex from the graph.
     * @param source ID of the vertex.
     */
    private void vertexRemoval(int source){
        if(0 <= source && source < size && vertices[source] != null) { /* If there is a vertex on the graph which has the source ID, continue. */
            if(!isDirected) { /* If the graph is not directed, continue. */
                Iterator<Edge> iterator = vertices[source].edgeIterator();
                while (iterator.hasNext()) {
                    Edge edge = iterator.next();
                    vertices[edge.getDestination()].remove(new Edge(edge.getDestination(), source)); /* Removes every edge of the vertex from destination vertex. */
                }
            }
            else{ /* If the graph is directed, continue. */
                for(int i = 0; i < size; i++){ /* Checks all vertex. */
                    if(vertices[i] != null) {
                        Iterator<Edge> iterator = vertices[i].edgeIterator();
                        while (iterator.hasNext()) {
                            Edge edge = iterator.next();
                            if(edge.getDestination() == source) /* If the vertex has an edge whose destination is equal to source ID, removes it. */
                                vertices[i].remove(new Edge(i, source));
                        }
                    }
                }
            }
            vertices[source] = null; /* Deletes the vertex. */
            deleted = deleted + 1; /* Increases the number of deleted vertex by one. */
        }
    }
}
