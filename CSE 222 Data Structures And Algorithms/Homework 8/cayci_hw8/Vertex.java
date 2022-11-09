package cayci_hw8;

import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Random;

/**
 * A Vertex class to keep edges and data of vertices.
 */
public class Vertex{
    /**
     * Unique ID of the vertex.
     */
    private int ID;

    /**
     * Boosting value of the vertex.
     */
    private double boosting;

    /**
     * Weight of the vertex.
     */
    private double weight;

    /**
     * Label of the vertex.
     */
    private String label;

    /**
     * Keeps key-value pairs.
     */
    private HashMap<String, String> pairs;

    /**
     * Keeps the edges whose source is the same with ID.
     */
    private LinkedList<Edge> edges;

    /**
     * Two parameters constructor for Vertex class.
     * @param label Label of the vertex.
     * @param weight Weight of the vertex.
     */
    public Vertex(String label, double weight){
        this.label = label;
        this.weight = weight;
        this.pairs = new HashMap<String, String>();
        this.edges = new LinkedList<Edge>();
        Random random = new Random();
        this.boosting = random.nextDouble(0, 1);
    }

    /**
     * Gets the ID of the vertex.
     * @return Returns the ID of the vertex.
     */
    public int getID() {
        return ID;
    }

    /**
     * Gets the label of the vertex.
     * @return Returns the label of the vertex.
     */
    public String getLabel() {
        return label;
    }

    /**
     * Gets the edges which are connected to the vertex.
     * @return Returns the edges which are connected to the vertex.
     */
    public LinkedList<Edge> getEdges() {
        return edges;
    }

    /**
     * Gets the key-value pairs .
     * @return Returns the key-value pairs.
     */
    public HashMap<String, String> getPairs() {
        return pairs;
    }

    /**
     * Gets the boosting value of the vertex.
     * @return Returns the boosting value of the vertex.
     */
    public double getBoosting() {
        return boosting;
    }

    /**
     * Sets the pairs which the vertex keeps.
     * @param pairs Gets the pairs.
     */
    public void setPairs(HashMap<String, String> pairs) {
        this.pairs = pairs;
    }

    /**
     * Set the ID of the vertex.
     * @param ID ID of the vertex.
     */
    public void setID(int ID) {
        this.ID = ID;
    }

    /**
     * Adds an edge to the graph.
     * @param edge Gets the edge which will be added to the graph.
     */
    public void add(Edge edge){
        if(!contains(edge))
            edges.add(edge);
    }

    /**
     * Adds an edge to the graph.
     * @param edge Gets the edge which will be added to the graph.
     */
    public void remove(Edge edge){
        edges.remove(edge);
    }

    /**
     * Checks whether the vertex has the edge or not.
     * @param obj The object which will be compared.
     * @return Returns true if the vertex has the edge, otherwise false.
     */
    public boolean contains(Object obj){
        return edges.contains(obj);
    }

    /**
     * Return an iterator to the edges connected to vertex.
     * @return An edge iterator to the vertex.
     */
    public Iterator<Edge> edgeIterator(){
        return edges.listIterator();
    }

    /**
     * Creates a hash code value for the object.
     * @return Returns a hash code value for this object.
     */
    @Override
    public int hashCode(){
        return 17 * ID * label.hashCode();
    }

    /**
     * Indicates whether some other object is equal to this one.
     * @param obj The object which will be compared.
     * @return Returns true if the objects equal, otherwise false.
     */
    @Override
    public boolean equals(Object obj){
        if(obj instanceof Vertex){
            return ID == ((Vertex) obj).ID;
        }
        return false;
    }

    /**
     * Converts vertex object to String.
     * @return Returns String representation of the vertex object.
     */
    @Override
    public String toString() {
        return "Vertex{" +
                "ID=" + ID +
                ", label='" + label + '\'' +
                ", weight=" + weight +
                ", boosting=" + boosting +
                '}';
    }
}
