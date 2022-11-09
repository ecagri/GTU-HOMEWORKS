package cayci_hw7;

/**
 * An implementation of a Binary Search Tree to use its add method.
 * @param <T> Generics T parameter which extends from Comparable class.
 */
public class BinarySearchTree<T extends Comparable<T>>{

    /**
     * Keeps the root node of the Binary Search Tree.
     */
    private Node<T> rootNode;

    /**
     * Keeps the number of elements in Binary Search Tree.
     */
    private int elementsNumber;
    
    /**
     * Keeps current state of the BinarySearchTree.
     */
    private boolean balanced = false;

    /**
     * No parameter constructor for BinarySearchTree class.
     * Creates an empty Binary Search Tree.
     */
    public BinarySearchTree(){
        this.rootNode = null;
        this.elementsNumber = 0;
    }

    /**
     * Finds the size of the Binary Search Tree.
     * @return Returns the number of elements in BinarySearchTree.
     */
    public int size(){
        return elementsNumber;
    }

    /**
     * Adds an item to BinarySearchTree. Returns true if the add operation is completed.
     * @param item Takes item to add.
     * @return Returns true if the element is added, otherwise false.
     */
    public boolean add(T item){
        if(this.rootNode == null) { /* If the Binary Search Tree is empty, creates a new node and assigns it to root node. */
            this.rootNode = new Node<T>(item);
            elementsNumber = elementsNumber + 1; /* Increases elements number by one. */
            return true;
        }
        else{ /* If the Binary Search Tree is not empty, calls overloaded add method. */
            return add(item, rootNode);
        }
    }

    /**
     * Prints Binary Search Tree in pretty format.
     */
    public void printBinarySearchTree(){
        printBinarySearchTree(rootNode, 0);
    }

    /**
     * Converts Binary Search Tree into a balanced Binary Search Tree (AVL Tree) and prints it.
     * @param toConvert Gets a Binary Search Tree which will be converted into AVL Tree.
     */
    public void toAVLTree(BinarySearchTree<T> toConvert){
        do{ /* Continues until Binary Search Tree is balanced. */
            toConvert.balanceTree(toConvert.rootNode); /* Balances Binary Search Tree. */
        }while(!toConvert.balanced);
        toConvert.printBinarySearchTree(); /* Prints AVL Tree. */
    }

    /**
     * Recursively balances Binary Search Tree and returns it.
     * @param node Gets the root node of the Binary Search Tree.
     */
    private void balanceTree(Node<T> node){
        balanced = true; /* Makes balanced field false. */

        if(node == null) return; /* If node is null, terminates. */

        balanceTree(node.leftChild); /* Balances left subtree. */
        balanceTree(node.rightChild); /* Balances right subtree. */

        setHeight(node); /* Set height of the node. */

        setWeight(node);

        balanced = balanceNode(node); /* Balance the node, returns true if it is balanced. */

    }

    /**
     * Balances a node according to states(LL, LR, RL, RR).
     * @param node Gets a node to balance it.
     * @return Returns true if the node is one of the states, otherwise false.
     */
    private boolean balanceNode(Node<T> node){
        if(1 < node.weight){ /* If weight of the node is bigger than 1. */
            if(node.rightChild.weight > -1) {/* If weight of the right child of the node is bigger than -1, continues. */
                /* This is Right-Right tree. */
                rotateLeft(node.parent, node); /* Rotates the node left. */
            }
            else{ /* If weight of right child is less than or equal to -1, continues. */
                /* This is Right-Left tree. */
                rotateRight(node, node.rightChild); /* Rotates the right child of the node right. */
                rotateLeft(node.parent, node); /* Rotates the node left. */
            }
            return false;
        }
        else if(node.weight < -1){ /* If weight of the node is less than -1. */
            if(node.leftChild.weight < 1) { /* If weight of the left child of the node is less than 1, continues. */
                /* This is Left-Left tree. */
                rotateRight(node.parent, node); /* Rotates the node right. */
            }
            else{ /* If weight of left child is less than or equal to -1, continues. */
                rotateLeft(node, node.leftChild); /* Rotates the left child of the node left. */
                rotateRight(node.parent, node); /* Rotates the node right. */
            }
            return false;
        }
        return true;
    }

