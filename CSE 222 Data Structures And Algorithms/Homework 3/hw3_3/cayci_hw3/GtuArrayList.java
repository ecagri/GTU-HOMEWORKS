package cayci_hw3;

import java.util.ArrayList;

/**
 * Helper class to keep structures ArrayList and makes operation on it. 
 * @author cagri cayci 
 */
public class GtuArrayList{
    /**
     * Keeps structures as ArrayList. 
     */
    private final ArrayList<Structure> structures;
    
    /**
     * No parameter constructor.
     */
    public GtuArrayList(){
        structures = new ArrayList<Structure>();
    }
    
    /**
     * Add an Structure to ArrayList.
     * @param building Takes a building as a Structure
     */
    public void add(Structure building){ /* O(n) time complexity. */
        if(placeable(building)) /* Controls the placeablity of building. */
            structures.add(building);
    }
    
    /**
     * Deletes a building from ArrayList. 
     * @param position Takes position of the building as integer.
     * @param length Takes length of the building as integer. 
     */
    public void delete(int position, int length){ /* /* O(n) time complexity. */
        for(int index = 0; index < structures.size(); index++){ /* Checks all element. */
            if(structures.get(index).getMinPosition() == position && structures.get(index).getLenght() == length){ /* If the element found, removes it and terminates the loop. */
                structures.remove(index);
                return;
            }
        }
    }
    
    /**
     * Finds the max height a building has on the street.
     * @param maxHeight Takes current maxHeight as integer.
     * @return Returns new maxHeight as integer.
     */
    public int findMaxHeight(int maxHeight){ /* θ(n) time complexity. */
        for(int index = 0; index < structures.size(); index++){ /* Searches all element. */
            if(structures.get(index).getHeight() > maxHeight) /* If the height of the element is bigger than maxHeight, assigns height of the element to maxHeight. */
                maxHeight = structures.get(index).getHeight();
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
        for(int index = 0; index < structures.size(); index++){ /* Searches all element. */
            if(structures.get(index).getClass() == obj) /* If both an element of the structure and obj are the same class objects, increases objectNumber by one. */
                objectsNumber++;
        }
        return objectsNumber;
    }
    
    /**
     * Finds length which occupied by Structures..
     * @return Returns the occupied length as integer.
     */
    public int occupiedLength(){ /* θ(n) time complexity. */
        int occupied = 0;
        for(int index = 0; index < structures.size(); index++){ /* Searches all element. */
            occupied += structures.get(index).getLenght();
        }
        return occupied;
    }
    
    /**
     * Checks the building can be placed on the street.
     * @param building Takes a building as Structure.
     * @return Returns true if it can be placed, otherwise returns false.
     */
    public boolean placeable(Structure building){ /* O(n) time complexity. */
        for(int index = 0; index < structures.size(); index++){ /* Searches all element. */
            if(structures.get(index).getMinPosition() < building.getMaxPosition() && building.getMinPosition() < structures.get(index).getMaxPosition()) /* If new structure violates borders of any elements, return false. */
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
        for(int i = 0; i < structures.size(); i++){ /* Prints every elements of the structures GtuArrayList. */
            height = structures.get(i).getHeight(); /* Gets height of the ith structure. */
            minPosition = structures.get(i).getMinPosition(); /* Gets min position of the ith structure. */
            maxPosition = structures.get(i).getMaxPosition(); /* Gets max position of the ith structure. */
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
        for(int index = 0; index < structures.size(); index++){ /* Controls all element. */
            if(structures.get(index).getClass() == Playground.class) /* If any element of structure is a Playground object, gets lenght of the structure and adds it to sum. */
                totalLenght += structures.get(index).getLenght();
        }
        return totalLenght;
    }
}
