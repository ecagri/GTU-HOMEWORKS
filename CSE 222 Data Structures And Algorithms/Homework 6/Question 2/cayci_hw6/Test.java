package cayci_hw6;

/**
 * To test some sorting algorithms.
 * @author cagri cayci.
 */
public class Test {
    /**
     * Main method for Test Class.
     * @param args Takes args as String array parameter.
     */
    public static void main(String[] args){
        Integer[] array = {506, 563, 731, 549, 776, 843, 456, 286, 346, 882, 318, 87,
                       381, 700, 304, 749, 738, 210, 620, 812, 681, 479, 147, 682,
                       815, 635, 926, 358, 413, 155, 869, 850, 298, 297, 332, 395,
                       301, 211, 495, 804, 131, 369, 962, 236, 791, 3, 466, 383, 195, 44};
        
        Double[] array2 = {7.7, 11.7, 80.9, 12.8, 28.4, 52.7, 88.8, 40.0, 96.9, 71.3, 5.7, 9.1,
                           7.3, 15.2, 69.1, 43.4, 30.0, 17.2, 10.5, 99.5, 72.3, 84.6, 51.1, 1.2,
                           83.7, 19.9, 17.9, 94.0, 70.6, 84.5, 63.2, 33.8, 53.7, 8.2, 62.5, 24.4,
                           36.9, 39.0, 59.8, 4.0, 80.6, 37.1, 72.9, 71.1, 24.4, 45.9, 64.4, 18.9, 5.6, 84.5};
        
        Character[] array3 = {'c', 'e', 'g', 'l', 'm', 'r', 'a', 'z', 'u', 'd', 'o'};
                
        testMerge(array);
        
        testQuick(array2);
        
        testNew(array3);
       
    }
    
    /**
     * Testing merge sort.
     * @param <T> To make method generics.
     * @param array Takes array to sort.
     */
    @SuppressWarnings("unchecked")
    public static <T> void testMerge(T[] array){
        array = (T[]) SortingAlgorithms.MergeSort((Comparable[]) array);
        printArray(array);
    }
    
    /**
     * Testing quick sort.
     * @param <T> To make method generics.
     * @param array Takes array to sort.
     */
    @SuppressWarnings("unchecked")
    public static <T> void testQuick(T[] array){
        array = (T[]) SortingAlgorithms.QuickSort((Comparable[]) array);
        printArray(array);
    }
    
    /**
     * Testing new sort.
     * @param <T> To make method generics.
     * @param array Takes array to sort.
     */
    @SuppressWarnings("unchecked")
    public static <T> void testNew(T[] array){
        array = (T[]) SortingAlgorithms.new_sort((Comparable[]) array);
        printArray(array);
    }
    
    /**
     * Prints an array.
     * @param <T> To make method generics.
     * @param array Takes array to print.
     */
    public static <T> void printArray(T[] array){
        System.out.print("{");
        for(int i = 0; i < array.length; i++){
            System.out.print(array[i]);
            if(i != array.length - 1)
                System.out.print(", ");
        }
        System.out.println("}");
    }
}
