#include <stdio.h>

#include <math.h>

void writepolynomials();

void is_armstrong_palindrome();

void sum_primes_inbetween();

void helperfunction(double coeffiecent, int power, int degree); /* A helper function to write polynomials */

void writepretty(double number); /* A helper function to write coefficient without tralling zeros. */

/*---------------------------------------------------------------------------------*/

int main(){

	writepolynomials();

	is_armstrong_palindrome();
	
	sum_primes_inbetween();

	return 0;
}

/*---------------------------------------------------------------------------------*/

void writepolynomials(){
	int degree,temp,logicvalue;

	double coeffiecent;
	
	printf("Enter your polynomial [n a_n a_n-1 a_n-2 ... a_0]: ");

	logicvalue= scanf("%d",&degree); /* Gets degree from the user. */

	while(logicvalue==0 || degree<0){

		printf("Enter your polynomial [n a_n a_n-1 a_n-2 ... a_0]: ");

		getchar();

		logicvalue= scanf("%d",&degree); /* Gets degree from the user. */

		}


	temp=degree; /* Assigns degree to temp to keep the value of degree */

	for(;temp>=0;temp--){ /* This blocks provides to get coefficients from max degree term to min degree term */

		scanf("%lf",&coeffiecent);

		if(coeffiecent>0.05 || coeffiecent<-0.05){

			helperfunction(coeffiecent,temp,degree);
		}
		else{
			if(temp==degree){
				degree-=1;
			}
		}
	}

	printf("\n");
}

void sum_primes_inbetween(){
	int firstnumber,secondnumber,divisor,sum=0,numberofdivisors,temp;

	printf("Please enter first integer number: ");

	scanf("%d",&firstnumber);

	while(firstnumber<0){
		printf("Please enter first integer number: ");

		scanf("%d",&firstnumber);
	}

	printf("Please enter second integer number: ");

	scanf("%d",&secondnumber);

	while(secondnumber<0){
		printf("Please enter second integer number: ");

		scanf("%d",&secondnumber);
	}
	
	if(secondnumber<firstnumber){

		temp=secondnumber;

		secondnumber=firstnumber;

		firstnumber=temp;

	}
	

	printf("Sum of prime numbers between %d and %d : ",firstnumber,secondnumber);

	for(firstnumber=firstnumber+1;firstnumber<secondnumber;firstnumber++){ /* This blocks try all numbers between first number and second number. firstnumber=firstnumber+1 because, first number is not included this range. */

		numberofdivisors=0; /* Reset the numberof divisors every loop */

		for(divisor=1;divisor<=firstnumber;divisor++){ /* This blocks decide the number is prime or not */

			if(firstnumber%divisor==0){

				numberofdivisors++;
			}
			if(numberofdivisors>2){ /* If number of divisors greater than 2, this is not a prime number */

				break;
			}

		}
		if(numberofdivisors==2){ /* If there is just two divisors at the end of the loop, this is a prime number. */

			sum+=firstnumber; /* Add the prime number to sum. */

			}
	}
	printf("%d\n",sum);
}

/*---------------------------------------------------------------------------------*/

void is_armstrong_palindrome(){

	int sum1=0, sum2=0, digit, coeffiecent, numberofdigits=0, temp, number;

	printf("Please enter an integer number : ");

	scanf("%d",&number); /* Gets the number */

	while(number<0){
		printf("Please enter an integer number : ");

		scanf("%d",&number); /* Gets the number */
	}

	temp=number; /* Assigns number to temp variable to keep value of number. */

	/* ------------------------This blocks for the Armstrong number checker--------------------------- */

	for(;temp>=1;temp/=10){ /* Find the number of digits of the number */

		numberofdigits+=1;
	}

	for(temp=number;temp>=1;temp/=10){ /* Seperates the numbers to digits*/
		
		digit=temp%10;

		sum1+=pow(digit,numberofdigits); /* Gets digit to the power of number of digits */

	}


	/* ------------------------This blocks for the Palindrome number checker--------------------------- */

	coeffiecent=pow(10, numberofdigits-1);  /* For example for the number 351, coefficient will be 100 . For 2250, coefficient will be 1000.*/
	
	for(temp=number;temp>=1;temp/=10){ /* Continues the process until each digits of the numbers are taken into account. */

		digit = temp % 10; /* Gets each digits in order from 1's. */

		digit = coeffiecent * digit; /* Multiplies them by coefficient. */

		sum2 += digit; /* Adds the result to sum. */

		coeffiecent/=10; /* Divides coefficient by 10. */
	}
	if(number==sum1 && number==sum2){
		printf("This number is both Palindrome and Armstrong number.\n");
	}
	else if(number==sum1 && number!=sum2){
		printf("This number is only Armstrong number.\n");
	}
	else if(number!=sum1 && number==sum2){
		printf("This number is only Palindrome number.\n");
	}
	else{
		printf("This number does not satisfy any special cases.\n");
	}
}

/*---------------------------------------------------------------------------------*/

void helperfunction(double coeffiecent, int power, int degree){
	if(coeffiecent>0){
		if(power!=degree){ 
			printf("+"); /* if power of x is not the highest degree of polynomial, print "+". */
		}
		if(coeffiecent!=1 || power==0){
			writepretty(coeffiecent); /* if coefficient does not equal to 1 or power equals to zero print x. */
		}
		if(power>1){
			printf("x^%d",power); /* if power is greater than 1 print power. */
		}			
		else if(power==1){ 
			printf("x"); /*  if power equals to 1, just print x. */
		}
	}
	else if(coeffiecent<0){
		if(coeffiecent!=-1 || power==0){
			writepretty(coeffiecent); /* if coefficient doesn't equal to -1 or power equals to 0 print x. */
		}
		else{
			printf("-"); /* if x equals to 1 and power doesn't equal to 0 print '-'. */
		}	
		if(power>1){
			printf("x^%d",power); /* if power is greater than 1 print power. */
		}
		else if(power==1){
			printf("x"); /* if power equals to 1, just print x. */
		}
			
	}
}

/*---------------------------------------------------------------------------------*/

void writepretty(double number){
	if(fmod(number,1)==0){
		printf("%.0f",number);
	}
	else{
		printf("%.1f",number);
	}	
}
