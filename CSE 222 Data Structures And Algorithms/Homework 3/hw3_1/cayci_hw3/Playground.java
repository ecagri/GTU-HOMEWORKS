package cayci_hw3;

/**
 * Does not keeps type-specific data fields for Playground but it is not BUILDING so, it has different class.
 * @author cagri cayci
 */
public class Playground extends Structure{
    /**
     * Two parameter constructor.
     * @param _position Takes position of the Playground as integer.
     * @param _lenght Takes lenght of the Playground as integer.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public Playground(int _position, int _lenght) throws OUTOFRANGEEXCEPTION{
        super(_position, _lenght, 5);
    }

    /**
     * Overrides toString method. Calls toString method of ancestor class.
     * @return Returns Playground object as String.
     */
    @Override
    public String toString(){
        return super.toString();
    }
}
