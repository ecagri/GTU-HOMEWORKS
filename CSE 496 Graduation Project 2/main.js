async function loadTokens() { /* Loads the corresponding tokens for words from 'tokens.txt' file. */
    let tokens = new Map();
    try {
        const response = await fetch(chrome.runtime.getURL('tokens.txt'));
        const data = await response.text();
        const lines = data.split('\n');
        lines.forEach(line => {
            const [key, value] = line.trim().split(' ');
            const intValue = parseInt(value);
            if (tokens.has(key)) {
                tokens.get(key).push(intValue);
            } else {
                tokens.set(key, [intValue]);
            }
        });
        console.log("Tokens loaded.");
    } catch (error) {
        console.error('Error fetching the text file:', error);
    }
    return tokens;
}

async function loadWords() { /* Loads the corresponding tokens for words from 'tokens.txt' file. */
    let dictionary = new Set()
    try {
        const response = await fetch(chrome.runtime.getURL('words.txt'));
        const data = await response.text();
        const allWords = data.split('\n').map(word => word.trim().toLowerCase());
        allWords.forEach(word => dictionary.add(word));
        console.log("Words loaded.");
        
    } catch (error) {
        console.error('Error fetching the text file:', error);
    }
    return dictionary;
}

async function loadModel() {
    let model;

    try {
        const response = await fetch('https://cdn.jsdelivr.net/npm/@tensorflow/tfjs@4.19.0/dist/tf.min.js');
        const script = await response.text();

        eval(script); // This will define the `tf` object globally


        tf.setBackend('webgl'); // Set TensorFlow.js to use the WebGL backend
        await tf.ready(); // Wait for the backend to be ready

        const modelUrl = 'finalDL/model.json';
        model = await tf.loadLayersModel(chrome.runtime.getURL(modelUrl));

        console.log("Model loaded.", model);
    } catch (error) {
        console.error('Error loading TensorFlow.js or model:', error);
    }

    return model;
}

