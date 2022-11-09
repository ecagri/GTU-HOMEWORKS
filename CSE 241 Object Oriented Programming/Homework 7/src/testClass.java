import cayci_cse241_hw7.DayofYearSet;
import java.util.ArrayList;
import java.io.FileWriter;
import java.io.IOException;
/**
 *
 * @author Cagri Cayci
 */
public class testClass {
    /**
     * Test DayofYearSet class constructors. 
    */
    public static void test_constructors(){
        var s1 = new DayofYearSet();
        ArrayList<DayofYearSet.DayofYear> setList = new ArrayList<>();
        setList.add(new DayofYearSet.DayofYear());
        setList.add(new DayofYearSet.DayofYear(3));
        setList.add(new DayofYearSet.DayofYear(2,2));
        var s2 = new DayofYearSet(setList);
        System.out.println("DayofYearSet class constructors test...\nfirst set: " + s1 + "\n" + "second set: " + s2 + "\n\n");
    }
    /**
     * Test DayofYear class constructors. 
    */
    public static void test_constructors_2(){
        var first_day = new DayofYearSet.DayofYear();
        var second_day = new DayofYearSet.DayofYear(17);
        var third_day = new DayofYearSet.DayofYear(29, 2);
        System.out.println("DayofYear class constructors test...\nfirst day: " + first_day + "\n" + "second day: " + second_day + "\n" + "third day: " + third_day + "\n\n");
    }
    /**
     * Writes sets to txt files.
     * @param s1 Gets first DayofYearSet.
     * @param s2 Gets second DayofYearSet.
     */
    public static void write(DayofYearSet s1, DayofYearSet s2){
        try{
            FileWriter example1 = new FileWriter("example1.txt");
            FileWriter example2 = new FileWriter("example2.txt");
            example1.write("s1 = " + s1);
            example2.write("s2 = " + s2);
            example1.close();
            example2.close();
        }
        catch(IOException x){
            System.out.println("Error");
        }
    }
    /**
     * Tests add method.
     * @param s1 Gets a DayofYearSet objects.
    */
    public static void test_add(DayofYearSet s1){
        s1.add(new DayofYearSet.DayofYear(12, 12));
        System.out.println("Add method test...\nAdd DayofYear(12, 12) to set\nnew version of set: " + s1);
    }
    /**
     * Tests remove method.
     * @param s1 Gets a DayofYearSet objects.
    */
    public static void test_remove(DayofYearSet s1){
        s1.remove(new DayofYearSet.DayofYear(3, 3));
        System.out.println("Remove method test...\nRemove DayofYear(3, 3) from set\nnew version of set: " + s1);
    }
    /**
     * Tests equals method, compares two DayofYearSet objects.
     * @param s1 Gets first DayofYearSet.
     * @param s2 Gets second DayofYearSet.
     */
    public static void test_equals(DayofYearSet s1, DayofYearSet s2){
        System.out.println("Equals method test...");
        if(s1.equals(s2) == true){
            System.out.println("They are equal.\n\n");
        }
        else{
            System.out.println("They are not equal.\n\n");
        }
    }
    /**
     * Tests setIntersection method, prints the intersection of two DayofYearSet objects.
     * @param s1 Gets first DayofYearSet.
     * @param s2 Gets second DayofYearSet.
     */
    public static void test_intersection(DayofYearSet s1, DayofYearSet s2){
        System.out.println("Intersection method test...\nintersection set: " + s1.setIntersection(s2) + "\n\n");
    }
    /**
     * Tests setUnion method, prints the union of two DayofYearSet objects.
     * @param s1 Gets first DayofYearSet.
     * @param s2 Gets second DayofYearSet.
     */
    public static void test_union(DayofYearSet s1, DayofYearSet s2){
        System.out.println("Union method test...\nunion set: " + s1.setUnion(s2) + "\n\n");
    }
    /**
     * Tests setDifference method, prints the difference of two DayofYearSet objects.
     * @param s1 Gets first DayofYearSet.
     * @param s2 Gets second DayofYearSet.
     */
    public static void test_difference(DayofYearSet s1, DayofYearSet s2){
        System.out.println("Difference method test...\ndifference set: " + s1.setDifference(s2) + "\n\n");
    }
    /**
     * Tests setComplement method, prints the complement of a DayofYearSet object.
     * @param s1 Gets the DayofYearSet object.
     */
    public static void test_complement(DayofYearSet s1){
         System.out.println("Complement method test...\ncomplement set: " + s1.setComplement() + "\n\n");
    }
    /**
     * Tests size method, prints the size of the DayofYear array of DayofYearSet object.
     * @param s1 Gets the DayofYearSet object.
     */
    public static void test_size(DayofYearSet s1){
        System.out.println("Size method test...\nsize: " + s1.size() + "\n\n");
    }
    /**
     * Prints the number of alive objects in all set.
    */
    public static void test_aliveObj(){
        System.out.println("The number of alive objects is: " + DayofYearSet.aliveObjects() + "\n");
    }
    /**
     * Tests De Morgan Rule.
     * @param s1 Gets first DayofYearSet.
     * @param s2 Gets second DayofYearSet
     */
    public static void test_De_Morgan(DayofYearSet s1, DayofYearSet s2){
        System.out.println("De Morgan test...");
        if(((s1.setUnion(s2)).setComplement()).equals(((s1.setComplement()).setIntersection(s2.setComplement())))){
            System.out.println("They are equal.\n");
        } 
        else{
            System.out.println("They are not equal.\n");
        }
    }
    /**
     * Main method, runs all test methods.
     * @param args Gets arguments from the user.
     */
    public static void main(String[] args) {
        test_constructors();
        test_constructors_2();
        var first_set = new DayofYearSet();
        var second_set = new DayofYearSet();
        var third_set = new DayofYearSet();
        System.out.println("Initializing sets...");
        first_set.add(new DayofYearSet.DayofYear(1, 1));
        first_set.add(new DayofYearSet.DayofYear(2, 2));
        first_set.add(new DayofYearSet.DayofYear(3, 3));
        first_set.add(new DayofYearSet.DayofYear(4, 4));
        second_set.add(new DayofYearSet.DayofYear(4, 4));
        second_set.add(new DayofYearSet.DayofYear(5, 5));
        second_set.add(new DayofYearSet.DayofYear(6, 6));
        third_set.add(new DayofYearSet.DayofYear(4, 4));
        third_set.add(new DayofYearSet.DayofYear(5, 5));
        third_set.add(new DayofYearSet.DayofYear(6, 6));
        System.out.println("first set: " + first_set);
        System.out.println("second set: " + second_set);
        System.out.println("third set: " + third_set + "\n");
        /* Write assignment. */
        write(first_set, second_set);
        /* Alive objects test */
        test_aliveObj();
        /* De Morgan rule test */
        test_De_Morgan(first_set, second_set);
        /* Equality test */
        System.out.println("Equality of the first set and second set: ");
        test_equals(first_set, second_set);
        System.out.println("Equality of the second set and third set: ");
        test_equals(second_set, third_set);
        /* Intersection test */
        System.out.println("Intersection of the first set and second set: ");
        test_intersection(first_set, second_set);
        System.out.println("Intersection of the second set and third set: ");
        test_intersection(second_set, third_set);
        /* Union test */
        System.out.println("Union of the first set and second set: ");
        test_union(first_set, second_set);
        System.out.println("Union of the second set and third set: ");
        test_union(second_set, third_set);
        /* Difference test */
        System.out.println("Difference of the first set and second set: ");
        test_difference(first_set, second_set);
        System.out.println("Difference of the second set and third set: ");
        test_difference(second_set, third_set);
        /* Complement test */
        System.out.println("Complement of the first set: ");
        test_complement(first_set);
        System.out.println("Complement of the second set: ");
        test_complement(second_set);
        /* Size test */
        System.out.println("Size of the first set: ");
        test_size(first_set);
        System.out.println("Size of the second set: ");
        test_size(second_set);
        /* Add test */
        test_add(first_set);
        test_add(second_set);
        /* Remove test */
        test_remove(first_set);
        test_remove(second_set);
    }
}
