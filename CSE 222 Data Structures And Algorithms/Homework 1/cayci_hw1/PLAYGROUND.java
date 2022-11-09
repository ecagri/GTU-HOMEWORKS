package cayci_hw1;

/**
 * Does not keeps type-specific data fields for PLAYGROUND but it is not BUILDING so, it has different class.
 * @author cagri cayci
 */
public class PLAYGROUND extends STRUCTURE{
    /**
     * Two parameter constructor.
     * @param _position Takes position of the PLAYGROUND as integer.
     * @param _lenght Takes lenght of the PLAYGROUND as integer.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public PLAYGROUND(int _position, int _lenght) throws OUTOFRANGEEXCEPTION{
        super(_position, _lenght, 5);
    }

    /**
     * Overrides toString method. Calls toString method of ancestor class.
     * @return Returns PLAYGROUND object as String.
     */
    @Override
    public String toString(){
        return super.toString();
    }
}
