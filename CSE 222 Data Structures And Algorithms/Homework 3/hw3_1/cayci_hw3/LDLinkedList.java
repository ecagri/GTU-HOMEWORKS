package cayci_hw3;

import java.util.AbstractList; 
import java.util.List;

/**
 * LinkedList implementation of List. 
 * @author cagri cayci
 * @param <E> To make class generics. 
 */
public class LDLinkedList<E> extends AbstractList<E> implements List<E> {
    /**
     * Keeps size of the LDLinkedList as integer.
     */
    private int size;
    
    /**
     * Keeps head of the LDLinkedList as Node to reach the elements of the LDLinkedList.
     */
    private Node<E> head;
    
    /**
     * Keeps tail of the LDLinkedList as Node to increase performance of reaching the elements.
     */
    private Node<E> tail;
    
    /**
     * No parameter constructor. 
     */
    public LDLinkedList(){ /* θ(1) time complexity. */
        size = 0;
        head = null;
    }
    
    /**
     * Clears the LDLinkedList.
     */
    @Override 
    public void clear(){ /* θ(1) time complexity. */
        head = null;
        tail = null;
        size = 0;
    }
    
    /**
     * Adds an element to LDLinkedList to the end of the list.
     * @param data Takes a data of type E.
     * @return Returns true.
     */
    @Override 
    public boolean add(E data){ /* θ(1) time complexity. */
        Node<E> element = new Node<E>(data); /* Creates a element. */
        
        if(head == null){ /* If the LDLinkedList is empty, assings the element the head of the LDLinkedList. */
            head = element;
        }
        else{ 
            tail.next = element; /* Assigns element to next element of the tail. */
            element.prev = tail; /* Makes previous element of the element tail. */
        }
        tail = element; /* Assings element to tail .*/
        size++; /* Increases the size. */
        return true; /* Returns true. */
    }
    
    /**
     * Adds an element to LdLinkedList to the end of the list.
     * @param element Takes an element of type Node.
     * @return Returns true if element is not null, otherwise false.
     */
    public boolean add(Node<E> element){ /* θ(1) time complexity. */
        if(element == null)
            return false;
        else{
            element.next = null; /* Sets element next to null.*/
            element.prev = null; /* sets element prev to null. */
            if(head == null){ /* If the LDLinkedList is emptyi assigns the element the head of the LDLinkedList. */
                head = element;
            }
            else{
                tail.next = element; /* Assigns element to next element of the tail. */ 
                element.prev = tail; /* Makes previous element of the element tail. */
            }
            tail = element; /* Assigns element to tail. */
            size++; /* Icreases the size. */
            return true; 
        }
    }
    
    /**
     * Adds an element to the given index.
     * @param index Gets index as integer.
     * @param data Gets data as integer.
     * @throws IndexOutOfBoundsException Throws exception if index is out of boundaries. 
     */
    @Override  
    public void add(int index, E data) throws IndexOutOfBoundsException{ /* O(n) time complexity. */
        if(index < 0 || index >= size) /* Checks boundaries. */
           throw new IndexOutOfBoundsException();
        else{
            Node<E> element = new Node<E>(data); /* Creates a new node. */
            if(index == size - 1){ /* If index is the last element of the LDLinkedList calls add method. */
                tail.next = element;
                element.prev = tail;
                tail = element;
            }
            else if(index == 0){
                element.next = head; /* Assigns head to next of the element. */
                head.prev = element; /* Assings element to prev of the head. */
                head = element; /* Assigns element to head. */
            }
            else{
                Node<E> temp = head; /* Creates a temp node. */
                for(int i = 0; i < index; i++) /* Traverses the LDLinkedList. */
                    temp = temp.next;
                element.next = temp.next; /* Assigns next of the next of the temp to next of the element. */
                temp.next.prev = element;
                element.prev = temp; /* Assings temp to prev of the element. */
                temp.next = element; /* Assigns element to next of the temp. */
            }
            size++; /* Increases size. */
        }
    }
    
    /**
     * Search the list for a data, if it founds, returns the node.
     * @param data  Gets the data type of E. 
     * @return  Returns a Node which contain the data if it found, otherwise returns null.
     */
    public Node<E> findNode(E data){ /* O(n) time complexity. */
        Node<E> temp = head;
        while(temp != null){
            if(temp.data.equals(data))
                return temp;
            temp = temp.next;
        }
        return null;
    }
    
