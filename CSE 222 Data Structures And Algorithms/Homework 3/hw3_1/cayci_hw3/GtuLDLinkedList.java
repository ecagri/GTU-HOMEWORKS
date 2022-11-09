package cayci_hw3;

import java.util.ListIterator;


/**
 * Helper class to keep structures LDLinkedList and makes operation on it. 
 * @author cagri cayci 
 */
public class GtuLDLinkedList{
    /**
     * Keeps structures as LDLinkedList.
     */
    private final LDLinkedList<Structure> structures;
    /**
     * Keeps removed elements as LDLinkedList for lazy deletion strategy.
     */
    private final LDLinkedList<Structure> removedElements = new LDLinkedList<Structure>();
    
    /**
     * No parameter constructor for GtuLDLinkedList.
     */
    public GtuLDLinkedList(){
        structures = new LDLinkedList<Structure>();
    }
    
    /**
     * Adds a building to structures LDLinkedList. 
     * @param building Gets a building as Structure.
     */
    public void add(Structure building){
        if(placeable(building)){ /* Controls the placeablity of building. */
            if(structures.add(removedElements.findNode(building)) == false)
                structures.add(building); /* If removed elements LDLinkedList does not contain the building, add a new building. */
        }
    }
    
    /**
     * Deletes an element from structures LDLinkedList and adds it to removed elements LDLinkedList.
     * @param position Takes position of the building as integer.
     * @param lenght Takes lenght of the building as integer.
     */
    public void delete(int position, int lenght){
        ListIterator<Structure> iter = structures.listIterator(); /* Creates a ListIterator. */
        while(iter.hasNext()){ /* Searchs the building in structures LDLinkedList. */
            Structure s1 = iter.next();
            if(s1.getMinPosition() == position && s1.getLenght() == lenght){ /* If the element is found, continue. */
                iter.remove(); /* Removes the element from structures LDLinkedList. */
                removedElements.add(s1); /* Adds the element to removed element LDLinkedList. */
                return; /* Terminates the program. */
            }
        }
    }
  
    /**
     * Checks the building can be placed on the street.
     * @param building Takes a building as Structure.
     * @return Returns true if it can be placed, otherwise returns false.
     */
    public boolean placeable(Structure building){
        ListIterator<Structure> iter = structures.listIterator(); /* Creates a ListIterator. */
        while(iter.hasNext()){ /* Checks every elements of the structures LDLinkedList to check placeablity of the new building. */
            Structure s1 = iter.next();
            if(s1.getMinPosition() < building.getMaxPosition() && building.getMinPosition() < s1.getMaxPosition()) /* If the building violates any structures borders, returns false. */
                return false;
        }
        return true; /* If the building does not violates any structures borders, returns true. */
    }
    
    /**
     * Finds the max height a building has on the street.
     * @param maxHeight Takes current maxHeight as integer.
     * @return Returns new maxHeight as integer.
     */
    public int findMaxHeight(int maxHeight){
        ListIterator<Structure> iter = structures.listIterator(); /* Creates a ListIterator. */
        while(iter.hasNext()){ /* Checks heights of every structure. */
            Structure s1 = iter.next();
            if(s1.getHeight() > maxHeight) /* If height of the structure is higher than maxHeight, assign the height as maxHeight. */
                maxHeight = s1.getHeight();  
        }
        return maxHeight; /* Returns maxHeight. */
    }
    
    
    /**
     * Prints the borders of the structure, fills inside borders with 'X'.
     * @param array Takes an array as 2D char array.
     * @param maxHeight Takes maxHeight on the street as integer.
     */
    public void printBorders(char[][] array, int maxHeight){
        int height, minPosition, maxPosition;
        ListIterator<Structure> iter = structures.listIterator();  /* Creates a ListIterator. */
        while(iter.hasNext()){ /* Prints every elements of the structures GtuLDLinkedList. */
            Structure s1 = iter.next();
            height = s1.getHeight(); /* Gets height of the structure. */
            minPosition = s1.getMinPosition(); /* Gets minPosition of the structure. */
            maxPosition = s1.getMaxPosition(); /* Gets maxPosition of the structure. */
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
     * Finds length which occupied by Structures.
     * @return Returns the occupied length as integer.
     */
    public int occupiedLength(){
        int occupied = 0;
        ListIterator<Structure> iter = structures.listIterator(); /* Creates a ListIterator. */
        while(iter.hasNext()){ /* Adds lenghts of every building in the LDLinkedList. */
            Structure s1 = iter.next();
            occupied += s1.getLenght();
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
        ListIterator<Structure> iter = structures.listIterator(); /* Creates a ListIterator. */
        while(iter.hasNext()){ /* Searchs all elements. */
            Structure s1 = iter.next();
            if(s1.getClass() == obj) /* If the type of structure and obj is same, increases objectsNumber. */
                objectsNumber++;
        }
        return objectsNumber;
    }
    
    /**
     * Finds total length occupied by Playground on the street.
     * @return Returns the total length occupied by Playground as integer.
     */
    public int totalPlaygroundsLength(){
        int totalLenght = 0;
        ListIterator<Structure> iter = structures.listIterator(); /* Creates a ListIterator. */
        while(iter.hasNext()){ /* Searchs all elements. */
            Structure s1 = iter.next();
            if(s1.getClass() == Playground.class) /* If the type of the structure is Playground, adds the structure lenght to sum. */
                totalLenght += s1.getLenght();
        }
        return totalLenght;
    }
}
