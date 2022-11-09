package cayci_hw3;

import java.util.LinkedList;
import java.util.ListIterator;

/**
 * Helper class to keep structures LinkedList and makes operation on it. 
 * @author cagri cayci 
 */
public class GtuLinkedList{
    /**
     * Keeps Structures as Structure LinkedList.
     */
    private final LinkedList<Structure> structures;
    
    /**
     * No parameter constructor.
     */
    public GtuLinkedList(){
        structures = new LinkedList<Structure>();
    }  
    
    /**
     * Add an Structure to LinkedList.
     * @param building Takes a building as a Structure
     */
    public void add(Structure building){ /* θ(1) time complexity. */
        if(placeable(building) == true){ /* Controls building can be placed or not. */
            structures.addLast(building);
        }
    }
    
    /**
     * Deletes a building from LinkedList. 
     * @param position Takes position of the building as integer.
     * @param lenght Takes length of the building as integer. 
     */
    public void delete(int position, int lenght){ /* O(n) time complexity. */
        ListIterator<Structure> iter = structures.listIterator(); /* Creates an ListIterator. */
        while(iter.hasNext()){ /* Searches an element */
            Structure s1 = iter.next();
            if(s1.getMinPosition() == position && s1.getLenght() == lenght){ /* If it found the element, remove it. */
                iter.remove();
                return; /* Terminates the loop. */
            }
        }
    }
    
    /**
     * Finds the max height a building has on the street.
     * @param maxHeight Takes current maxHeight as integer.
     * @return Returns new maxHeight as integer.
     */
    public int findMaxHeight(int maxHeight){ /* θ(n) time complexity. */
        ListIterator<Structure> iter = structures.listIterator(); /* Creates an ListIterator. */
        while(iter.hasNext()){ /* Compares all element with maxHeight. */
            Structure s1 = iter.next();
            if(s1.getHeight() > maxHeight) /* If height of an element is bigger than maxHeight, assign the height to maxHeight. */
                maxHeight = s1.getHeight();  
        }
        return maxHeight;
    }
    
    /**
     * Finds number of specific objects on the street. 
     * @param obj Takes an obj as Object class.
     * @return Returns the number of specific objects as integer.
     */
    public int numberofObjects(Object obj){ /* θ(n) time complexity. */
        int objectsNumber = 0;
        ListIterator<Structure> iter = structures.listIterator(); /* Creates an ListIterator. */
        while(iter.hasNext()){ /* Searches all element. */
            Structure s1 = iter.next();
            if(s1.getClass() == obj) /* If obj and s1 are the elements of the same class, increases objectsNumber by one. */
                objectsNumber++;
        }
        return objectsNumber;
    }
    
    /**
     * Finds length which occupied by Structures.
     * @return Returns the occupied length as integer.
     */
    public int occupiedLength(){ /* θ(n) time complexity. */
        int occupied = 0;
        ListIterator<Structure> iter = structures.listIterator(); /* Creates an ListIterator. */
        while(iter.hasNext()){ /* Searches all element. */ 
            Structure s1 = iter.next();
            occupied += s1.getLenght(); 
        }
        return occupied;
    }
    
    /**
     * Checks the building can be placed on the street.
     * @param building Takes a building as Structure.
     * @return Returns true if it can be placed, otherwise returns false.
     */
    public boolean placeable(Structure building){ /* O(n) time complexity. */
        ListIterator<Structure> iter = structures.listIterator(); /* Creates an ListIterator. */
        while(iter.hasNext()){ /* Searches all element. */
            Structure s1 = iter.next();
            if(s1.getMinPosition() < building.getMaxPosition() && building.getMinPosition() < s1.getMaxPosition()) /* If new structure violates borders of any structure, return false. */
                return false;
        }
        return true;
    }
    
    
    /**
     * Prints the borders of the structure, fills inside borders with 'X'.
     * @param array Takes an array as 2D char array.
     * @param maxHeight Takes maxHeight on the street as integer.
     */
    public void printBorders(char[][] array, int maxHeight){
        int height, minPosition, maxPosition;
        ListIterator<Structure> iter = structures.listIterator(); /* Creates a ListIterator. */ 
        while(iter.hasNext()){ /* Prints every elements of the structures GtuLinkedList. */
            Structure s1 = iter.next();
            height = s1.getHeight(); /* Gets height of the s1. */
            minPosition = s1.getMinPosition(); /* Gets min position of the s1. */
            maxPosition = s1.getMaxPosition(); /* Gets max position of the s1. */
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
     * Finds total length occupied by Playground on the street.
     * @return Returns the total length occupied by Playground as integer.
     */
    public int totalPlaygroundsLength(){ /* θ(n) time complexity. */
        int totalLenght = 0;
        ListIterator<Structure> iter = structures.listIterator(); /* Creates an ListIterator. */
        while(iter.hasNext()){ /* Searches all element. */
            Structure s1 = iter.next();
            if(s1.getClass() == Playground.class) /* If the structure is a Playground, adds lenght of it to sum. */
                totalLenght += s1.getLenght();
        }
        return totalLenght;
    }
}
