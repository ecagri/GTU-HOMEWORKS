from syllable import Encoder
import os
import string
import json

file_path = 'archive/wiki_00_out' 

if os.path.exists(file_path):
    file_size = os.path.getsize(file_path)
    with open(file_path, 'r', encoding='utf-8') as file:
        content = file.read(int(file_size * 0.95))
else:
    print('File not found')

Unigrams = {}
Bigrams = {}
Trigrams = {}
encoder = Encoder(lang="tr", limitby="vocabulary", limit=3000) # Encoder for syllabler #

for line in content.splitlines(): # Each line in dataset #
    syllables = []
    word = ""
    for char in line:
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
    syllables.append("newline")
    for i in range (len(syllables)): # Traverse all the syllables. #
        if(i < len(syllables) - 2): # If the syllables is not the second from the end, add it and it the next two neighbours to trigrams. #
            Trigram = str(syllables[i] + " " + syllables[i + 1] + " " + syllables[i + 2])
            if(Trigram in Trigrams): # If the trigram is already exist, increase it frequency. #
                Trigrams[Trigram] += 1
            else: # Otherwise, set its frequency as 1. #
                Trigrams[Trigram] = 1
        if(i < len(syllables) - 1):  # If the syllables is not the first from the end, add it and it the next neighbour to bigrams. #
            Bigram = str(syllables[i] + " " + syllables[i + 1])
            if(Bigram in Bigrams): # If the bigram is already exist, increase it frequency. #
                Bigrams[Bigram] += 1 
            else: # Otherwise, set its frequency as 1. #
                Bigrams[Bigram] = 1 
        if syllables[i] in Unigrams: # If the unigram is already exist, increase it frequency. #
            Unigrams[syllables[i]] += 1
        else: # Otherwise, set its frequency as 1. #
            Unigrams[syllables[i]] = 1

# Dump n-grams to file. #
with open("Ngrams/Unigrams.json", "w", encoding='utf-8') as outFile:
    json.dump(Unigrams, outFile)

with open("Ngrams/Bigrams.json", "w", encoding='utf-8') as outFile:
    json.dump(Bigrams, outFile)

with open("Ngrams/Trigrams.json", "w", encoding='utf-8') as outFile:
    json.dump(Trigrams, outFile)


