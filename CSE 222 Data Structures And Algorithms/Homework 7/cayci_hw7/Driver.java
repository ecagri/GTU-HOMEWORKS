package cayci_hw7;

import java.util.Random;

/**
 * A class to test methods.
 */
public class Driver{
    /**
     * Main method for Driver class.
     * @param args Gets args as String array from user.
     */
    public static void main(String[] args){
        testCustomSkipList();
        testToBinarySearchTreeMethod();
        testToAVLMethod();
    }

    /**
     * Test Custom Skip List class.
     */
    public static void testCustomSkipList(){
        System.out.println("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
        System.out.println("TESTING CUSTOM SKIP LIST...");

        CustomSkipList<Integer> csl = new CustomSkipList<Integer>();

        Random random = new Random();

        csl.printCustomSkipList();

        for(int i = 0; i < 30; i++){
            int element = random.nextInt(1000);
            System.out.println(element + " is adding to the list.");
            csl.add(element);
            csl.printCustomSkipList();
        }
    }

    /**
     * Tests toAVL method.
     */
    public static void testToAVLMethod(){
        System.out.println("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
        System.out.println("TESTING toAVL method...");
        System.out.println("Balance a Binary Search Tree with full of right child.");
        BinarySearchTree<Integer> bst = new BinarySearchTree<Integer>();
        for(int i = 0; i < 10; i++){
            bst.add(i);
        }
        System.out.println("Binary Search Tree before balanced: ");
        bst.printBinarySearchTree();
        System.out.println("Binary Search Tree after balanced: ");
        bst.toAVLTree(bst);
        System.out.println("******************************************************************************************************************");
        System.out.println("Balance a Binary Search Tree with full of left child.");
        BinarySearchTree<Integer> bst2 = new BinarySearchTree<Integer>();
        for(int i = 9; i > -1; i--){
            bst2.add(i);
        }
        System.out.println("Binary Search Tree before balanced: ");
        bst2.printBinarySearchTree();
        System.out.println("Binary Search Tree after balanced: ");
        bst2.toAVLTree(bst2);
        System.out.println("******************************************************************************************************************");
        System.out.println("Balance a Binary Search Tree.");
        BinarySearchTree<Integer> bst3 = new BinarySearchTree<Integer>();
        Random random = new Random();
        for(int i = 0; i < 15; i++){
            bst3.add(random.nextInt(50));
        }
        System.out.println("Binary Search Tree before balanced: ");
        bst3.printBinarySearchTree();
        System.out.println("Binary Search Tree after balanced: ");
        bst3.toAVLTree(bst3);

    }

    /**
     * Tests toBinarySearchTree method.
     */
    public static void testToBinarySearchTreeMethod(){
        System.out.println("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
        System.out.println("TESTING toBinarySearchTree method...");
        System.out.println("Create a Binary Search Tree with full of left child. Fills the Binary Search Tree with array = {3, 2, 1, 4, 6, 5}");
        Integer[] binaryTreeArray1 =
                {0,
                 0, null,
                 0, null, null, null,
                 0, null, null, null, null, null, null, null,
                 0, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null,
                 0, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null};
        Integer[] array1 = {3, 2, 1, 4, 6, 5};

        BinaryTree<Integer> binaryTree1 = new BinaryTree<Integer>(binaryTreeArray1);
        BinarySearchTree<Integer> binarySearchTree1 = TreeConverter.toBinarySearchTree(binaryTree1, array1);
        binarySearchTree1.printBinarySearchTree();
        System.out.println("******************************************************************************************************************");
        System.out.println("Create a Binary Search Tree with full of right child. Fills the Binary Search Tree with array = {3, 2, 1, 4, 6, 5}");
        Integer[] binaryTreeArray2 =
                {0,
                 null, 0,
                 null, null, null, 0,
                 null, null, null, null, null, null, null, 0,
                 null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, 0,
                 null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, 0};
        Integer[] array2 = {3, 2, 1, 4, 6, 5};

        BinaryTree<Integer> binaryTree2 = new BinaryTree<Integer>(binaryTreeArray2);
        BinarySearchTree<Integer> binarySearchTree2 = TreeConverter.toBinarySearchTree(binaryTree2, array2);
        binarySearchTree2.printBinarySearchTree();
        System.out.println("******************************************************************************************************************");
        System.out.println("Create a Binary Search Tree with this structure: ");
        System.out.println("""
                0
                __0
                ____null
                ____0
                ______0
                ________null
                ________null
                ______0
                ________null
                ________null
                __0
                ____null
                ____0
                ______null
                _____0
                ________null
                ________0
                __________null
                __________0
                ____________null
                ____________null
                """);
        System.out.println("Fills the Binary Search Tree with array = {5, 6, 2, 4, 3, 1, 7, 10, 8, 9}");
        Integer[] binaryTreeArray3 =
               {0,
                0, 0,
                null, 0, null, 0,
                null, null, 0, 0, null, null, null, 0,
                null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, 0,
                null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, null, 0};
        Integer[] array3 = {5, 6, 2, 4, 3, 1, 7, 10, 8, 9};
        BinaryTree<Integer> binaryTree3 = new BinaryTree<Integer>(binaryTreeArray3);
        BinarySearchTree<Integer> binarySearchTree3 = TreeConverter.toBinarySearchTree(binaryTree3, array3);
        binarySearchTree3.printBinarySearchTree();
        System.out.println("******************************************************************************************************************");
        System.out.println("Create a Binary Search Tree with this structure: ");
        System.out.println("""
                0
                __0
                ____0
                ______0
                ________null
                ________null
                ______null
                ____null
                __0
                ____0
                ______0
                ________null
                ________null
                ______0
                ________null
                ________null
                ____0
                ______null
                ______0
                ________null
                ________null
                """);
        System.out.println("Fills the Binary Search Tree with array = {5, 6, 2, 4, 3, 1, 7, 10, 8, 9}");
        Integer[] binaryTreeArray4 =
                {0,
                 0, 0,
                 0, null, 0, 0,
                 0, null, null, null, 0, 0, null, 0};
        Integer[] array4 = {5, 6, 2, 4, 3, 1, 7, 10, 8, 9};
        BinaryTree<Integer> binaryTree4 = new BinaryTree<Integer>(binaryTreeArray4);
        BinarySearchTree<Integer> binarySearchTree4 = TreeConverter.toBinarySearchTree(binaryTree4, array4);
        binarySearchTree4.printBinarySearchTree();

    }
}
