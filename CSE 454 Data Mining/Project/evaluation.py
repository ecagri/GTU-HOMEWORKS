def precision(testy, predictedy): # Calculates precision #
    TP = 0
    FP = 0
    for i in range(len(testy)):
        if(testy[i] == '1' and predictedy[i] == '1'):
            TP += 1
        elif(testy[i] == '0' and predictedy[i] == '1'):
            FP += 1
    return TP / (TP + FP)

def recall(testy, predictedy): # Calculates recall #
    TP = 0
    FN = 0
    for i in range(len(testy)):
        if(testy[i] == '1' and predictedy[i] == '1'):
            TP += 1
        elif(testy[i] == '1' and predictedy[i] == '0'):
            FN += 1
    return TP / (TP + FN)

def F1(testy, predictedy): # Calculates F1 score #
    p = precision(testy, predictedy)
    r = recall(testy, predictedy)
    return (2 * p * r)  / (p + r)

def accuracy(testy, predictedy): # Calculates accuracy #
    T = 0
    for i in range(len(testy)):
        if testy[i] == predictedy[i]:
            T += 1
    return T / len(testy)