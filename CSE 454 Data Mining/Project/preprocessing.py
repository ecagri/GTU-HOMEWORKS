import csv
import numpy as np
import random

def createDataset(filename): # Read a .csv file and converts it into dataset #
    dataset = []

    with open(filename, 'r') as file:
        csv_reader = csv.reader(file)

        for row in csv_reader:
            data = []
            for feature in row:
                data.append(feature)
            dataset.append(data)
    return dataset

def writeDataset(filename, dataset): # write dataset to a .csv file #
    with open(filename, 'w', newline='') as csv_file:
        csv_writer = csv.writer(csv_file)

        for row in dataset:
            csv_writer.writerow(row)

def identicalData(dataset): # Finds identical data #
    not_uniques = []
    for i in range(len(dataset)):
        if(i not in not_uniques):
            for j in range(i + 1, len(dataset)):
                if(dataset[i] == dataset[j]):
                    not_uniques.append(j)
    return not_uniques

def missingValues(dataset): # Finds missing values #
    category = {}
    for i in range(len(dataset[0])):
        number_of_missing = 0

        for j in range(len(dataset)):
            if(dataset[j][i] == ""):
                number_of_missing += 1
        category[dataset[0][i]] = number_of_missing
    return category

def removeIdenticalData(dataset, not_uniques): # Removes identical data from dataset #
    new_dataset = []
    for i in range(len(dataset)):
        if(i not in not_uniques):
            new_dataset.append(dataset[i])
    return new_dataset

def fillMissingValueWithMode(dataset): # Fills missing features with using mode #
    categories = {}
    for index in range(len(dataset[0])):
        for i in range(1, len(dataset)):
            value = dataset[i][index]
            if(value != ""):
                if value in categories:
                    categories[value] = categories[value] + 1
                else:
                    categories[value] = 1

        for i in range(1, len(dataset)):
            if(dataset[i][index] == ""):
                dataset[i][index] = max(categories, key=categories.get)
    return dataset

def NearestNeighbor(dataset): # Creates graph for Nearest Neighbor #
    dataset = np.array(dataset)
    
    graph = {}
    for i in range(1, len(dataset)):
        distances = np.sum(dataset[i] != dataset, axis=1)

        sorted_indices = np.argsort(distances)

        graph[i] = sorted_indices

    return graph

def fillMisingValueWithKNN(dataset, k):  # Fills missing features using KNN algorithm #
    graph = NearestNeighbor(dataset)

    for index in range(len(dataset[0])):
        for i in range(1, len(dataset)):
            if dataset[i][index] == "":
                categories = {}
                for j in range(k):
                    value = dataset[graph[i][j]][index]
                    if value in categories:
                        categories[value] = categories[value] + 1
                    elif value != "":
                        categories[value] = 1
                if(len(categories) == 0):
                    for counter in range(k, len(dataset)):
                        value = dataset[graph[i][counter]][index]
                        if value != "":
                            categories[value] = 1
                            break
                dataset[i][index] = max(categories, key=categories.get)
    return dataset  

def normalization(dataset): # Converts categorical features into numerical features by one-hot coding #
    new_dataset = []
    uniques = [[] for i in range(len(dataset[0]) - 1)]
    for i in range(1, len(dataset)):
        data = []
        for j in range(len(dataset[i])):
            if(j != len(dataset[i]) - 1):
                if dataset[i][j] not in uniques[j]:
                    uniques[j].append(dataset[i][j])
                data.append(uniques[j].index(dataset[i][j]))
            else:
                value = int(dataset[i][j])
                data.append(value)
        new_dataset.append(data)
    return new_dataset
def splitDatasetRandom(dataset, ratio): # Splits dataset randomly #
    X = [sublist[:len(sublist) - 1] for sublist in dataset]
    Y = [sublist[-1] for sublist in dataset]

    return X[:int(ratio * len(X))], X[int(ratio * len(X)):], Y[:int(ratio * len(Y))], Y[int(ratio * len(Y)):]

def splitDatasetEqual(dataset, ratio): # Splits train set where equal positive and negative number of data #
    dataset_positive = []
    dataset_negative = []
    for i in range(len(dataset)):
        if(dataset[i][len(dataset[i]) - 1] == '1'):
            dataset_positive.append(dataset[i])
        else:
            dataset_negative.append(dataset[i]) 

    size = int(len(dataset) * ratio / 2)
    new_dataset = []

    for i in range(size):
        new_dataset.append(dataset_positive[i])
    for i in range(size): 
        new_dataset.append(dataset_negative[i])
    
    for i in range(size, len(dataset_positive)):
        new_dataset.append(dataset_positive[i])
    for i in range(size, len(dataset_negative)):
        new_dataset.append(dataset_negative[i])

    X = [sublist[:len(sublist) - 1] for sublist in new_dataset]
    Y = [sublist[-1] for sublist in new_dataset]

    return X[:int(ratio * len(X))], X[int(ratio * len(X)):], Y[:int(ratio * len(Y))], Y[int(ratio * len(Y)):]

"""
dataset = createDataset('in-vehicle-coupon-recommendation.csv')

not_uniques = identicalData(dataset)

dataset = removeIdenticalData(dataset, not_uniques)

dataset1 = fillMissingValueWithMode(dataset)

writeDataset('dataset_mode.csv', dataset1)

dataset2 = fillMisingValueWithKNN(dataset, 3)

writeDataset('dataset_knn.csv', dataset2)

dataset = preprocessing.createDataset('dataset_mode.csv')

dataset = preprocessing.normalization(dataset)

dataset2 = preprocessing.createDataset('dataset_knn.csv')

dataset2 = preprocessing.normalization(dataset2)

preprocessing.writeDataset('dataset_knn_normalized.csv', dataset2)

preprocessing.writeDataset('dataset_mode_normalized.csv', dataset)


"""