package cayci_hw1;

/**
 * Ancestor class for BUILDING and PLAYGROUND.
 * @author cagri cayci
 */
public class STRUCTURE{
    /**
     * Keeps the position of the STRUCTURE as integer.
     */
    private int position;
    /**
     * Keeps the lenght of the STRUCTURE as integer.
     */
    private int lenght;
    /**
     * Keeps the height of the STRUCTURE as integer.
     */
    private int height;
    
    /**
     * Three parameter constructor.
     * @param _position Takes position of the STRUCTURE as integer.
     * @param _lenght Takes lenght of the STRUCTURE as integer.
     * @param _height Takes height of the STRUCTURE as integer.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public STRUCTURE(int _position, int _lenght, int _height) throws OUTOFRANGEEXCEPTION{
        setLenght(_lenght); /* Sets lenght of the STRUCTURE calling setLenght method. */
        setPosition(_position); /* Sets position of the STRUCTURE calling setPosition method. */
        setHeight(_height); /* Sets height of the STRUCTURE calling setHeight method. */
    }
    
    /**
     * Set lenght of the STRUCTURE. 
     * @param _lenght Takes lenght of the STRUCTURE as integer.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public void setLenght(int _lenght) throws OUTOFRANGEEXCEPTION{
        if(_lenght > 0) /* If _lenght is bigger than 0, assigns it into lenght. */
            lenght = _lenght;
        else /* Otherwise throw an exception. */
            throw new OUTOFRANGEEXCEPTION(_lenght);
    }
    
    /**
     * Set position of the STRUCTURE.
     * @param _position Takes position of the STRUCTURE as integer.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public void setPosition(int _position) throws OUTOFRANGEEXCEPTION{
        if(0 <= _position){ /* If _position is bigger or equals to 0, assigns it into position. */
            position = _position;
        }
        else /* Otherwise throw an exception. */
            throw new OUTOFRANGEEXCEPTION(_position);
    }
    
    /** 
     * Set height of the STRUCTURE.
     * @param _height Takes height of the STRUCTURE as integer.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public void setHeight(int _height) throws OUTOFRANGEEXCEPTION{
        if(_height > 0) /* If _height is bigger than 0, assigns it into height. */
            height = _height;
        else /* Otherwise throw an exception. */
            throw new OUTOFRANGEEXCEPTION(_height);
    }
    
    /**
     * Get minimum position of the STRUCTURE.
     * @return Returns position of the STRUCTURE as integer.
     */
    public int getMinPosition(){
        return position;
    }
    
    /**
     * Get maximum position of the STRUCTURE.
     * @return Returns position + lenght of the STRUCTURE as integer.
     */
    public int getMaxPosition(){
        return position + lenght;
    }
    /**
     * Get lenght of the STRUCTURE.
     * @return Returns lenght of the STRUCTURE as integer.
     */
    public int getLenght(){
        return lenght;
    }
    
    /**
     * Get height of the STRUCTURE.
     * @return Returns height of the STRUCTURE as integer.
     */
    public int getHeight(){
        return height;
    }
    
    /**
     * Prints the fields of STRUCTURE object.
     */
    public void getInfo(){
        System.out.println("Position is: " + getMinPosition() + "\nLenght is: " + getLenght() + "\nHeight is: " + getHeight());
    }
    
    /**
     * Overrides hashCode method.
     * @return Returns hashCode of the STRUCTURE as integer.
     */
    @Override
    public int hashCode(){
        return 7 * (position + 1) * (lenght) * (height);
    }
    
    /**
     * Overrides equals method.
     * @param other Gets other object as Object class.
     * @return Returns true if two objects are equals, otherwise false.
     */
    public boolean equals(Object other){
        boolean equality = false; 
        if(this.getClass() == other.getClass()){ /* If their class equals, continue. */
            STRUCTURE otherobj = (STRUCTURE) other; 
            if(this.height == otherobj.height && this.lenght == otherobj.lenght && this.position == otherobj.position){ /* Compares their data field. */
                equality = true;
            }
        }
        else 
            equality = false;
        return equality;
    }
    
    /**
     * Overrides toString method.
     * @return Returns STRUCTURE object as String.
     */
    @Override
    public String toString(){
        return "The lenght of the structure is: " + lenght;
    }
}
