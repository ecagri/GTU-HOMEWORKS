.data
	arr:
	getlength:.asciiz "Enter the length of array: "
	getdivisor:.asciiz "Enter the integer divisor: "
.text
main:
	li $v0, 4 #Print string code. 
	la $a0, getlength #Load string to a0 register to print.
	syscall #Prints string.
	li $v0, 5 #Get integer code.
	syscall #Gets integer.
	add $s0, $zero, $v0 #Saves user input to s0 register.
	
	li $v0, 4 #Print string code. 
	la $a0, getdivisor #Load string to a0 register to print.
	syscall #Prints string.
	li $v0, 5 #Get integer code.
	syscall #Gets integer.
	add $s1, $zero, $v0 #Saves user input to s0 register.
		
	mul $t1, $s0, 4 #Multiply array length by 4.
	addi $t0, $zero, 0 #Sets t0 register to 0 to use as a counter in a loop.
	addi $t5, $zero, 0 #Sets t5 register to 0 to use as a counter in a loop.
	
loop: # Gets array elements from user.
	slt $t2, $t0, $t1 #If t0 is less than t1, sets t2 to 1.
	beq $t2, $zero, continue #If t2 is 0, go to continue label.
	li $v0, 5 #Get integer code.
	syscall #Gets integer.
	sw $v0, arr($t0) #Saves user input to array.
	addi $t0, $t0, 4 #Increases counter by four.
	jal loop #Jumps to loop.
continue: 
	addi $t0, $zero, 0 #Sets t0 register to 0 to use a counter in a loop.
	addi $t7, $t1, -4 
loop2: #Gets ith index of array.
	slt $t2, $t0, $t7 #If t0 is less than t7, sets t2 to 1.
	beq $t2, $zero, exit #If t2 is 0, go to exit label.
	lw $s2, arr($t0) #Loads ith index value of array to s2 register.
	addi $t0, $t0, 4 # Increases counter by four.
	add $t3, $zero, $t0 #Sets t3 to t0.
loop3: #Gets (i+1)th index of array.
	slt $t4, $t3, $t1 #If t3 is less than t1, sets t4 to 1.
	beq $t4, $zero, loop2 #If t4 is 0, go to upper loop.
	lw $s3, arr($t3) #Loads (i+1)th index value of array to s3 register.
	addi $t3, $t3, 4 #Increases counter by four.
	jal divisible #Jumps to divisible label.
	jal loop2 #Jumps to upper loop.
increase: #Increases t5 register value by 1 if sum of two elements is divisible.
	addi $t5 $t5 1	#Increase counter by 1.
	jal loop3 #Go back to loop3.
divisible: #Checks divisibility of the sum of the element at ith index and (i+1)th index to divisor. If they are divisible increase counter by 1. 
	add $s7, $s2, $s3
	div $s7, $s1 
	mfhi $s6 #Save remainder to s6 register.
	beq $s6 0 increase #if remainder is 0, increase counter by 1.
	jal loop3 #Go back to loop3.
exit: #Add a0 register to exit code, and terminates the program.
	add $a0, $zero, $t5 #Load t5 value to a0 register to print.
	li $v0 1 #Print integer code.
	syscall #Prints integer.
	li $v0 10
	syscall
