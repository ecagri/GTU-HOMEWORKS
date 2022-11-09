package cayci_hw7;

import java.util.Random;

/**
 * A class keeps elements in Skip List format.
 * @param <T> To make class generics.
 * @author cagri cayci
 */
public class CustomSkipList<T extends Comparable<T>>{
    /**
     * Keeps elements in Node array.
     */
    private Node<T>[] lists;
    /**
     * Keeps the number of lists on Skip List.
     */
    private int level = 2;
    /**
     * Keeps the number of elements on Skip List.
     */
    private int elementsNumber = 0;

    /**
     * No parameter constructor.
     */
    @SuppressWarnings("unchecked")
    public CustomSkipList(){
        lists = (Node<T>[]) new Node[level];
    }

    /**
     * Adds a data to the list.
     * @param data Takes the data to add.
     */
    @SuppressWarnings("unchecked")
    public void add(T data){
        if((elementsNumber + 1) % 10 == 0)
            increaseLevel();
        Node<T>[] predecessor = (Node<T>[]) new Node[level]; /* Creates a Node array to keep predecessor. */
        predecessor = search(predecessor, lists[level - 1], data, level - 1); /* Finds predecessor and assigns it. */
        addHeightLayer(predecessor, null, data, 0); /* Adds the element to the layers. */
        elementsNumber = elementsNumber + 1; /* Increases element number by one. */
    }

    /**
     * Prints Skip List in pretty way.
     */
    public void printCustomSkipList(){
        for(int i = 0; i < elementsNumber; i++){
            System.out.print("--");
        }
        System.out.println();
        for(int index = level - 1; index > -1; index--){ /* Starts from top list goes to the bottom list. */
            Node<T> temp = lists[index];
            while(temp != null){
                System.out.print(temp + " -> ");
                temp = temp.next;
            }
            System.out.println();
        }
        for(int i = 0; i < elementsNumber; i++){
            System.out.print("--");
        }
        System.out.println();
    }

    /**
     * Adds the element to the layers according to its height.
     * @param predecessor Takes the predecessor to place element.
     * @param prevElement Takes the prevElement as element of down layer.
     * @param data Takes the data of the new element.
     * @param index Takes the index of the layer.
     */
    private void addHeightLayer(Node<T>[] predecessor, Node<T> prevElement, T data, int index){
        Node<T> newElement = new Node<T>(data); /* Creates a new node. */

        addOneLayer(predecessor[index], newElement, index); /* Adds the element to the layer. */

        if(prevElement != null){ /* If this is not the bottom layer, sets down and height of the element. */
            newElement.down = prevElement;
            prevElement.up = newElement;
            newElement.height = prevElement.height;
        }
        else /* If this is the bottom layer, set the height of the element. */
            setHeight(newElement);

        if(index < newElement.height - 1) /* Recursively call the function until all layer is filled. */
            addHeightLayer(predecessor, newElement, data, index + 1);
    }

    /**
     * Searches the lists and finds the predecessor of an element.
     * @param predecessor Takes the predecessor as Node array.
     * @param node Takes the node which is the beginning of the top layer.
     * @param data Takes the data of the new element.
     * @param index Takes the index of the layer.
     * @return Returns the predecessor as Node array.
     */
    private Node<T>[] search(Node<T>[] predecessor, Node<T> node, T data, int index){
        if(node != null){ /* If node is not equal to null, continue. */
            while(data.compareTo(node.data) >= 0 && node.next != null){ /* Goes until data is bigger than data of the node or next node is null. */
                node = node.next;
            }
            predecessor[index] = node; /* Assigns predecessor. */

            if(node.prev != null) /* If previous node is not null, recursively call search function with down node of the prev node of the node. */
                return search(predecessor, node.prev.down, data, index - 1);
        }
        if(index <= 0) /* If index is less than or equal to 0, return predecessor. */
            return predecessor;
        else /* Otherwise, recursively call search function with down layer. */
            return search(predecessor, lists[index - 1], data, index - 1);
    }

