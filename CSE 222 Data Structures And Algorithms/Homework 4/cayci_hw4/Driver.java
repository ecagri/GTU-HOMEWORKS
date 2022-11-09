package cayci_hw4;

/**
 * Test class to test Questions methods.
 * @author cagri cayci
 */
public class Driver {
    /**
     * Test the indexOfOccurence method.
     */
    public static void Question1(){
        System.out.println("*****QUESTION 1 TESTING*****");
        String main = "CSE222 Homework 4 at 01.04.2022";
        String key = "22";
        System.out.println("Main string is: " + main);
        System.out.println("Key string is: " + key);
        System.out.println("The index of first ocurrence of 22 is: " + Questions.indexOfOccurence(main, key, 1));
        System.out.println("The index of second ocurrence of 22 is: " + Questions.indexOfOccurence(main, key, 2));
        System.out.println("The index of third ocurrence of 22 is: " + Questions.indexOfOccurence(main, key, 3));
        System.out.println("The index of fourth ocurrence of 22 is: " + Questions.indexOfOccurence(main, key, 4));
        String key2 = "56";
        System.out.println("Key string is changed to 56");
        System.out.println("The index of first ocurrence of 56 is: " + Questions.indexOfOccurence(main, key2, 1));
    }
    
    /**
     * Test the elementsInBetween method.
     */
    public static void Question2(){
        System.out.println("*****QUESTION 2 TESTING*****");
        int[] array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int[] array2 = {1, 3, 4, 5, 6, 7, 8, 9, 10};
        int[] array3 = {1, 2, 3, 4, 5, 6, 7, 8, 10};
        int[] array4 = {2, 3, 4, 5, 7, 8, 9, 10};
        System.out.println("The array is: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}");
        System.out.println("The array2 is: {1, 3, 4, 5, 6, 7, 8, 9, 10}");
        System.out.println("The array3 is: {1, 2, 3, 4, 5, 6, 7, 8, 10}");
        System.out.println("The array4 is: {2, 3, 4, 5, 7, 8, 9, 10}");
        System.out.println("The number of elements in between 3-7 in array is: " + Questions.elementsInBetween(array, 3, 7));
        System.out.println("The number of elements in between 2-7 in array2 is: " + Questions.elementsInBetween(array2, 2, 7));
        System.out.println("The number of elements in between 1-9 in array3 is: " + Questions.elementsInBetween(array3, 1, 9));
        System.out.println("The number of elements in between 0-6 in array4 is: " + Questions.elementsInBetween(array4, 0, 6));
        System.out.println("The number elements in between 11-13 in array is: " + Questions.elementsInBetween(array, 11, 13));
    }
    
    /**
     * Test the equalSumSubarray method.
     */
    public static void Question3(){
        System.out.println("*****QUESTION 3 TESTING*****");
        int[] array = {2, 2, 2, 3, 4, 5, 6};
        System.out.println("The array is: {2, 2, 2, 3, 4, 5, 6}");
        System.out.println("The list of subarrays which sum of all elements of it is equal to 6 in the array is: ");
        Questions.equalSumSubarray(array, 6);
        System.out.println("The list of subarrays which sum of all elements of it is equal to 17 in the array is: ");
        Questions.equalSumSubarray(array, 17);
        System.out.println("The list of subarrays which sum of all elements of it is equal to 18 in the array is: ");
        Questions.equalSumSubarray(array, 18);
    }
    
    /**
     * Main function.
     * @param args Takes String array as parameter.
     */
    public static void main(String[] args){
        Question1();
        Question2();
        Question3();
    }
}
