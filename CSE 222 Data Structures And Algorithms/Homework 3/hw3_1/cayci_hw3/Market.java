package cayci_hw3;


/**
 * Keeps type-specific data fields for Market.
 * @author cagri cayci
 */
public class Market extends Building{
    /**
     * Keeps opening time of the Market as double.
     */
    private double openingTime;
    /**
     * Keeps closing time of the Market as double.
     */
    private double closingTime;
    
    /**
     * Six parameter constructor.
     * @param _position Takes position of the Market as integer.
     * @param _lenght Takes lenght of the Market as integer.
     * @param _height Takes height of the Market as integer.
     * @param _owner Takes owner of the Market as String.
     * @param _openingTime Takes opening time of the Market as double.
     * @param _closingTime Takes closing time of the Market as double.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public Market(int _position, int _lenght, int _height, String _owner, double _openingTime, double _closingTime) throws OUTOFRANGEEXCEPTION{
        super(_position, _lenght, _height, _owner); /* Calls constructor of ancestor class. */
        setOpeningTime(_openingTime);
        setClosingTime(_closingTime);
    }
    
    /**
     * Sets opening time of the Market.
     * @param _openingTime Takes opening time of the Market as double.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public void setOpeningTime(double _openingTime) throws OUTOFRANGEEXCEPTION{
        if(0 < _openingTime && _openingTime < 24) /* If _openingTime is in between 0-24, assigns it into openingTime. */
            openingTime = _openingTime;
        else /* Otherwise throw an exception. */
            throw new OUTOFRANGEEXCEPTION(_openingTime);
    }
    
    /**
     * Sets closing time of the Market.
     * @param _closingTime Takes closing time of the Market as double.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public void setClosingTime(double _closingTime) throws OUTOFRANGEEXCEPTION{
        if(0 < _closingTime && _closingTime < 24) /* If _closingTime is in between 0-24, assigns it into closingTime. */
            closingTime = _closingTime;
        else /* Otherwise throw an exception. */
            throw new OUTOFRANGEEXCEPTION(_closingTime);
    }

    /**
     *  Prints fields of Market and fields of ancestor classes of Market. 
     */
    @Override
    public void getInfo(){
        super.getInfo(); /* Calls getInfo method of ancestor class. */
        System.out.println("Opening time is: " + openingTime + "\nClosing time is: " + closingTime);
    }
    
    /**
     * Overrides hashCode method.
     * @return Returns hashCode of the Market as integer.
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
            Market otherobj = (Market) other;
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
     * @return Returns Market object as String.
     */
    @Override
    public String toString(){
        return "The closing time of this market is: " + closingTime;
    }
    
}
