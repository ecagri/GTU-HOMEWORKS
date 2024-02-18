from sklearn.tree import DecisionTreeClassifier

def NaiveBayesClassification(train_x, train_y, test_x): # Naive Bayes Classification Algorithm #
    probabilities = {}

    predicted_y = []

    for i in range(len(test_x)):
        probability_yes = 1
        probability_no = 1
        for j in range(len(test_x[i])):
            if test_x[i][j] in probabilities:
                probability_yes = probability_yes * probabilities[test_x[i][j]][0]
                probability_no = probability_no * probabilities[test_x[i][j]][1]
            else:
                counter_yes = 0
                counter_no = 0
                for x in range(len(train_x)):
                    if(train_x[x][j] == test_x[i][j]):
                        if train_y[x] == "1":
                            counter_yes = counter_yes + 1
                        else:
                            counter_no = counter_no + 1
                probabilities[test_x[i][j]] = [counter_yes/len(train_x), counter_no/len(train_x)]
                probability_yes = probability_yes * counter_yes / len(train_x)
                probability_no = probability_no * counter_no / len(train_x)
        prediction = 1 if probability_yes > probability_no else 0
        predicted_y.append(str(prediction))
    return predicted_y



def DecisionTreeClassification(X_train, y_train, X_test): # Decision Tree Classification Algorithm #

    # Creating a decision tree classifier
    clf = DecisionTreeClassifier()

    # Training the classifier on the training data
    clf.fit(X_train, y_train)

    # Making predictions on the test data
    return clf.predict(X_test)

def dist(data1, data2):
    distance = 0
    for i in range(len(data1)):
        if(data1[i] != data2[i]):
            distance += 1
    return distance

def hierarchicalClustering(dataset):
    clusters = []
    for i in range(len(dataset)):
        clusters.append(dataset[i])

    while(len(clusters) > 2):
        min = float('inf')
        index1 = -1
        index2 = -1
        for i in range(len(clusters)):
            for j in range(i + 1, len(clusters)):
                for k in range(len(clusters[i])):
                    for l in range(len(clusters[k])):
                        distance = dist(clusters[i][k], clusters[j][l])

                        if(distance < min):
                            min = distance
                            index1 = i
                            index2 = j
        clusters[i].append(j)
        clusters.remove(j)
    return clusters
