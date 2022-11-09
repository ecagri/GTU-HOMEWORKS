package cayci_hw5;

/**
 * A class to test the methods of BinarySearchTree.
 * @author cagri cayci
 */
public class Driver {
    /**
     * Main method of the class.
     * @param args Takes arguments from user as String.
     */
    public static void main(String[] args){
        BinarySearchTree<Integer> test = new BinarySearchTree<Integer>();
        test.add(5);
        System.out.println("Adding 5 to an empty BinarySearchTree.");
        System.out.println(test.toString());
        test.add(7);
        System.out.println("Adding 7 to the BinarySearchTree.");
        System.out.println(test.toString());
        test.add(3);
        System.out.println("Adding 3 to the BinarySearchTree.");
        System.out.println(test.toString());
        test.add(2);
        System.out.println("Adding 2 to the BinarySearchTree.");
        System.out.println(test.toString());
        test.add(1);
        System.out.println("Adding 8 to the BinarySearchTree.");
        System.out.println(test.toString());
        test.add(8);
        System.out.println("Adding 1 to the BinarySearchTree.");
        System.out.println(test.toString());
        System.out.println("Does tree contain 2(with contains method): " + test.contains(2));
        System.out.println("Does tree contain 9(with contains method): " + test.contains(9));
        System.out.print("Does tree contain 3(with find method): ");
        boolean equality = (test.find(3) != null);
        System.out.println(equality);
        System.out.print("Does tree contain 15(with find method): ");
        equality = (test.find(15) != null);
        System.out.println(equality);   
        System.out.println("Removing 1 from the BinarySearchTree(A leaf of the tree)");
        test.remove(1);
        System.out.println(test.toString());
        System.out.println("Removing 5 from the BinarySearchTree(Root of the tree)");
        test.remove(5);
        System.out.println(test.toString());
        System.out.println("Removing 11 from the BinarySearchTree(Is not on the tree)");
        test.remove(11);   
        System.out.println(test.toString()); 
        System.out.println("Removing 2 from the BinarySearchTree(To test free method.)");
        test.remove(2);   
        System.out.println(test.toString());
        System.out.println("Deleting 8 from the BinarySearchTree");
        int returnValue = test.delete(8);   
        System.out.println(test.toString());
        System.out.println(returnValue + " is deleted.");
        System.out.println("Deleting 17 from the BinarySearchTree");  
        System.out.println(test.delete(17) + " is deleted.");
        System.out.println(test.toString());
    }
}
