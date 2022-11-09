package cayci_hw5;

/**
 * A class to see exception.
 * @author cagri cayci
 */
public class TreeHasNotCreatedYetException extends Exception{
    /**
     * Gives a warning.
     */
    public TreeHasNotCreatedYetException(){
        System.out.println("Tree has not created yet. So, tree is neither leaf or internal node.");
    }
}
