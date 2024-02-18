import preprocessing
import evaluation
import models
from tabulate import tabulate

dataset_mode_normalized = preprocessing.createDataset('dataset_mode_normalized.csv')

trainx, testx, trainy, testy = preprocessing.splitDatasetRandom(dataset_mode_normalized, 0.8)

predictedy_nb = models.NaiveBayesClassification(trainx, trainy, testx)

predictedy_dt = models.DecisionTreeClassification(trainx, trainy, testx)


classificationModels = ["Naive Bayes Mode Imbalanced", "Decision Tree Mode Imbalanced", "Naive Bayes KNN Imbalanced", "Decision Tree KNN Imbalanced", "Naive Bayes Mode Equal", "Decision Tree Mode Equal", "Naive Bayes KNN Equal", "Decision Tree KNN Equal"]
accuracy = [evaluation.accuracy(testy, predictedy_nb), evaluation.accuracy(testy, predictedy_dt)]
precision = [evaluation.precision(testy, predictedy_nb), evaluation.precision(testy, predictedy_dt)]
recall = [evaluation.recall(testy, predictedy_nb), evaluation.recall(testy, predictedy_dt)]
f1_score = [evaluation.F1(testy, predictedy_nb), evaluation.F1(testy, predictedy_dt)]

data = {
    "Model": classificationModels,
    "Accuracy": accuracy,
    "Precision": precision,
    "Recall": recall,
    "F1 Score": f1_score
}


dataset_knn_normalized = preprocessing.createDataset('dataset_knn_normalized.csv')

trainx, testx, trainy, testy = preprocessing.splitDatasetRandom(dataset_knn_normalized, 0.8)

predictedy_nb = models.NaiveBayesClassification(trainx, trainy, testx)

predictedy_dt = models.DecisionTreeClassification(trainx, trainy, testx)

accuracy += [evaluation.accuracy(testy, predictedy_nb), evaluation.accuracy(testy, predictedy_dt)]
precision += [evaluation.precision(testy, predictedy_nb), evaluation.precision(testy, predictedy_dt)]
recall += [evaluation.recall(testy, predictedy_nb), evaluation.recall(testy, predictedy_dt)]
f1_score += [evaluation.F1(testy, predictedy_nb), evaluation.F1(testy, predictedy_dt)]



dataset_mode_normalized = preprocessing.createDataset('dataset_mode_normalized.csv')

trainx, testx, trainy, testy = preprocessing.splitDatasetEqual(dataset_mode_normalized, 0.8)

predictedy_nb = models.NaiveBayesClassification(trainx, trainy, testx)

predictedy_dt = models.DecisionTreeClassification(trainx, trainy, testx)

accuracy += [evaluation.accuracy(testy, predictedy_nb), evaluation.accuracy(testy, predictedy_dt)]
precision += [evaluation.precision(testy, predictedy_nb), evaluation.precision(testy, predictedy_dt)]
recall += [evaluation.recall(testy, predictedy_nb), evaluation.recall(testy, predictedy_dt)]
f1_score += [evaluation.F1(testy, predictedy_nb), evaluation.F1(testy, predictedy_dt)]

dataset_knn_normalized = preprocessing.createDataset('dataset_knn_normalized.csv')

trainx, testx, trainy, testy = preprocessing.splitDatasetEqual(dataset_knn_normalized, 0.8)

predictedy_nb = models.NaiveBayesClassification(trainx, trainy, testx)

predictedy_dt = models.DecisionTreeClassification(trainx, trainy, testx)

accuracy += [evaluation.accuracy(testy, predictedy_nb), evaluation.accuracy(testy, predictedy_dt)]
precision += [evaluation.precision(testy, predictedy_nb), evaluation.precision(testy, predictedy_dt)]
recall += [evaluation.recall(testy, predictedy_nb), evaluation.recall(testy, predictedy_dt)]
f1_score += [evaluation.F1(testy, predictedy_nb), evaluation.F1(testy, predictedy_dt)]




print(tabulate(data, headers="keys", tablefmt="grid"))
