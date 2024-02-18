import re

# PREPARING DATASET #

X_previous = []

Y_previous = []

with open('wiki_00', 'r', encoding='utf-8',  errors='ignore') as file: # Read wiki dump.
    for line in file: # Line by line.
        sentences = re.split(r'(?<=[.!?])\s', line.strip()) # Divide line into sentences.

        for sentence in sentences:
            if re.search(r'\b\w*ki\b', sentence) and re.search(r'\b\w*de\b', sentence): # If sentence does not contain either '-de' and 'ki', continue.
                continue
            elif not re.search(r'\b\w*ki\b', sentence) and not re.search(r'\b\w*de\b', sentence): # If sentence contains both '-de' and 'ki', continue.
                continue
            if re.search(r'\b\w+de\b', sentence): # If sentence contains adjacent '-de', append 1 to Y.
                Y_previous.append(1)
            elif re.search(r'\sde\s', sentence): # If sentence contains seperated '-de', append 0 to Y and merge '-de' with previous word.
                words = sentence.split()
                for i in range(len(words)):
                    if(words[i] == 'de'):
                        words[i-1] += 'de'
                        words.pop(i)
                        break
                sentence = ' '.join(words)
                Y_previous.append(0)
            elif re.search(r'\b\w+ki\b', sentence): # If sentence contains adjacent '-ki', append 1 to Y.
                Y_previous.append(1)
            elif re.search(r'\ski\s', sentence): # If sentence contains seperated '-ki', append 0 to Y and merge '-ki' with previous word.
                Y_previous.append(0)
                words = sentence.split()
                for i in range(len(words)):
                    if(words[i] == 'ki'):
                        words[i-1] += 'ki'
                        words.pop(i)
                        break
                sentence = ' '.join(words)
            else:
                continue
            X_previous.append(sentence) # Add sentence to X.

count_p = 0
count_n = 0
Y = []
X = []
for i in range(len(X_previous)): # Make X contains same number (50K) of sample of each class.
  if(count_p == 50000 and count_n == 50000):
    break
  elif(count_p == 50000 and Y_previous[i] == 1):
    continue
  elif(count_n == 50000 and Y_previous[i] == 0):
    continue
  else:
    if(Y_previous[i] == 1):
      count_p += 1
    else:
      count_n += 1
    X.append(X_previous[i])
    Y.append(Y_previous[i])

from keras.preprocessing.text import Tokenizer
from keras.preprocessing.sequence import pad_sequences
from sklearn.utils import shuffle
import numpy as np

Y_train = np.array(Y) 
tokenizer = Tokenizer() # Tokenizer is created.
tokenizer.fit_on_texts(X) # Fits the tokenizer into dataset.
X_train = tokenizer.texts_to_sequences(X) # Makes each data sample tokenized.
max_length = max(len(seq) for seq in X_train)
X_train = pad_sequences(X_train, maxlen=max_length, padding='post') # Pad tokenized sequences to make them fixed-length.
word_index = tokenizer.word_index
X_train, Y_train = shuffle(X_train, Y_train) # Shuffle the dataset to get randomly distributed dataset.

from keras.models import Sequential
from keras.layers import Embedding, LSTM, Dense, Dropout, Bidirectional

model = Sequential() # Creates a sequential model. 
model.add(Embedding(input_dim=len(word_index) + 1, output_dim=64))  # Adds an embedding layer to model.
model.add(Bidirectional(LSTM(64, return_sequences=True))) # Adds a bidirectional LSTM layer to model.
model.add(Bidirectional(LSTM(32))) # Adds a bidirectional LSTM layer to model.
model.add(Dense(64, activation='relu')) # Adds a dense layer to model.
model.add(Dropout(0.5)) # Adds a dropout layer for regularization.
model.add(Dense(1, activation='sigmoid'))  # Output layer for binary classification

model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy']) # Compile the model.
model.summary()

import matplotlib.pyplot as plt

# Train the model
history = model.fit(X_train[50000:], Y_train[50000:], epochs=6, batch_size=64, verbose=1, validation_split=0.2) # Train the model with last 50K data points.

# Plot training history
plt.figure(figsize=(10, 5))

# Plot training & validation accuracy values
plt.subplot(1, 2, 1)
plt.plot(history.history['accuracy'])
plt.plot(history.history['val_accuracy'])
plt.title('Model accuracy')
plt.ylabel('Accuracy')
plt.xlabel('Epoch')
plt.legend(['Train', 'Validation'], loc='upper left')

# Plot training & validation loss values
plt.subplot(1, 2, 2)
plt.plot(history.history['loss'])
plt.plot(history.history['val_loss'])
plt.title('Model loss')
plt.ylabel('Loss')
plt.xlabel('Epoch')
plt.legend(['Train', 'Validation'], loc='upper left')

plt.tight_layout()
plt.show()

# Evaluate the model
loss, accuracy = model.evaluate(X_train[:50000], Y_train[:50000]) # Evaluate the model performance with unseen 50K data points.
print(f'Loss: {loss}, Accuracy: {accuracy}')


import random
from tabulate import tabulate

random_start = random.randint(0, 49980)

table_data = []

# Iterate over the range
for i in range(random_start, random_start + 20): # Tests the model with randomly choosen 20 sentences.
    X_test = tokenizer.sequences_to_texts([X_train[i]])
    prediction = model.predict(np.reshape(X_train[i], (1, X_train[i].shape[0])))

    prediction_label = 'not_separated' if prediction[0] >= 0.5 else 'separated'
    ground_truth = 'not_separated' if Y_train[i] >= 0.5 else 'separated'
    table_data.append([X_test[0], ground_truth, prediction[0], prediction_label])

headers = ["Sentence", "Ground Truth", "Prediction", "Predicted Label"]

print(tabulate(table_data, headers=headers, tablefmt="fancy_grid"))
