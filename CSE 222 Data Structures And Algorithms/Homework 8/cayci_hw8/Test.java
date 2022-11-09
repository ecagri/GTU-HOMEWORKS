package cayci_hw8;

import java.util.HashMap;

/**
 *  Test class.
 */
public class Test {
    /**
     * Main method.
     * @param args Takes arguments from the user as String array.
     */
    public static void main(String[] args){

        testAddingRemoving(true);
        testingExportMatrix(true);
        testingGraphFilter(true);
        testingBFSvsDFS(true);
        testingDijkstraAlgorithm(true);

        testAddingRemoving(false);
        testingExportMatrix(false);
        testingGraphFilter(false);
        testingBFSvsDFS(false);
        testingDijkstraAlgorithm(false);

    }

    /**
     * Test add and remove operations on graph.
     * @param isDirected Creates an undirected/directed graph according to isDirected.
     */
    public static void testAddingRemoving(boolean isDirected){

        System.out.println("CREATING A GRAPH");

        MyGraph myGraph = new MyGraph(isDirected);

        System.out.println("GENERATING AN VERTEX WITH 'A' AS LABEL, 1 AS WEGİHT.");

        Vertex vertex0 = myGraph.newVertex("A", 1);

        System.out.println(vertex0);

        System.out.println("ADDING THE VERTEX TO THE GRAPH.");

        myGraph.addVertex(vertex0);

        System.out.println("PRINTING THE GRAPH.");

        myGraph.printGraph();

        System.out.println("ADDING AN EDGE WITH 0 AS SOURCE, 1 AS DESTINATION, 5 AS WEIGHT TO THE GRAPH.");

        System.out.println("There is no vertex whose ID is 1, so the edge will not be added.");

        myGraph.addEdge(0 , 1, 5);

        System.out.println("PRINTING THE GRAPH.");

        myGraph.printGraph();

        System.out.println("GENERATING AN VERTEX WITH 'B' AS LABEL, 2 AS WEGİHT, AND ADDING IT TO THE GRAPH");

        myGraph.addVertex(myGraph.newVertex("B", 2));

        System.out.println("PRINTING THE GRAPH.");

        myGraph.printGraph();

        System.out.println("ADDING AN EDGE WITH 0 AS SOURCE, 1 AS DESTINATION, 5 AS WEIGHT TO THE GRAPH.");

        myGraph.addEdge(0 , 1, 5);

        System.out.println("PRINTING THE GRAPH.");

        myGraph.printGraph();

        System.out.println("REMOVING AN EDGE BETWEEN 0 AND 1");

        myGraph.removeEdge(0 , 1);

        System.out.println("PRINTING THE GRAPH.");

        myGraph.printGraph();

        System.out.println("REMOVING AN EDGE BETWEEN 2 AND 3");

        System.out.println("There is not the edge on the graph, so there will not be any change.");

        myGraph.removeEdge(2 , 3);

        System.out.println("PRINTING THE GRAPH.");

        myGraph.printGraph();

        System.out.println("REMOVING A VERTEX WHOSE ID IS 1");

        myGraph.removeVertex(1);

        System.out.println("PRINTING THE GRAPH.");

        myGraph.printGraph();

        System.out.println("REMOVING A VERTEX WHOSE ID IS 5");

        System.out.println("There is not the vertex on the graph, so there will not be any change.");

        myGraph.removeVertex(5);

        System.out.println("PRINTING THE GRAPH.");

        myGraph.printGraph();

        System.out.println("REMOVING A VERTEX WHOSE LABEL IS 'A'");

        myGraph.removeVertex("A");

        System.out.println("PRINTING THE GRAPH.");

        myGraph.printGraph();

        System.out.println("REMOVING A VERTEX WHOSE LABEL IS 'D'");

        System.out.println("There is not the vertex on the graph, so there will not be any change.");

        myGraph.removeVertex('D');

        System.out.println("PRINTING THE GRAPH.");

        myGraph.printGraph();

    }

