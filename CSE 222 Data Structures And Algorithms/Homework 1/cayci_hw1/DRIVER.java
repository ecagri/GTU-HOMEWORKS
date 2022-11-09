package cayci_hw1;

/**
 * Methods of the GTUArray class has already tested by STREET class methods. So I didn't tested it twice.
*/
public class DRIVER {
    /**
     * test
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public void testHouseFunctions() throws OUTOFRANGEEXCEPTION{
        System.out.println("HOUSE constructor testing...\nSets position 0, lenght 10, height 20, owner çağrı, numberofRooms 5, colour blue");
        HOUSE h1 = new HOUSE(0, 10, 20, "çağrı", 5, "blue");
        h1.getInfo();
        System.out.println("******************************************************");
        System.out.println("Makes the numberofRooms 7");
        h1.setRoomNumber(7);
        h1.getInfo();
        System.out.println("******************************************************");
        System.out.println("toString method testing...");
        System.out.println(h1.toString());
        System.out.println("******************************************************");
        System.out.println("hashCode of House is: " + h1.hashCode());
        System.out.println("++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    }
    
    /**
     * test
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public void testMarketFunctions() throws OUTOFRANGEEXCEPTION{
        System.out.println("MARKET constructor testing...\nSets position 10, lenght 20, height 15, owner çağrı, openingTime 9, closingTime 17");
        MARKET m1 = new MARKET(10, 20, 15, "çağrı", 9, 17);
        m1.getInfo();
        System.out.println("******************************************************");
        System.out.println("Makes the openingTime 10.30");
        m1.setOpeningTime(10.30);
        m1.getInfo();
        System.out.println("******************************************************");
        System.out.println("Makes the closingTime 18");
        m1.setClosingTime(18);
        m1.getInfo();
        System.out.println("******************************************************");
        System.out.println("toString method testing...");
        System.out.println(m1.toString());
        System.out.println("******************************************************");
        System.out.println("hashCode of MARKET is: " + m1.hashCode());
        System.out.println("++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    }
    
    /**
     * test
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public void testOfficeFunctions() throws OUTOFRANGEEXCEPTION{
        System.out.println("Office constructor testing... \nSets position 5, lenght 10, height 30, owner çağrı, jobType engineering");
        OFFICE o1 = new OFFICE(5, 10, 30, "çağrı", "engineering");
        o1.getInfo();
        System.out.println("******************************************************");
        System.out.println("toString method testing...");
        System.out.println(o1.toString());
        System.out.println("******************************************************");
        System.out.println("hashCode of OFFICE is: " + o1.hashCode());
        System.out.println("++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    }
    
    /**
     * test
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public void testPlaygroundFunctions() throws OUTOFRANGEEXCEPTION{
        System.out.println("Playground constructor testing...\nSets position 30, lenght 20");
        PLAYGROUND p1 = new PLAYGROUND(30, 20);
        p1.getInfo();
        System.out.println("******************************************************");
        System.out.println("toString method testing...");
        System.out.println(p1.toString());
        System.out.println("******************************************************");
        System.out.println("hashCode of PLAYGROUND is: " + p1.hashCode());
        System.out.println("++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    }
    
    /**
     * test
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public void testBuildingFunctions() throws OUTOFRANGEEXCEPTION{
        System.out.println("Building constructor testing... \nSets position 10, lenght 15, height 20, owner çağrı");
        BUILDING b1 = new BUILDING(10, 15, 20, "çağrı");
        b1.getInfo();
        System.out.println("******************************************************");
        System.out.println("toString method testing...");
        System.out.println(b1.toString());
        System.out.println("******************************************************");
        System.out.println("hashCode of BUILDING is: " + b1.hashCode());
        System.out.println("++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    }
    
    /**
     * test
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public void testStructureFunctions() throws OUTOFRANGEEXCEPTION{
        System.out.println("Structure constructor testing... \nSets position 17, lenght 21, height 19");
        STRUCTURE s1 = new STRUCTURE(17, 21, 19);
        s1.getInfo();
        System.out.println("******************************************************");
        System.out.println("Makes lenght 11");
        s1.setLenght(11);
        System.out.println("Lenght of structure is: " + s1.getLenght());
        System.out.println("******************************************************");
        System.out.println("Makes height 13");
        s1.setHeight(13);
        System.out.println("Height of structure is: " + s1.getHeight());
        System.out.println("******************************************************");
        System.out.println("The position of the structure is: " + s1.getMinPosition());
        System.out.println("******************************************************");
        System.out.println("The max position(position + lenght) of the structure is: " + s1.getMaxPosition());
        System.out.println("toString method testing...");
        System.out.println(s1.toString());
        System.out.println("******************************************************");
        System.out.println("hashCode of STRUCTURE is: " + s1.hashCode());
        System.out.println("++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    }
    
    /**
     * test
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public void testStreetFunctions() throws OUTOFRANGEEXCEPTION{
        System.out.println("Street constructor testing... \nSets lenght 50");
        STREET s1 = new STREET(50);
        System.out.println("Lenght of the street is: " + s1.getLenght());
        System.out.println("******************************************************");
        System.out.println("Makes lenght of the street 60");
        s1.setLenght(60);
        System.out.println("Lenght of the street is: " + s1.getLenght());
        System.out.println("******************************************************");
        HOUSE h1 = new HOUSE(0, 10, 20, "çağrı", 5, "blue");
        HOUSE h2 = new HOUSE(5, 15, 15, "çağrı", 7, "red");
        MARKET m1 = new MARKET(10, 20, 10, "çağrı", 9, 17);
        MARKET m2 = new MARKET(25, 7, 17, "çağrı", 5, 15);
        OFFICE o1 = new OFFICE(5, 10, 30, "çağrı", "engineering");
        OFFICE o2 = new OFFICE(35, 8, 23, "çağrı", "police");
        PLAYGROUND p1 = new PLAYGROUND(30, 10);
        PLAYGROUND p2 = new PLAYGROUND(45, 10);
        s1.addBuildingRights(h1);
        s1.addBuildingRights(m1);
        s1.addBuildingRights(o1);
        s1.addBuildingRights(p1);
        s1.printSiluette();
        s1.addBuildingLefts(h2);
        s1.addBuildingLefts(m2);
        s1.addBuildingLefts(o2);
        s1.addBuildingLefts(p2);
        s1.printSiluette();
        s1.streetInfo();
        s1.occupiedLenght();
        s1.playGroundsInfo();
        s1.remainingLenght();
        s1.deleteBuildingsRights(0, 10);
        s1.printSiluette();
        s1.deleteBuildingsRights(10, 10);
        s1.printSiluette();
        s1.deleteBuildingsLefts(25, 7);
        s1.printSiluette();
        System.out.println("++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    }
    
    /**
     * test
     * @throws OUTOFRANGEEXCEPTION If it violates the borders, throws OUTOFRANGEEXCEPTION.
     */
    public DRIVER() throws OUTOFRANGEEXCEPTION{
        testHouseFunctions();
        testMarketFunctions();
        testOfficeFunctions();
        testPlaygroundFunctions();
        testBuildingFunctions();
        testStructureFunctions();
        testStreetFunctions();
        HOUSE h1 = new HOUSE(3, 10, 20, "çağrı", 7, "blue");
        HOUSE h2 = new HOUSE(0, 10, 20, "çağrı", 7, "blue");
        System.out.println("h1: ");
        h1.getInfo();
        System.out.println("\nh2: ");
        h2.getInfo();
        System.out.println("h1 and h2 equals: " + h1.equals(h2));
        OFFICE o1 = new OFFICE(0, 10, 20, "çağrı", "engineer");
        OFFICE o2 = new OFFICE(0, 10, 20, "çağrı", "engineer");
        System.out.println("o1: ");
        o1.getInfo();
        System.out.println("\no2: ");
        o2.getInfo();
        System.out.println("o1 and o2 equals: " + o1.equals(o2));
        

    }
}
