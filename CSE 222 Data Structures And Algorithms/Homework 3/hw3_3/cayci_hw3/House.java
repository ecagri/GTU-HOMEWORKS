package cayci_hw3;

/**
 * Keeps type-specific data fields for House.
 * @author cagri cayci
 */
public class House extends Building{
    /**
     * Keeps the number of rooms of the House as integer.
     */
    private int numberofRooms;
    /**
     * Keeps the colour of the House as String.
     */
    private String colour;
    
    /**
     * Six parameter constructor.
     * @param _position Takes position of the House as integer.
     * @param _lenght Takes lenght of the House as integer.
     * @param _height Takes height of the House as integer.
     * @param _owner Takes owner of the House as String.
     * @param _numberofRooms Takes the number of rooms of the House as integer.
     * @param _colour Takes the colour of the House as String.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public House(int _position, int _lenght, int _height, String _owner, int _numberofRooms, String _colour) throws OUTOFRANGEEXCEPTION{
        super(_position, _lenght, _height, _owner); /* Calls constructor of ancestor method. */
        setRoomNumber(_numberofRooms);
        colour = _colour;
    }
    
    /**
     * Set the number of rooms of the House.
     * @param _numberofRooms Takes number of the rooms as integer.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public void setRoomNumber(int _numberofRooms) throws OUTOFRANGEEXCEPTION{
        if(_numberofRooms > 0) /* If _numberofRooms is bigger than 0, assigns it into numberofRooms. */
            numberofRooms = _numberofRooms;
        else /* Otherwise throw an exception. */
            throw new OUTOFRANGEEXCEPTION(_numberofRooms);
    }
    
    /**
     * Prints the fields of House and fields of ancestor classes of the House.
     */
    public void getInfo(){
        super.getInfo(); /* Calls getInfo method of ancestor class. */
        System.out.println("Number of rooms is: " + numberofRooms + "\nColour is: " + colour);
    }
    
    /**
     * Overrides hashCode method.
     * @return Returns the hashCode of the House as integer.
     */
    @Override
    public int hashCode(){
        return 7 * (numberofRooms + 1) * (colour.hashCode()) * super.hashCode();
    }
    
    /**
     * Overrides equals method.
     * @param other Gets other object as Object class.
     * @return Returns true if two objects are equal, otherwise false.
     */
    @Override
    public boolean equals(Object other){
        boolean equality = false;
        if(this.getClass() == other.getClass()){ /* If their class are equal, continue. */
            House otherobj = (House) other;
            if(this.numberofRooms == otherobj.numberofRooms && this.colour.equals(otherobj.colour)){
                equality = true;
            }
        }
        else 
            equality = false;
        return equality && super.equals(other); /* Returns true if data fields and data fields of ancestor class of objects are equal, otherwise false. */
    }
    /**
     * Overrides toString method. Calls ancestor method.
     * @return Returns House object as String.
     */
    @Override
    public String toString(){
        return super.toString();
    }
    
}
