package cayci_hw1;


/**
 * A class for exceptions.
 * @author cagri cayci
 */
public class OUTOFRANGEEXCEPTION extends Exception{
    /**
     * One parameter constructor.
     * @param variable Gets a variable as Object.
     */
    public OUTOFRANGEEXCEPTION(Object variable){
        System.out.println("The variable cannot be " + variable + ".");
    }
}
