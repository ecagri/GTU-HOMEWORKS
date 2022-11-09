package cayci_hw6;

/**
 * Helper class for HashTableHybrid.
 * @author cagri cayci
 */
public class Prime {
    /**
     * Finds previous prime number.
     * @param number Gets starting number.
     * @return Returns previous prime number.
     */
    public static int previousPrime(int number){ 
        if(isPrime(number - 1))
            return number - 1;
        else
            return previousPrime(number - 1);
    }
    
    /**
     * Finds next prime number.
     * @param number Gets starting number.
     * @return Returns next prime number.
     */
    public static int nextPrime(int number){
        if(isPrime(number + 1))
            return number + 1;
        else
            return nextPrime(number + 1);
    }
    
    /**
     * Checks whether a number is prime or not. 
     * @param number Gets number. 
     * @return Returns true if the number is prime, otherwise false.
     */
    private static boolean isPrime(int number){
        for(int divisor = 2; divisor < number; divisor++){
            if(number % divisor == 0)
                return false;
        }
        return true;
    }
}
