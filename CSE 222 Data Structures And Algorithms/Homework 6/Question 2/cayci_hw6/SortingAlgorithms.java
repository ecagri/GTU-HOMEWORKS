package cayci_hw6;

/**
 * A class which implements some sorting algorithms.
 * @author cagri cayci
 */
public class SortingAlgorithms{
    /**
     * Sorts the array with merge sort algorithm.
     * @param <T> To make method generics
     * @param array Takes an array to sort.
     * @return Returns the array sorted.
     */
    public static <T extends Comparable<T>> T[] MergeSort(T[] array){
        return (array == null)? null: MergeSort(array, 0, array.length);
    }
    
    /**
     * Helps for merge sorting.
     * @param <T> To make method generics.
     * @param array Takes an array to sort.
     * @param beginning Beginning index of sorting.
     * @param end End index of sorting.
     * @return Returns the array sorted.
     */
    private static <T extends Comparable<T>> T[] MergeSort(T[] array, int beginning, int end){
        int size = end - beginning;
        
        if(size == 1)
            return array;

        int middle = (beginning + end + 1) / 2;
        
        array = MergeSort(array, beginning, middle);
        
        array = MergeSort(array, middle, end); 
        
        array = merge(array, beginning, middle, end);
        
        return array;
    }
    
    /**
     * Merge two array to help merge sorting.
     * @param <T> To make method generics.
     * @param array Takes an array to sort.
     * @param beginning Beginning index of first array.
     * @param middle End index of first array, beginning index of second array.
     * @param end End index of second array.
     * @return Returns merging version of two array.
     */
    @SuppressWarnings("unchecked")
    private static <T extends Comparable<T>> T[] merge(T[] array, int beginning, int middle, int end){
        T[] firstHalf = (T[]) new Comparable[middle - beginning];
        
        T[] secondHalf = (T[]) new Comparable[end - middle];       
        
        int firstIndex = 0, secondIndex = 0, comparision;
        
        for(int index = 0; index + beginning < middle; index++)
            firstHalf[index] = array[index + beginning];

        for(int index = 0; index + middle < end; index++)
            secondHalf[index] = array[index + middle];

        for(int index = beginning; index < end; index++){
            if(firstIndex != firstHalf.length && secondIndex != secondHalf.length)
                comparision =  ((T) firstHalf[firstIndex]).compareTo((T) secondHalf[secondIndex]);  
            
            else if(firstIndex == firstHalf.length)
                comparision = 1;
            
            else
                comparision = -1;
            
            if(comparision <= 0){
                array[index] = (T) firstHalf[(firstIndex)];
                
                firstIndex++;
            }
            else if(comparision > 0){
                array[index] = (T) secondHalf[(secondIndex)];
                
                secondIndex++;
            }
        }
        return array;
    }
    
    /**
     * Sorts the array with quick sort algorithm.
     * @param <T> To make method generics.
     * @param array Takes an array to sort.
     * @return Returns the array sorted.
     */
    public static <T extends Comparable<T>> T[] QuickSort(T[] array){
        return (array == null)? null : QuickSort(array, array.length);
    }
    
    
    /**
     * Helps to sort an array with quick sort algorithm.
     * @param <T> To make method generics.
     * @param array Takes an array to sort.
     * @param length Takes length of the array.
     * @return Returns the array sorted.
     */
    @SuppressWarnings("unchecked")
    private static <T extends Comparable<T>> T[] QuickSort(T[] array, int length){
        if(length < 2)
            return array;
        
        int firstIndex = 0, secondIndex = 0;
        
        T[] rightSubArray = (T[]) new Comparable[length - 1];
        
        T[] leftSubArray = (T[]) new Comparable[length - 1];
        
        T pivot = array[0];
        
        for(int i = 1; i < length; i++){
            int comparision = pivot.compareTo(array[i]);
            
            if(comparision >= 0){
                leftSubArray[firstIndex] = array[i];
                firstIndex++;
            }
            else{
                rightSubArray[secondIndex] = array[i];
                secondIndex++;
            }
        }
        
        leftSubArray = QuickSort(leftSubArray, firstIndex);
        
        rightSubArray = QuickSort(rightSubArray, secondIndex);
        
        for(int index = 0; index < firstIndex; index++)
            array[index] = leftSubArray[index];
        
        array[firstIndex] = pivot;
        
        for(int index = 0; index < secondIndex; index++)
            array[firstIndex + index + 1] = rightSubArray[index];
        
        return array;
        
    }
    
    /**
     * Sorts an array with new sort algorithm.
     * @param <T> To make method generics.
     * @param array Takes an array to sort.
     * @return Returns the array sorted.
     */
    public static <T extends Comparable<T>> T[] new_sort(T[] array){
        return (array == null) ? null : new_sort(array, 0, array.length - 1);
    }
    
    /**
     * Helps sorting an array with new sort algorithm.
     * @param <T> To make method generics.
     * @param array Takes an array to sort.
     * @param head Takes head of the array.
     * @param tail Takes tail of the array.
     * @return Returns the array sorted.
     */
    private static <T extends Comparable<T>> T[] new_sort(T[] array, int head, int tail){
        if(head > tail)
            return array;
        else{
            int[] minMax = min_max_finder(array, head, tail);
            
            boolean indexCoincidence = false;
            
            if(head == minMax[1])
                indexCoincidence = true;
            
            array = swap(array, head, minMax[0]);
            
            array = (indexCoincidence == false) ? swap(array, minMax[1], tail) : swap(array, minMax[0], tail);
            
            return new_sort(array, head + 1, tail - 1);
        }
    }
    
    /**
     * Swaps two elements values.
     * @param <T> To make method generics.
     * @param array Takes the array the elements in it.
     * @param first Takes index of first element.
     * @param second Takes index of second element.
     * @return Returns the changed version of array.
     */
    private static <T extends Comparable<T>> T[] swap(T[] array, int first, int second){
        T value;
        
        value = array[first];
        
        array[first] = array[second];
        
        array[second] = value;
        
        return array;
    }
    
    /**
     * Finds max and min value in array.
     * @param <T> To make methods generics.
     * @param array Takes the array to find min and max elements.
     * @param head Takes the head index of the array.
     * @param tail Takes the tail index of the array.
     * @return Returns the indexes of min and max values.
     */
    private static <T extends Comparable<T>> int[] min_max_finder(T[] array, int head, int tail){
        int[] minMax = {head, head};
        
        return min_max_finder(array, head, tail, minMax);
    }

    /**
     * Finds max and min value in array.
     * @param <T> To make methods generics.
     * @param array Takes the array to find min and max elements.
     * @param head Takes the head index of the array.
     * @param tail Takes the tail index of the array.
     * @param minMax Indexes of min and max values. 
     * @return Returns the indexes of min and max values.
     * @return 
     */
    private static <T extends Comparable<T>> int[] min_max_finder(T[] array, int head, int tail, int[] minMax){
        if(head >= tail)
            return minMax;
        
        int comparision = array[minMax[0]].compareTo(array[head + 1]);
        
        int comparision2 = array[minMax[1]].compareTo(array[head + 1]);
        
        if(comparision > 0)
            minMax[0] = head + 1;
        
        if(comparision2 < 0)
            minMax[1] = head + 1;
        
        return min_max_finder(array, head + 1, tail, minMax);

    }
}
