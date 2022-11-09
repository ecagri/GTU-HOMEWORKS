package cayci_hw1;

/**
 * Ancestor class for HOUSE, MARKET and OFFICE.
 * @author cagri cayci
 */
public class BUILDING extends STRUCTURE{
    /**
     * Keeps owner of the BUILDING as String.
     */
    private String owner;
    
    /**
     * Four parameter constructor.
     * @param _position Takes position of the BUILDING as integer.
     * @param _lenght Takes lenght of the BUILDING as integer.
     * @param _height Takes height of the BUILDING as integer
     * @param _owner Takes owner of the BUILDING as String.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public BUILDING(int _position, int _lenght, int _height, String _owner) throws OUTOFRANGEEXCEPTION{
        super(_position, _lenght, _height); /* Calls constructor of ancestor method. */
        owner = _owner;
    }
    
    /**
     * Prints the fields of the BUILDING and fields of the ancestor class of the BUILDING.
     */
    @Override
    public void getInfo(){
        super.getInfo(); /* Calls getInfo method of ancestor class. */
        System.out.println("Owner is: " + owner);
    }
    
    /**
     * Overrides hashCode method.
     * @return Returns hashcode of the BUILDING as integer.
     */
    @Override
    public int hashCode(){
        return 7 * (owner.hashCode()) * super.hashCode();
    }
    
    /**
     * Overrides equals method.
     * @param other Gets other objects as Object class.
     * @return Returns true if two objects equals, otherwise false.
     */
    @Override
    public boolean equals(Object other){
        boolean equality = false;
        if(this.getClass() == other.getClass()){ /* If their class are equal, continue. */
            BUILDING otherobj = (BUILDING) other;
            if(this.owner.equals(otherobj.owner)){
                equality = true;
            }
        }
        else 
            equality = false;
        return equality && super.equals(other); /* Returns true if data fields and data fields of ancestor class of objects are equal, otherwise false. */
    }
    
    /**
     * Overrides toString method.
     * @return Returns BUILDING object as a String.
     */
    @Override
    public String toString(){
        return "The owner of this building is: " + owner;
    }
}
