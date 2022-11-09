package cayci_hw6;

/**
 * Testing Time Complexities.
 * @author cagri cayci
 */
public class TimeComplexityTest{  
    /**
     * Creates 1000 integer array.
     * @param size Gets array size.
     * @return Returns 2D integer array.
     */
    public static Integer[][] createArray(int size){
        Integer[][] array = new Integer[1000][size];
        for(int i = 0; i < 1000; i++){
            for(int j = 0; j < size; j++){
                array[i][j] = (int)(Math.random() * 100);
            }
        }
        return array;
    }
    
    /**
     * Test time complexities of merge sort.
     * @param size Gets size of the array.
     */
    public static void testmerge(int size){ 
        Integer[][] array = createArray(size);
        long start = System.nanoTime();
        for(int i = 0; i < 1000; i++){
            SortingAlgorithms.MergeSort(array[i]);
        }
        long end = System.nanoTime();
        System.out.println("Sorting " + array[0].length + " size array takes " + ((end - start)/1000) + " with merge sort."); 
    }
    
    /**
     * Test time complexities of quick sort.
     * @param size Gets size of the array.
     */
    public static void testQuick(int size){
        Integer[][] array = createArray(size);

        long start = System.nanoTime();
        for(int i = 0; i < 1000; i++){
            SortingAlgorithms.QuickSort(array[i]);
        }
        long end = System.nanoTime();
        System.out.println("Sorting " + array[0].length + " size array takes " + ((end - start)/1000) + " time with quick sort."); 
    }
    
    /**
     * Test time complexities of new sort.
     * @param size Gets size of the array.
     */
    public static void testNew(int size){
        Integer[][] array = createArray(size);
        long start = System.nanoTime();
        for(int i = 0; i < 1000; i++){
            SortingAlgorithms.new_sort(array[i]);
        }
        long end = System.nanoTime();
        System.out.println("Sorting " + array[0].length + " size array takes " + ((end - start)/1000) + " time with new sort."); 
    }
}

