package cayci_hw1;

import java.util.InputMismatchException;
import java.util.Scanner;

/**
 * Provides MENU for program.
 * @author cagri cayci
 */
public class TEST {
    /**
     * Main class.
     * @param args Takes args as String.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public static void main(String args[]) throws OUTOFRANGEEXCEPTION{
        try{
            DRIVER d1 = new DRIVER();
            Scanner input = new Scanner(System.in);
            int decision, lenght;
            STREET s1 = new STREET(50);
            do{
                System.out.println("MENU");
                System.out.println("1- EDIT MODE");
                System.out.println("2- VIEW MODE");
                System.out.println("3- CHANGE STREET LENGHT");
                System.out.println("4- EXIT");
                System.out.println("Your decision: ");
                decision = input.nextInt();
                switch(decision){
                    case 1:
                        // EDIT MODE //
                        editMode(s1);
                        break;
                    case 2:
                        // VIEW MODE //
                        viewMode(s1);
                        break;
                    case 3:
                        // SET STREET LENGHT //
                        System.out.println("Enter the lenght: ");
                        lenght = input.nextInt();
                        s1.setLenght(lenght);
                        break;
                }
            }while(0 < decision && decision < 4);
            
        }
        catch(OUTOFRANGEEXCEPTION | InputMismatchException e){  
        }
    }
    
    /**
     * Edit mode menu. 
     * @param s1 Takes s1 as STREET.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public static void editMode(STREET s1) throws OUTOFRANGEEXCEPTION{
        int decision, position, lenght;
        Scanner input = new Scanner(System.in);
        do{
            System.out.println("1- ADD BUILDING RIGHT SIDE");
            System.out.println("2- ADD BUILDING LEFT SIDE");
            System.out.println("3- DELETE BUILDING FROM RIGHT SIDE");
            System.out.println("4- DELETE BUILDING FROM LEFT SIDE");
            System.out.println("5- EXIT");
            System.out.println("Your decision: ");
            decision = input.nextInt();
            switch(decision){
                case 1:
                    // ADD BUILDING RIGHT SIDE //
                    STRUCTURE temp = buildingType();
                    s1.addBuildingRights(temp);
                    break;
                case 2:
                    // ADD BUILDING LEFT SIDE //
                    STRUCTURE temp2 = buildingType();
                    s1.addBuildingLefts(temp2);
                    break;
                case 3:
                    // DELETE BUILDING FROM RIGHT SIDE //
                    System.out.println("Enter the position: ");
                    position = input.nextInt();
                    System.out.println("Enter the lenght: ");
                    lenght = input.nextInt();
                    s1.deleteBuildingsRights(position, lenght);
                    break;
                case 4:
                    // DELETE BUILDING FROM LEFT SIDE //
                    System.out.println("Enter the position: ");
                    position = input.nextInt();
                    System.out.println("Enter the lenght: ");
                    lenght = input.nextInt();
                    s1.deleteBuildingsLefts(position, lenght);
                    break;
            }
        }while(0 < decision && decision < 5);
    }
    
    /**
     * View mode menu.
     * @param s1 Takes s1 as STREET.
     */
    public static void viewMode(STREET s1){
        int decision;
        Scanner input = new Scanner(System.in);
        do{
            System.out.println("1- DISPLAY THE TOTAL REMAINING LENGHT ON THE STREET");
            System.out.println("2- DISPLAY THE LIST OF THE BUILDINGS ON THE STREET");
            System.out.println("3- DISPLAY THE NUMBER AND RATIO OF LENGHT OF THE PLAYGROUNDS IN THE STREET");
            System.out.println("4- CALCULATE THE TOTAL LENGHT OF STREET OCCUPİED BY THE MARKETS, HOUSES OR OFFICES");
            System.out.println("5- DISPLAY THE SKYLINE SILHOUETTE OF THE STREET");
            System.out.println("6- EXIT");
            System.out.println("Your decision: ");
            decision = input.nextInt();
            switch(decision){
                case 1:
                    // DISPLAY THE TOTAL REMAINING LENGHT ON THE STREET //
                    s1.remainingLenght();
                    break;
                case 2:
                    // DISPLAY THE LIST OF THE BUILDINGS ON THE STREET //
                    s1.streetInfo();
                    break;
                case 3:
                    // DISPLAY THE NUMBER AND RATIO OF LENGHT OF THE PLAYGROUNDS IN THE STREET //
                    s1.playGroundsInfo();
                    break;
                case 4:
                    // CALCULATE THE TOTAL LENGHT OF STREET OCCUPİED BY THE MARKETS, HOUSES OR OFFICES //
                    s1.occupiedLenght();
                    break;
                case 5:
                    // DISPLAY THE SKYLINE SILHOUETTE OF THE STREET //
                    s1.printSiluette();
                    break;
            }
        }while(0 < decision && decision < 6);
    }
    