    /**
     * Sets height of a node according to its child.
     * @param root Gets a node to set its height.
     */
    private void setHeight(Node<T> root){
        if(root.rightChild == null && root.leftChild == null) /* If the node is leaf, height of it is 1. */
            root.height = 1;
        else if(root.rightChild == null && root.leftChild != null) /* If the node has only left child, height of it is 1 more of height of the left child. */
            root.height = root.leftChild.height + 1;
        else if(root.leftChild == null) /* If the node has only right child, height of it is 1 more of height of the right child. */
            root.height = root.rightChild.height + 1;
        else /* If the node has both children, height of the node is 1 more of the max of the height of the right and left child. */
            root.height = Math.max(root.rightChild.height, root.leftChild.height) + 1;
    }

    /**
     * Sets weight of a node according to height of the children of it.
     * @param node Gets a node to set its weight.
     */
    private void setWeight(Node<T> node){
        int rightHeight = (node.rightChild != null) ? node.rightChild.height : 0; /* Gets right child height of the node. */
        int leftHeight = (node.leftChild != null) ? node.leftChild.height : 0; /* Gets left child height of the node. */
        node.weight = rightHeight - leftHeight; /* Sets weight of the node as subtraction of height of left child from right child. */
    }

    /**
     * Rotates a node right.
     * @param parent Gets a node which is parent of the node which will be rotated.
     * @param toRotate Gets the node which will be rotated.
     */
    private void rotateRight(Node<T> parent, Node<T> toRotate){
        boolean isRootNode = (toRotate == rootNode); /* Checks whether the node which will be rotated is root node or not. */
        boolean isRightChild = !isRootNode && (parent.rightChild == toRotate); /* Checks whether the node which will be rotated is right or left child of its parent if the node is not root node. */
        /* Make rotation. */
        Node<T> temp = toRotate.leftChild;
        toRotate.leftChild = temp.rightChild;
        temp.rightChild = toRotate;
        toRotate.parent = temp;
        if(isRootNode) /* If the node is root node, assign root node to temp. */
            rootNode = temp;
        else{ /* If the node is not root node, continues. */
            if(isRightChild)  /* If the node is right child of its parent, assigns temp to right child of the parent. */
                parent.rightChild = temp;
            else parent.leftChild = temp; /* If the node is left child of its parent, assigns temp to left child of the parent. */
        }
        setHeight(toRotate); /* Sets height of the toRotate node. */
        setHeight(temp); /* Sets height of the temp node. */
        setWeight(toRotate);
        setWeight(temp);
    }

    /**
     * Rotates a node left.
     * @param parent Gets a node which is parent of the node which will be rotated.
     * @param toRotate Gets the node which will be rotated.
     */
    private void rotateLeft(Node<T> parent, Node<T> toRotate){
        boolean isRootNode = (toRotate == rootNode); /* Checks whether the node which will be rotated is root node or not. */
        boolean isRightChild = !isRootNode && (parent.rightChild == toRotate); /* Checks whether the node which will be rotated is right or left child of its parent if the node is not root node. */
        /* Makes rotation. */
        Node<T> temp = toRotate.rightChild;
        toRotate.rightChild = temp.leftChild;
        temp.leftChild = toRotate;
        toRotate.parent = temp;
        if(isRootNode) /* If the node is root node, assign root node to temp. */
            rootNode = temp;
        else{ /* If the node is not root node, continues. */
            if(isRightChild)  /* If the node is right child of its parent, assigns temp to right child of the parent. */
                parent.rightChild = temp;
            else parent.leftChild = temp; /* If the node is left child of its parent, assigns temp to left child of the parent. */
        }
        setHeight(toRotate); /* Sets height of the toRotate node. */
        setHeight(temp); /* Sets height of the temp node. */
        setWeight(toRotate);
        setWeight(temp);
    }

