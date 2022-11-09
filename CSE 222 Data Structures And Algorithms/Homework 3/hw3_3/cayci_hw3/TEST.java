package cayci_hw3;

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
            long start = System.nanoTime();
            DRIVER driver = new DRIVER();
            System.out.println("The running time of the system is: " + (System.nanoTime() - start));
            Scanner input = new Scanner(System.in);
            int decision, lenght;
            Street s1 = new Street(50);
            do{
                System.out.println("MENU");
                System.out.println("1- EDIT MODE");
                System.out.println("2- VIEW MODE");
                System.out.println("3- CHANGE Street LENGHT");
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
                        // SET Street LENGHT //
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
     * @param s1 Takes s1 as Street.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public static void editMode(Street s1) throws OUTOFRANGEEXCEPTION{
        int decision, position, lenght;
        Scanner input = new Scanner(System.in);
        do{
            System.out.println("1- ADD Building RIGHT SIDE");
            System.out.println("2- ADD Building LEFT SIDE");
            System.out.println("3- DELETE Building FROM RIGHT SIDE");
            System.out.println("4- DELETE Building FROM LEFT SIDE");
            System.out.println("5- EXIT");
            System.out.println("Your decision: ");
            decision = input.nextInt();
            switch(decision){
                case 1:
                    // ADD Building RIGHT SIDE //
                    Structure temp = buildingType();
                    s1.addBuildingRights(temp);
                    break;
                case 2:
                    // ADD Building LEFT SIDE //
                    Structure temp2 = buildingType();
                    s1.addBuildingLefts(temp2);
                    break;
                case 3:
                    // DELETE Building FROM RIGHT SIDE //
                    System.out.println("Enter the position: ");
                    position = input.nextInt();
                    System.out.println("Enter the lenght: ");
                    lenght = input.nextInt();
                    s1.deleteBuildingsRights(position, lenght);
                    break;
                case 4:
                    // DELETE Building FROM LEFT SIDE //
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
     * @param s1 Takes s1 as Street.
     */
    public static void viewMode(Street s1){
        int decision;
        Scanner input = new Scanner(System.in);
        do{
            System.out.println("1- DISPLAY THE TOTAL REMAINING LENGHT ON THE Street");
            System.out.println("2- DISPLAY THE LIST OF THE BuildingS ON THE Street");
            System.out.println("3- DISPLAY THE NUMBER AND RATIO OF LENGHT OF THE PlaygroundS IN THE Street");
            System.out.println("4- CALCULATE THE TOTAL LENGHT OF Street OCCUPİED BY THE MarketS, HouseS OR OfficeS");
            System.out.println("5- DISPLAY THE SKYLINE SILHOUETTE OF THE Street");
            System.out.println("6- EXIT");
            System.out.println("Your decision: ");
            decision = input.nextInt();
            switch(decision){
                case 1:
                    // DISPLAY THE TOTAL REMAINING LENGHT ON THE Street //
                    s1.remainingLenght();
                    break;
                case 2:
                    // DISPLAY THE LIST OF THE BuildingS ON THE Street //
                    s1.streetInfo();
                    break;
                case 3:
                    // DISPLAY THE NUMBER AND RATIO OF LENGHT OF THE PlaygroundS IN THE Street //
                    s1.playGroundsInfo();
                    break;
                case 4:
                    // CALCULATE THE TOTAL LENGHT OF Street OCCUPİED BY THE MarketS, HouseS OR OfficeS //
                    s1.occupiedLength();
                    break;
                case 5:
                    // DISPLAY THE SKYLINE SILHOUETTE OF THE Street //
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
    public static Structure buildingType() throws OUTOFRANGEEXCEPTION{
        int decision;
        Scanner input = new Scanner(System.in);
        Structure temp = null;
        do{
            System.out.println("1- House\n2- Market\n3- Office\n4- Playground");
            decision = input.nextInt();
            switch(decision){
                case 1:
                    // CREATE House //
                    temp = createHouse();
                    break;
                case 2:
                    // CREATE Market //
                    temp = createMarket();
                    break;
                case 3:
                    // CREATE Office //
                    temp = createOffice();
                    break;
                case 4:
                    // CREATE Playground //
                    temp = createPlayground();
                    break;
            }
        }while(decision < 0 || decision > 4);
        return temp;
    }
    
    /**
     * Creates a House.
     * @return Returns a House.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */    
    public static House createHouse() throws OUTOFRANGEEXCEPTION{
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
        return new House(position, lenght, height, owner, numberofRooms, colour);
    }
    
    /**
     * Creates a Market.
     * @return Returns a Market.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public static Market createMarket() throws OUTOFRANGEEXCEPTION{
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
        return new Market(position, lenght, height, owner, openingTime, closingTime);
    }
    
    /**
     * Creates a Office.
     * @return Returns a Office.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION. 
     */
    public static Office createOffice() throws OUTOFRANGEEXCEPTION{
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
        return new Office(position, lenght, height, owner, jobType);
    }
    
    /**
     * Creates a Playground.
     * @return Returns a Playground.
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public static Playground createPlayground() throws OUTOFRANGEEXCEPTION{
        Scanner input = new Scanner(System.in);
        int position, lenght;
        System.out.println("Enter position: ");
        position = input.nextInt();
        System.out.println("Enter lenght: ");
        lenght = input.nextInt();
        return new Playground(position, lenght);
    }
}
