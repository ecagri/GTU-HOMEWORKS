import random
from random import randint

#QUESTION 1

def largestCommonSubstring(array, start, end): # Compares strings in string array and finds largest common substring.
    if(start == end): # If start element is equal to end, returns array[start].
        return array[start]
    else:
        mid = int((start + end) / 2) # Finds middle index.
        leftPart = largestCommonSubstring(array, start, mid) # Finds largest common substring on left part of the array.
        rightPart = largestCommonSubstring(array, mid + 1, end) # Finds largest common substring on right part of the array.
        return compareStrings(leftPart, rightPart) # Compares left largest common substring with right largest common substring and returns the largest common substring of them.
def compareStrings(firstString, secondString): # Compares two string and returns the largest common substring.
    repeat = min(len(firstString), len(secondString)) 
    for i in range(repeat): # Checks the characters of the string until a string end or characters do not match.
        if(firstString[i] != secondString[i]):
            return firstString[0:i]
    return firstString[0:repeat] # If there is no unmatched character, returns the first string from beginning to the minimum length of two strings.

#---------------------------------------------------------------------------------------------------------------
#QUESTION 2.a

def findMin(array, start, end): # Finds minimum value index in array starting from start index to the end index.
    minValue = array[start]
    minValueIndex = start
    for i in range(start + 1, end + 1):
        if(array[i] < minValue):
            minValue = array[i]
            minValueIndex = i
    return minValueIndex

def findMax(array, start, end): # Finds maximum value index in array starting from start index to the end index.
    maxValue = array[start]
    maxValueIndex = start
    for i in range(start + 1, end + 1):
        if(array[i] > maxValue):
            maxValue = array[i]
            maxValueIndex = i
    return maxValueIndex

def findMaxDif(array, leftPoints, rightPoints, minMaxPoints): # Finds maximum difference of three points.
    biggest = [-1, -1]
    if(leftPoints == biggest and rightPoints == biggest): # If leftPoints and rightPoints are empty, returns minMaxPoints.
        return minMaxPoints
    elif(leftPoints == biggest and minMaxPoints == biggest): # If leftPoints and minMaxPoints are empty, returns rightPoints.
        return rightPoints
    elif(rightPoints == biggest and minMaxPoints == biggest): # If rightPoints and minMaxPoints are empty, returns leftPoints.
        return leftPoints
    # Otherwise returns the biggest of them.
    if(array[leftPoints[1]] - array[leftPoints[0]] > array[rightPoints[1]] - array[rightPoints[0]]):
        biggest[1] = leftPoints[1]
        biggest[0] = leftPoints[0]
    else:
        biggest[1] = rightPoints[1]
        biggest[0] = rightPoints[0]
    if(array[minMaxPoints[1]] - array[minMaxPoints[0]] > array[biggest[1]] - array[biggest[0]]):
        biggest[1] = minMaxPoints[1]
        biggest[0] = minMaxPoints[0]
    return biggest

def findMaxProfitDAC(array): # Finds max profit with divide and conqueer algorithm.
    calculate = True
    profit = False

    # Some error checkings.
    if(len(array) == 1 or len(array) == 0):
        calculate = False
    if(calculate == True):
        points = divideAndConqueer(array, 0, len(array) - 1)
        if(array[points[1]] - array[points[0]] > 0):
            print("Buy on Day", points[0], "for", array[points[0]], "and sell on Day", points[1], "for", array[points[1]])
            profit = True
    if(calculate == False or profit == False):
            print("There is no good days to get profit.")
    

def divideAndConqueer(array, start, end): # Divide and conqueer algorithm to find max profit.
    if(start >= end): # If start is equal to or bigger than end, returns empty point.
        return [-1, -1] 
    middle = int((start + end) / 2) # Finds middle of the array.
    leftPartPoints = divideAndConqueer(array, start, middle) # Finds biggest profit for the part starting from start to the middle.
    rightPartPoints = divideAndConqueer(array, middle + 1, end) # Finds biggest profit for the part starting from middle to the end.
    leftMin = findMin(array, start, middle) # Finds minimum number in the left part.
    rightMax = findMax(array, middle + 1, end) # Finds maximum number in the right part.
    minMaxPoints = [leftMin, rightMax]
    return findMaxDif(array, leftPartPoints, rightPartPoints, minMaxPoints) # Returns the biggest profit.

#---------------------------------------------------------------------------------------------------------------
#QUESTION 2.b

