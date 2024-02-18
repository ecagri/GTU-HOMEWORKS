import json
import random

Unigrams = {}
Bigrams = {}
Trigrams = {}

with open('Ngrams/Unigrams.json', 'r', encoding='utf-8') as file:
    Unigrams = json.load(file)
with open('Ngrams/Bigrams.json', 'r', encoding='utf-8') as file:
    Bigrams = json.load(file)
with open('Ngrams/Trigrams.json', 'r', encoding='utf-8') as file:
    Trigrams = json.load(file)

SortedUnigrams = dict(sorted(Unigrams.items(), key=lambda item: item[1], reverse=True))
SortedUnigramsList = list(SortedUnigrams.keys())
SortedBigrams = dict(sorted(Bigrams.items(), key=lambda item: item[1], reverse=True))
SortedBigramsList = list(SortedBigrams.keys())
SortedTrigrams = dict(sorted(Trigrams.items(), key=lambda item: item[1], reverse=True))
sortedTrigramsList = list(SortedTrigrams.keys())

def printSyllable(syllable):
    if(syllable == "space"):
        print(" ", end="")
    elif(syllable == "newline"):
        return False
    else:
        print(syllable, end="")
    return True

print("RANDOM SENTENCES FOR UNIGRAM")

for i in range(5):
    print(f"Sentence {i + 1}: ", end="")
    for j in range(50):
        index = random.randint(0, 4)
        if(printSyllable(SortedUnigramsList[index]) == False):
            break
    print()

print("RANDOM SENTENCES FOR BIGRAM")

for i in range(5):
    Syllables = []
    print(f"Sentence {i + 1}: ", end="")
    for j in range(50):
        index = random.randint(0, 4)
        if j == 0:
            Syllables = SortedBigramsList[index].split()
        else: 
            filteredSyllables = [(key) for key in SortedBigrams.keys() if key.startswith(Syllables[1]) and (key[len(Syllables[1])] == ' ')]
            if(len(filteredSyllables) == 0):
                printSyllable(Syllables[1])
                break
            elif(len(filteredSyllables) < 5):
                index = random.randint(0, len(filteredSyllables) - 1)
            Syllables = filteredSyllables[index].split()
        if(printSyllable(Syllables[0]) == False):
            break
    print()

print("RANDOM SENTENCES FOR TRIGRAM")

for i in range(5):
    Syllables = []
    print(f"Sentence {i + 1}: ", end="")
    for j in range(50):
        index = random.randint(0, 4)
        if j == 0:
            Syllables = sortedTrigramsList[index].split()
        else: 
            filteredSyllables = [(key) for key in SortedTrigrams.keys() if Syllables[1] in key[0:len(Syllables[1])] and Syllables[2] in key[len(Syllables[1]): len(Syllables[1]) + len(Syllables[2]) + 1]]
            if(len(filteredSyllables) == 0):
                printSyllable(Syllables[1])
                break
            elif(len(filteredSyllables) < 5):
                index = random.randint(0, len(filteredSyllables) - 1)
            Syllables = filteredSyllables[index].split()
        if(printSyllable(Syllables[0]) == False):
            break
    print()


