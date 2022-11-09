package cayci_hw3;

/**
 * Class keeps StructureS.
 * @author cagri cayci
 */
public class Street {
    /**
     * Keeps lenght of the Street as integer.
     */
    private int lenght;
    /**
     * Keeps Structures of the right side of the Street as GtuLDLinkedList.
     */
    private GtuLDLinkedList rights = new GtuLDLinkedList();
    
    /**
     * Keeps Structures of the lefts side of the Street as GtuLDLinkedList.
     */
    private GtuLDLinkedList lefts = new GtuLDLinkedList();
    /**
     * One parameter constructor
     * @param _lenght Takes lenght of the Street as an integer.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public Street(int _lenght) throws OUTOFRANGEEXCEPTION{
        setLenght(_lenght);
    }
    
    /**
     * Sets lenght of the Street.
     * @param _lenght Takes lenght of the Street as an integer.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public void setLenght(int _lenght) throws OUTOFRANGEEXCEPTION{
        if(_lenght > 0){ /* If _lenght is bigger than 0, assign it lenght. */
            lenght = _lenght;
        }
        else /* Otherwise throws an exception. */
            throw new OUTOFRANGEEXCEPTION(_lenght);
    }
    
    /**
     * Gets lenght of the street.
     * @return Returns lenght of the street as integer.
     */
    public int getLenght(){
        return lenght;
    }
    
    /**
     * Adds a Structure to rights field by calling add function of GtuLinkedList object.
     * @param building Takes a building as a Structure.
     */
    public void addBuildingRights(Structure building){
        if(0 <= building.getMinPosition() && building.getMaxPosition() <= lenght){ /* If building is in the border of Street object, calls add method of GtuLinkedList class. */
            rights.add(building);
        }
    }
    
    /**
     * Adds a Structure to lefts field by calling add function of GtuLinkedList object.
     * @param building Takes a building as a Structure.
     */ 
    public void addBuildingLefts(Structure building){
        if(0 <= building.getMinPosition() && building.getMaxPosition() <= lenght){ /* If building is in the border of Street object, calls add method of GtuLinkedList class. */
            lefts.add(building);
        }
    }
    
    /**
     * Deletes a Structure from rights field by calling delete function of GtuLinkedList object.
     * @param position Takes position of the building which will be removed as an integer.
     * @param lenght Takes lenght of the building which will be removed as an integer. 
     */
    public void deleteBuildingsRights(int position, int lenght){
        rights.delete(position, lenght);
    }
    
    /**
     * Deletes a Structure from lefts field by calling delete function of GtuLinkedList object.
     * @param position Takes position of the building which will be removed as an integer.
     * @param lenght Takes lenght of the building which will be removed as an integer. 
     */
    public void deleteBuildingsLefts(int position, int lenght){
        lefts.delete(position, lenght);
    }
    
    /**
     * Prints the siluette of the Street.
     */
    public void printSiluette(){
        int generalMaxHeight = rights.findMaxHeight(0); /* Finds the max height of the buildings in the right side of the street. */
        generalMaxHeight = lefts.findMaxHeight(generalMaxHeight); /* Finds total max height of the building on the whole street. */
        char[][] array = new char[generalMaxHeight + 1][lenght + 1]; /* Creates a char array. */
        for(int i = 0; i <= lenght; i++){ /* Sets the format of the char array. */
            for(int j = 0; j <= generalMaxHeight; j++){
                array[j][i] = ' ';
            }
            array[generalMaxHeight][i] = '*';
        }
        
        rights.printBorders(array, generalMaxHeight); /* Prints the building on the right side of the street. */
        lefts.printBorders(array, generalMaxHeight); /* Prints the building on the left side of the street. */
        
        for(int i = 0; i <= generalMaxHeight; i++){ /* Converts 'X' char to ' ' char. */
            for(int j = 0; j <= lenght; j++){
                if(array[i][j] == 'X')
                    array[i][j] = ' ';
                System.out.print(array[i][j]);
            }
            System.out.println();
        }
    }
    
    /**
     * Prints the remaining lenght of the Street by calling occupiedLength function of the GtuLinkedList object.
     */
    public void remainingLenght(){
        System.out.println("Remaining lenght is: " + ((2 * lenght) - rights.occupiedLength() - lefts.occupiedLength()));
    }
    
    /**
     * Prints the occupied lenght of the Street by calling occupiedLength and totalPlaygroundsLenght functions of the GtuLinkedList object.
     */
    public void occupiedLength(){
        System.out.println("Occupied lenght is: " + (rights.occupiedLength() + lefts.occupiedLength() - rights.totalPlaygroundsLength() - lefts.totalPlaygroundsLength()));
    }
    
    /**
     * Prints the information about Playgrounds of both sides of the Street.
     */
    public void playGroundsInfo(){
        double ratio = (rights.totalPlaygroundsLength() + lefts.totalPlaygroundsLength()) / (double) (2 * lenght);
        System.out.println("Number of playgrounds is: " + (rights.numberofObjects(Playground.class) + lefts.numberofObjects(Playground.class)));    
        System.out.println("The ratio of lenght of the playgrounds in the Street is: " + ratio);
    }
    
    /**
     * Prints the information about Street.
     */
    public void streetInfo(){
        System.out.println("The Street includes:");
        System.out.println((rights.numberofObjects(House.class) + lefts.numberofObjects(House.class)) + " House(S)");
        System.out.println((rights.numberofObjects(Market.class) + lefts.numberofObjects(Market.class)) + " Market(S)");
        System.out.println((rights.numberofObjects(Office.class) + lefts.numberofObjects(Office.class)) + " Office(S)");
        System.out.println((rights.numberofObjects(Playground.class) + lefts.numberofObjects(Playground.class) + " Playground(S)"));
    }
}
