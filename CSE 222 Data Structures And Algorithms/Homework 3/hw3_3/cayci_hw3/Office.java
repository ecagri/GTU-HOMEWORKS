package cayci_hw3;


/**
 * Keeps type-specific data fields for Office.
 * @author cagri cayci
 */
public class Office extends Building{
    /**
     * Keeps type of the job as String.
     */
    private String jobType;
    
    /**
     * Five parameter constructor.
     * @param _position Takes position of the Office as integer. 
     * @param _lenght Takes lenght of the Office as integer.
     * @param _height Takes height of the Office as integer.
     * @param _owner Takes owner of the Office as String.
     * @param _jobType Takes type of the job of the OFFICe as String.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public Office(int _position, int _lenght, int _height, String _owner, String _jobType) throws OUTOFRANGEEXCEPTION{
        super(_position, _lenght, _height, _owner); /* Calls constructor of ancestor class. */
        jobType = _jobType;
    }
    
    /**
     * Prints fields of Office and fields of ancestor classes of Office.
     */
    @Override
    public void getInfo(){
        super.getInfo(); /* Calls getInfo method of ancestor class. */
        System.out.println("Job type is: " + jobType);
    }
    
    /**
     * Overrides hashCode method.
     * @return Returns hashCode of the OFFICe as integer.
     */
    @Override
    public int hashCode(){ 
        return 7 * (jobType.hashCode()) * super.hashCode();
    }
    
    /**
     * Overrides equals method.
     * @param other Gets other object as Object class.
     * @return Returns true if they are equal, otherwise false.
     */
    @Override
    public boolean equals(Object other){
        boolean equality = false;
        if(this.getClass() == other.getClass()){ /* If their class are equal, continue. */
            Office otherobj = (Office) other;
            if(this.jobType.equals(otherobj.jobType)){
                equality = true;
            }
        }
        else 
            equality = false;
        return equality && super.equals(other); /* Returns true if data fields and data fields of ancestor class of objects are equal, otherwise false. */
    }
    
    /**
     * Overrides toString method.
     * @return Returns MARKET object as String.
     */
    @Override
    public String toString(){
        return "The type of the job is: " + jobType;
    }
}
