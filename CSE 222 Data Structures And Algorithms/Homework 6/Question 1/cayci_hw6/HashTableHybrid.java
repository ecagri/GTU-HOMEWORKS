package cayci_hw6;

/**
 * A class to keep elements in a HashTable which is designed as hybrid.
 * @author cagri cayci
 * @param <K> Generic type for Key.
 * @param <V> Generic type for Value.
 */
public class HashTableHybrid<K, V>{  
    /**
     * Creates an Element array.
     */
    private Element<K, V>[] table;
    
    /**
     * Keeps capacity of the HashTable table.
     */
    private int size = 10; /* It must be 11 but to show example in the pdf it sets to 10. */
    
    /**
     * Keeps the largest prime number which is less than capacity.
     */
    private int Prime_number = 7;
    
    /**
     * Keeps the number of elements on HashTable.
     */
    private int elementsNumber = 0;
    
    /**
     * Keeps the THRESHOLD value to increase the capacity of the HashTable table when it is needed.
     */
    private final double THRESHOLD = 0.70;
    
    /**
     * Creates a HashTable table.
     */
    @SuppressWarnings("unchecked")
    public HashTableHybrid(){
        table = (Element<K, V>[]) new Element[size];
    }
    
    /**
     * Associates the specified value with the specified key. Returns the previous value
     * associated with the specified key, or null if there was no mapping for the key. 
     * Increase the elementsNumber if it is needed, rehash the table if it is needed.
     * @param _key Key of an element.
     * @param _value Value of an element.
     * @return Returns previous value of an element which is key equals to specified key, otherwise null.
     */
    public V put(K _key, V _value){            
            int index = indexOf(_key, 1); /* Finds index of the new element. */
            
            V prev = put(_key, _value, 1, index, table[index]); /* Put the new element to table and if there is an element with the same key, assigns its value to prev. */
            
            if(prev == null) /* If there is no element which has same key, increases the element number. */
                elementsNumber = elementsNumber + 1;
            
            if((double) elementsNumber / size > THRESHOLD) /* If division of elements number by size crosses the threshold, rehash the table. */
                rehash();
            
            return prev;
    }
    
    /**
     * Remove the element with the specified key.
     * @param _key Key of an element.
     * @return Returns the value of an element if it is found, otherwise null.
     */
    public V remove(Object _key){
        return remove(_key, 1);
    }  
    
    /**
     * Check whether HashTable is empty or not.
     * @return Returns true if it is empty, otherwise false.
     */
    public boolean isEmpty(){
        return (elementsNumber == 0);
    }
    
    /**
     * Returns the capacity of the HashTable.
     * @return Returns the capacity of the HashTable.
     */
    public int size(){
        return size;
    }
    
