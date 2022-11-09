/*
** hw1_io.c:
**
** The source file implementing output functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.03.03.20.16
** 
*/


                                           /*     I wrote that code by taking a0 as the coefficient of     */
                                          /*        the term with the highest degree of a polynomial.     */
                                          

#include <stdio.h>

#include "hw1_io.h"

void helperfunction(double x, int power, int degree){
	if(x>0){
		if(power!=degree){ 
			printf("+"); /* if power of x is not the highest degree of polynomial, print "+". */
			}
		if(x!=1 || power==0){
			printf("%.2f",x); /* if x does not equal to 1 or power equals to zero print x. */
			}
		if(power>1){
			printf("x^%d",power); /* if power is greater than 1 print power. */
			}
		else if(power==1){ 
			printf("x"); /*  if power equals to 1, just print x. */
			}
		}
	else if(x<0){
		if(x!=-1 || power==0){
			printf("%.2f",x); /* if x doesn't equal to -1 or power equals to 0 print x. */
			}
		else{
			printf("-"); /* if x equals to 1 or power doesn't equal to 0 print '-'. */
			}
			

		if(power>1){
			printf("x^%d",power); /* if power is greater than 1 print power. */
			}
		else if(power==1){
			printf("x"); /* if power equals to 1, just print x. */
			}
			
		}
}
	
void write_polynomial3(double a0, double a1, double a2, double a3)
{	
    	helperfunction(a0,3,3);
    	
    	helperfunction(a1,2,3);
    	
    	helperfunction(a2,1,3);
    	
    	helperfunction(a3,0,3);
    	
    	printf("\n");
}
void write_polynomial4(double a0, double a1, double a2, double a3, double a4)
{
    	helperfunction(a0,4,4);
    	
 	helperfunction(a1,3,4);
    	
    	helperfunction(a2,2,4);
    	
    	helperfunction(a3,1,4);
    	
    	helperfunction(a4,0,4);
    	
    	printf("\n");
}
