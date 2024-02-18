with open("archive/wiki_00", 'r', encoding='utf-8') as inFile:
    with open("archive/wiki_00_out", "w", encoding='utf-8') as outFile:
        for line in inFile:
            for char in line:
                newChar = char.lower()
                if(newChar == 'ç'):
                    newChar = 'c'
                elif(newChar == 'ş'):
                    newChar = 's'
                elif(newChar == 'ğ'):
                    newChar = 'g'
                elif(newChar == 'ö'):
                    newChar = 'o'
                elif(newChar == 'ı'):
                    newChar = 'i' 
                elif(newChar == 'ü'):
                    newChar = 'u'
                outFile.write(newChar)