    /**
     * Converts the HashTable to String in pretty way.
     * @return Returns the String version of the HashTable.
     */
    public String toString(){
        StringBuilder string = new StringBuilder();
        for(int index = 0; index < size; index++){
            string.append(index);
            string.append("   ");
            if(table[index] != null){
                string.append(table[index]);
                string.append("   ");
                if(table[index].next != null)
                    string.append(table[index].next);
                else string.append("null");
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
    
    /**
     * Rehash the HashTable when it is needed.
     */
    @SuppressWarnings("unchecked")
    private void rehash(){
        Element<K, V>[] temp = table; /* Creates an temp Element array. */
        
        int prevCap = size; /* Keeps the previous capacity. */
        
        size = Prime.nextPrime(2 * size); /* Assigns the closest big prime number of twice the capacity to capacity. */
        
        Prime_number = Prime.previousPrime(size); /* /* Assigns the closest small prime number of twice the capacity to capacity. */
        
        elementsNumber = 0; /* Makes elements number 0. */
         
        table = (Element<K, V>[]) new Element[size]; /* Creates a Element array an assigns it to table. */
        
        for(int index = 0; index < prevCap; index++){ /* Fills the table. */            
            if(temp[index] != null)
                put(temp[index].getKey(), temp[index].getValue());
        }
    }
    
    /**
     * Remove the element with the specified key.
     * @param _key Key of an element.
     * @return Returns the value of an element if it is found, otherwise null.
     */
    @SuppressWarnings("unchecked")
    private V remove(Object _key, int probe){
        int index = indexOf((K) _key, probe); /* Finds the index of ith probe of key. */
        
        if(table[index] == null) /* If indexth element of table is null, returns null. */
            return null;
        
        if(table[index].key.equals(_key)){ /* If indexth element of table equals to key, continue. */
            V prevValue = table[index].getValue(); /* Get previous value. */
            
            if(table[index].next == null) /* If the element points null, makes the element null. */
                table[index] = null;
            
            else{ /* If the element does not point null, continues. */
                Element<K, V> temp = table[index].next;  /* Gets next element of the element and assigns it to temp. */
                
                table[index] = temp; /* Assigns temp to indexth element of table. */
                
                int indexOfCollide = indexOf(temp.getKey(), probe + 1); /* Finds index of the next element. */
                
                table[indexOfCollide] = null; /* Makes next element null. */
            }
            elementsNumber = elementsNumber - 1; /* Decreases the elements number by one. */
            
            return prevValue;
        }
        else{ /* If the indexth element of table does not equal to element, continues. */
            if(table[index].next == null)  /* If next element is null, the element is not found on table. */
                return null;
            
            else /* If the next element is not null, keeps searching the element. */
                return remove(_key, probe + 1);
        }
    } 
    
    /**
     * Associates the specified value with the specified key. Returns the previous value
     * associated with the specified key, or null if there was no mapping for the key. 
     * @param _key Key of an element.
     * @param _value Value of an element.
     * @return Returns previous value of an element which is key equals to specified key, otherwise null.
     */
    private V put(K _key, V _value, int probe, int index, Element<K, V> element){
        if(element == null){ /* If element is null in index, adds the new element to table. */
            table[index] = new Element<K, V>(_key, _value);
            
            return null;
        }
        V prevValue;
        
        if(element.getKey().equals(_key)){ /* If element equals to new element replaces its value with new one. */
            prevValue = element.getValue(); /* Gets previous value of the element. */
            
            element.setValue(_value); /* Changes its value. */
            
            return prevValue;
        }
        if(element.next == null){ /* If next element of the element is null, continue. */
            do{ /* Finds proper index to place new element. */
                probe = probe + 1;
                index = indexOf(_key, probe);
            }while(index < size && table[index] != null);
            
            table[index] = new Element<K, V>(_key, _value); /* Adds new element to table. */
            
            element.next = table[index]; /* Sets next element. */
            
            return null;
        }
        else{
            index = indexOf(element.next.getKey(), probe + 1); /* Calculates index. */
            
            return put(_key, _value, probe + 1, index, element.next); /* Recursively call the function. */
        }
    }
    
    /**
     * Finds the index of an element with specified key.
     * @param _key Gets key to calculate index of the element.
     * @param probe Gets probe number to calculate index of the element.
     * @return Returns index of the element with specified key.
     */
    private int indexOf(K _key, int probe){
        int key = (int) _key;
        int hash1 = key % size; /* Calculates hash1 with given equation. */
        int hash2 = Prime_number - (key  % Prime_number); /* Calculates hash2 with given equation. */
        if(hash2 == 0)
            hash2 = 1;
        int index = (hash1 + (probe * hash2)) % size; /* Calculates index with given equation. */
        return (index < 0) ? index + size: index;
    }
    
    /**
     * A inner class to keep key, value and reference of the next element of an element.
     * @param <K> Generic type for Key.
     * @param <V> Generic type for Value.
     */
    private class Element<K, V>{
        /**
         * Keeps key of the element as constant.
         */
        private final K key;
        
        /**
         * Keeps value of the element.
         */
        private V value;
        
        /**
         * Keeps the next element reference.
         */
        private Element<K, V> next = null;
        
        /**
         * Creates an element with key, value.
         * @param _key To get Key.
         * @param _value To get Value.
         */
        public Element(K _key, V _value){
            key = _key;
            value = _value;
        }
        
        /**
         * Gets key of an element.
         * @return Returns key of the element.
         */
        public K getKey(){
            return key;
        }
        
        /**
         * Gets value of an element. 
         * @return Returns value of the element.
         */
        public V getValue(){
            return value;
        }
        
        /**
         * Set value of an element.
         * @param _value Gets value to assign it to value of an element.
         */
        public void setValue(V _value){
            value = _value;
        }
        
        /**
         * Converts Element to String.
         * @return Returns String version of the element.
         */
        public String toString(){
            return key.toString() + "," + value.toString();
        }
    }
}
