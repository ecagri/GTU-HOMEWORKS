package cayci_hw6;

import java.util.LinkedList;

/**
 * A class to implement BinarySearchTree with an array.
 * @author cagri cayci
 * @param <K> To make the class generics.
 * @param <V> To make the class generics.
 */
public class BinarySearchTree<K extends Comparable<K>, V>{
    /**
     * An object array to keep datas.
     */
    private Node<K, V>[] array;
    /**
     * An integer value to keep size of the tree.
     */
    private int size = 0; 
    
    /**
     * Keeps the elements random order.
     */
    private LinkedList<Node<K, V>> elements = new LinkedList<Node<K, V>>();
        
    /**
     * An integer value to keep capacity of the array.
     */
    private int capacity = 1;  
    
    /**
     * Creates a BinarySearchTree.
     */
    @SuppressWarnings("unchecked")
    public BinarySearchTree(){
        array = (Node<K, V>[]) new Node[capacity];
    }
    
    /**
     * Returns the size of the BinarySearchTree.
     * @return Returns the number of elements BinarySearchTree contains.
     */
    public int size(){
        return size;
    }
    
    /**
     * Gets all elements on the BinarySearchTree in random order.
     * @return Retruns the BinarySearchTree in random order.
     */
    public LinkedList<Node<K, V>> getElements(){
        return elements;
    }
    
    /**
     * Inserts key where it belongs in the tree. Returns true if key is inserted, false if it is not inserted.
     * @param _key Gets the key as type K.
     * @param _value Gets the value as type V.
     * @return Returns true if item is inserted, otherwise false.
     */
    
    public boolean add(K _key, V _value){
        int index = whereToPlace(_key); /* Search a correct index to place the item. */
        if(index >= capacity) /* If index violates capacity, reallocate. */
            reallocate();
        if(array[index] != null) /* Checks the item is already there or not. */
            return false; /* If the item is already inserted to tree, returns false. */
        array[index] = new Node<K, V>(_key, _value); /* Place the item. */
        elements.add(new Node<K, V>(_key, _value)); /* Adds item to the ArrayList. */
        size++; /* Increase size by one. */
        return true; /* Returns true. */
    }
    
    /**
     * Search the target in the tree, returns true if the target is found, false if it is not found.
     * @param target Gets the target value as type K.
     * @return Returns true if the target is found, otherwise false.
     */
    
    public boolean contains(K target) {
        return (find(target) != null); /* Calls find method, if it does not return null, the target is found. */
    }
    
    /**
     * Removes target value if it is found from tree and returns it, otherwise returns null. 
     * @param target Gets the target value as type K.
     * @return Returns the target value if it is found, otherwise null.
     */
    
    public boolean remove(K target) {
        int index = indexOf(target); /* Finds the index of the target value in array. */
        if(index == -1) /* If the index is -1 (There is no such an element), returns false. */
            return false;
        remove(index); /* Calls overloaded remove function with index parameter. */
        elements.remove(new Node<K, V>(target, null)); /* Removes the element from elements list. */
        size--; /* Decreases size. */
        if(capacity >= Math.pow(2, size) + 1) /* If the capacity is more than the number of nodes of an binary tree which its height equals to number of nodes, decreases the capacity. */
            free(); /* Frees the empty space. */
        return true;
    }
    
    /**
     * Returns a reference to the data on the tree node that is equal to target. If there is no such a node, returns null.
     * @param target Gets the target value as type K.
     * @return Returns a reference of a node which is equal to target, otherwise null.
     */
    
    @SuppressWarnings("unchecked") /* I had to add this annotion to avoid error while casting Object to K. */
    public V find(K target) {
        int index = indexOf(target);
        return (index != -1) ? (V) array[index].getValue() : null;
    }

    /**
     * Removes target value if it is found from tree and returns true, otherwise returns false. 
     * @param target Gets the target value as type K.
     * @return Returns true if target value is found, otherwise false.
     */
    
