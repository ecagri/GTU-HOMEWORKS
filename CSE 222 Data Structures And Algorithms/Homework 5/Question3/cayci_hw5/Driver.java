package cayci_hw5;

/**
 * A class to test BinaryHeap methods.
 * @author cagri cayci
 */
public class Driver {
    /**
     * Main method for Driver class.
     * @param args Takes arguments from user as a String.
     */
    public static void main(String[] args){
        BinaryHeap<Integer> heap = new BinaryHeap<Integer>();
        System.out.println("BinaryHeap: \n" + heap);
        System.out.println("Adding an element with 10 priority to empty BinaryHeap...");
        heap.add(99, 10);
        System.out.println("BinaryHeap: \n" + heap);
        try{
            System.out.println("Is root leaf: " + heap.isLeaf());
        }
        catch(TreeHasNotCreatedYetException e){
        }
        System.out.println("Adding an element with 7 priority to the BinaryHeap (low priority test)...");
        heap.add(88, 7);
        System.out.println("BinaryHeap: \n" + heap);
        try{
            System.out.println("Is root leaf: " + heap.isLeaf());
        }
        catch(TreeHasNotCreatedYetException e){
        }
        System.out.println("Adding an element with 3 priority to the BinaryHeap (low priority test)...");
        heap.add(77, 3);
        System.out.println("BinaryHeap: \n" + heap);
        System.out.println("Adding an element with 15 priority to the BinaryHeap (high priority test)...");
        heap.add(66, 15);
        System.out.println("BinaryHeap: \n" + heap);
        System.out.println("Adding an element with 24 priority to the BinaryHeap (high priority test)...");
        heap.add(55, 24);
        System.out.println("BinaryHeap: \n" + heap);
        System.out.println("Adding an element with 1 priority to the BinaryHeap (low priority test)...");
        heap.add(44, 1);
        System.out.println("BinaryHeap: \n" + heap);
        System.out.println("Changing priority(1) of the node which has 44 as data to 27.");
        heap.setPriority(44, 27);
        System.out.println("BinaryHeap: \n" + heap);
        BinaryHeap<Integer> heap2 = new BinaryHeap<Integer>();
        System.out.println("BinaryHeap2: \n" + heap2);
        System.out.println("Data of the first element of the heap is: " + heap2.getData());
        System.out.println("Adding an element with 9 priority to the BinaryHeap2...");
        heap2.add(33, 9);
        System.out.println("BinaryHeap2: \n" + heap2);
        System.out.println("Data of the first element of the heap is: " + heap2.getData());
        System.out.println("Adding an element with 4 priority to the BinaryHeap2");
        heap2.add(22, 4);
        System.out.println("BinaryHeap2: \n" + heap2);
        System.out.println("Adding an element with 13 priority to the BinaryHeap2");
        heap2.add(11, 13);
        System.out.println("BinaryHeap2: \n" + heap2);
        System.out.println("Merging of BinaryHeap and BinaryHeap2 is: \n" + heap2.mergeHeapWith(heap));
    }
}