    /**
     * Gets the data of the Node by giving index.
     * @param index Gets index as integer.
     * @return Returns the data.
     * @throws IndexOutOfBoundsException Throws an exception if index is out of boundaries.
     */
    @Override
    public E get(int index) throws IndexOutOfBoundsException{ /* O(n) time complexity. */
        if(index < 0 || index >= size) /* Checks boundaries. */
           throw new IndexOutOfBoundsException();
        else{
            if(index == 0)
                return head.data;
            else if(index == size - 1)
                return tail.data;
            else{
                Node<E> temp = head;
                for(int i = 0; i < index; i++){
                    temp = temp.next;
                }
                return temp.data;
            }
        }
    }
       
    /**
     * Removes an element by given index.
     * @param index Takes index of the element as integer
     * @return Returns the data of the removed element
     * @throws IndexOutOfBoundsException Throws IndexOutOfBoundsException if index is less than 0, index is bigger than or equal to size.
     */
    @Override 
    public E remove(int index) throws IndexOutOfBoundsException { /* O(n) time complexity. */
        if(index < 0 || index >= size) /* If index is less than 0, index is bigger than or equal to size, throw an exception. */
           throw new IndexOutOfBoundsException();
        else{
            E data; /* Creates a data. */
            size--; /* Decreases the size. */
            if(index == 0){ /* If index is 0, removes an element from at the beginning of the LDLinkedList. */
                data = head.data; /* Assings data to data of head. */
                head = head.next; /* Makes head, the next element of the head */
            }
            else if(index == size - 1){  /* If index is last element of the list, removes an element from the at end of the LDLinkedList. */
                data = tail.data; /* Assings data to data of tail. */
                tail.prev.next = null; /* Makes the next node of the previous element from tail, null. */
                tail = tail.prev; /* Makes tail, the next element of the tail. */
            }
            else{ /* If the element is not first or last element, continue. */
                Node<E> temp = head; /* Creates a temp Node and assign it to head. */
                for(int i = 0; i < index; i++) /* Traverses in the LDLinkedList index time. */
                    temp = temp.next;
                data = temp.data; /* Assings data to data of the indexth element of the LDLinkedList. */
                temp.prev.next = temp.next; /* Assings the next of the previous element of the temp, next of the temp. */
                temp = temp.next; /* Asssings temp to next element of the temp. */
            }
            return data; /* Returns the data. */
        }
    }
    
    /**
     * Sets the data of the node of the given index.
     * @param index Takes index as integer.
     * @param element Takes element type of E.
     * @return Returns the element
     * @throws IndexOutOfBoundsException Throws an exception if it violates boundaries.
     */
    @Override
    public E set(int index, E element) throws IndexOutOfBoundsException{ /* O(n) time complexity. */
        if(index < 0 || index >= size) /* Checks boundaries. */
           throw new IndexOutOfBoundsException();
        else{
            E data; /* Creates a data. */
            if(index == 0){ /* If the index is 0, replace head element. */
                data = head.data; /* Gets the previous data. */
                head.data = element; /* Replaces the element. */
            }
            else if(index == size - 1){ /* If the index is last element, replace tail. */
                data = tail.data; /* Gets the previous data. */
                tail.data = element; /* Replaces the element. */
            }
            else{ 
                Node<E> temp = head; /* Creates a temp Node. */
                for(int i = 0; i < index; i++){  /* Traverses in the LDLinkedList. */
                    temp = temp.next;
                }
                data = temp.data; /* Gets the previous data. */
                temp.data = element; /* Replaces the element. */
            }
            return data;
        }
    }

    /**
     * Gets size of the LDLinkedList.
     * @return Returns size as integer.
     */
    @Override 
    public int size() { /* θ(1) time complexity. */
        return size;
    }
    
    public String toString(){ /* θ(n) time complexity. */
        Node<E> node = new Node<E>();
        StringBuilder str = new StringBuilder();
        node = head;
        for(int index = 0; index < size; index++){
            if(index != 0)
                str.append("->");
            str.append(node.data);
            node = node.next;
        }
        return str.toString();
    }    
    
    /**
     * Inner class for Node.
     * @param <E> To make class generics.
     */
    protected static class Node<E>{
        /**
         * Keeps next element reference.
         */
        private  Node<E> next = null;
        
        /**
         * Keeps previous element reference.
         */
        private Node<E> prev = null;
        
        /**
         * Keeps data of Node.
         */
        private E data;
        /**
         * One parameter constructor.
         * @param _data Gets data type of E.
         */
        public Node(E _data){ /* θ(1) time complexity. */
            data = _data;
        }
        
        /**
         * No parameter constructor.
         */
        public Node(){ /* θ(1) time complexity. */
            data = null;
        } 
    }
}

