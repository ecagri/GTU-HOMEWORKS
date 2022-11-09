package cayci_hw4;

/**
 * A class with recursive functions for some problems.
 * @author cagri cayci
 */
public class Questions{
    /**
     * Finds nth occurence of a String in a String.
     * @param main Takes main String which a String is searched in it.
     * @param key Takes key String which will be searched.
     * @param mainIndex Keeps track of the index of the main String.
     * @param keyIndex Keeps track of the index of the key String.
     * @param occurence Keeps track of the number of occurence.
     * @return Return the index of the nth occurence of the key String as integer.
     */
    public static int indexOfOccurence(String main, String key, int mainIndex, int keyIndex, int occurence){
        if(occurence == 0) /* If the occurence reach 0, return mainIndex - length of the key. */
            return mainIndex - key.length() + 1;
        if(keyIndex == key.length()) /* If keyIndex reached end of the key String, calls the function with assigning keyIndex to 0, and occurence to occurence - 1. */
            return indexOfOccurence(main, key, mainIndex - key.length() + 1, 0, occurence - 1);
        if(mainIndex == main.length()) /* If mainIndex reached end of the main String, returns -1. */
            return -1;
        if(main.charAt(mainIndex) == key.charAt(keyIndex)) /* Compares characters, if they are equal, calls the function again to compares next characters. */
            return indexOfOccurence(main, key, mainIndex + 1, keyIndex + 1, occurence);
        else /* If characters are not equal, calls the function to start comparing characters from begining of the key String. */
            return indexOfOccurence(main, key, mainIndex + 1, 0, occurence);
    }
    
    
    /**
     * Overloading version of indexOfOccurence function to prevent the user from changing the mainIndex and keyIndex parameters.
     * @param main Takes main String which a String is searched in it.
     * @param key Takes key String which will be searched.
     * @param occurence Keeps track of the number of occurence.
     * @return Return the index of the nth occurence of the key String as integer.
     */
    public static int indexOfOccurence(String main, String key, int occurence){
        if(main == null || key == null || main.length() == 0 || key.length() == 0 || occurence < 0) /* If Strings are null or their length is 0 or occurence is lower than 0, returns -1. */
            return -1;
        return indexOfOccurence(main, key, 0, 0, occurence);
    }
    
    /**
     * Finds index of an element in a sorted array. If array does not contain the element, returns the index which the element must be.
     * @param array Takes an integer array which an element is searched in it.
     * @param number Takes the number which will be searched.
     * @param first Takes first index.
     * @param last Takes last index.
     * @return Returns the index of element.
     */
    public static int elementsInBetween(int[] array, int number, int first, int last){
        int middle = (last + first) / 2; /* Find middle index of the array. */
        if(first >= last) /* If there is 1 element to compare the number, continue. */
            return (array[middle] >= number) ? middle : middle + 1; /* Compares middle element with number, if the middle element is bigger or equal to number, return middle, otherwise middle + 1*/
        if(array[middle] == number) /* Compares middle element with number. If they are equal return middle. */
            return middle;
        else if(array[middle] > number) /* If middle element is bigger than number, search the number from first to the middle -1 index. */
            return elementsInBetween(array, number, first, middle - 1);
        else /* If middle element is less than number, search the number from middle + 1 to the last index. */
            return elementsInBetween(array, number, middle + 1, last);
    }
    
    /**
     * Finds the number of elements in between two numbers in a sorted array.
     * @param array Takes an integer array which an element is searched in it.
     * @param number1 Takes the first border as integer.
     * @param number2 Takes the second border as integer.
     * @return Returns the number of element in between two numbers.
     */
    public static int elementsInBetween(int[] array, int number1, int number2){
        if(array == null) /* If array is null, return -1. */
            return -1;
        if(array.length == 0)
            return 0;
        int numberOfItems = elementsInBetween(array, number1, 0, array.length - 1) - elementsInBetween(array, number2, 0, array.length - 1); /* Finds both numbers indexes, and substract from each other. */
        return (numberOfItems > 0) ? numberOfItems : -numberOfItems; /* If numberOfItems is bigger than 0, return numberOfItems, otherwise return -numberOfItems. */
    }


    /**
     * Searches the subarrays which the sum of all elements of it is equal to given value of an array.
     * @param array Takes an integer array.
     * @param contigousSum Takes an integer number.
     */
    public static void equalSumSubarray(int[] array, int contigousSum){
        if(array == null) /* If array is null, return -1. */
            return;
        StringBuilder string = new StringBuilder("{");
        equalSumSubarray(array, contigousSum, 0, 0, 0, string); 
    }
    
    /**
     * Searches the subarrays which the sum of all elements of it is equal to given value of an array.
     * @param array Takes an integer array.
     * @param contigousSum Takes an integer number.
     * @param sum Keeps track of current subarray sum.
     * @param beginning Beginning index of subarray.
     * @param end End index of subarray.
     * @param string Helps the print the subarrays. 
     */
    public static void equalSumSubarray(int[] array, int contigousSum, int sum, int beginning, int end, StringBuilder string){
        if(beginning == array.length) /* If beginning index reached the end of the array, end the function. */
            return;
        if(end == array.length){ /* If the end index of subarray reached the end of the array, calls the function for different subarray. */
            string = new StringBuilder("{");
            equalSumSubarray(array, contigousSum, 0, beginning + 1, beginning + 1, string);
            return;
        }
        sum += array[end]; /* Adds the element to sum. */
        string.append(array[end]);
        if(sum == contigousSum){ /* If sum is equals to contigousSum, print subarray and calls the function for current subarray and next element. */
            System.out.println(string.toString() + "}");
            equalSumSubarray(array, contigousSum, sum, beginning, end + 1, string);
        }
        else{  /* If sum is less or bigger than contigousSum, continue to current subarray. */
            string.append(",");
            equalSumSubarray(array, contigousSum, sum, beginning, end + 1, string);
        }
    }
}
