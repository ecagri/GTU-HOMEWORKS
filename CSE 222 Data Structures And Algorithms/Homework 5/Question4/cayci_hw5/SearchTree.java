package cayci_hw5;

/**
 * An interface for BinarySearchTree.
 * @author cagri cayci
 * @param <E> To make interface generics.
 */
public interface SearchTree<E> {
    /**
     * Inserts item where it belongs in the tree. Returns true if item is inserted, false if it is not inserted.
     * @param item Gets the item as type E.
     * @return Returns true if item is inserted, otherwise false.
    */
    public boolean add(E item);
    
    /**
     * Search the target in the tree, returns true if the target is found, false if it is not found.
     * @param target Gets the target value as type E.
     * @return Returns true if the target is found, otherwise false.
    */
    public boolean contains(E target);
    
    /**
     * Removes target value if it is found from tree and returns it, otherwise returns null. 
     * @param target Gets the target value as type E.
     * @return Returns the target value if it is found, otherwise null.
    */
    public boolean remove(E target);
    
    /**
     * Returns a reference to the data on the tree node that is equal to target. If there is no such a node, returns null.
     * @param target Gets the target value as type E.
     * @return Returns a reference of a node which is equal to target, otherwise null.
    */
    public E find(E target);
    
    /**
     * Removes target value if it is found from tree and returns true, otherwise returns false. 
     * @param target Gets the target value as type E.
     * @return Returns true if target value is found, otherwise false.
    */
    public E delete(E target);
}
