/*
** main.c:
**
** The test/driver program for the homework.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.02.23.55
** 
*/

/* I wrote my functions according to pdf. There was no time to make changes which are said in last day. Please evaluate it by considering this conditions. */
#include <stdio.h>
#include "hw5_lib.h"


void test_operate_polynomials () 
{
	double a3, a2, a1, a0, b3, b2, b1, b0;

	char op;
	
	int degree1=0,degree2=0,degree3=0,degree4=0, logicvalue=0;
	
	printf("Enter first polynomial ( (3,a),(2,b),(1,c),(0,d) ! Write them in correct order like example !):"); /* You have to enter in correct order. */
	
	while(1){
	
		logicvalue = scanf("(%d,%lf),(%d,%lf),(%d,%lf),(%d,%lf)",&degree1,&a3,&degree2,&a2,&degree3,&a1,&degree4,&a0); /* Gets input from the user. */

		getchar();
		
		if(degree1==3 && degree2==2 && degree3==1 && degree4==0 && logicvalue==8){ /* If the input is not in the format like in pdf (3,a),(2,b),(1,c),(0,d) continue to get inputs. */
			break;
		}
		printf("Invalid input please enter again\n");
	}
	printf("Enter second polynomial ( (3,a),(2,b),(1,c),(0,d) ! Write them in correct order like example !): "); /* You have to enter in correct order. */
	
	while(1){
	
		logicvalue==scanf("(%d,%lf),(%d,%lf),(%d,%lf),(%d,%lf)",&degree1,&b3,&degree2,&b2,&degree3,&b1,&degree4,&b0); /* Gets input from the user. */
		
		getchar();
		
		if(degree1==3 && degree2==2 && degree3==1 && degree4==0 && logicvalue==8){ /* If the input is not in the format like in pdf (3,a),(2,b),(1,c),(0,d) continue to get inputs. */
			break;
		}
		printf("Invalid input please enter again\n");
	}
	printf("Enter the operator (* or + or -):");
	
	while(1){

		scanf("%c",&op); /* Gets operator from the user. */

		if(op=='+' || op=='-' || op=='*'){ /* If the input is not *,- or + operator, continue to get inputs. */
			break;
			}
		printf("Invalid input please enter again\n");
		}
		
	operate_polynomials(&a3, &a2, &a1, &a0, &b3, &b2, &b1, &b0, op);

	if(op=='+' || op=='-'){ /* If operator + or -, prints them. */

		printf("Coefficient of x^3 : %.2f\n",a3);
		
		printf("Coefficient of x^2 : %.2f\n",a2);
		
		printf("Coefficient of x : %.2f\n",a1);
		
		printf("Constant is : %.2f\n",a0);
	}
	else if(op=='*'){ /* If operator *, prints them. */
		printf("Coefficient of x^6 : %.2f\n",a3);
		
		printf("Coefficient of x^5 : %.2f\n",a2);
		
		printf("Coefficient of x^4 : %.2f\n",a1);
		
		printf("Coefficient of x^3 : %.2f\n",a0);
		
		printf("Coefficient of x^2 : %.2f\n",b3);
		
		printf("Coefficient of x : %.2f\n",b2);
		
		printf("Coefficient is : %.2f\n",b1);
	}
}


void test_four_d_vectors ()
{
	double mean_a0=0.0, mean_a1=0.0, mean_a2=0.0, mean_a3=0.0, longest_distance=0.0;
	int N=0;
	four_d_vectors (&mean_a0, &mean_a1, &mean_a2, &mean_a3, &longest_distance, N);
	printf("Mean a0: %f\nMean a1: %f\nMean a2: %f\nMean a3: %f\nThe longest distance between two points: %f\n\n\n", mean_a0, mean_a1, mean_a2, mean_a3, longest_distance);
}


void test_dhondt_method ()
{
	int partyA=0, partyB=0, partyC=0, partyD=0, partyE=0, numberOfSeats=0;
	dhondt_method (&partyA, &partyB, &partyC, &partyD, &partyE, numberOfSeats);
	printf("Party A: %d seat(s).\nParty B: %d seat(s).\nParty C: %d seat(s).\nParty D: %d seat(s).\nParty E: %d seat(s).\n\n\n", partyA, partyB, partyC, partyD, partyE);
}


void test_order_2d_points_cc ()
{
	double x1=0.0, y1=0.0, x2=0.0, y2=0.0, x3=0.0, y3=0.0;
	order_2d_points_cc (&x1, &y1, &x2, &y2, &x3, &y3);
	printf("Counter-Clockwise Order: (%f,%f) - (%f,%f) - (%f,%f)\n\n\n", x1, y1, x2, y2, x3, y3);
}


void test_number_encrypt ()
{
	unsigned char number=0;
	number_encrypt (&number);
	printf("Encrypted number: %d\n\n\n", number);
}


/*
** main function for testing the functions...
**
*/
int main(void) {
	test_operate_polynomials ();
	test_four_d_vectors ();
	test_dhondt_method ();
	test_order_2d_points_cc ();
	test_number_encrypt ();
	return (0);
} /* end main */
