/*
** hw4_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.03.03.20.16
** 
*/


                                           /*     I wrote that code by taking a0 as the coefficient of    */
                                          /*       the term with the highest degree of a polynomial.     */
                                          
                                          
#include <stdio.h>

#include "hw1_lib.h"

double integral3(double a0, double a1, double a2, double a3, double xs, double xe, double delta)
{
    /* The method of calculating integral is: (delta/2) * [P(xs)+2P(xs+delta)+2P(xs+2delta)+........+P(xe)] */
    
    double sum=0.0;
    
    int subintervals=(xe-xs)/delta;
    
    int i;
    
    for(i=0;i<=subintervals;i++){
    
    	double polynomial_xs=(a0*xs*xs*xs)+(a1*xs*xs)+(a2*xs)+a3;
    	
    	if(0<i && i<subintervals){ 
    	
    		polynomial_xs*=2; /* According to formula, multiplying polynomial by 2 for it is not first or last interval. */
    		
    		}
    		
   	xs+=delta;
   	
    	sum+=polynomial_xs;
        
    	}
    	
    sum*=delta/2; /* According to formula, multiplying sum of the polynomials by half of the delta. */
    
    return sum;
}


double integral4(double a0, double a1, double a2, double a3, double a4, double xs, double xe, double delta)
{
    /* The method of calculating integral is: (delta/2) * [P(xs)+2P(xs+delta)+2P(xs+2delta)+........+P(xe)] */
    
    double sum=0.0;
    
    int subintervals=(xe-xs)/delta;
    
    int i;
    
    for(i=0;i<=subintervals;i++){
    
    	double polynomial_xs=(a0*xs*xs*xs*xs)+(a1*xs*xs*xs)+(a2*xs*xs)+(a3*xs)+a4;
    	
    	if(0<i && i<subintervals){ 
    	
    		polynomial_xs*=2; /* According to formula, multiplies polynomial by 2 if it is not first or last interval. */
    		
    		}
   	xs+=delta;
   	
    	sum+=polynomial_xs;
        
    	}
    	
    sum*=delta/2; /* According to formula, multiplying sum of the polynomials by half of the delta. */
    
    return sum;
}


double root3(double a0, double a1, double a2, double a3, double xs, double xe)
{
    /* The method of calculating root of polynomial is taking the number which makes polynomial's result most close to zero as root. */
	
    double root,result;
    
    double min=100.0;
    
    while(xs<=xe){ /* This loop calculate the result of the polynomial by increasing variable 0.001 from lowerbound(xs) to upperbound(xe) */
    
    	result=a0*xs*xs*xs+a1*xs*xs+a2*xs+a3;
    	
    	if(result<0){ /* This takes absolute value of results. */
    	
    		result*=-1;
    		}
    		
    		
    	if(result<min){  /* This blocks compares to absolute values of results of polynomials and which one is close to zero, takes the variable of that polynomial as root */
    	
    		min=result;
    		
    		root=xs;
    		}
    		
    		
    	xs+=0.001;
    	}
    	
	return root;
}


double root4(double a0, double a1, double a2, double a3, double a4, double xs, double xe)
{
    /* The method of calculating root of polynomial is taking the number which makes polynomial's result most close to zero as root. */
	
    double root,result;
    
    double min=100.0;
    
    while(xs<=xe){ /* This loop calculate the result of the polynomial by increasing variable 0.001 from lowerbound(xs) to upperbound(xe) */
    
    	result=a0*xs*xs*xs*xs+a1*xs*xs*xs+a2*xs*xs+a3*xs+a4;
    	
    	if(result<0){ /* This takes absolute value of results. */
    	
    		result*=-1;
    		}
    		
    		
    	if(result<min){  /* This blocks compares to absolute values of results of polynomials and which one is close to zero, takes the variable of that polynomial as root */
    	
    		min=result;
    		
    		root=xs;
    		}
    		
    		
    	xs+=0.001;
    	}
    	
	return root;
}
