(setf keywords
    (make-array '(10 2) :initial-contents '(("nil" "KW_NIL")("defvar" "DEFV")("deffun" "DEFF")("while" "KW_WHILE")("if" "KW_IF")("exit" "KW_EXIT")("load" "KW_LOAD")("disp" "KW_DISP")("true" "KW_TRUE")("false" "KW_FALSE"))))
(setf operators
    (make-array '(6 2) :initial-contents '(("set" "OP_SET")("and" "OP_AND")("or" "OP_OR")("not" "OP_NOT")("eq" "OP_EQ")("gt" "OP_GT"))))
(setf operators-sign
    (make-array '(6 2) :initial-contents '((#\+ "OP_PLUS")(#\- "OP_MINUS")(#\/ "OP_DIV")(#\* "OP_MULT")(#\left_parenthesis "OP_OP")(#\right_parenthesis "OP_CP"))))

(setf current_word "") ; keeps current_word
(setf current_list (list)) ; keeps current_list
(setf comment_mode nil) ; keeps comment_mode.
(defun check-operator(word index) ; check whether the word is an operator.
    (if (<= (/ (array-total-size operators) 2) index)(return-from check-operator nil))
    (if (string= word (aref operators index 0)) ; if word is equal to indexth operator, add the token of the operator to the list and return true.

        (progn
        (setq current_list (append current_list (list (list word (aref operators index 1))))) 
        (return-from check-operator T)) 

    (check-operator word (+ index 1))) ; otherwise, recursively call check-operator function.
)
(defun check-keyword(word index) ; check whether the word is a keyword.
    (if (<= (/ (array-total-size keywords) 2) index)(return-from check-keyword nil)) ; if all keywords are checked, and there is no match, return false.

    (if (string= word (aref keywords index 0)) ; if word is equal to indexth keyword, add the token of the keyword to the list and return true.

            (progn
            (setq current_list (append current_list (list (list word (aref keywords index 1)))))
            (return-from check-keyword T))

    (check-keyword word (+ index 1))) ; otherwise, recursively call check-keyword function.
)
(defun check-operator-sign (char index control) ; check whether the char is one of the sign.
    (if (<= (/ (array-total-size operators-sign) 2) index) ; if all operator signs are checked, and there is no match, return false.
        (return-from check-operator-sign nil))

    (if (char= char (aref operators-sign index 0)) ; if char is equal to indexth operator, add the token of the operator to the list and return true.

        (progn
        (if (equal control nil)
            (setq current_list (append current_list (list (list char (aref operators-sign index 1)))))
        )
        (return-from check-operator-sign T))

    (check-operator-sign char (+ index 1) control)) ; otherwise, recursively call check-operator-sign function.
    
)
(defun check-identifier(word index) ; check whether the word is an identifier.
    (if (> index (- (length word) 1)) ; if index is bigger than length of the word - 1 return true.

        (progn
        (setq current_list (append current_list (list (list word "IDENTIFIER"))))
        (return-from check-identifier T)))

    (setq current_char (char word index)) ; set current_char to indexth char of the word.

    (if (or (char<= #\a current_char #\z)(char<= #\A current_char #\Z)(and(/= index 0)(or(char<= #\0 current_char #\9)(char= current_char #\_)))) ; if current_char provides the conditions, recursively call check_identifier function.

        (check-identifier word (+ index 1))

    (progn ; otherwise print error and return false.
    (print (concatenate 'string word ": ILLEGAL CHARACTER FOR IDENTIFIER" "(" (string current_char) ")\n"))
    (return-from check-identifier nil))) 
)
(defun check-valueF(word index fraction) ; check whether the word is a valuef
    (if (> index (- (length word) 1)) ; if all character of word is checked, return true.
        (return-from check-valueF T)
    )

    (setq current_char (char word index)) ; set current_char according to index.

    (if (char= current_char #\f) ; if current char is fraction sign, continue.

        (if (= index 0) ; if index is 0, print error and return false.

            (progn
            (print (concatenate 'string word ": NOT HAVING DIVIDEND PART"))
            (return-from check-valueF nil))

        (if (equal fraction T) ; if fraction sign is already used, print error and return false.

            (progn 
            (print (concatenate 'string word ": REPEATED FRACTION SIGN ERROR"))
            (return-from check-valueF nil))
            
        (if (= index (- (length word) 1)) ; if fraction sign is at the end of the word, print error and return false.

            (progn
            (print (concatenate 'string word ": NOT HAVING FRACTION PART!"))
            (return-from check-valueF nil))

        (check-valueF word (+ index 1) T) ; if it passes all test, recursively call check-valueF function for next char.
        )
        )
        )

    (if (char= current_char #\0) ; if current_char is 0, continue.

        (if (and(> index 0)(char/= (char word (- index 1)) #\f)) ; if index is bigger than 0 and previous char is not the fraction sign, recursively call check-valueF function for next char.

            (check-valueF word (+ index 1) fraction)

        (if (and (= index 0)(> (length word) 2)(char= (char word (+ index 1)) #\f)) ; if there is no leading zero for both dividend and divisor part, recursively call check-valueF function for next char.

            (check-valueF word (+ index 1) fraction)

        (progn ; if the word does not provide the conditions, print error and return false.
        (print (concatenate 'string word ": LEADING ZEROS ERROR"))
        (return-from check-valueF nil))
        )
        )

    (if (char<= #\1 current_char #\9) ; if current_char is between 1 and 9, recursively call check-valueF function for next char.

        (check-valueF word (+ index 1) fraction)

    (progn ; if char is not one of them (0-9 or f) print error and return false.
    (print (concatenate 'string word ": ILLEGAL CHARACTER" "(" (string current_char) ")"))
    (return-from check-valueF nil))
    )
    )
    )
)
(defun check-token(word) ; parse the word according to first char. 
    (if (or(string= word "")(string= word " "))(return-from check-token T)) ; if the word is space or empty, return true.

    (setq first_char (char word 0)) ; set first_char to first character of the word. 

    (if (char<= #\0 first_char #\9) ; if first_char is between '0' and '9', continue.

        (if (equal (check-valueF word 0 nil) T) ; if the word is a VALUEI, add word and VALUEI token to list, and return true.

            (progn 
            (setq current_list (append current_list (list (list word "VALUEF"))))
            (return-from check-token T))
            
        (return-from check-token nil)
        )
    (if (or (char<= #\a first_char #\z)(char<= #\A first_char #\Z)) ; if the first_char is between 'a' and 'z' or 'A' and 'Z' or is '_', continue.

        (if (equal (check-keyword word 0) T) ; if the word is a KEYWORD, add word and token of the word to list, and return true.

            (return-from check-token T)

        (if (equal (check-operator word 0) T)

            (return-from check-token T)
            
        (return-from check-token (check-identifier word 0)) ; otherwise, call check_identifier function.
        )
        )
    )
    )
    ; if the first_letter is not in the one of these character sets, print error and return false.
    (print (concatenate 'string word ": SYNTAX ERROR"))

    (return-from check-token nil)
)
(defun readLine (stream-in stream-out) ; read line char by char.

    (let ((char (read-char stream-in nil)))

        (unless (null char) ; continue until null char.

            (if (char= char #\semicolon) ; if char is semicolon, continue.
                (if (and (> (length current_word) 0)(char= (char current_word (- (length current_word) 1)) #\semicolon)) ; if previous char is also semicolon, open comment_mode.
                    (setq comment_mode T)
                )
            )
            (if (equal comment_mode nil) ; if comment_mode is close, continue.
                (if (or (char= char #\space)(char= char #\lf)(equal (check-operator-sign char 0 T) T)) ; if char is space, new line sign or one of the operator-sign, tokenize current_word.
                    (progn
                    (if (equal (check-token current_word) nil) ; if current_word is not tokenizable, return false.
                        (return-from readLine nil)
                    )
                    (check-operator-sign char 0 nil)
                    (setq current_word "")) ; clear the current_word.

                (setq current_word (concatenate 'string current_word (string char)))) ; otherwise, add char to current_word.
            )

            (if (char= char #\lf) ; if char is new line sign, continue.
                (progn
                (if (equal comment_mode T) ; if comment mode is open, remove comment_sign from the current_word.
                    (setq current_word (subseq current_word 0 (- (length current_word) 1)))
                )
                (if (equal (check-token current_word) nil) ; if current_word is not tokenizable, return false.
                    (return-from readLine nil)
                )
                (write current_list) ; print current_list
                (terpri)
                (setq comment_mode nil) ; close comment_mode.
                (setq current_word "") ; clear the current_word
                (setq current_list (list))) ; clear the current_list
            )

            (readLine stream-in stream-out)
        )
    )
)
(defun lexer (&optional filename) ; read the file and parse it.

    (with-open-file (file-stream filename :if-does-not-exist nil)

        (with-output-to-string (string-stream)

            (readLine file-stream string-stream)
        )
    )
)
(lexer)
