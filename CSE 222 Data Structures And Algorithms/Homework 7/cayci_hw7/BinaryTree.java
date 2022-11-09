package cayci_hw7;

/**
 * A class to keeps elements in Binary Tree format.
 * @param <T> To make class generics.
 */
public class BinaryTree<T>{
    /**
     * Keeps elements of the Binary Tree.
     */
    private T[] array;

    /**
     * One parameter constructor.
     * @param array Takes an array as parameter and fills the Binary Tree.
     */
    @SuppressWarnings("unchecked")
    public BinaryTree(T[] array){
        this.array = (T[]) new Object[array.length];
        for(int i = 0; i < array.length; i++){
            this.array[i] = array[i];
        }
    }

    /**
     * Finds number of right child of a node.
     * @param index Takes the index of the node.
     * @return Returns the number of right child.
     */
    public int findRightChildNumber(int index){
        if(get(2 * index + 2) == null)
            return 0;
        return getChildNumber(2 * index + 2, 1);
    }
    /**
     * Finds number of left child of a node.
     * @param index Takes the index of the node.
     * @return Returns the number of left child.
     */
    public int findLeftChildNumber(int index){
        if(get(2 * index + 1) == null)
            return 0;
        return getChildNumber(2 * index + 1, 1);
    }

    /**
     * Finds the number of children of a node.
     * @param index Takes the index of the node.
     * @param childNumber Keeps child number.
     * @return Returns the number of children of a node.
     */
    public int getChildNumber(int index, int childNumber){
        if(2 * index + 2 >= size())
            return childNumber;
        if(get(2 * index + 1) != null){
            childNumber = getChildNumber(2 * index + 1, childNumber + 1);
        }
        if(get(2 * index + 2) != null){
            childNumber = getChildNumber(2 * index + 2, childNumber + 1);
        }
        return childNumber;
    }

    /**
     * Finds the size of the Binary Tree.
     * @return Returns the size of the Binary Tree.
     */
    public int size(){
        return array.length;
    }

    /**
     * Gets an element of the Binary Tree with given index.
     * @param index Takes the index of the node.
     * @return Returns the element on given index.
     */
    public T get(int index){
        try{
            if(index >= array.length)
                throw new IndexOutOfBoundsException();
        }
        catch(IndexOutOfBoundsException e){
            System.out.println("The index violates boundaries.");
        }
        return array[index];
    }
}