    /**
     * Recursively prints the Binary Search Tree.
     * @param rootNode Gets the root node of the Binary Search Tree.
     * @param symbol Gets the number of symbol before prints data of the node.
     */
    private void printBinarySearchTree(Node<T> rootNode, int symbol){
        for(int i = 0; i < symbol; i++){ /* Put '__' sign before the data. */
            System.out.print("__");
        }
        if(rootNode == null){
            System.out.println("null");
            return;
        }
        System.out.println(rootNode); /* Prints data. */
        printBinarySearchTree(rootNode.leftChild, symbol + 2); /* Prints left child data with 2 more symbol. */
        printBinarySearchTree(rootNode.rightChild, symbol + 2); /* Prints right child data with 2 more symbol. */
    }

    /**
     * Recursively adds an item to BinarySearchTree. Returns true if the add operation is completed.
     * @param item Takes item to add.
     * @param rootNode Starts searching the position of the new item from root node.
     * @return Returns true if the element is added, otherwise false.
     */
    private boolean add(T item, Node<T> rootNode){
        if(this.rootNode == null) /* If the root node is empty, returns false. */
            return false;

        int comparison = item.compareTo(rootNode.getData()); /* Compares item with data of root node. */
        if(comparison == 0) /* If the item is already in Binary Search Tree, returns false. */
            return false;
        else if(comparison < 0){ /* If the item is less the data of the root node, continue. */
            if(rootNode.getLeftChild() == null){ /* If the left child of the root node is empty, adds item there. */
                rootNode.leftChild = new Node<T>(item);
                rootNode.leftChild.parent = rootNode;
                elementsNumber = elementsNumber + 1; /* Increases elements number by 1. */
                return true;
            }
            else{ /* If the left child of the root node is not empty, continues searching. */
                return add(item, rootNode.getLeftChild());
            }
        }
        else{ /* If the item is bigger than the data of the root node, continue. */
            if(rootNode.getRightChild() == null){ /* If the right child of the root node is empty, adds item there. */
                rootNode.rightChild = new Node<T>(item);
                rootNode.rightChild.parent = rootNode;
                elementsNumber = elementsNumber + 1; /* Increases elements number by 1. */
                return true;
            }
            else{ /* If the right child of the root node is not empty, continues searching. */
                return add(item, rootNode.getRightChild());
            }
        }
    }

    /**
     * Keeps nodes of the Binary Search Tree.
     * @param <T> Generics T parameter which extends from Comparable class.
     */
    private static class Node<T extends Comparable<T>>{

        /**
         * Keeps data of the node.
         */
        private final T data;

        /**
         * Keeps the right child of the node.
         */
        private Node<T> rightChild;

        /**
         * Keeps the left child of the node.
         */
        private Node<T> leftChild;

        /**
         * Keeps the parent of the node.
         */
        private Node<T> parent;

        /**
         * Keeps the height of the node.
         */
        private int height;

        /**
         * Keeps the weight of the node.
         */
        private int weight;

        /**
         * One parameter constructor for Node class.
         * @param data Takes data of the node as parameter.
         */

        public Node(T data){
            this.data = data;
            rightChild = null;
            leftChild = null;
        }

        /**
         * Gets the left child of the node.
         * @return Returns the left child of the node.
         */
        public Node<T> getLeftChild() {
            return leftChild;
        }

        /**
         * Gets the right child of the node.
         * @return Returns the left child of the node.
         */
        public Node<T> getRightChild() {
            return rightChild;
        }

        /**
         * Gets the data of the node.
         * @return Returns the data of the node.
         */
        public T getData() {
            return data;
        }

        /**
         * Converts Node class to String.
         * @return Returns the String version of the Node class.
         */
        @Override
        public String toString() {
            return data.toString();
        }
    }
}
