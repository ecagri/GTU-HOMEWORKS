package cayci_hw8;

/**
 * An Edge class to keep data of edges.
 */
public class Edge{
    /**
     * ID of the source vertex.
     */
    private int source;

    /**
     * ID of the destination vertex.
     */
    private int destination;

    /**
     * Weight of the edge. Weight of the edge is set 1 as default.
     */
    private double weight = 1.0;

    /**
     * Two parameter constructor for Edge class.
     * @param source ID of the source vertex.
     * @param destination ID of the destination vertex.
     */
    public Edge(int source, int destination){
        this.source = source;
        this.destination = destination;
    }

    /**
     * Three parameter constructor for Edge class.
     * @param source ID of the source vertex.
     * @param destination ID of the destination vertex.
     * @param weight Weight of the edge.
     */
    public Edge(int source, int destination, double weight){
        this.source = source;
        this.destination = destination;
        this.weight = weight;
    }

    /**
     * Gets the ID of the source vertex of the edge.
     * @return Returns the ID of the source vertex of the edge.
     */
    public int getSource(){ return source; }

    /**
     * Gets the ID of the destination vertex of the edge.
     * @return Returns the ID of the destination vertex of the edge.
     */
    public int getDestination() {
        return destination;
    }

    /**
     * Gets the weight of the edge.
     * @return Returns the weight of the edge.
     */
    public double getWeight(){
        return weight;
    }

    /**
     * Converts edge object to String.
     * @return Returns String representation of the edge object.
     */
    @Override
    public String toString() {
        return "Edge{" +
                "source=" + source +
                ", destination=" + destination +
                ", weight=" + weight +
                '}';
    }

    /**
     * Indicates whether some other object is equal to this one.
     * @param obj The object which will be compared.
     * @return Returns true if the objects equal, otherwise false.
     */
    @Override
    public boolean equals(Object obj) {
        if(obj instanceof Edge){
            Edge other = (Edge) obj;
            return other.destination == destination && other.source == source;
        }
        return false;
    }

    /**
     * Creates a hash code value for the object.
     * @return Returns a hash code value for this object.
     */
    @Override
    public int hashCode() {
        return 17 * source * destination;
    }
}
