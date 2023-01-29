# For the first question, prepared tests are used. The tests which inputs given by user is not applied for first question because of no library rules for graph.

def topological_sort_dfs(graph): # Traverse the graph with dfs based topological sort.
    stack = [] # Create a empty stack to keep path.
    visited = set() # Create a empty set to keep visited elements.
    for i in range(len(graph)): # Visit every node.
        node = list(graph)[i] 
        if node not in visited: # If the node is not visited, call dfs_based function.
            dfs_based(graph, stack, visited, node)
    print(stack[::-1]) # Print the stack after all nodes are visited.

def dfs_based(graph, stack, visited, node): # Traverse the graph with dfs.
    visited.add(node) # Add current node to the set which keeps the visited elements.
    for neighbour in graph.get(node, []): # Get all node which is directed from current node.
        if neighbour not in visited: # If the directed node is not visited, recursively call dfs_based function for directed node.
            dfs_based(graph, stack, visited, neighbour)
    stack.append(node) # Add current node to stack.

def topological_sort_bfs(graph): # Traverse the graph with bfs based topological sort.
    queue = [] # Create a empty queue.
    path = [] # Create a empty stack to keep path.
    for i in range(len(graph)): # Visit every node.
        node = list(graph)[i] 
        if node not in path: # If the node is not visited, add node to queue and call bfs_based function.
            queue.append(node)
            bfs_based(graph, queue, path)
    print(path[::-1]) #Print path.

def bfs_based(graph, queue, path):
    if not queue: # If queue is empty, stop.
        return
    node = queue.pop(0) # Pop the first element of the queue.
    for neighbour in graph.get(node, []): # Get all node which is directed from current node.
        if neighbour not in path: # If the directed node is not visited, add directed node to queue.
            queue.append(neighbour)
    bfs_based(graph, queue, path) # Call bfs_based function.
    path.append(node) # Add current node to stack.


def pow(a, n): # Finds the value of a to the power of n.
    if n < 0: # If n is less than 0, recursively call the function by replacing a with 1/a.
        return pow(1/a, -n)
    if n == 0: # If n is 0, return 1.
        return 1
    if n % 2 == 0: # If n is even, calculate half power recursively, and return half power * half power.
        half_pow = pow(a, n/2) # Half power is the value a to the power n/2.
        return half_pow * half_pow
    elif n % 2 == 1: # If n is odd, calculate half power recursively and return half power * half power.
        half_pow = pow(a, (n-1)/2) # Half power is the value a to the power (n-1)/2.
        return a * half_pow * half_pow

def validPos(board, x, y, key): # Check the key is valid for position (x,y).
    for i in range(9):
        if board[i][y] == key: # If there is an element with the same value with key in y. coloumn, return false.
            return False
    for i in range(9): # If there şs an element with the same value with key in x. row, return false.
        if board[x][i] == key:
            return False
    col = int(x/3) * 3 # Find y position of sub sudoku which is 3*3.
    row = int(y/3) * 3 # Find x position of sub sudoku which is 3*3.
    for i in range(col, col + 3): 
        for j in range(row, row + 3):
            if board[i][j] == key: # Search the key sub sudoku, if there is a match, return false.
                return False
    return True # If the key pass all test, return true.

def sudokusolver(board): # Solve 9*9 sudoku with Exhaustive Search approach.
    for i in range(9):
        for j in range(9):
            if board[i][j] == 0: # If i. row j. coloumn is empty, continue. (Being equal to zero means empty grid.)
                for key in range(1, 10): # Try all possible keys for current grid.
                    if validPos(board, i, j, key): # Check whether the key is valid for the position.
                        board[i][j] = key # If the key is valid, fill the grid with key.
                        if sudokusolver(board): # If sudoku is still solveable, return true.
                                return True
                        board[i][j] = 0 # Otherwise, make grid empty.
                return False # If none of the key is valid for the position, return false.
    return True # If the sudoku is solved, return true.

graph = { "CSE 102": ["CSE 241"],
          "CSE 241": ["CSE 222"],
          "CSE 222": ["CSE 321"],
          "CSE 211": ["CSE 321"],
          "CSE 321": ["CSE 422"],
        }

graph2 = { "a" : ["b", "c", "d"],
          "e" : ["c"],
           "d" : ["f"]
          }

board = [
        [0, 0, 0, 2, 6, 0, 7, 0, 1],
        [6, 8, 0, 0, 7, 0, 0, 9, 0],
        [1, 9, 0, 0, 0, 4, 5, 0, 0],
        [8, 2, 0, 1, 0, 0, 0, 4, 0],
        [0, 0, 4, 6, 0, 2, 9, 0, 0],
        [0, 5, 0, 0, 0, 3, 0, 2, 8],
        [0, 0, 9, 3, 0, 0, 0, 7, 4],
        [0, 4, 0, 0, 5, 0, 0, 3, 6],
        [7, 0, 3, 0, 1, 8, 0, 0, 0]
        ]
board2 = [
        [0, 2, 0, 6, 0, 8, 0, 0, 0],
        [5, 8, 0, 0, 0, 9, 7, 0, 0],
        [0, 0, 0, 0, 4, 0, 0, 0, 0],
        [3, 7, 0, 0, 0, 0, 5, 0, 0],
        [6, 0, 0, 0, 0, 0, 0, 0, 4],
        [0, 0, 8, 0, 0, 0, 0, 1, 3],
        [0, 0, 0, 0, 2, 0, 0, 0, 0],
        [0, 0, 9, 8, 0, 0, 0, 3, 6],
        [0, 0, 0, 3, 0, 6, 0, 9, 0]
        ]


def printSudoku(sudoku):
    for i in range(9):
        for j in range(9):
            print(sudoku[i][j],end="")
        print()

print("Some prepared sudokus: ")
print("First version of sudoku: ")
printSudoku(board)
print("Last version of sudoku: ")
sudokusolver(board)
printSudoku(board)

print("First version of sudoku: ")
printSudoku(board2)
print("Last version of sudoku: ")
sudokusolver(board2)
printSudoku(board2)

def test_pow():
    print("Test pow...")
    a = int(input("Print a: "))
    n = int(input("Print n: "))
    print(pow(a, n))

def test_sudoku_solver():
    print("Test sudoku solver...")
    sudoku = [
        [0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0]
    ]
    a = int(input("Enter how many input you will enter: "))
    for i in range(a):
        y = int(input("Enter coloumn: ")) 
        x = int(input("Enter row: "))
        key = int(input("Enter key: "))
        sudoku[x][y] = key
    print("First version of sudoku: ")
    printSudoku(sudoku)
    print("Last version of sudoku: ")
    sudokusolver(sudoku)
    printSudoku(sudoku)
        

test_pow()
test_sudoku_solver()

topological_sort_bfs(graph)
topological_sort_dfs(graph)
topological_sort_bfs(graph2)
topological_sort_dfs(graph2)











