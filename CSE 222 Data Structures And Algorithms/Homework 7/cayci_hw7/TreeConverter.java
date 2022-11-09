package cayci_hw7;

import java.util.Arrays;

/**
 * A class to create a Binary Search Tree which has the same structure with a Binary Tree.
 */
public class TreeConverter{
    /**
     * Creates a Binary Search Tree which has the same structure with a Binary Tree. Fills the Binary Search Tree with data on the array.
     * @param binaryTree Gets the Binary Tree.
     * @param array Gets the array.
     * @return Returns the Binary Search Tree.
     * @param <T> To make method generics.
     */
    public static <T extends Comparable<T>> BinarySearchTree<T> toBinarySearchTree(BinaryTree<T> binaryTree, T[] array){
        Arrays.sort(array); /* Sorts the array. */
        BinarySearchTree<T> binarySearchTree = new BinarySearchTree<T>(); /* Creates an empty Binary Search Tree. */
        return toBinarySearchTree(binaryTree, array , binarySearchTree, 0, 0,  array.length - 1);
    }

    /**
     * A helper method to create a Binary Search Tree which has the same structure with a Binary Tree.
     * @param binaryTree Gets the Binary Tree.
     * @param sortedArray Gets the array in sorted.
     * @param binarySearchTree Keeps Binary Search Tree.
     * @param index Keeps the current index.
     * @param currentMin Keeps the index of the current minimum element.
     * @param currentMax Keeps the index of the current maximum element.
     * @return Returns the Binary Search Tree.
     * @param <T> To make method generics.
     */
    private static <T extends Comparable<T>> BinarySearchTree<T> toBinarySearchTree(BinaryTree<T> binaryTree, T[] sortedArray, BinarySearchTree<T> binarySearchTree, int index, int currentMin, int currentMax){
        if(2 * index + 2 >= binaryTree.size()){ /* If the children of the node violates the boundaries of the binary tree, it has no child, adds it to the Binary Search tree and returns the Binary Search Tree. */
            binarySearchTree.add(sortedArray[currentMin]);
            return binarySearchTree;
        }

        int rightChildNumber = binaryTree.findRightChildNumber(index); /* Finds number of right child. */
        int leftChildNumber = binaryTree.findLeftChildNumber(index); /* Finds number of left child. */

        if(rightChildNumber == 0 && leftChildNumber != 0){ /* If the node has only left child, adds the current max element to the Binary Search Tree and recursively calls the method for left child.*/
            binarySearchTree.add(sortedArray[currentMax]);
            binarySearchTree = toBinarySearchTree(binaryTree, sortedArray, binarySearchTree, 2 * index + 1, currentMin, currentMax - 1);
        }
        else if(leftChildNumber == 0){ /* If the node does not have left child, adds the current min element to the Binary Search Tree. */
            binarySearchTree.add(sortedArray[currentMin]);

            if(rightChildNumber != 0) /* If the node has right child, recursively call the method for right child. */
                binarySearchTree = toBinarySearchTree(binaryTree, sortedArray, binarySearchTree, 2 * index + 2, currentMin + 1, currentMax);
        }
        else{ /* If the node does not have both right and left child, continues. */
            binarySearchTree.add(sortedArray[currentMin + leftChildNumber]); /* Adds the element at position current min + left child number. */
            /* Splits the array into two. The first part starts from current min position and goes up to number of left child. */
            binarySearchTree = toBinarySearchTree(binaryTree, sortedArray, binarySearchTree, 2 * index + 1, currentMin, currentMin + leftChildNumber - 1);
            /* Splits the array into two. The first part starts from current min position + number of left child and goes until current max position. */
            binarySearchTree = toBinarySearchTree(binaryTree, sortedArray, binarySearchTree, 2 * index + 2, currentMin + leftChildNumber + 1, currentMax);
        }
        return binarySearchTree;
    }

}
