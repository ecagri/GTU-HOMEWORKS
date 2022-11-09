package cayci_cse241_hw7;
import java.util.ArrayList;

/**
 *
 * @author Cagri Cayci
 */
public class DayofYearSet {
    /**
     * Keeps DayofYear objects as array.  
    */
    private DayofYear[] dayArray;
    /**
     * Keeps the size of the DayofYear array.
    */
    private int arraySize;
    /**
     * Tracks of the alive DayofYear objects.
    */
    private static int aliveNumber = 0;
    /**
     * Inner class, Keeps two integers as day and month.
     */
    public static class DayofYear{
            /**
             * Keeps the day as an integer.
             */
            private int day;
            /**
             * Keeps the month as an integer.
             */
            private int month;
            /**
             * No parameter constructor
            */
            public DayofYear(){
                this(1, 1);
            }
            /** Constructor 
            * @param _day Gets an integer as day.
            */
            public DayofYear(int _day){
                this(_day, 1);
            }
            /** Constructor
            * @param _day Gets an integer as day. 
            * @param _month Gets an integer as month.
            */
            public DayofYear(int _day, int _month) {
                int monthArray[] = {31,28,31,30,31,30,31,31,30,31,30,31};
                if(0 < _month && _month < 13){
                    month = _month;
                }
                else{
                    month = 1;
                }
                if(0 < _day && _day <= monthArray[month-1]){
                    day = _day;
                }
                else{
                    day = 1;
                }
            }
            /** Compares two DayofYear object.
             * @param other Gets a DayofYear object.
             * @return Returns true if they are equal, returns false if they are not equal.
            */
            public boolean equals(DayofYear other){
                return (this.day == other.day && this.month == other.month);         
            }
            /** Convert objects into Strings.
             * @return Returns object as a String.
            */
            public String toString(){
                String[] nameofMonths = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
                return "\"" + day + ".day of " + nameofMonths[month-1] + "\"";
            }
    }
    /** No parameter Constructor.
     *
    */
    public DayofYearSet(){
            dayArray = null;
            arraySize = 0;
    }
    /** Constructor.
     * @param arr Gets an ArrayList of DayofYear objects and convert it into DayofYearSet object.
    */
    public DayofYearSet(ArrayList<DayofYear> arr) {
        arraySize = arr.size();
        dayArray = new DayofYear[arraySize]; 
        for(int  i = 0; i < arraySize; i++){
            dayArray[i] = arr.get(i);
        }
        aliveNumber += arraySize; 
    }
    /** Add a DayofYear object to DayofYearSet object.  
     * @param obj Gets an DayofYear object.
    */
    public void add(DayofYear obj){
        boolean found = false;
        for(int i = 0; i < arraySize && found == false; i++){
            if(dayArray[i].equals(obj) == true){
                found = true;
            }
        }
        if(found == false){
            DayofYear[] temp = new DayofYear[arraySize+1];
            for(int i = 0; i < arraySize; i++){
                temp[i] = dayArray[i];
            }
            temp[arraySize] = obj;
            arraySize += 1;
            dayArray = new DayofYear[arraySize];
            for(int i = 0; i < arraySize; i++){
                dayArray[i] = temp[i];
            }
            aliveNumber++;
        }
    }
    /** Remove the object if the DayofYearSet has that object.
     * @param obj Gets an object which will be deleted.
    */
    public void remove(DayofYear obj){
        boolean found = false;
        int index = 0;
        for(int i = 0; i < arraySize && found == false; i++){
            if(dayArray[i].equals(obj)){
                found = true;
                index = i;
            }
        }
        if(found == true){
            arraySize -= 1;
            DayofYear[] temp = new DayofYear[arraySize];
            for(int i = 0; i < arraySize; i++){
                if(i < index)
                    temp[i] = dayArray[i];
                else
                    temp[i] = dayArray[i+1];
            }
            dayArray = new DayofYear[arraySize];
            for(int i = 0; i < arraySize; i++){
                dayArray[i] = temp[i];
            }
            aliveNumber--;
        }
    }
    /** Compares two DayofYearSet objects.
     * @param other Gets a DayofYearSet object.
     * @return Returns true if they are equal, returns false if they are not equal.
    */
    public boolean equals(DayofYearSet other){
        boolean found, equal = (this.size() == other.size());
        for(int i = 0; i < this.size() && equal == true; i++){
            found = false;
            for(int j = 0; j < other.size() && found == false; j++){
                if(this.dayArray[i].equals(other.dayArray[j])){
                    found = true;
                }
            }
            if(found == false){
                equal = false;
            }
        }
        return equal;
    }
    /** Find intersection of two DayofYearSet.
     * @param other Gets an DayofYearSet object.
     * @return Returns an DayofYearSet object which is intersection of two DayofYearSet objects.
    */
    public DayofYearSet setIntersection(DayofYearSet other){
        DayofYearSet intersection = new DayofYearSet();
        boolean found;
        for(int i = 0; i < this.size(); i++){
            found = false;
            for(int j = 0; j < other.size() && found == false; j++){
                if(this.dayArray[i].equals(other.dayArray[j]) == true){
                    found = true;
                    intersection.add(this.dayArray[i]);
                }
            }
        }
        return intersection;
    }
    /** Find union of two DayofYearSet.
     * @param other Gets an DayofYearSet object.
     * @return Returns an DayofYearSet object which is union of two DayofYearSet objects.
    */
    public DayofYearSet setUnion(DayofYearSet other){
        DayofYearSet union = new DayofYearSet();
        for(int i = 0; i < this.size(); i++){
            union.add(this.dayArray[i]);
        }
        for(int j = 0; j < other.size(); j++){
            union.add(other.dayArray[j]);
        }
        return union;
    }
    /** Substracts an DayofYearSet object from another DayofYearSet object.
     * @param other Gets an DayofYearSet object.
     * @return Returns the substraction of two DayofYearSet objects.
    */
    public DayofYearSet setDifference(DayofYearSet other){
        DayofYearSet difference = new DayofYearSet();
        boolean found;
        for(int i = 0; i < this.size(); i++){
            found = false;
            for(int j = 0; j < other.size(); j++){
                if(this.dayArray[i].equals(other.dayArray[j]) == true){
                    found = true;
                }
            }
            if(found == false){
                difference.add(this.dayArray[i]);
            }
        }
        return difference;
    }
    /** Finds the complement set of an DayofYearSet object. 
     * @return Returns the complement set of DayofYearSet object.
    */
    public DayofYearSet setComplement(){
        DayofYearSet complement = new DayofYearSet();
        int[] monthArray = {31,28,31,30,31,30,31,31,30,31,30,31};
        for(int i = 0; i < 12 ; i++){
            for(int j = 0; j < monthArray[i]; j++){
                DayofYear date = new DayofYear(j+1, i+1);
                complement.add(date);
            }
        }
        return complement.setDifference(this);
    }
    /**
     * @return Returns the size of the array of DayofYear objects.
    */
    public int size(){
        return arraySize;
    }
    /**
     * @return Returns the number of alive DayofYear objects in all sets.
    */
    public static int aliveObjects(){
        return aliveNumber;
    }
    /** Convert objects into Strings.
     * @return Returns object as a String. 
    */
    public String toString() {
            String s1 =  "{";
            for(int i = 0; i < arraySize; i++) {
                s1 += dayArray[i].toString();
                if(i != dayArray.length -1)s1 += ", ";
            }
            s1 += "}";
            return s1;
    }
}