    /**
     * Increase the number of lists on skip list.
     */
    @SuppressWarnings("unchecked")
    private void increaseLevel(){
        Node<T>[] newLists = (Node<T>[]) new Node[level + 1]; /* Creates new Node array with level + 1 size. */

        for(int i = 0; i < level; i++){ /* Copies previous lists. */
            newLists[i] = lists[i];
        }
        level = level + 1; /* Increases level by one. */

        lists = newLists; /* Assigns new lists to lists. */

        increaseHeight(); /* Increases the height of the tall nodes by one. */
    }

    /**
     * Increases the height of the tall nodes by one.
     */
    private void increaseHeight(){

        Node<T> node = lists[1]; /* Starts from second list. */

        while(node != null){ /* Continues until the end of the second list. */

            Node<T> temp = node; /* Keeps the node. */

            Node<T> element = new Node<T>(node.data); /* Creates an element which has the same data with node. */

            node.height = node.height + 1; /* Increases the height of the node by one. */

            element.height = node.height; /* Sets the element height. */

            /* Goes up to the top element. */
            while(node.up != null)
                node = node.up;

            /* Adds one more layer on top element. */
            node.up = element;

            element.down = node;

            Node<T> layer = lists[temp.height - 1];

            /* Adds the layer to the lists. */
            addOneLayer(layer, element, element.height - 1);

            node = temp.next;
        }
    }

    /**
     * Adds an element to one layer.
     * @param node The starting node of layer.
     * @param newElement The new element to add.
     * @param index Keeps the index of the current layer.
     */
    private void addOneLayer(Node<T> node, Node<T> newElement, int index){
        if(node == null) /* If the list is empty, adds it as first element. */
            lists[index] = newElement;
        else{ /* If the list is not empty, continue. */
            while(newElement.data.compareTo(node.data) >= 0 && node.next != null){ /* Goes until data of new element is bigger than data of the element on the list or list is finished. */
                node = node.next;
            }
            if(newElement.data.compareTo(node.data) >= 0){ /* If the data of new element is bigger than data of the node, adds it as the next element of the node. */
                node.next = newElement;
                newElement.prev = node;
            }
            else{ /* If the data of the new element is less than data of the node, adds it as the previous element of the node. */
                if(node.prev == null) /* If the previous element is null, the new element is the beginning of the list. */
                    lists[index] = newElement;
                else{
                    newElement.prev = node.prev;
                    node.prev.next = newElement;
                }
                newElement.next = node;
                node.prev = newElement;
            }
        }
    }

    /**
     * Randomly set height of a node which will be added to list.
     * @param node The node which will be added to the list.
     */
    private void setHeight(Node<T> node){

        int[] possibilityArray = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; /* Creates an array with full of zeros. */

        int distance = 0;

        int height = 1;

        Random rand = new Random();

        Node<T> temp = node;
        /* Finds the distance to the nearest left node which height is greater than 1. */
        while(temp.prev != null && temp.prev.height == 1){
            distance = distance + 1;
            temp = temp.prev;
        }

        temp = node;

        /* Finds the distance to the nearest left node which height is greater than 1. */
        while(temp.next != null && temp.next.height == 1){
            distance = distance + 1;
            temp = temp.next;
        }

        /* Fills possibility array with ones as much as distance. */
        for(int i = 0; i < distance && i < possibilityArray.length; i++){
            possibilityArray[i] = 1;
        }

        /* Randomly increases height. */
        while(possibilityArray[rand.nextInt(10)] == 1 && height < level){
            height = height + 1;
        }

        /* Assigns height to height of the node. */
        node.height = height;
    }

    /**
     * An inner class which keeps data, height, and links of four directions.
     * @param <T> To make class generics.
     */
    private static class Node<T extends Comparable<T>>{
        /**
         * Keeps data.
         */
        private T data;
        /**
         * Keeps the link of next element.
         */
        private Node<T> next;
        /**
         * Keeps the link of prev element.
         */
        private Node<T> prev;
        /**
         * Keeps the link of down element.
         */
        private Node<T> down;
        /**
         * Keeps the link of up element.
         */
        private Node<T> up;
        /**
         * Keeps height of the node.
         */
        private int height;

        /**
         * One parameter constructor.
         * @param data Gets data of the node.
         */
        public Node(T data){
            this.data = data;
        }

        /**
         * Converts the Node into String.
         * @return Returns the String version of the Node.
         */
        @Override
        public String toString() {
            return data.toString();
        }
    }
}
