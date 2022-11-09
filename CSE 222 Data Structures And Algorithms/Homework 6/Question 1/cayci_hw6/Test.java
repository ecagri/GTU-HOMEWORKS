package cayci_hw6;

/**
 * Test class for HashTables.
 * @author cagri cayci
 */
public class Test {
    /**
     * Main function.
     * @param args Takes args as String array.
     */
    public static void main(String[] args){
        System.out.println("""
                           ++++++++++++++++++++++++++++++
                           HashTableChainTest
                           ++++++++++++++++++++++++++++++
                           """);
        testHashTableChain();
        System.out.println("""
                            ++++++++++++++++++++++++++++++
                            HashTableHybridTest
                            ++++++++++++++++++++++++++++++
                            """);
        testHashTableHybrid();
    }
    
    /**
     * Tests HashTableHybrid methods.
     */
    public static void testHashTableHybrid(){
        HashTableHybrid<Integer, Character> hth = new HashTableHybrid<Integer, Character>();
        System.out.println("Is hashtable empty: " + hth.isEmpty());
        System.out.println("******************************");
        System.out.println("What is the size of the hashtable: " + hth.size());
        System.out.println("******************************");
        System.out.println("Adding 3 to hashtable.");
        hth.put(3, 'a');
        System.out.println(hth.toString());
        System.out.println("******************************");
        System.out.println("Adding 12 to hashtable.");
        hth.put(12, 'b');
        System.out.println(hth.toString());
        System.out.println("******************************");
        System.out.println("Adding 13 to hashtable.");
        hth.put(13, 'c');
        System.out.println(hth.toString());
        System.out.println("******************************");
        System.out.println("Adding 25 to hashtable.");
        hth.put(25, 'd');
        System.out.println(hth.toString());
        System.out.println("******************************");
        System.out.println("Adding 23 to hashtable.");
        hth.put(23, 'e');
        System.out.println(hth.toString());
        System.out.println("******************************");
        System.out.println("Adding 51 to hashtable.");
        hth.put(51, 'f');
        System.out.println(hth.toString());
        System.out.println("******************************");
        System.out.println("Removing 25 from hashtable (25 is on the hashtable).");
        hth.remove(25);
        System.out.println(hth.toString());
        System.out.println("******************************");
        System.out.println("Removing 17 from hashtable (17 is not on the hashtable).");
        hth.remove(17);
        System.out.println(hth.toString());
        System.out.println("******************************");
        System.out.println("Adding 3 to hashtable with different value.");
        hth.put(3, 'z');
        System.out.println(hth.toString());
        System.out.println("******************************");
        System.out.println("Is hashtable empty: " + hth.isEmpty());
        System.out.println("Adding some elements to see rehash...");
        hth.put(191, 'l');
        hth.put(125, 'm');
        hth.put(94, 'o');
        System.out.println(hth.toString());
        System.out.println("******************************");
        System.out.println("What is the size of the hashtable: " + hth.size());
    }
    
    /**
     * Tests HashTableChain.
     */
    public static void testHashTableChain(){
        HashTableChain<Integer, Character> htc = new HashTableChain<Integer, Character>();
        System.out.println("Is hashtable empty: " + htc.isEmpty());
        System.out.println("******************************");
        System.out.println("What is the size of the hashtable: " + htc.size());
        System.out.println("******************************");
        System.out.println("Adding 3 to hashtable.");
        htc.put(3, 'a');
        System.out.println(htc.toString());
        System.out.println("******************************");
        System.out.println("Adding 12 to hashtable.");
        htc.put(12, 'b');
        System.out.println(htc.toString());
        System.out.println("******************************");
        System.out.println("Adding 13 to hashtable.");
        htc.put(13, 'c');
        System.out.println(htc.toString());
        System.out.println("******************************");
        System.out.println("Adding 25 to hashtable.");
        htc.put(25, 'd');
        System.out.println(htc.toString());
        System.out.println("******************************");
        System.out.println("Adding 23 to hashtable.");
        htc.put(23, 'e');
        System.out.println(htc.toString());
        System.out.println("******************************");
        System.out.println("Adding 51 to hashtable.");
        htc.put(51, 'f');
        System.out.println(htc.toString());
        System.out.println("******************************");
        System.out.println("Removing 25 from hashtable (25 is on the hashtable).");
        htc.remove(25);
        System.out.println(htc.toString());
        System.out.println("******************************");
        System.out.println("Removing 17 from hashtable (17 is not on the hashtable).");
        htc.remove(17);
        System.out.println(htc.toString());
        System.out.println("******************************");
        System.out.println("Adding 3 to hashtable with different value.");
        htc.put(3, 'z');
        System.out.println(htc.toString());
        System.out.println("******************************");
        System.out.println("Is hashtable empty: " + htc.isEmpty());
        System.out.println("Adding some elements to see rehash...");
        for(int i = 0; i < 30; i++){
            htc.put(100- i, (char) ('A' + i));
        }
        System.out.println(htc.toString());
        System.out.println("******************************");
        System.out.println("What is the size of the hashtable: " + htc.size());
    }
    
    /**
     * Test time complexities of the HashTableChain.
     * @param size Takes array size.
     */
    public static void testHashTableChainTime(int size){
        Double[] array = new Double[size];
        for(int i = 0; i < size; i++){
            array[i] = Math.random();
        }
        
        HashTableChain<Double, Integer> htc = null;
        long start = System.nanoTime();
        for(int i = 0; i < 100; i++){
            htc = new HashTableChain<Double, Integer>();
            for(int j = 0; j < size; j++){
                htc.put(array[j], j);
            }
        }
        long end = System.nanoTime();
        System.out.println("Adding an element to HashTableChain takes " + ((end - start) / (100 * size)) + ". Size is: " + size);
        
        start = System.nanoTime();
                
        for(int i = 0; i < 100; i++){
            HashTableChain<Double, Integer> htcNew = htc;
            for(int j = 0; j < size; j++){
                htcNew.remove(array[j]);
            }
        }
        end = System.nanoTime();
        
        System.out.println("Removing an element to HashTableChain takes " + ((end - start) / (100 * size)) + ". Size is: " + size);
    }
    
    /**
     * Test time complexities of the HashTableHybrid.
     * @param size Takes array size.
     */
    public static void testHashTableHybridTime(int size){
        Integer[] array = new Integer[size];
        for(int i = 0; i < size; i++){
            array[i] = (int) (Math.random() * 100);
        }
        
        HashTableHybrid<Integer, Integer> htc = null;
        long start = System.nanoTime();
        for(int i = 0; i < 100; i++){
            htc = new HashTableHybrid<Integer, Integer>();
            for(int j = 0; j < size; j++){
                htc.put(array[j], j);
            }
        }
        long end = System.nanoTime();
        System.out.println("Adding an element to HashTableHybrid takes " + ((end - start) / (100 * size)) + ". Size is: " + size);
        start = System.nanoTime();                
        for(int i = 0; i < 100; i++){
            HashTableHybrid<Integer, Integer> htcNew = htc;
            for(int j = 0; j < size; j++){
                htcNew.remove(array[j]);
            }
        }
        end = System.nanoTime();
        
        System.out.println("Removing an element to HashTAbleHybrid takes " + ((end - start) / (100 * size)) + ". Size is: " + size);
    }
    
    
}
