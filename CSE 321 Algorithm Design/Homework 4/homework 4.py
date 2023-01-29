import random
from random import randint

# QUESTION 1
def maxPointsFinder(board, x, y, curPoints, maxPoints): # Finds the path with the most points.
    curPoints = curPoints + board[y][x]; # Gets points of current location.
    if(x == len(board[0])-1 and y == len(board)-1): # If the location is AnBn, continue.
        if(curPoints > maxPoints): # If the points which are collected from current path is bigger than maximum points, set current points to max points.
            maxPoints = curPoints
    if(x != len(board[0]) - 1): # If the coloumn is not the last coloumn, recursively call maxPointsFinder function.
        maxPoints = maxPointsFinder(board, x + 1, y, curPoints, maxPoints)
    if(y != len(board) - 1): # If the row is not the last row, recursively call maxPointsFinder function.
        maxPoints = maxPointsFinder(board, x, y + 1, curPoints, maxPoints)
    return maxPoints # Returns the max points.
#---------------------------------------------------------------------------------------------------------------
# QUESTION 2 
def findMedian(array, start, end, k): # Find median of an array.
    if(len(array)%2 == 1): # If number of elements is odd, call kthElementSearch function.
        return kthElementSearch(array, start, end, k)
    else: # If number of elements is even, call kthElementSearch function for both k and k + 1.
        return (kthElementSearch(array, start, end, k) + kthElementSearch(array, start, end, k + 1)) / 2

def kthElementSearch(array, start, end, k): # Find kth element in sorted array.
    position = partition(array, start, end)
    if(position == k): # If position equals to k, return positionth element in the array.
        return array[position]
    elif(position > k): # If position is bigger than k, recursively call kthElementSearch function for the left side of the array.
        return kthElementSearch(array, start, position - 1, k)
    else: # If position is less than k, recursively call kthElementSearch function for the right side of the array.
        return kthElementSearch(array, position + 1, end, k)


def partition(array, start, end): # Selects last element as pivot and place lower elements in left side of the pivot, upper elements in right side of the pivot.
    pivot = array[end] # Selects last element as pivot.
    for i in range(start, end): # Continues from start to end.
        if(array[i] <= pivot): # If ith element is lower than pivot, swap it with element at position start and icrease start by 1.
            array = swap(array, i, start)
            start = start + 1
    swap(array, start, end) # Swap start end end.
    return start
    
def swap(array, first, second): # Swap location of two elements in the array.
    temp = array[first] 
    array[first] = array[second]
    array[second] = temp
    return array

#---------------------------------------------------------------------------------------------------------------
# QUESTION 3.a
class node: 
    def __init__(self, name): # Constructor for node.
        self.name = name
        self.visited = False
        self.next = None
class circularLinkedList:
    def __init__(self): # Constructor for circularLinkedList.
        self.head = None
        self.length = 0
    def addNode(self, name): # Add a node to end of the circularLinkedList.
        newNode = node(name)
        if(self.length == 0): # If the circularLinkedList is empty, add the element to the beginning.
            self.head = newNode
            newNode.next = self.head
        else: # If the circularLinkedList is not empty, continue.
            curNode = self.head 
            while(curNode.next != self.head): # Traverse until the last element of the list.
                 curNode = curNode.next
            # Set new element as next element of the last element.
            newNode.next = self.head 
            curNode.next = newNode

        self.length = self.length + 1
    def findWinner(self): # Finds the winner of the game.
        node = self.head
        while(node.next != None and node.next != node): # Traverse the circularLinkedList until one element is left.
            node.next = node.next.next # Eliminate next element.
            node = node.next # Continue with the new next element.
        print("\nThe winner is: ", node.name)
    def traverse(self): # Traverse and print the circularLinkedList.
        node = self.head
        while(node != None):
            print(node.name, "->" , end="")
            node = node.next
            if(node == self.head):
                break

#---------------------------------------------------------------------------------------------------------------
# QUESTION 3.b

