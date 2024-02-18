import json
from syllable import Encoder
import string
import math
import os
from collections import Counter


file_path = 'archive/wiki_00_out' 

if os.path.exists(file_path):
    file_size = os.path.getsize(file_path)
    with open(file_path, 'r', encoding='utf-8') as file:
        content = file.read(file_size)
else:
    print('File not found')

restContent = content[-int(file_size*0.000001):]

Unigrams = {}
Bigrams = {}
Trigrams = {}
encoder = Encoder(lang="tr", limitby="vocabulary", limit=3000) # Encoder for syllabler #
syllables = []
word = ""

for char in restContent:
    if char.isspace() or char in string.punctuation:
        if word.isdigit(): # Check the word is digit. #
            syllables.append(word)
        elif len(word) != 0:
            wordSyllables = encoder.tokenize(word).split() # Split the word into syllables. # 
            for syllable in wordSyllables:
                syllables.append(syllable) # Add each syllable to syllables array. #
            if len(wordSyllables) == 0:
                syllables.append(word)
        word = ""
    else:
        word += f'{char}'
    if char in string.punctuation: # If the char is a punctuation, add it to syllables. #
        syllables.append(char)   
    elif char.isspace(): # If the char is space, add "space" keyword to syllables. #
        syllables.append("space")



def get_frequency(target_value):
    if target_value in Bucket:
        return Bucket[target_value]
    else:
        frequency = counter[target_value]
        frequency = frequency if frequency > 0 else 1
        Bucket[target_value] = frequency
        return frequency

with open('Ngrams/Unigrams.json', 'r', encoding='utf-8') as file:
    Unigrams = json.load(file)
with open('Ngrams/Bigrams.json', 'r', encoding='utf-8') as file:
    Bigrams = json.load(file)
with open('Ngrams/Trigrams.json', 'r', encoding='utf-8') as file:
    Trigrams = json.load(file)

totalProbability = 0
Bucket = {}
counter = Counter(Unigrams.values())
sum_of_values = sum(Unigrams.values())
for syllable in syllables:
    if syllable not in Unigrams:
        current_probability = get_frequency(1) / sum_of_values
    else:
        current_probability = ((Unigrams[syllable] + 1) * get_frequency(Unigrams[syllable] + 1)) / (get_frequency(Unigrams[syllable]) * sum_of_values)
    totalProbability += math.log(current_probability, 10)
print("Unigram perplexity: ", (1) / (10 ** (totalProbability/len(syllables))))

Bucket = {}
totalProbability = 0
counter = Counter(Bigrams.values())
for j in range(len(syllables) - 1):
    syllable = syllables[j] + " " + syllables[j+1]
    sum_of_values = sum(value for key, value in Unigrams.items() if key == syllables[j])
    sum_of_values = sum_of_values if sum_of_values > 0 else 1
    if syllable not in Bigrams:
        current_probability = get_frequency(1) / sum_of_values
    else:
        current_probability = ((Bigrams[syllable] + 1) * get_frequency(Bigrams[syllable] + 1)) / (get_frequency(Bigrams[syllable]) * sum_of_values)
    totalProbability += math.log(current_probability, 10)
print("Bigram perplexity: ", (1) / (10 ** (totalProbability/(len(syllables) - 1))))


Bucket = {}
totalProbability = 0
counter = Counter(Trigrams.values())
for j in range(len(syllables) - 2):
    syllable = syllables[j] + " " + syllables[j+1] + " " + syllables[j+2]
    sum_of_values = sum(value for key, value in Bigrams.items() if key == syllables[j] + " " + syllables[j+1])
    sum_of_values = sum_of_values if sum_of_values > 0 else 1
    if syllable not in Trigrams:
        current_probability = get_frequency(1) / sum_of_values
    else:
        current_probability = ((Trigrams[syllable] + 1) * get_frequency(Trigrams[syllable] + 1)) / (get_frequency(Trigrams[syllable]) * sum_of_values)
    totalProbability += math.log(current_probability, 10)
print("Trigram perplexity: ", (1) / (10 ** (totalProbability/(len(syllables) - 2))))