package cayci_hw1;


/**
 * Helper class to keeps STRUCTURE array and makes operations on it. 
 * @author cagri cayci
 */
public class GTUArray {
    /**
     * Keeps STRUCTUREs as STRUCTURE array.
     */
    private STRUCTURE[] structures = new STRUCTURE[1];
    /**
     * Keeps the capacity of the array.
     */
    private int capacity;
    /**
     * Keeps the size of the array.
     */
    private int size;
    
    /**
     * No parameter constructor.
     */
    public GTUArray(){
        size = 0;
        capacity = 1;
    }
    
    /**
     * Doubles the capacity of the array.
     */
    private void reallocate(){
        STRUCTURE[] temp = new STRUCTURE[capacity * 2]; /* Creates a temp array with double capacity of the current capacity. */
        for(int i = 0; i < size; i++){ /* Copies the elements of the array. */
            temp[i] = structures[i];
        }
        structures = temp; /* Assigns temp array to structures. */
        capacity *= 2; /* Doubles the capacity. */
    }
    
    /**
     * Add an STRUCTURE to array.
     * @param building Takes a building as a STRUCTURE
     */
    public void add(STRUCTURE building){
        if(placeable(building) == true){ /* Controls building can be placed or not. */
            if(capacity <= size){ /* If capacity is not enough, reallocate. */
                reallocate();
            }
            structures[size] = building; /* Adds the building at the end of the array. */
            size += 1; /* Increases size by one. */
        }
    }
    
    /**
     * Deletes a building from array. 
     * @param position Takes position of the building as integer.
     * @param lenght Takes length of the building as integer. 
     */
    public void delete(int position, int lenght){
        int index = itFound(position, lenght); /* Finds index of the building on the array. */
        for(int i = index; i < size - 1; i++){ /* After indexth element of the array, every element is shifted one unit back. */
            structures[i] = structures[i+1];
        }
        if(index != size){ /* If index not equals the size , continue. */
            structures[size -1] = null; /* Free last element of the array. */
            size -= 1; /* Decreases size by one. */
            if(capacity == 2 * size) /* If capacity is twice the size, free. */
                free();
        }
    }
    
    /**
     * Divides array capacity by two
     */
    public void free(){ 
        STRUCTURE[] temp = new STRUCTURE[capacity/2]; /* Creates a temp array with size divided by 2. */
        for(int i = 0; i < size; i++){ /* Copies the elements of the array. */
            temp[i] = structures[i];
        }
        structures = temp; /* Assigns temp to structures array. */
        capacity /= 2; /* Divides capacity by two. */
    }
    
    /**
     * Search a building with its position and length in the array.
     * @param position Takes position of the building as integer.
     * @param lenght Takes length of the building as integer.
     * @return Returns the index of the building if it found, otherwise return size as integer.
     */
    public int itFound(int position, int lenght){
        int index = size; /* Assings index to size. */
        for(int i = 0; i < size; i++){
            if(structures[i].getMinPosition() == position && structures[i].getLenght() == lenght){
                index = i; /* If the building has found, assings i to index. */
            }
        }
        return index;
    }
    
    /**
     * Checks the building can be placed on the street.
     * @param building Takes a building as STRUCTURE.
     * @return Returns true if it can be placed, otherwise returns false.
     */
    private boolean placeable(STRUCTURE building){
        boolean canPlaced = true;
        for(int i = 0; i < size; i++){
           if(structures[i].getMinPosition() < building.getMaxPosition() && building.getMinPosition() < structures[i].getMaxPosition()){ /* If the position and lenght of the building */
               canPlaced = false;                                                                                                       /* violates any building position, canPlaced is false. */    
           }
        }
        return canPlaced;
    }
    
    /**
     * Finds the max height a building has on the street.
     * @param maxHeight Takes current maxHeight as integer.
     * @return Returns new maxHeight as integer.
     */
    public int findMaxHeight(int maxHeight){
        for(int i = 0; i < size; i++){ /* Search every element of the array, and finds max height. */
            if(structures[i].getHeight() > maxHeight){
                maxHeight = structures[i].getHeight();
            }
        }
        return maxHeight;
    }
    
    
    /**
     * Prints the borders of the structure, fills inside borders with 'X'.
     * @param array Takes an array as 2D char array.
     * @param maxHeight Takes maxHeight on the street as integer.
     */
    public void printBorders(char[][] array, int maxHeight){
        int height, minPosition, maxPosition;
        for(int i = 0; i < size; i++){
            height = structures[i].getHeight();
            minPosition = structures[i].getMinPosition();
            maxPosition = structures[i].getMaxPosition();
            for(int k = minPosition; k <= maxPosition; k++){ /* For roof of the building. */
                if(array[maxHeight - height][k] != 'X') 
                    array[maxHeight - height][k] = '*';
            }
            height -= 1;
            for(;height > 0; height--){ /* For sides of the building. */
                if(array[maxHeight - height][minPosition] != 'X')  
                    array[maxHeight - height][minPosition] = '*';
                if(array[maxHeight - height][maxPosition] != 'X') 
                    array[maxHeight - height][maxPosition] = '*';
                for(int k = minPosition + 1; k < maxPosition; k++){
                    array[maxHeight - height][k] = 'X';
                }
            }
        }
    }
    
    /**
     * Finds length which occupied by BUILDINGS(HOUSE, MARKET, OFFICE).
     * @return Returns the occupied length as integer.
     */
    public int occupiedLenght(){
        int occupied = 0;
        for(int i = 0; i < size; i++){ /* Sums all the buildings length and finds total occupied length. */
            occupied += structures[i].getLenght();
        }
        return occupied;
    }
 
    /**
     * Finds number of specific objects on the street. 
     * @param obj Takes an obj as Object class.
     * @return Returns the number of specific objects as integer.
     */
    public int numberofObjects(Object obj){
        int objectsNumber = 0;
        for(int i = 0; i < size; i++){ /* Sums all the buildings which type is the same as type of the parameter object. */
            if(structures[i].getClass() == obj){
                objectsNumber++;
            }
        }
        return objectsNumber;
    }
    
    /**
     * Finds total length occupied by PLAYGROUND on the street.
     * @return Returns the total length occupied by PLAYGROUND as integer.
     */
    public int totalPlaygroundsLenght(){
        int totalLenght = 0;
        for(int i = 0; i < size; i++){ /* Sums all the length occupied by PLAYGROUNDs. */
            if(structures[i].getClass() == PLAYGROUND.class){
                totalLenght += structures[i].getLenght();
            }
        }
        return totalLenght;
    }
}