    public V delete(K target) {
        int index = indexOf(target); /* Finds the index of the target value in array. */
        if(index == -1) /* If the index is -1 (There is no such an element), returns null. */
            return null;
        V prevValue = array[index].getValue();
        remove(index); /* Calls overloaded remove function with index parameter. */
        elements.remove(new Node<K, V>(target, null)); /* Removes the element from elements list. */
        size--; /* Decreases size. */
        if(capacity >= Math.pow(2, size) + 1) /* If the capacity is more than the number of nodes of an binary tree which its height equals to number of nodes, decreases the capacity. */
            free(); /* Frees the empty space. */
        return prevValue;
    }

    /**
     * Converts BinarySearchTree to String.
     * @return Returns String version of BinarySearchTree.
     */
    public String toString(){
        StringBuilder string = new StringBuilder();
        string.append("{");
        for(int i = 0; i < capacity; i++){
            string.append(array[i]);
            if(i != capacity - 1)
                string.append(", ");
        }
        string.append("}");
        return string.toString();
    }
    
    /**
     * Removes the element at the indexth element of array. 
     * @param index Gets index as integer.
     */
    private void remove(int index){ 
        int rightChild = 2 * index + 2;  /* Sets right child index. */
        int leftChild = 2 * index + 1; /* Sets left child index. */
        if(rightChild < capacity){ /* If the node has one or two children, continue. */
            if(array[rightChild] != null && array[leftChild] == null){ /* If there is only right child, continue. */
                array[index]  = array[rightChild]; /* Assign right child to node. */
                slide(index, rightChild); /* Moves children of right child. */
            }
            else if(array[rightChild] == null && array[leftChild] != null){ /* If there is only left child, continue. */
                array[index]  = array[leftChild]; /* Assign left child to node. */
                slide(index, leftChild); /* Moves children of left child. */
            }
            else{ /* If there are both right and left child, continue. */
                int successor = successorOf(rightChild); /* Gets index of successor. */
                array[index] = array[successor]; /* Assign node at successor to node at index. */
                remove(successor); /* Slide children of successor up. */
            }
        }
        else /* If there is no child of the node, assign null to node. */
            array[index] = null;
    }
    
    /**
     * Makes children of child to children of parent. 
     * @param parent Takes parent node index as integer.
     * @param child Takes child node index as integer.
     */
    private void slide(int parent, int child){
        int leftGrandChild = 2 * child + 1; /* Sets left grandchild index.*/
        int leftChild = 2 * parent + 1; /* Sets left child index. */
        if(leftGrandChild >= capacity) /* If indexes of grandchildren violates capacity, terminate the method. */
            return;
        array[leftChild + 1] = array[leftGrandChild + 1]; /* Assign right child of parent to right child of child. */
        array[leftChild] = array[leftGrandChild]; /* Assign left child of parent to left child of child. */
        array[leftGrandChild + 1]  = null; /* Makes right grandchild null. */
        array[leftGrandChild] = null; /* Makes left grandchild null. */
        slide(leftChild + 1, leftGrandChild + 1); /* Recursively call the function for right child of child. */
        slide(leftChild, leftGrandChild); /* Recursively call the function for left child of child. */
    }
    
    /**
     * Finds successor of an element. 
     * @param index Gets index as integer.
     * @return Returns successor index as integer.
     */
    private int successorOf(int index){
        int successor = index;
        while(2 * successor + 1 < capacity && array[2 * successor + 1] != null) /* Moves until most left node. */
            successor = 2 * successor + 1;
        return successor; /* Return index of the most left node of the tree. */
    }
    
    /**
     * Gets a target and search for a node to place the target.
     * @param target Gets the target value as type K.
     * @return Returns index of the node.
     */
    private int whereToPlace(K target){
        return whereToPlace(target, 0);
    }
    
    /**
     * Gets a target and search the target in tree.
     * @param target Gets a target value as type K.
     * @return Returns the index of the node which contains target value, otherwise -1.
     */
    private int indexOf(K target){
        return indexOf(target, 0);
    }
    