    /**
     * Tests export matrix method.
     * @param isDirected Creates an undirected/directed graph according to isDirected.
     */
    public static void testingExportMatrix(boolean isDirected) {
        MyGraph myGraph = new MyGraph(isDirected);

        System.out.println("GENERATING AN VERTEX WITH 'A' AS LABEL, 1 AS WEGİHT, AND ADDING IT TO THE GRAPH");

        System.out.println("GENERATING AN VERTEX WITH 'B' AS LABEL, 2 AS WEGİHT, AND ADDING IT TO THE GRAPH");

        System.out.println("GENERATING AN VERTEX WITH 'C' AS LABEL, 3 AS WEGİHT, AND ADDING IT TO THE GRAPH");

        System.out.println("GENERATING AN VERTEX WITH 'D' AS LABEL, 4 AS WEGİHT, AND ADDING IT TO THE GRAPH");

        System.out.println("ADDING AN EDGE WITH 0 AS SOURCE, 1 AS DESTINATION, 5 AS WEIGHT TO THE GRAPH.");

        System.out.println("ADDING AN EDGE WITH 2 AS SOURCE, 3 AS DESTINATION, 3 AS WEIGHT TO THE GRAPH.");

        System.out.println("ADDING AN EDGE WITH 0 AS SOURCE, 2 AS DESTINATION, 2 AS WEIGHT TO THE GRAPH.");

        System.out.println("ADDING AN EDGE WITH 1 AS SOURCE, 3 AS DESTINATION, 4 AS WEIGHT TO THE GRAPH.");

        myGraph.addVertex(myGraph.newVertex("A", 0));

        myGraph.addVertex(myGraph.newVertex("B", 1));

        myGraph.addVertex(myGraph.newVertex("C", 2));

        myGraph.addVertex(myGraph.newVertex("D", 3));

        myGraph.addEdge(0 , 1, 5);

        myGraph.addEdge(0 , 2, 2);

        myGraph.addEdge(2 , 3, 3);

        myGraph.addEdge(1 , 3, 4);

        System.out.println("PRINTING THE GRAPH.");

        myGraph.printGraph();

        System.out.println("PRINTING THE GRAPH IN MATRIX FORMAT");

        double[][] matrix = myGraph.exportMatrix();

        for(int i = 0; i < myGraph.getVerticesNumber(); i++){
            for(int j = 0; j < myGraph.getVerticesNumber(); j++){
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }

    }

    /**
     * Test filterVertices method.
     * @param isDirected Creates an undirected/directed graph according to isDirected.
     */
    public static void testingGraphFilter(boolean isDirected){
        MyGraph myGraph = new MyGraph(isDirected);

        System.out.println("GENERATING AN VERTEX WITH 'A' AS LABEL, 1 AS WEGİHT, AND ADDING IT TO THE GRAPH");

        System.out.println("GENERATING AN VERTEX WITH 'B' AS LABEL, 2 AS WEGİHT, AND ADDING IT TO THE GRAPH");

        System.out.println("GENERATING AN VERTEX WITH 'C' AS LABEL, 3 AS WEGİHT, AND ADDING IT TO THE GRAPH");

        System.out.println("GENERATING AN VERTEX WITH 'D' AS LABEL, 4 AS WEGİHT, AND ADDING IT TO THE GRAPH");

        System.out.println("ADDING AN EDGE WITH 0 AS SOURCE, 1 AS DESTINATION, 5 AS WEIGHT TO THE GRAPH.");

        System.out.println("ADDING AN EDGE WITH 2 AS SOURCE, 3 AS DESTINATION, 3 AS WEIGHT TO THE GRAPH.");

        System.out.println("ADDING AN EDGE WITH 0 AS SOURCE, 2 AS DESTINATION, 2 AS WEIGHT TO THE GRAPH.");

        System.out.println("ADDING AN EDGE WITH 1 AS SOURCE, 3 AS DESTINATION, 4 AS WEIGHT TO THE GRAPH.");

        System.out.println("ADDING ('A', '0') AND ('B', '1') PAIRS TO THE VERTEX WHOSE ID 0");

        System.out.println("ADDING ('B', '1') AND ('C', '2') PAIRS TO THE VERTEX WHOSE ID 0");

        System.out.println("ADDING ('C', '2') AND ('D', '3') PAIRS TO THE VERTEX WHOSE ID 0");

        System.out.println("ADDING ('D', '3') AND ('E', '4') PAIRS TO THE VERTEX WHOSE ID 0");

        myGraph.addVertex(myGraph.newVertex("A", 0));

        myGraph.addVertex(myGraph.newVertex("B", 1));

        myGraph.addVertex(myGraph.newVertex("C", 2));

        myGraph.addVertex(myGraph.newVertex("D", 3));

        myGraph.addEdge(0 , 1, 5);

        myGraph.addEdge(0 , 2, 2);

        myGraph.addEdge(2 , 3, 3);

        myGraph.addEdge(1 , 3, 4);

        HashMap<String, String> pair0 = new HashMap<String, String>();

        pair0.put("A", "0");

        pair0.put("B", "1");

        HashMap<String, String> pair1 = new HashMap<String, String>();

        pair1.put("B", "1");

        pair1.put("C", "2");

        HashMap<String, String> pair2 = new HashMap<String, String>();

        pair2.put("C", "2");

        pair2.put("D", "3");

        HashMap<String, String> pair3 = new HashMap<String, String>();

        pair3.put("D", "3");

        pair3.put("E", "4");

        myGraph.addPairs(pair0, 0);

        myGraph.addPairs(pair1, 1);

        myGraph.addPairs(pair2, 2);

        myGraph.addPairs(pair3, 3);

        System.out.println("PRINTING THE GRAPH.");

        myGraph.printGraph();

        System.out.println("PRINTS THE GRAPH WHİCH ALL VERTEX HAS ('C', '2') PAIR");

        myGraph.filterVertices("B", "1").printGraph();

    }

    /**
     * Tests BFS and DFS search algorithms.
     * @param isDirected Creates an undirected/directed graph according to isDirected.
     */
    public static void testingBFSvsDFS(boolean isDirected){
        MyGraph myGraph = new MyGraph(isDirected);

        System.out.println("GENERATING AN VERTEX WITH 'A' AS LABEL, 1 AS WEGİHT, AND ADDING IT TO THE GRAPH");

        System.out.println("GENERATING AN VERTEX WITH 'B' AS LABEL, 2 AS WEGİHT, AND ADDING IT TO THE GRAPH");

        System.out.println("GENERATING AN VERTEX WITH 'C' AS LABEL, 3 AS WEGİHT, AND ADDING IT TO THE GRAPH");

        System.out.println("GENERATING AN VERTEX WITH 'D' AS LABEL, 4 AS WEGİHT, AND ADDING IT TO THE GRAPH");

        System.out.println("ADDING AN EDGE WITH 0 AS SOURCE, 1 AS DESTINATION, 5 AS WEIGHT TO THE GRAPH.");

        System.out.println("ADDING AN EDGE WITH 2 AS SOURCE, 3 AS DESTINATION, 3 AS WEIGHT TO THE GRAPH.");

        System.out.println("ADDING AN EDGE WITH 0 AS SOURCE, 2 AS DESTINATION, 2 AS WEIGHT TO THE GRAPH.");

        System.out.println("ADDING AN EDGE WITH 1 AS SOURCE, 3 AS DESTINATION, 4 AS WEIGHT TO THE GRAPH.");

        System.out.println("ADDING ('A', '0') AND ('B', '1') PAIRS TO THE VERTEX WHOSE ID 0");

        System.out.println("ADDING ('B', '1') AND ('C', '2') PAIRS TO THE VERTEX WHOSE ID 0");

        System.out.println("ADDING ('C', '2') AND ('D', '3') PAIRS TO THE VERTEX WHOSE ID 0");

        System.out.println("ADDING ('D', '3') AND ('E', '4') PAIRS TO THE VERTEX WHOSE ID 0");

        myGraph.addVertex(myGraph.newVertex("A", 0));

        myGraph.addVertex(myGraph.newVertex("B", 1));

        myGraph.addVertex(myGraph.newVertex("C", 2));

        myGraph.addVertex(myGraph.newVertex("D", 3));

        myGraph.addEdge(0 , 2, 10);

        myGraph.addEdge(0 , 1, 3);

        myGraph.addEdge(2 , 3, 1);

        myGraph.addEdge(1 , 3, 5);

        System.out.println("PRINTING THE GRAPH.");

        myGraph.printGraph();

        Searches.distanceDifference(myGraph);
    }

    /**
     * Tests Dijkstra algorithm.
     * @param isDirected Creates an undirected/directed graph according to isDirected.
     */
    public static void testingDijkstraAlgorithm(boolean isDirected){
        MyGraph myGraph = new MyGraph(isDirected);

        System.out.println("GENERATING AN VERTEX WITH 'A' AS LABEL, 1 AS WEGİHT, AND ADDING IT TO THE GRAPH");

        System.out.println("GENERATING AN VERTEX WITH 'B' AS LABEL, 2 AS WEGİHT, AND ADDING IT TO THE GRAPH");

        System.out.println("GENERATING AN VERTEX WITH 'C' AS LABEL, 3 AS WEGİHT, AND ADDING IT TO THE GRAPH");

        System.out.println("GENERATING AN VERTEX WITH 'D' AS LABEL, 4 AS WEGİHT, AND ADDING IT TO THE GRAPH");

        System.out.println("GENERATING AN VERTEX WITH 'E' AS LABEL, 5 AS WEGİHT, AND ADDING IT TO THE GRAPH");

        System.out.println("GENERATING AN VERTEX WITH 'F' AS LABEL, 6 AS WEGİHT, AND ADDING IT TO THE GRAPH");

        System.out.println("GENERATING AN VERTEX WITH 'G' AS LABEL, 7 AS WEGİHT, AND ADDING IT TO THE GRAPH");

        System.out.println("GENERATING AN VERTEX WITH 'H' AS LABEL, 8 AS WEGİHT, AND ADDING IT TO THE GRAPH");

        System.out.println("ADDING AN EDGE WITH 0 AS SOURCE, 1 AS DESTINATION, 3 AS WEIGHT TO THE GRAPH.");

        System.out.println("ADDING AN EDGE WITH 0 AS SOURCE, 2 AS DESTINATION, 4 AS WEIGHT TO THE GRAPH.");

        System.out.println("ADDING AN EDGE WITH 1 AS SOURCE, 4 AS DESTINATION, 1 AS WEIGHT TO THE GRAPH.");

        System.out.println("ADDING AN EDGE WITH 1 AS SOURCE, 7 AS DESTINATION, 4 AS WEIGHT TO THE GRAPH.");

        System.out.println("ADDING AN EDGE WITH 6 AS SOURCE, 7 AS DESTINATION, 2 AS WEIGHT TO THE GRAPH.");

        System.out.println("ADDING AN EDGE WITH 2 AS SOURCE, 6 AS DESTINATION, 7 AS WEIGHT TO THE GRAPH.");

        System.out.println("ADDING AN EDGE WITH 3 AS SOURCE, 5 AS DESTINATION, 2 AS WEIGHT TO THE GRAPH.");

        System.out.println("ADDING AN EDGE WITH 3 AS SOURCE, 6 AS DESTINATION, 3 AS WEIGHT TO THE GRAPH.");

        myGraph.addVertex(myGraph.newVertex("A", 1));

        myGraph.addVertex(myGraph.newVertex("B", 2));

        myGraph.addVertex(myGraph.newVertex("C", 3));

        myGraph.addVertex(myGraph.newVertex("D", 4));

        myGraph.addVertex(myGraph.newVertex("E", 5));

        myGraph.addVertex(myGraph.newVertex("F", 6));

        myGraph.addVertex(myGraph.newVertex("G", 7));

        myGraph.addVertex(myGraph.newVertex("H", 8));

        myGraph.addEdge(0, 1, 3);

        myGraph.addEdge(0, 2, 4);

        myGraph.addEdge(1, 4, 1);

        myGraph.addEdge(1, 7, 4);

        myGraph.addEdge(6, 7, 2);

        myGraph.addEdge(2, 6, 7);

        myGraph.addEdge(3, 5, 2);

        myGraph.addEdge(3, 6, 3);

        System.out.println("PRINTING THE GRAPH.");

        myGraph.printGraph();

        Searches.dijkstraSearch(myGraph, 0);

    }
}