def findWinner(table): # Finds the winner of the game.
    numberOfPlayer = len(table) # Number of player is equal to length of the array.
    totalSum = 0; # Current sum.
    multiplier = 2 # Current multiplier.
    while numberOfPlayer > 1: # Continue until number of player is equal to or less than 1.
        remainder = int(numberOfPlayer % 2) # Finds remainder.
        totalSum = totalSum + multiplier * remainder # Add remainder * multiplier to total sum.
        multiplier = multiplier * 2 # Multiply multiplier by 2.
        if(remainder == 1): # If remainder is 1, subtract numberofplayer than 1, and divide it by 2.
            numberOfPlayer = (numberOfPlayer - 1)/2
        else: # Otherwise divide numberofplayer by 2.
            numberOfPlayer = numberOfPlayer/2
    if(numberOfPlayer == 1): # If the numberofplayer is 1, add 1 to the total sum.
        totalSum = totalSum + 1
    print("The winner is: P" + str(totalSum))

#---------------------------------------------------------------------------------------------------------------
# TESTS

def maxPointsFinderTest(): # Test maxPointsFinder function with random numbers.
    print("Test maxPointsFinder randomly...")
    cols = random.randint(3, 8)
    rows = random.randint(3, 8)
    board = [[random.randint(1,9) for i in range(cols)] for i in range(rows)]
    for i in range(rows):
        for j in range(cols):
            print(board[i][j], ", ", end="")
        print()
    print(maxPointsFinder(board, 0, 0, 0, 0));      

def maxPointsFinderTestv2(): # Test maxPointsFinder function with user inputs.
    print("Test maxPointsFinder by getting input...")
    cols = int(input("Print number of cols: "))
    rows = int(input("Print number of rows: "))
    board = [[0]*cols] * rows
    for i in range(rows):
        row = [0] * cols
        for j in range(cols):
            print("Enter the board[", i,"][", j,"]: ", end="")
            row[j] = int(input())
        board[i] = row
    for i in range(rows):
        for j in range(cols):
            print(board[i][j], ", ", end="")
        print()
    print(maxPointsFinder(board, 0, 0, 0, 0));

def findMedianTest(): # Test findMedian function with random numbers.
    print("Test findMedian randomly...")
    array = [random.randint(1, 100) for i in range(random.randint(1, 10))]
    print(array)
    print("Median is: ", findMedian(array, 0, len(array) - 1, int((len(array) - 1) / 2)))

def findMedianTestv2(): # Test findMedian function with user inputs.
    print("Test maxPointsFinder by getting input...")
    size = int(input("Print size: "))
    array = [0] * size
    for i in range(size):
        print("Enter the array[", i,"]: ", end="")
        array[i] = int(input())
    print(array)
    print("Median is: ", findMedian(array, 0, len(array) - 1, int((len(array) - 1) / 2)))
def findWinnerCLLTest(): # Test findWinner function for circular linked list with random size.
    print("Test findWinner randomly for Q3.a...")
    playerNumber = random.randint(1, 10)
    table = circularLinkedList()
    for i in range(playerNumber):
        table.addNode("P" + str(i+1))
    table.traverse()
    table.findWinner()
def findWinnerCLLTestv2(): # Test findWinner function for circular linked list with user inputs.
    print("Test findWinner by getting input for Q3.a...")
    playerNumber = int(input("Enter the number of players: "))
    table = circularLinkedList()
    for i in range(playerNumber):
        table.addNode("P" + str(i+1))
    table.traverse()
    table.findWinner()
def findWinnerTest():
    print("Test findWinner randomly for Q3.b...")
    playerNumber = random.randint(1, 10)
    table = []
    for i in range(playerNumber):
        table.append("P" + str(i+ 1))
    print(table)
    findWinner(table)
def findWinnerTestv2():
    print("Test findWinner by getting input for Q3.b...")
    playerNumber = int(input("Enter the number of players: "))
    table = []
    for i in range(playerNumber):
        table.append("P" + str(i+1))
    print(table)
    findWinner(table)

maxPointsFinderTest()
findMedianTest()
findWinnerCLLTest()
findWinnerTest()
maxPointsFinderTestv2()
findMedianTestv2()
findWinnerCLLTestv2()
findWinnerTestv2()