    /**
     * A recursive function to find a suitable node to place the target value.
     * @param target Gets a target value as type K.
     * @param index Gets an index as type integer.
     * @return Returns the index of the node.
     */
    @SuppressWarnings("unchecked") /* I had to add this annotion to avoid error while casting Object to K. */
    private int whereToPlace(K target, int index){
        if(index >= capacity)
            return index;
        if(array[index] == null)
            return index;
        int comparision = target.compareTo(array[index].getKey()); /* Compare item and indexth element of array. */
        if(comparision == 0) /* If item is already in the tree, returns -1. */
            return index;
        else if(comparision > 0) /* If item is bigger than indexth element of array, continue with right binary tree. */
            return whereToPlace(target, 2 * index + 2); 
        else /* If item is less than indexth element of array, continue with left binary tree. */
            return whereToPlace(target, 2 * index + 1);
    }
    
    /**
     * Gets a target and search the target in tree.
     * @param target Gets a target value as type K.
     * @param index Gets a index as type integer.
     * @return Returns the index of the node which contains target value, otherwise -1.
     */
    @SuppressWarnings("unchecked") /* I had to add this annotion to avoid error while casting Object to K. */
    private int indexOf(K target, int index){
        if(index >= capacity)
            return -1;
        if(array[index] == null)
            return -1;
        int comparision = target.compareTo(array[index].getKey()); /* Compare item and indexth element of array. */
        if(comparision == 0) /* If item is already in the tree, returns index. */
            return index;
        else if(comparision > 0) /* If item is bigger than indexth element of array, continue with right binary tree. */
            return indexOf(target, 2 * index + 2); 
        else /* If item is less than indexth element of array, continue with left binary tree. */
            return indexOf(target, 2 * index + 1);
    }
    
    /**
     * Decreases the size of the array when it is needed.
     */
    @SuppressWarnings("unchecked")
    private void free(){
        Node<K, V>[] temp = (Node<K, V>[]) new Node[(capacity - 1) / 2]; /* Create an array which can keep a binary tree with height is 1 less than previous height. */
        for(int i = 0; i < (capacity - 1) / 2; i++) /* Copies the previous array to new array. */
            temp[i] = array[i];
        array = temp; /* Assign the new array to previous array. */
        capacity = (capacity - 1) / 2; /* Decrease capacity as if it were a perfect binary tree. */
    }
       
    /**
     * Increases the size of the array when it is needed.
     */
    @SuppressWarnings("unchecked")
    private void reallocate(){ 
        Node<K, V>[] temp = (Node<K, V>[]) new Node[capacity * 2 + 1];
        for(int i = 0; i < capacity; i++) /* Copy the previous array to new array. */
            temp[i] = array[i];
        array = temp; /* Assign the new array to previous array. */
        capacity = 2 * capacity + 1; /* Increase capacity as if it were a perfect binary tree. */
    }
    
    /**
     * An inner class to keep nodes.
     * @param <K> Generic key.
     * @param <V> Generic value.
     */
    protected class Node<K extends Comparable<K>, V>{
        /**
         * Keeps key of the node.
         */
        private K key;
        
        /**
         * Keeps value of the node.
         */
        private V value;
        
        /**
         * Two parameter constructor to create a Node.
         * @param _key Key for node.
         * @param _value Value for node.
         */
        public Node(K _key, V _value){
            key = _key;
            value = _value;
        }
        
        /**
         * Gets key of the Node.
         * @return Returns key of the Node.
         */
        public K getKey(){
            return key;
        }
        
        /**
         * Gets value of the Node.
         * @return Returns value of the Node.
         */
        public V getValue(){
            return value;
        }
        
        /**
         * Converts Node to String.
         * @return Returns String version of Node.
         */
        public String toString(){
            return key.toString() + "  " + value.toString();
        }
    }
}