function generateVariations(words) { /* Generates variations of the word i.e. "coktu", "çoktu", "cöktu", "çöktu", "coktü", "çoktü", "cöktü", "çöktü" for the word "coktu". */
    let allVariations = [];
    
    for (let i = 0; i < words.length; i++) {
        let baseWord = words[i].toLowerCase().replace(/[.,\/#!$%\^&\*;:{}=\-_’”“`~()]/g, "");
        let variations = new Set([baseWord]);

        function replaceAt(word, index, replacement) {
            return word.substring(0, index) + replacement + word.substring(index + 1);
        }

        for (let word of variations) {
            for (let j = 0; j < word.length; j++) {
                switch (word[j]) {
                    case 'i':
                        variations.add(replaceAt(word, j, 'ı'));
                        break;
                    case 'o':
                        variations.add(replaceAt(word, j, 'ö'));
                        break;
                    case 'u':
                        variations.add(replaceAt(word, j, 'ü'));
                        break;
                    case 's':
                        variations.add(replaceAt(word, j, 'ş'));
                        break;
                    case 'g':
                        variations.add(replaceAt(word, j, 'ğ'));
                        break;
                    case 'c':
                        variations.add(replaceAt(word, j, 'ç'));
                        break;
                    case 'I':
                        variations.add(replaceAt(word, j, 'İ'));
                        break;
                }
            }
        }
        
        allVariations.push(Array.from(variations));
    }
    return allVariations;
}

async function eliminatingVariations(allVariations){ /* Eliminate variations which are not valid Turkish word i.e. "coktu", "cöktu", "çöktu", "coktü", "çoktü", "cöktü". */
    for(let i = 0; i < allVariations.length; i++){
        let eliminatedVariations = [];
        if(allVariations[i].length > 1){
            console.log(allVariations[i])
            for(let j = 0; j < allVariations[i].length; j++){
                if(!dictionary.has(allVariations[i][j])){
                    eliminatedVariations.push(allVariations[i].splice(j, 1)[0]); 
                    j--;
                }
            }
            if(allVariations[i].length == 0){
                let max_length = 0;
                let stems = new Set();
                for(let j = 0; j < eliminatedVariations.length; j++){
                    for(let k = 1; k < eliminatedVariations[j].length && max_length <= eliminatedVariations[j].length - k - 1; k++){
                        if(dictionary.has(eliminatedVariations[j].substring(0, eliminatedVariations[j].length - k - 1))){
                            if(max_length == eliminatedVariations[j].length - k - 1){
                                stems.add(eliminatedVariations[j].substring(0, eliminatedVariations[j].length - k - 1));
                            }else{
                                stems = new Set([eliminatedVariations[j].substring(0, eliminatedVariations[j].length - k - 1)]);
                                max_length = eliminatedVariations[j].length - k - 1;
                            }
                        }                        
                    }
                }
                for(let j = 0; j < eliminatedVariations.length; j++){
                    for(let stem of stems){
                        if(eliminatedVariations[j].substring(0, stem.length) == stem){
                            let word = eliminatedVariations[j].substring(findLastVowelIndex(eliminatedVariations[j].substring(0, stem.length)));
                            if(major_vowel_harmony(word) && minor_vowel_harmony(word)){
                                allVariations[i].push(eliminatedVariations[j]);
                            }
                        }
                    }
                }

            }

            if(allVariations[i].length == 0){
                allVariations[i].push(eliminatedVariations[0]);
            }
            let remainings = []

            for(let j = 0; j < allVariations[i].length; j++){
                if(tokens.has(allVariations[i][j])){
                    remainings.push(allVariations[i][j]);
                }
            } 
            
            if(remainings.length >= 1){
                allVariations[i] = remainings;
            }
        }
             
    }


    return allVariations
}

function combiningWords(arrays, index = 0, combination = []) { /* Combines the possible words to form sentences. */
    const result = [];
    if (index === arrays.length) {
        result.push(combination.join(' '));
        return result;
    }
    for (let i = 0; i < arrays[index].length; i++) {
        const newCombination = combination.concat(arrays[index][i]);
        result.push(...combiningWords(arrays, index + 1, newCombination));
    }
    return result;
}


function tokenize(sentence, tokens) {
    let words = sentence.replace(/[!"#$%&'()*+,-\/:;<=>?@[\\\]^_`{|}~]+$/g, '').replace(/\.$/, '');
    words = words.toLowerCase().split(/\s+/);
    let valuesArray = [];

    words.forEach(word => {
        if (tokens.has(word)) {
            valuesArray.push(tokens.get(word)[0]);
        } else {
            valuesArray.push(undefined);
        }
    });

    const numberOfZerosToAdd = 100 - valuesArray.length;
    for (let i = 0; i < numberOfZerosToAdd; i++) {
        valuesArray.unshift(0);
    }
    return valuesArray;
}

async function predict(tokens_of_combinations) {
    // Convert the array of input combinations to a tensor and perform batch prediction within tf.tidy
    const inputTensor = tf.tensor2d(tokens_of_combinations);
    const predictions = model.predict(inputTensor);

    // Wait for the predictions to be computed
    await predictions.data();

    // Convert the predictions tensor to a JavaScript array
    const predictionsArray = predictions.arraySync();

    // Dispose tensors to free up memory
    inputTensor.dispose();
    predictions.dispose();

    return predictionsArray;
}

function findLastVowelIndex(word) { /* Finds the index of last vowel of the words. */
    word = word.toLowerCase();
    
    const vowels = ['a', 'e', 'i', 'ı', 'o', 'u', 'ü', 'ö'];
    
    for (let i = word.length - 1; i >= 0; i--) {
        if (vowels.includes(word[i])) {
            return i;
        }
    }
    
    return -1;
}

function indexOfCharInHarmony(char, harmony) {
    for (let i = 0; i < harmony.length; i++) {
        if (harmony[i].includes(char)) {
            return i; 
        }
    }
    return -1; 
}

function minor_vowel_harmony(word){ /* Controls the words meet the requirements of minor vowel harmony. */
    let harmony = [['a', 'ı'], ['e', 'i'], ['u', 'o'], ['ü', 'ö']];
    let indexOfPrev = -1;
    for(let i = 0; i < word.length; i++){
        let indexOfCurrent = indexOfCharInHarmony(word[i], harmony)
        if(indexOfCurrent != -1){
            if(indexOfPrev != -1){
                if(indexOfPrev == 0 && indexOfCurrent != 0){
                    return false;
                }else if(indexOfPrev == 1 && indexOfCurrent != 1){
                    return false;
                }else if(indexOfPrev == 2 && !(harmony[indexOfCurrent][0] == word[i] && indexOfCurrent % 2 == 0)){
                    return false;
                }else if(indexOfPrev == 3 && !(harmony[indexOfCurrent][0] == word[i] && indexOfCurrent % 2 == 1)){
                    return false;
                }
            }
            indexOfPrev = indexOfCurrent
        }
    }
    return true;
}

function major_vowel_harmony(word){ /* Controls the words meet the requirements of major vowel harmony. */
    let harmony = [['a', 'ı', 'o', 'u'], ['e', 'i', 'ö', 'ü']];

    let indexOfFirstHarmony = -1;

    for(let i = 0; i < word.length; i++){
        let indexOfCurrentHarmony = indexOfCharInHarmony(word[i], harmony);
        if(indexOfCurrentHarmony != -1){
            if(indexOfFirstHarmony != -1  && indexOfFirstHarmony != indexOfCurrentHarmony){
                return false;
            }
            indexOfFirstHarmony = indexOfCurrentHarmony;
        }
    }
    return true;
}

function transferPunctuation(firstWord, secondWord) {
    function isPunctuation(char) {
        return /[^\w\sçğıüşöÇĞİÜŞÖ]/.test(char);
    }
  
    let punctuationPositions = [];
  
    for (let i = 0; i < firstWord.length; i++) {
      if (isPunctuation(firstWord[i])) {
        punctuationPositions.push({ char: firstWord[i], position: i });
      }
    }
  
    let resultArray = secondWord.split('');
  
    punctuationPositions.forEach(punc => {
        if(resultArray[punc.position] != punc.char)
            resultArray.splice(punc.position, 0, punc.char);
    });
  
    return resultArray.join('');
  }

function transferCapitalLetters(firstWord, secondWord) {
    function isCapitalLetter(char) {
        return /[A-ZÇĞİÖŞÜ]/.test(char);
    }
  
    let capitalPositions = [];
  
    for (let i = 0; i < firstWord.length; i++) {
      if (isCapitalLetter(firstWord[i])) {
        capitalPositions.push({ char: (secondWord[i] != 'i') ? secondWord[i].toUpperCase(): 'İ', position: i });
      }
    }
  
    let resultArray = secondWord.split('');
  
    capitalPositions.forEach(cap => {
        if (cap.position < resultArray.length) {
            resultArray[cap.position] = cap.char;
        }
    });
  
    return resultArray.join('');
}

function getSubstringUntilPreviousPunctuation(input) {
    const lastPunctuationIndex = Math.max(
        input.lastIndexOf('!'),
        input.lastIndexOf('.'),
        input.lastIndexOf('?')
    );

    if (lastPunctuationIndex === -1) {
        return input;
    }

    return input.substring(0, lastPunctuationIndex + 1);
}

function removeLastOccurrence(text, sentence) {
    // Escape special characters in the sentence
    const escapedSentence = sentence.replace(/[-\/\\^$*+?.()|[\]{}]/g, '\\$&');
    // Construct regex pattern to match the last occurrence of the sentence within <span> tags
    const pattern = new RegExp(`(<span[^>]*>[^<]*\\b${escapedSentence}\\b[^<]*<\\/span>)(?!.*\\1)`, 'g');
    // Replace the matched pattern with an empty string
    const result = text.replace(pattern, '');
    return result;
}


var model;
var tokens;
var dictionary;
var uniqueTextAreas = [];
var sentences = [];
var modelLoaded = false;

async function loadData() {
    document.body.spellcheck = false;

    if (modelLoaded) return; // Prevent reloading if already loaded
    modelLoaded = true;
    tokens = await loadTokens();
    dictionary = await loadWords();
    model = await loadModel();
}

async function convertToDivs() {

    var allInputs = document.querySelectorAll('div[contenteditable]');

    if (!modelLoaded && allInputs.length > 0) {
        await loadData();

        let alertElement = document.createElement('div');
        alertElement.textContent = "Turkish Text Corrector is ready to use.";
        alertElement.style.padding = "20px";
        alertElement.style.backgroundColor = "green"; 
        alertElement.style.color = "white";
        alertElement.style.position = "fixed";
        alertElement.style.top = "20px";
        alertElement.style.left = "50%";
        alertElement.style.transform = "translateX(-50%)";
        alertElement.style.zIndex = "1000"; 

        document.body.appendChild(alertElement);

        setTimeout(function() {
            alertElement.style.display = "none";
        }, 3000);
    }

    allInputs.forEach(textArea => {
        if (!uniqueTextAreas.includes(textArea)) {
            uniqueTextAreas.push(textArea);
            textArea.addEventListener('click', myfunc);
            function myfunc(){
                var editableDiv;
                let exists = false;
                if(textArea.isContentEditable == true){
                    editableDiv = textArea;
                    exists = true;
                    var textAreaComputedStyle = window.getComputedStyle(textArea);

                    editableDiv.style.cssText += 
                        "cursor: default; user-select: text; outline: none;" +
                        "height: " + textAreaComputedStyle.getPropertyValue('height') + "; " +
                        "box-sizing: " + textAreaComputedStyle.getPropertyValue('box-sizing') + "; " +
                        "overflow: " + textAreaComputedStyle.overflow + "; " + 
                        "white-space: pre-wrap; word-wrap: break-word;";

                }else{
                    editableDiv = document.createElement("div");
                    editableDiv.contentEditable = true;
                    
                    var textAreaComputedStyle = window.getComputedStyle(textArea);
                    var parentStyle = window.getComputedStyle(textArea.parentNode);
                    
                    if (parentStyle.getPropertyValue('position') === 'static') {
                        textArea.parentNode.style.position = 'relative';
                    }
                    
                    editableDiv.style.cssText = 
                        "cursor: default; user-select: text; outline: none;" +
                        "height: " + textAreaComputedStyle.getPropertyValue('height') + "; " +
                        "width: " + textAreaComputedStyle.getPropertyValue('width') + "; " +
                        "font-size: " + textAreaComputedStyle.getPropertyValue('font-size') + "; " +
                        "font-family: " + textAreaComputedStyle.getPropertyValue('font-family') + "; " +
                        "color: " + textAreaComputedStyle.getPropertyValue('color') + "; " +
                        "background-color: " + textAreaComputedStyle.getPropertyValue('background-color') + "; " +
                        "padding: " + textAreaComputedStyle.getPropertyValue('padding') + "; " +
                        "border: " +  textAreaComputedStyle.getPropertyValue('border') + "; " +
                        "box-sizing: " + textAreaComputedStyle.getPropertyValue('box-sizing') + "; " +
                        "overflow: " + textAreaComputedStyle.overflow + "; " + 
                        "white-space: pre-wrap; word-wrap: break-word;";

                    textArea.style.display = "none"; // Hide the textarea
                    
                    textArea.parentNode.insertBefore(editableDiv, textArea.nextSibling);
                }
                

                editableDiv.addEventListener('input', myfunc2)
                
                function myfunc2(event){
                    editableDiv.style.height = 'auto';
                    editableDiv.style.height = editableDiv.scrollHeight + 'px';

                    let input = editableDiv.innerText;
                    const inputSentences = input.split(/(?<=[.!?])/);
                    let sentence = inputSentences[inputSentences.length - 1].trimStart();
                    if (/[!.?]/.test(input.charAt(input.length - 1)) && sentence != sentences[sentences.length - 1]) {

                        async function processSentence(sentence) {

                            let words = sentence.split(' ');
                            let result = '';
                        
                            let possible_words = await eliminatingVariations(generateVariations(words, tokens));
                        
                            let combinations = combiningWords(possible_words.slice(0, possible_words.length), 0, []);
                            
                            let content = editableDiv.innerHTML;
                            let newContent = content.replace(sentence, '');
                            if (newContent == content) {
                                newContent = removeLastOccurrence(content);
                            }
                            editableDiv.innerHTML = newContent;
                        
                            if(combinations.length > 1){
                        
                                let tokens_of_combinations = [];
                        
                                for (let i = 0; i < combinations.length; i++) {
                                    tokens_of_combinations.push(tokenize(combinations[i], tokens));
                                }
                        
                                let predictions = await predict(tokens_of_combinations);
                        
                                let indices = combinations.map((_, index) => index);
                        
                                indices.sort((a, b) => predictions[b] - predictions[a]);
                        
                                let sortedCombinations = indices.map(index => combinations[index]);
                                let sortedPredictions = indices.map(index => predictions[index]);

                                let correctedSentence = sortedCombinations[0];
                                let correctedWords = correctedSentence.split(' ');

                                for (let i = 0; i < correctedWords.length; i++) {
                                    let correctedWord = transferPunctuation(words[i], correctedWords[i]);
                                    correctedWord = transferCapitalLetters(words[i], correctedWord);
                                    let span = document.createElement('span');
                                    
                                    result += correctedWord;

                                    if(i != correctedWords.length - 1)
                                        result += ' ';

                                    if (possible_words[i].length == 1) {
                                        span.textContent = correctedWord;
                                        editableDiv.appendChild(span);
                                        editableDiv.appendChild(document.createTextNode(' '));
                                    } else {
                                        let confidence = -1;
                                        for (let j = 1; j < sortedCombinations.length && confidence == -1; j++) {
                                            for (let k = 0; k < possible_words[i].length; k++) {
                                                if (sortedCombinations[0].replace(correctedWords[i], possible_words[i][k]) == sortedCombinations[j]) {
                                                    confidence = sortedPredictions[0] - sortedPredictions[j];
                                                    break;
                                                }
                                            }
                                        }
                                        if (confidence > 0.1) {
                                            span.textContent = correctedWord;
                                            editableDiv.appendChild(span);
                                            editableDiv.appendChild(document.createTextNode(' '));
                                        } else {
                                            span.style.textDecoration = 'underline';
                                            span.style.textDecorationColor = 'red';
                                            span.style.textDecorationStyle = 'wavy';
                                            span.textContent = correctedWord;

                                            if (possible_words[i].length != 1) {
                                                span.style.cssText = "text-decoration: underline; text-decoration-style: wavy; text-decoration-color: orange; position: relative;";

                                                (function (wordList) {
                                                    let ul;

                                                    span.addEventListener('contextmenu', function (event) {
                                                        event.preventDefault()
                                                        let ul = document.createElement('ul');
                                                        ul.style.position = 'absolute';
                                                        ul.style.top = span.getBoundingClientRect().bottom + 'px';
                                                        ul.style.left = span.getBoundingClientRect().left + 'px';
                                                        ul.style.backgroundColor = 'white';
                                                        ul.style.border = '1px solid black';
                                                        ul.style.padding = '5px';
                                                        ul.style.zIndex = 10;
                                                        ul.style.listStyleType = 'none'; // Remove default bullet points
                                                        ul.style.margin = '0';
                                                        ul.style.boxShadow = '0 2px 5px rgba(0, 0, 0, 0.15)'; // Add shadow for better visibility

                                                        // Iterate over the word list to create list items
                                                        for (let x = 0; x < wordList.length; x++) {
                                                            let li = document.createElement('li');
                                                            li.textContent = transferCapitalLetters(correctedWord, transferPunctuation(correctedWord, wordList[x]));

                                                            // Style each list item
                                                            li.style.padding = '8px 12px';
                                                            li.style.cursor = 'pointer';
                                                            li.style.borderBottom = '1px solid #ddd'; // Add bottom border for separation
                                                            
                                                            // Add click event listener to list items
                                                            li.addEventListener('click', (function (ul, li, x) {
                                                                return function () {
                                                                    span.innerText = li.textContent;
                                                                    document.body.removeChild(ul);
                                                                    textArea.value = editableDiv.innerText;
                                                                    textArea.dispatchEvent(new Event('input'));
                                                                    ul = null;
                                                                };
                                                            })(ul, li, x));

                                                            // Append list item to the unordered list
                                                            ul.appendChild(li);
                                                        }

                                                        // Append the unordered list to the document body
                                                        document.body.appendChild(ul);

                                                        document.addEventListener('click', function handleClickOutside(event) {
                                                            // Check if the click was outside the ul element
                                                            if (!ul.contains(event.target) && event.target !== span) {
                                                                document.body.removeChild(ul);
                                                                document.removeEventListener('click', handleClickOutside);
                                                                ul = null;
                                                            }
                                                        });
                                                    });
                                                })(possible_words[i]);
                                            }

                                            editableDiv.appendChild(span);

                                            let spaceSpan = document.createElement('span');
                                            spaceSpan.innerHTML = "&nbsp;";
                                            editableDiv.appendChild(spaceSpan);
                                        }
                                    }
                                    const range = document.createRange();
                                    range.selectNodeContents(editableDiv);
                                    range.collapse(false);
                                    const selection = window.getSelection();
                                    selection.removeAllRanges();
                                    selection.addRange(range);
                                }
                            }else{

                                let correctedSentence = combinations[0];
                                let correctedWords = correctedSentence.split(' ');


                                for(let i = 0; i < correctedWords.length; i++){
                                    let correctedWord = transferPunctuation(words[i], correctedWords[i]);
                                    correctedWord = transferCapitalLetters(words[i], correctedWord);
                                    let span = document.createElement('span');
                                    span.textContent = correctedWord;
                                    editableDiv.appendChild(span);
                                    editableDiv.appendChild(document.createTextNode(' '));
                                    result += correctedWord;

                                    if(i != correctedWords.length - 1)
                                        result += ' ';

                                    const range = document.createRange();
                                    range.selectNodeContents(editableDiv);
                                    range.collapse(false);
                                    const selection = window.getSelection();
                                    selection.removeAllRanges();
                                    selection.addRange(range);
                                }
                                
                            }
                            if(!exists){
                                textArea.textContent = editableDiv.innerText;
                                textArea.dispatchEvent(new Event('input'));
                                editableDiv.focus();
                            }
                            
                            sentences.push(result)
                            editableDiv.style.height = 'auto';
                            editableDiv.style.height = editableDiv.scrollHeight + 'px';
                        }

                        processSentence(sentence)
                    }
                }
                editableDiv.removeEventListener('click', myfunc);
            }
        }
    });
}

setInterval(convertToDivs, 1000);
