package cayci_hw1;


/**
 * Keeps type-specific data fields for MARKET.
 * @author cagri cayci
 */
public class MARKET extends BUILDING{
    /**
     * Keeps opening time of the MARKET as double.
     */
    private double openingTime;
    /**
     * Keeps closing time of the MARKET as double.
     */
    private double closingTime;
    
    /**
     * Six parameter constructor.
     * @param _position Takes position of the MARKET as integer.
     * @param _lenght Takes lenght of the MARKET as integer.
     * @param _height Takes height of the MARKET as integer.
     * @param _owner Takes owner of the MARKET as String.
     * @param _openingTime Takes opening time of the MARKET as double.
     * @param _closingTime Takes closing time of the MARKET as double.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public MARKET(int _position, int _lenght, int _height, String _owner, double _openingTime, double _closingTime) throws OUTOFRANGEEXCEPTION{
        super(_position, _lenght, _height, _owner); /* Calls constructor of ancestor class. */
        setOpeningTime(_openingTime);
        setClosingTime(_closingTime);
    }
    
    /**
     * Sets opening time of the MARKET.
     * @param _openingTime Takes opening time of the MARKET as double.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public void setOpeningTime(double _openingTime) throws OUTOFRANGEEXCEPTION{
        if(0 < _openingTime && _openingTime < 24) /* If _openingTime is in between 0-24, assigns it into openingTime. */
            openingTime = _openingTime;
        else /* Otherwise throw an exception. */
            throw new OUTOFRANGEEXCEPTION(_openingTime);
    }
    
    /**
     * Sets closing time of the MARKET.
     * @param _closingTime Takes closing time of the MARKET as double.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public void setClosingTime(double _closingTime) throws OUTOFRANGEEXCEPTION{
        if(0 < _closingTime && _closingTime < 24) /* If _closingTime is in between 0-24, assigns it into closingTime. */
            closingTime = _closingTime;
        else /* Otherwise throw an exception. */
            throw new OUTOFRANGEEXCEPTION(_closingTime);
    }

    /**
     *  Prints fields of MARKET and fields of ancestor classes of MARKET. 
     */
    @Override
    public void getInfo(){
        super.getInfo(); /* Calls getInfo method of ancestor class. */
        System.out.println("Opening time is: " + openingTime + "\nClosing time is: " + closingTime);
    }
    
    /**
     * Overrides hashCode method.
     * @return Returns hashCode of the MARKET as integer.
     */
    @Override
    public int hashCode(){
        return 7 * ((int)openingTime + 1) * ((int)closingTime + 1) * super.hashCode();
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
            MARKET otherobj = (MARKET) other;
            if(this.openingTime == otherobj.openingTime && this.closingTime == otherobj.closingTime){
                equality = true;
            }
        }
        else 
            equality = false;
        return equality && super.equals(other); /* Returns true if data fields and data fields of ancestor class of objects are equal, otherwise false. */
    }
    
    /**
     * Overrides toString method.
     * @return Returns MARKET object as String.
     */
    @Override
    public String toString(){
        return "The closing time of this market is: " + closingTime;
    }
    
}