def findMaxProfitNormal(array): # Finds max profit in a row in linear time.
    maxPrice = 0 # Minimum price is thought as 0.
    maxPriceIndexPrev = -1 # Keeps the index of max price of all days. 
    maxPriceIndexCur = - 1 # Keeps the index of max price which we can profit.
    minPriceIndex = -1 # Keeps the index of min price which we can profit.
    profit = 0 # Minimum profit is thought as 0.
    for i in range(len(array)): # Checks all days from end to the beginning.
        last = len(array) - 1 
        if(array[last - i] > maxPrice): # If ith to last is bigger than max price, max price is set as ith to last element of the array.
            maxPrice = array[last - i] 
            maxPriceIndexPrev = last - i # All time max price index is updated.
        if(maxPrice - array[last-i] > profit): # If the max price - ith to last element is bigger than profit, new profit is set as max price - ith to last element.
            profit = maxPrice - array[last - i]
            maxPriceIndexCur = maxPriceIndexPrev # Index of max price which we can profit is updated.
            minPriceIndex = last - i # Index of min prrice which we can profit is updated.
    if(maxPriceIndexCur == -1 or minPriceIndex == -1): # If there is no day to get profit, print an error.
        print("There is no good days to get profit.")
    else:
        print("Buy on Day", minPriceIndex, "for", array[minPriceIndex], "and sell on Day", maxPriceIndexCur, "for", array[maxPriceIndexCur]) 

#---------------------------------------------------------------------------------------------------------------
#QUESTION 3
        
def findLICS(array): # Finds longest increasing consecutive number sequence in an array.
    LIS = [1] * len(array) # Creates an array of size n, and fills with it ones.
    LISMax = 1 # Longest incerasing consecutive sequence is set as 1.
    for i in range(len(array)): # Continues for all element in the array.
        index = len(array) - 1 - i # Starts from the end of the array.
        LIS = lis(array, len(array) - 1 - i, LIS, LISMax) # Updates the LIS array with the output of lis function. 
        if(LIS[index] > LISMax): # Compares length of the current sequence with longest sequence, if current sequence is bigger, set longest sequence to current sequence. 
            LISMax = LIS[index]
    return LISMax # Returns longest sequence.
def lis(array, index, LIS, LISMax): # Finds the increasing sequence of indexth element.
    if(index != len(array) - 1 and array[index + 1] > array[index]): # If index is not the last element and, indexth element is less than (index + 1)th element, add length of the sequence of the (index + 1)th element to indexth element.
        LIS[index] = LIS[index + 1] + LIS[index]
    return LIS

#---------------------------------------------------------------------------------------------------------------
#QUESTION 4.a

def findMaxPoints(array): # Finds the path which contains max points.
    MPP = [[0 for i in range(len(array[0]))] for j in range(len(array))] # Creates a 2D array and fills it with zeros.
    MPP[0][0] = array[0][0] # Set first element of the MPP to first element of array.
    rowsNumber = len(array) # Gets the number of rows.
    colomnsNumber = len(array[0]) # Gets the number of coloumns.
    currentX = 0
    currentY = 0
    for i in range(1, colomnsNumber): # Starting from second element in first row, adds the point of left element to current element. 
        MPP[0][i] = array[0][i] + MPP[0][i - 1] 
    for i in range(1, rowsNumber): # Starting from first element in second row, adds the point of upper element to current element.
        MPP[i][0] = array[i][0] + MPP[i - 1][0]
    for j in range(1, rowsNumber):
        for i in range(1, colomnsNumber):
            MPP[j][i] = array[j][i] + max(MPP[j - 1][i], MPP[j][i - 1]) # Adds max of the left and upper elements points to current element.
    for i in range(2, colomnsNumber + rowsNumber): # Prints the path.
        print(array[currentY][currentX], "+ ", end="")
        if(currentY + 1 == rowsNumber):
            currentX = currentX + 1
        elif(currentX + 1 == colomnsNumber):
            currentY = currentY + 1    
        elif(MPP[currentY][currentX + 1] > MPP[currentY + 1] [currentX]):
            currentX = currentX + 1
        else:
            currentY = currentY + 1
    print(array[rowsNumber - 1][colomnsNumber - 1], "=", MPP[rowsNumber -1][colomnsNumber - 1])

#---------------------------------------------------------------------------------------------------------------
#QUESTION 4.b
    
def findMaxPointsGreedy(array): # Finds the path which contains max points whit greedy algorithm.
    currentX = 0
    currentY = 0
    pathSum = 0
    rowsNumber = len(array) # Gets the number of rows.
    colomnsNumber = len(array[0]) # Gets the number of coloumns.
    for i in range(2, colomnsNumber + rowsNumber): # From beginning to the end, in each iteration it goes to one of the right or bottom cell which has max points. 
        pathSum = pathSum + array[currentY][currentX]
        print(array[currentY][currentX], "+ ", end="")
        if(currentY + 1 == rowsNumber): # If there is no bottom cell, go right.
            currentX = currentX + 1
        elif(currentX + 1 == colomnsNumber): # If there is no right cell, go down.
            currentY = currentY + 1    
        elif(array[currentY][currentX + 1] > array[currentY + 1] [currentX]): # If right cell is bigger than bottom cell, go right.
            currentX = currentX + 1
        elif(array[currentY + 1][currentX] >= array[currentY][currentX + 1]): # If bottom cell is bigger than right cell, go down.
            currentY = currentY + 1
    print(array[currentY][currentX], "=", pathSum + array[currentY][currentX])

#---------------------------------------------------------------------------------------------------------------
#TESTS

def largestCommonSubstringTest(): # Test largestCommonSubstring function with random strings.
    print("Test largestCommonSubstring randomly...")
    size = random.randint(1, 5)
    array = []
    letters = ['a', 'b']
    for i in range(size):
        newString = ''.join(random.choice(letters) for j in range(1, 4)) 
        array.append(newString)
    print(array)
    print("The largest common substring is: ", largestCommonSubstring(array, 0, len(array) - 1))

