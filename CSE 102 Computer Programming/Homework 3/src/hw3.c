#include <stdio.h>

#include <math.h>

void calculate_fibonacci_sequence();

void decide_perfect_harmonic_number();

void difference_max_min();

void bmi_calculation();

void writepretty(double number); /* writes numbers in pretty format */

double whichGreater(double x1, double x2); /* Finds greater number in between two numbers. */

double whichLess(double x1, double x2); /* Finds less number in between two numbers. */

/*-------------------------------------------------------------------------------------*/

int main(){

	calculate_fibonacci_sequence();

	decide_perfect_harmonic_number();

	difference_max_min();

	bmi_calculation();

}

/*-------------------------------------------------------------------------------------*/

void calculate_fibonacci_sequence(){
	int term1, term2, temp, i, logicvalue,repetition;

	char isstar;
	
	printf("Please enter term(s) number: ");

	while(1){
		logicvalue=scanf("%d",&repetition); /* Checks the input is a numeric value or not. */
		
		scanf("%c",&isstar); /* Gets the input if it is not a numeric value. */

		if(logicvalue==1){ /* If input is a numeric value, continue. */

			if(repetition>0){ /* If input is posivite number, prints fibonacci sequence. */
				printf("Fibonacci Sequence:\n");

				term2=1;

				term1=0;

				for(i=0;i<repetition;i++){
					if(i!=0){
						temp=term2; /* temp assigned to term2, to keep the value of term2 */

						term2=term1+term2; /* Finding next term */

						printf("%d\n\n",term2);	
			
						term1=temp; /* taking the value of original term2 and assigned to term1 */
					}

					else if(i==0){
					printf("1\n\n"); 
					}
		
				}

				printf("Please enter term(s) number: ");
				}

			else{ /* If input is negative number, prints a warning. */
				printf("Please enter \"positive\" term(s) number: ");
			}
		}

		else{ /* If input is not a numeric value, continue. */
			if(isstar=='*'){ /* If input is exit value(*), exit. */

				break;
			}

			else{ /* If input is not exit value(*), prints a warning. */
				printf("Please enter \"numeric\" term(s) number: ");
			}
		}
	}

}

/*-------------------------------------------------------------------------------------*/


void decide_perfect_harmonic_number(){

	int sum, divisor,numberofdivisors,number;
	
	double sumofdivisors;

	float harmonicchecker;

	char isstar;

	printf("Please enter input number: ");

	while(1){
		sum=0;

		sumofdivisors=0;

		numberofdivisors=0;

		scanf("%d",&number); /* Gets the value */

		scanf("%c",&isstar); /* Gets the input if it is not a numeric value. */

		if(isstar=='*'){ /* Checks exit value(*) entered */
			break;
			}

		else if(number>0){ /* Controls input is positive or not. */
			printf("\nNatural number divisors : ");

			for(divisor=1;divisor<=number;divisor++){ /* This block provides to try all numbers to find is it divisor of the number or not ,in between 1 and number.  */

				if(number%divisor==0){ /* Checks is it a divisor */
				
					if(divisor!=number){ /* İf divisor doesn't equals to number, print it with comma. And adds the divisor to sum for perfect number checker.*/

						printf("%d, ",divisor);

						sum+=divisor;
						
					}

					else if(divisor==number){ /* İf divisor equals to number, print it without comma. */

						printf("%d",number);
					}

				numberofdivisors++; /* İf the numnber is a divisor, increases numberofdivisors by one. */

				sumofdivisors+=(1.0/divisor); /* Add 1/divisor to sumofdivisors for harmonic divisor number checker. */
				}
			}
		}

		printf("\n\nIs Perfect Number? :");

		if(sum==number){ /* if sum equals to number, it is a perfect number. */
			printf("Yes");
		}
		else{
			printf("No");
		}

		printf("\n");

		harmonicchecker=numberofdivisors / sumofdivisors; /* To control is it harmonic or not, number of divisors should divide by sum of 1/divisors .*/

		printf("\nIs Harmonic Divisor Number? :");

		if(fmod(harmonicchecker,1.0)==0){ /* If numberofdivisors/sumofdivisors equals an integer, the number is harmonic divisor number. */
			printf("Yes\n");
		}
		else{
			printf("No\n");
		}

		printf("\nPlease enter input number:");
	}
}

/*-------------------------------------------------------------------------------------*/


void difference_max_min(){
	double max1, max2, max3, MAX;

	double min1, min2, min3, MIN;

	double n1, n2, n3, n4, n5;

	printf("Please enter 5 numbers:");

	scanf("%lf %lf %lf %lf %lf",&n1,&n2,&n3,&n4,&n5);

	/* Finding max number */
	max1=whichGreater(n1,n2); /* Max number of group 1 */

	max2=whichGreater(n3,n4); /* Max number of group 2 */

	max3=whichGreater(max1,max2); /* Max number of group 1 and group 2 */

	MAX=whichGreater(max3,n5); /* Max number of total */

	min1=whichLess(n1,n2); /* Min number of group 1 */

	min2=whichLess(n3,n4); /* Min number of group 2 */

	min3=whichLess(min1,min2); /* Min number of group 1 and group 2 */

	MIN=whichLess(min3,n5); /* Min number of total */

	printf("Maximum number is: ");
	writepretty(MAX);

	printf("Minimum number is: ");
	writepretty(MIN);
	
	printf("Difference between max and min is ");
	writepretty(MAX-MIN);
}

/*-------------------------------------------------------------------------------------*/

void bmi_calculation(){
	double weight,height,BMI;

	printf("\nPlease enter weight: ");

	scanf("%lf",&weight);

	printf("\nPlease enter height: ");

	scanf("%lf",&height);

	printf("Your category: ");

	BMI=weight / (height * height);

	if(BMI<16.0){
			printf("Severely Underweight");
	}
	else if(16.0<=BMI && BMI<18.5){
			printf("Underweight");		
	}
	else if(18.5<=BMI && BMI<24.5){
			printf("Normal");
	}
	else if(24.5<=BMI && BMI<30.0){
			printf("Overweight");
	}
	else if(30.0<=BMI){
			printf("Obese");
	}
	printf("\n");
}

/*-------------------------------------------------------------------------------------*/

double whichGreater(double x1, double x2){
	if(x1>=x2){
		return x1;
	}
	else{
		return x2;
	}
}

/*-------------------------------------------------------------------------------------*/

double whichLess(double x1, double x2){
	if(x1<=x2){
		return x1;
	}
	else{
		return x2;
	}
}

/*-------------------------------------------------------------------------------------*/

void writepretty(double number){
	if(fmod(number,1)==0){
		printf("%.0f\n",number);
	}
	else if(fmod(number*10,1)==0){
		printf("%.1f\n",number);
	}
	else{
		printf("%.2f\n",number);
	}
}