    /**
     * Building type menu.
     * @return Returns a Structure. 
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public static STRUCTURE buildingType() throws OUTOFRANGEEXCEPTION{
        int decision;
        Scanner input = new Scanner(System.in);
        STRUCTURE temp = null;
        do{
            System.out.println("1- HOUSE\n2- MARKET\n3- OFFICE\n4- PLAYGROUND");
            decision = input.nextInt();
            switch(decision){
                case 1:
                    // CREATE HOUSE //
                    temp = createHouse();
                    break;
                case 2:
                    // CREATE MARKET //
                    temp = createMarket();
                    break;
                case 3:
                    // CREATE OFFICE //
                    temp = createOffice();
                    break;
                case 4:
                    // CREATE PLAYGROUND //
                    temp = createPlayground();
                    break;
            }
        }while(decision < 0 || decision > 4);
        return temp;
    }
    
    /**
     * Creates a HOUSE.
     * @return Returns a HOUSE.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */    
    public static HOUSE createHouse() throws OUTOFRANGEEXCEPTION{
        Scanner input = new Scanner(System.in);
        int position, lenght, height, numberofRooms;
        String owner, colour;
        System.out.println("Enter position: ");
        position = input.nextInt();
        System.out.println("Enter lenght: ");
        lenght = input.nextInt();
        System.out.println("Enter height: ");
        height = input.nextInt();
        System.out.println("Enter number of rooms: ");
        numberofRooms = input.nextInt();
        input.nextLine();
        System.out.println("Enter owner: ");
        owner = input.nextLine();
        System.out.println("Enter colour: ");
        colour = input.nextLine();
        return new HOUSE(position, lenght, height, owner, numberofRooms, colour);
    }
    
    /**
     * Creates a MARKET.
     * @return Returns a MARKET.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public static MARKET createMarket() throws OUTOFRANGEEXCEPTION{
        Scanner input = new Scanner(System.in);
        int position, lenght, height;
        double openingTime, closingTime;
        String owner;
        System.out.println("Enter position: ");
        position = input.nextInt();
        System.out.println("Enter lenght: ");
        lenght = input.nextInt();
        System.out.println("Enter height: ");
        height = input.nextInt();
        System.out.println("Enter opening time: ");
        openingTime = input.nextDouble();
        System.out.println("Enter closing time: ");
        closingTime = input.nextDouble();
        System.out.println("Enter owner: ");
        owner = input.nextLine();
        return new MARKET(position, lenght, height, owner, openingTime, closingTime);
    }
    
    /**
     * Creates a OFFICE.
     * @return Returns a OFFICE.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION. 
     */
    public static OFFICE createOffice() throws OUTOFRANGEEXCEPTION{
        Scanner input = new Scanner(System.in);
        int position, lenght, height;
        String owner, jobType;
        System.out.println("Enter position: ");
        position = input.nextInt();
        System.out.println("Enter lenght: ");
        lenght = input.nextInt();
        System.out.println("Enter height: ");
        height = input.nextInt();
        input.nextLine();
        System.out.println("Enter owner: ");
        owner = input.nextLine();
        System.out.println("Enter job type: ");
        jobType = input.nextLine();
        return new OFFICE(position, lenght, height, owner, jobType);
    }
    
    /**
     * Creates a PLAYGROUND.
     * @return Returns a PLAYGROUND.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public static PLAYGROUND createPlayground() throws OUTOFRANGEEXCEPTION{
        Scanner input = new Scanner(System.in);
        int position, lenght;
        System.out.println("Enter position: ");
        position = input.nextInt();
        System.out.println("Enter lenght: ");
        lenght = input.nextInt();
        return new PLAYGROUND(position, lenght);
    }
}