def largestCommonSubstringTestv2(): # Test largestCommonSubstring function with user inputs.
    print("Test largestCommonSubstring by getting input...")
    size = int(input("Enter the size of the array: "))
    array = []
    for i in range(size):
        print("Enter the", i + 1 ,"th string: ", end="")
        array.append(str(input()))
    print(array)
    if(size > 0):
        print("The largest common substring is: ", largestCommonSubstring(array, 0, len(array) - 1))
        
def largestCommonSubstringTestv3(): # Test largestCommonSubstring function with some inputs because it is hard to find match with random strings.
    print("Test largestCommonSubstring with specific inputs...")
    array =  ["programmable", "programming", "programmer", "programmatic", "programmability"]
    print(array)
    print(largestCommonSubstring(array, 0, len(array) - 1))
    array2 =  ["compute", "compatible", "computer", "compare", "compactness"]
    print(array2)
    print(largestCommonSubstring(array2, 0, len(array2) - 1))

def findMaxProfitDACTest(): # Test findMaxProfitDAC function randomly.
    print("Test findMaxProfitDAC randomly...")
    size = random.randint(2, 10)
    array = []
    for i in range(size):
        array.append(random.randint(1, 100))
    print(array)
    findMaxProfitDAC(array)

def findMaxProfitDACTestv2(): # Test findMaxProfitDAC function with user inputs.
    print("Test findMaxProfitDAC by getting input...")
    size = int(input("Enter the size of the array: "))
    array = []
    for i in range(size):
        print("Enter the price on Day", i, ": ", end="")
        array.append(int(input()))
    print(array)
    if(size > 0):
        findMaxProfitDAC(array)

def findMaxProfitNormalTest(): # Test findMaxProfitNormal function randomly.
    print("Test findMaxProfitNormal randomly...")
    size = random.randint(2, 10)
    array = []
    for i in range(size):
        array.append(random.randint(1, 100))
    print(array)
    if(size > 0):
        findMaxProfitNormal(array)

def findMaxProfitNormalTestv2(): # Test findMaxProfitNormal function with user inputs.
    print("Test findMaxProfitNormal by getting input...")
    size = int(input("Enter the size of the array: "))
    array = []
    for i in range(size):
        print("Enter the price on Day", i, ": ", end="")
        array.append(int(input()))
    print(array)
    if(size > 0):
        findMaxProfitNormal(array)

def findLICSTest(): # Test findMaxLICS function randomly.
    print("Test findMaxLICS randomly...")
    size = random.randint(1, 10)
    array = []
    for i in range(size):
        array.append(random.randint(1, 100))
    print(array)
    if(size > 0):
        print("Length of the longest increasing consecutive sequence is: ", findLICS(array))

def findLICSTestv2(): # Test findMaxLICS function with user input.
    print("Test findMaxLICS by getting input...")
    size = int(input("Enter the size of the array: "))
    array = []
    for i in range(size):
        print("Enter the array[", i ,"]: ", end="")
        array.append(int(input()))
    print(array)
    if(size > 0):
        print("Length of the longest increasing consecutive sequence is: ", findLICS(array))

def findMaxPointsTest(): # Test findMaxPoints function with random numbers.
    print("Test findMaxPoints randomly...")
    cols = random.randint(3, 8)
    rows = random.randint(3, 8)
    board = [[random.randint(1,9) for i in range(cols)] for i in range(rows)]
    for i in range(rows):
        for j in range(cols):
            print(board[i][j], ", ", end="")
        print()
    print("Path and result is: ")
    findMaxPoints(board);      

def findMaxPointsTestv2(): # Test findMaxPoints function with user inputs.
    print("Test findMaxPoints by getting input...")
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
    print("Path and result is: ")
    findMaxPoints(board);

def findMaxPointsGreedyTest(): # Test findMaxPointsGreedy function with random numbers.
    print("Test findMaxPointsGreedy randomly...")
    cols = random.randint(3, 8)
    rows = random.randint(3, 8)
    board = [[random.randint(1,9) for i in range(cols)] for i in range(rows)]
    for i in range(rows):
        for j in range(cols):
            print(board[i][j], ", ", end="")
        print()
    print("Path and result is: ")
    findMaxPointsGreedy(board);      

def findMaxPointsTestGreedyv2(): # Test findMaxPointsGreedy function with user inputs.
    print("Test findMaxPointsGreedy by getting input...")
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
    print("Path and result is: ")
    findMaxPointsGreedy(board);
    
largestCommonSubstringTest()
findMaxProfitDACTest()
findMaxProfitNormalTest()
findLICSTest()
findMaxPointsTest()
findMaxPointsGreedyTest()
largestCommonSubstringTestv2()
largestCommonSubstringTestv3()
findMaxProfitDACTestv2()
findMaxProfitNormalTestv2()
findLICSTestv2()
findMaxPointsTestv2()
findMaxPointsGreedyTestv2()


        
