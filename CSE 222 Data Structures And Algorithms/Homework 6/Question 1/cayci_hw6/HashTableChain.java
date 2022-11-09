package cayci_hw6;

import java.util.LinkedList;

/**
 * A class to keep elements in a HashTable which is designed as chain.
 * @author cagri cayci
 * @param <K> Generic type for Key.
 * @param <V> Generic type for Value.
 */
public class HashTableChain<K extends Comparable<K>, V>{
    /**
     * Keeps HashTable as an array.
     */
    private BinarySearchTree<K, V>[] table;
    
    /**
     * Threshold for array size is assigned to 3.
     */
    private final double THRESHOLD = 3.0;
    
    /**
     * Keeps number of elements on the HashTable.
     */
    private int numberOfElements = 0;
    
    /**
     * Keeps size of the array.
     */
    private int size = 11;
    
    /**
     * No parameter constructor to create an HashTable.
     */
    @SuppressWarnings("unchecked")
    public HashTableChain(){
        table = (BinarySearchTree<K, V>[])new BinarySearchTree[size];
    }
    
    /**
     * Put a key-value pair to HashTable. If the key is already on the list, change its value to new one.
     * @param _key Key of the new element.
     * @param _value Value of the new element.
     * @return Returns the previous value of the key if there was a key which is identical to new one.
     */
    public V put(K _key, V _value) {
        int index = _key.hashCode() % size; /* Finds index of the key according to its HashCode and size of the table. */
        
        if(index < 0) /* If index is negative, makes it positive. */
            index = index + size;
        
        V prevValue = null; /* Assigns null to prevValue. */
        
        if(table[index] == null) /* If indexth BinarySearchTree on array is empty, creates a new BinarySearchTree. */
            table[index] = new BinarySearchTree<K, V>();
       
        else /* If indexth BinarySearchTree on array is not empty, search the _key on the BinarySearchTree. */
            prevValue = table[index].find(_key); /* Assign the value of the key to prevValue if it is found. */
            
        table[index].add(_key, _value); /* Adds the key value pair to indexth BinarySearchTree. */
        
        if(prevValue == null) /* If the key is not on the BinarySearchTree before, increases elements number by one. */
            numberOfElements = numberOfElements + 1;
        
        if((double) numberOfElements / size > THRESHOLD) /* If division of elements number by size crosses the threshold, rehash the table. */
            rehash();
        
        return prevValue; 
    }
    
    /**
     * Remove an element from HashTable. Returns the value of the key if it is found on the HashTable, if it not returns null.
     * @param _key Key value of an element to search it on the HashTable.
     * @return Returns the value of the key if it is found, otherwise returns null.
     */
    @SuppressWarnings("unchecked")
    public V remove(Object _key) {
        int index = _key.hashCode() % size; /* Finds index of the key according to its HashCode and size of the table. */
        
        if(index < 0) /* If index is negative, makes it positive. */
            index = index + size;
        
        if(table[index] == null) /* If the indexth BinarySearchTree on array is empty, returns null. */
            return null;
        
        V prevValue = (V) table[index].delete((K) _key); /* Searches the key on the BinarySearchTree, deletes it if it is found and assigns its value ot prevValue. */
        
        if(prevValue != null) /* If the elements is found and deleted, decreases the elements number by one. */
            numberOfElements = numberOfElements - 1;
        
        if(table[index].size() == 0) /* After the element is deleted, if size of the BinarySearchTree is empty, assigns null to BinarySearchTree. */
            table[index] = null;
        
        return prevValue;
    }
    
    /**
     * Returns the size of the HashTable.
     * @return Returns ize of the HashTable as integer.
     */
    public int size() {
        return size;
    }
    
    /**
     * Checks whether HashTable is empty or not.
     * @return Returns true if HashTable is empty, otherwise false.
     */
    public boolean isEmpty() {
        return (numberOfElements == 0);
    }
    
    /**
     * Rehash the HashTable if elements number crosses the threshold.
     */
    @SuppressWarnings("unchecked")
    private void rehash(){
        BinarySearchTree<K, V>[] temp = table; /* Creates a temp BinarySearchTree array. */
        int prevSize = size; /* Keeps the previous size. */
        size = Prime.nextPrime(2 * size); /* Assigns the closest big prime number of twice the size to size. */
        numberOfElements = 0; /* Makes number of elements 0. */
        table = (BinarySearchTree<K, V>[]) new BinarySearchTree[size]; /* Creates a new BinarySearchTree and assigns it to table. */
        for(int index = 0; index < prevSize; index++){ /* Adds every elements of all BinarySearchTrees to new table. */
            if(temp[index] != null){ /* If BinarySearchTree is not null, continues. */
                LinkedList<BinarySearchTree<K, V>.Node<K, V>> elements = temp[index].getElements(); /* Creates a LinkedList which keeps the elements of BinarySearchTree in random order.*/
                for(BinarySearchTree<K, V>.Node<K, V> node : elements){ /* Adds all elements of the BinarySearchTree to new HashTable. */
                    put(node.getKey(), node.getValue());
                }
            }     
        }
    }
    
    /**
     * Converts the HashTable to String.
     * @return Returns the String version of HashTable.
     */
    public String toString(){
        StringBuilder string = new StringBuilder();
        for(int index = 0; index < size; index++){
            string.append(index);
            string.append("   ");
            if(table[index] != null){
                LinkedList<BinarySearchTree<K, V>.Node<K, V>> elements = table[index].getElements();
                for(BinarySearchTree<K, V>.Node<K, V> node : elements){
                    string.append(node);
                    string.append("    ");
                }
            }
            else{
                string.append("null");
                string.append("   ");
                string.append("null");
            }
            string.append("\n");
        }
        return string.toString();
    }   
}
