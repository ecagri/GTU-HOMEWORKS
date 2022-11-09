(setf keywords(make-array '(18 2) :initial-contents '(("and" "KW_AND")("or" "KW_OR")("not" "KW_NOT")("equal" "KW_EQUAL")("less" "KW_LESS")("nil" "KW_NIL")("list" "KW_LIST")
("append" "KW_APPEND")("concat" "KW_CONCAT")("set" "KW_SET")("deffun" "KW_DEFFUN")("for" "KW_FOR")("if" "KW_IF")("exit" "KW_EXIT")("load" "KW_LOAD")("disp" "KW_DISP")("true" "KW_TRUE")("false" "KW_FALSE"))))
(setf operators(make-array '(8 2) :initial-contents '(("+" "OP_PLUS")("-" "OP_MINUS")("/" "OP_DIV")("*" "OP_MULT")("(" "OP_OP")(")" "OP_CP")("**" "OP_DBLMULT")("," "OP_COMMA"))))
(setf current_word "") ; keeps current_word
(setf current_list (list)) ; keeps current_list
(setf str_sign 0) ; keeps number of qoutation mark.
(setf comment_sign 0) ; keeps number of semicolon.
(setf is_end nil) 


(defun check_valueI(word index) ; check whether the word is VALUEI or not.
    (if (> index (- (length word) 1))(return-from check_valueI T)) ; if index is bigger than lenght of the word - 1 return true.

    (setq current_char (char word index)) ; set current_char to indexth char of the word.

    (if (char= #\0 current_char) ; if current_char is '0' continue.

        (if (= index 0) ; if index is 0 continue.

        (if (= (length word) 1) ; if length of the word is 1 return true.

            (return-from check_valueI T)

        (return-from check_valueI nil) ; if length of the word is not 1 return false.
        )
        (check_valueI word (+ index 1)) ; if index is not 0, recursively call check_valueI function.
    )
    (if (char<= #\1 current_char #\9) ; if current_char is between '1' and '9', recursively call check_valueI function

        (check_valueI word (+ index 1)) 

    (return-from check_valueI nil) ; if current_char is not between '1' and '9', return false.
    )
    )
)

(defun check_valueF(word index fraction) ; check whether the word is VALUEF or not.
    (if (> index (- (length word) 1))(progn (setq current_list (append current_list (list (list word "VALUEF"))))(return-from check_valueF T))) ; if index is bigger than length of the word - 1 return true.

    (setq current_char (char word index)) ; set current_char to indexth char of the word.

    (if (char= current_char #\f) ; if current_char is 'f', continue.

        (if(equal fraction T) ; if fraction sign is already taken, print error and return false.

        (progn (print (concatenate 'string word ": REPEATED FRACTION SIGN ERROR"))(return-from check_valueF nil))

        (if (= index (- (length word) 1)) ; if fraction sign is not taken, and current_char is the last character of the word, print error and return false.

            (progn(print (concatenate 'string word ": NOT HAVING FRACTION PART!"))(return-from check_valueF nil))

        (check_valueF word (+ index 1) T)) ; if fraction sign is not taken, and current_char is not the last character of the word, recursively call check_valueF function.
        )

    (if (char= current_char #\0) ; if current_char is '0', continue.

        (if (= index 0) ; if index is 0 continue. 

        (if (or(= (length word) 1)(and (> (length word) 1)(char= (char word (+ index 1)) #\f))) ; if length of the word is 1 or length of the word is bigger than 1 and next char is 'f' recursively call check_valueF function.

            (check_valueF word (+ index 1) fraction)

        (progn (print (concatenate 'string word ": LEADING ZERO(S) ERROR"))(return-from check_valueF nil)) ; otherwise, print error and return false.
        )

        (check_valueF word (+ index 1) fraction) ; if index is not 0, recursively call check_valueF function.
    )

    (if (char<= #\1 current_char #\9) ; if current char is between '1' and '9', recursively call check_valueF function.

        (check_valueF word (+ index 1) fraction) ;

    (progn (print (concatenate 'string word ": ILLEGAL CHARACTER" "(" (string current_char) ")"))(return-from check_valueF nil)) ; if current_char is not between '1' and '9', print error and return false.
    )
    )
    )
)

(defun check_identifier(word index) ; check whether the word is an identifier.
    (if (> index (- (length word) 1)) ; if index is bigger than length of the word - 1 return true.

        (progn(setq current_list (append current_list (list (list word "IDENTIFIER"))))(return-from check_identifier T)))

    (setq current_char (char word index)) ; set current_char to indexth char of the word.

    (if (or (char<= #\0 current_char #\9)(char<= #\a current_char #\z)(char<= #\A current_char #\Z)(char= current_char #\_)) ; if current_char is between '0' and '9' or 'a' and 'z' or 'A' and 'Z' or is '_', recursively call check_identifier function.

        (check_identifier word (+ index 1))

    (progn(print (concatenate 'string word ": ILLEGAL CHARACTER FOR IDENTIFIER" "(" (string current_char) ")"))(return-from check_identifier nil))) ; otherwise print error and return false.
)

(defun check_keyword(word index) ; check whether the word is a keyword.
    (if (<= (/ (array-total-size keywords) 2) index)(return-from check_keyword nil)) ; if all keywords are checked, and there is no match, return false.

    (if (string= word (aref keywords index 0)) ; if word is equal to indexth keyword, add the token of the keyword to the list and return true.

            (progn(setq current_list (append current_list (list (list word (aref keywords index 1)))))(return-from check_keyword T))

    (check_keyword word (+ index 1))) ; otherwise, recursively call check_keyword function.
)

(defun check_operator(word index) ; check whether the word is an operator.
    (if (<= (/ (array-total-size operators) 2) index)(progn( print (concatenate 'string word ": SYNTAX ERROR"))(return-from check_operator nil))) ; if all operators are checked and there is no match, print error return false.
    (if (string= word (aref operators index 0)) ; if word is equal to indexth operator, add the token of the operator to the list and return true.

        (progn(setq current_list (append current_list (list (list word (aref operators index 1)))))(return-from check_operator T))

    (check_operator word (+ index 1))) ; otherwise, recursively call check_operator function.
)

(defun set_valueStr(word) ; set quotation signs and VALUESTR token.
    (if (= str_sign 1) ; if number of quotation sign is 1, add quotation mark and OP_OC token to the list, and remove quotation mark from word.
        (progn
            (setq current_list (append current_list (list (list (string #\quotation_mark) "OP_OC"))))
            (setq word (subseq word 1))
        )
    (progn ; if number of quotation sign is 2, continue.
        (setq word (subseq word 0 (- (length word) 1))) ; remove quotation mark at the end of the word.
        (setq current_list (append current_list (list (list word "VALUESTR")))) ; add word and VALUESTR token to the list.
        (setq current_list (append current_list (list (list (string #\quotation_mark) "OP_CC")))) ; add quotation mark and OP_CC token to the list.
        (setq str_sign 0) ; set str_sign to 0.
    ))

    (setq current_word "")

    (return-from set_valueStr T)
)

(defun set_comment(word) ; set COMMENT token. 
    (setq current_list(append current_list (list (list word "COMMENT")))) ; add current_word and COMMENT to list.
    (setq current_word "") ; set current_word to empty string.
    (setq comment_sign 0) ; set comment_sign to 0.
    (return-from set_comment T)
)

(defun parser(word) ; parse the word according to first char. 
    (if (or(string= word "")(string= word " "))(return-from parser T)) ; if the word is space or empty, return true.

    (setq first_char (char word 0)) ; set first_char to first character of the word. 

    (if (>= str_sign 1) ; if str_sing is more than 0, call set_valueStr function.
        (return-from parser (set_valueStr word))
    )

    (if (>= comment_sign 2) ; if comment_sign is bigger than 1, remove semicolons from word, and call set_comment function.
        (progn
            (setq word (subseq word 2))
            (return-from parser (set_comment word)))
    )


    (if (char<= #\0 first_char #\9) ; if first_char is between '0' and '9', continue.

        (if (equal (check_valueI word 0) T) ; if the word is a VALUEI, add word and VALUEI token to list, and return true.

            (progn (setq current_list (append current_list (list (list word "VALUEI"))))(return-from parser T))
        
        (return-from parser (check_valueF word 0 nil)) ;if the word is a VALUEF, add word and VALUEF token to list and return true.

        )
    (if (and (or (char<= #\a first_char #\z)(char<= #\A first_char #\Z)(char= first_char #\_))) ; if the first_char is between 'a' and 'z' or 'A' and 'Z' or is '_', continue.

        (if (equal (check_keyword word 0) T) ; if the word is a KEYWORD, add word and token of the word to list, and return true.

              (return-from parser T)

        (return-from parser (check_identifier word 0)) ; otherwise, call check_identifier function.
        )
    (if (or(char<= #\! first_char #\/)(char< #\9 first_char #\A)) ; if the first_char is between '!' and '/' or '9' and 'A', call check_operator function.

        (return-from parser (check_operator word 0))
    )
    )
    )
    ; if the first_letter is not in the one of these character sets, print error and return false.
    (print (concatenate 'string word ": SYNTAX ERROR"))

    (return-from parser nil)
)

(defun read-recursive (stream-in stream-out) ; read file recursively.

  (let ((char (read-char stream-in nil)))

    (unless (null char) ; continue until null char.

        (setq is_end nil) ; set is_end to nil.

        (if (and (< str_sign 1)(< comment_sign 2)) ; if str_sign is less than 1 and comment_sign is less than 2, continue.

            (if (char= char #\right_parenthesis) ; if char is right parenthesis, 

                (progn
                    (if (equal (parser current_word) nil) ; if current_word cannot be tokenized, return false.

                        (return-from read-recursive nil)

                    (setq current_word "")) ; otherwise, set current_word to empty string.
                    (check_operator (string char) 0)) ; parse right parenthesis char.
            (if (char= char #\left_parenthesis) ; if char is left parenthesis, 

                (progn
                    (check_operator (string char) 0) ; parse left parenthesis char.
                    (if (equal (parser current_word) nil) ; if current_word cannot be tokenized, return false.
                    
                        (return-from read-recursive nil)

                    (setq current_word ""))) ; otherwise set current_word to empty string.
            )
            )
        )

        (if (and(char= char #\semicolon)(< str_sign 1)) ; if char is semicolon and str_sign is less than 1, increase comment_sign by 1.
            (setq comment_sign (+ comment_sign 1))
        )
    
        (if (and (char/= char #\semicolon)(= comment_sign 1)) ; if char is not semicolon and comment_sign is 1, set comment_sign to 0.
            (setq comment_sign 0)
        )

        (if (or(= str_sign 2)(and(= str_sign 0)(char= char #\lf))(and(= str_sign 0)(< comment_sign 2)(char= char #\space)))

            (if (equal (parser current_word) nil) ; if current_word cannot be tokenized, return false.

                (return-from read-recursive nil)

            (setq current_word ""))) ; otherwise set current_word to empty string.

        (if (and (or(char/= char #\space)(= str_sign 1)(= comment_sign 2))(char/= char #\lf)(char/= char #\right_parenthesis)(char/= char #\left_parenthesis))
        
            (setq current_word (concatenate 'string current_word (string char)))) ; if conditions is satisfied, push char to current_word.  

        (if (and(char= char #\quotation_mark)(< comment_sign 2)) ; if char is quotation mark and comment_sign is less than 2, continue. 
            (progn
                (if (< str_sign 2) ;if str_sign is less than 2, increase str_sign by 1.
                    (setq str_sign (+ str_sign 1)))
                (parser current_word) ; call parser function.
            )
        )

        (if (char= char #\lf)(progn(if(equal current_list nil)()(progn(write current_list)(terpri)))(setq current_list (list)))) ; if char is new line, print list and make it empty.

        (setq is_end T) ; set is_end T.
        
    (read-recursive stream-in stream-out)
    )
    )
)

(defun lexer (&optional filename) ; read the file and parse it.

  (with-open-file (file-stream filename :if-does-not-exist nil)

    (with-output-to-string (string-stream)

        (read-recursive file-stream string-stream)

        (if (and(equal is_end T)(string/= current_word "")) ; it is to read last word incase of there is no new line or space sign at the end of the file.. 
            (parser current_word)
        )

        (if(equal current_list nil)()(progn(write current_list))) ; if current_list is not nil, print it.

      string-stream
    )
  )
)

(defun gppinterpreter()
    (setq filename (nth 0 #+CLISP *args*)) ; get name of the file.
    (lexer filename) ; call lexer.
)

(gppinterpreter)
