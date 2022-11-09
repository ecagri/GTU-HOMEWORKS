package cayci_hw1;

/**
 * Class keeps STRUCTURES.
 * @author cagri cayci
 */
public class STREET {
    /**
     * Keeps lenght of the STREET as integer.
     */
    private int lenght;
    /**
     * Keeps STRUCTUREs of the right side of the STREET as GTUArray.
     */
    private GTUArray rights = new GTUArray();
    /**
     * Keeps STRUCTUREs of the lefts side of the STREET as GTUArray.
     */
    private GTUArray lefts = new GTUArray();
    /**
     * One parameter constructor
     * @param _lenght Takes lenght of the STREET as an integer.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public STREET(int _lenght) throws OUTOFRANGEEXCEPTION{
        setLenght(_lenght);
    }
    
    /**
     * Sets lenght of the STREET.
     * @param _lenght Takes lenght of the STREET as an integer.
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
     * Adds a STRUCTURE to rights field by calling add function of GTUArray object.
     * @param building Takes a building as a STRUCTURE.
     */
    public void addBuildingRights(STRUCTURE building){
        if(0 <= building.getMinPosition() && building.getMaxPosition() <= lenght){ /* If building is in the border of STREET object, calls add method of GTUArray class. */
            rights.add(building);
        }
    }
    
    /**
     * Adds a STRUCTURE to lefts field by calling add function of GTUArray object.
     * @param building Takes a building as a STRUCTURE.
     */ 
    public void addBuildingLefts(STRUCTURE building){
        if(0 <= building.getMinPosition() && building.getMaxPosition() <= lenght){ /* If building is in the border of STREET object, calls add method of GTUArray class. */
            lefts.add(building);
        }
    }
    
    /**
     * Deletes a STRUCTURE from rights field by calling delete function of GTUArray object.
     * @param position Takes position of the building which will be removed as an integer.
     * @param lenght Takes lenght of the building which will be removed as an integer. 
     */
    public void deleteBuildingsRights(int position, int lenght){
        rights.delete(position, lenght);
    }
    
    /**
     * Deletes a STRUCTURE from lefts field by calling delete function of GTUArray object.
     * @param position Takes position of the building which will be removed as an integer.
     * @param lenght Takes lenght of the building which will be removed as an integer. 
     */
    public void deleteBuildingsLefts(int position, int lenght){
        lefts.delete(position, lenght);
    }
    
    /**
     * Prints the siluette of the STREET.
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
     * Prints the remaining lenght of the STREET by calling occupiedLenght function of the GTUArray object.
     */
    public void remainingLenght(){
        System.out.println("Remaining lenght is: " + ((2 * lenght) - rights.occupiedLenght() - lefts.occupiedLenght()));
    }
    
    /**
     * Prints the occupied lenght of the STREET by calling occupiedLenght and totalPlaygroundsLenght functions of the GTUArray object.
     */
    public void occupiedLenght(){
        System.out.println("Occupied lenght is: " + (rights.occupiedLenght() + lefts.occupiedLenght() - rights.totalPlaygroundsLenght() - lefts.totalPlaygroundsLenght()));
    }
    
    /**
     * Prints the information about PLAYGROUNDs of both sides of the STREET.
     */
    public void playGroundsInfo(){
        double ratio = (rights.totalPlaygroundsLenght() + lefts.totalPlaygroundsLenght()) / (double) (2 * lenght);
        System.out.println("Number of playgrounds is: " + (rights.numberofObjects(PLAYGROUND.class) + lefts.numberofObjects(PLAYGROUND.class)));    
        System.out.println("The ratio of lenght of the playgrounds in the STREET is: " + ratio);
    }
    
    /**
     * Prints the information about STREET.
     */
    public void streetInfo(){
        System.out.println("The STREET includes:");
        System.out.println((rights.numberofObjects(HOUSE.class) + lefts.numberofObjects(HOUSE.class)) + " HOUSE(S)");
        System.out.println((rights.numberofObjects(MARKET.class) + lefts.numberofObjects(MARKET.class)) + " MARKET(S)");
        System.out.println((rights.numberofObjects(OFFICE.class) + lefts.numberofObjects(OFFICE.class)) + " OFFICE(S)");
        System.out.println((rights.numberofObjects(PLAYGROUND.class) + lefts.numberofObjects(PLAYGROUND.class) + " PLAYGROUND(S)"));
    }
}
