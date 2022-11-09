/*
** hw5_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.02.23.55
** 
*/

#include <stdio.h>

#include "hw5_lib.h"

#include <math.h>

/*----------------------------------------------------------------------------------------------------------------------------------*/

void addpolynomials(double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0){ /* Adds polynomials. */

	double x3, x2, x1, x0;

	x3 = *a3 + *b3; /* Coefficient of x^3  */

	x2 = *a2 + *b2; /* Coefficient of x^2  */

	x1 = *a1 + *b1; /* Coefficient of x    */

	x0 = *a0 + *b0; /* The constant number */

	*a3 = x3; /* Assigns coefficient of x^3 to a3 pointer to return  */

	*a2 = x2; /* Assigns coefficient of x^2 to a2 pointer to return  */

	*a1 = x1; /* Assigns coefficient of x  to a1 pointer to return   */

	*a0 = x0; /* Assigns the constant number to a0 pointer to return */
}

void substractpolynomials (double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0){ /* Substracts polynomials. */
	double x3, x2, x1, x0;

	x3 = *a3 - *b3; /* Coefficient of x^3  */

	x2 = *a2 - *b2; /* Coefficient of x^2  */

	x1 = *a1 - *b1; /* Coefficient of x    */

	x0 = *a0 - *b0; /* The constant number */

	*a3 = x3; /* Assigns coefficient of x^3 to a3 pointer to return  */

	*a2 = x2; /* Assigns coefficient of x^2 to a2 pointer to return  */

	*a1 = x1; /* Assigns coefficient of x  to a1 pointer to return   */

	*a0 = x0; /* Assigns the constant number to a0 pointer to return */
}

void multiplypolynomials (double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0){ /* Multiplies polynomials. */
	double x6, x5, x4, x3, x2, x1, x0;

	x6 = (*a3 * *b3); /* Coefficient of x^6  */

	x5 = (*a3 * *b2) + (*a2 * *b3); /* Coefficient of x^5  */

	x4 = (*a3 * *b1) + (*a1 * *b3) + (*a2 * *b2); /* Coefficient of x^4  */

	x3 = (*a3 * *b0) + (*a0 * *b3) + (*a2 * *b1) + (*a1 * *b2); /* Coefficient of x^3  */

	x2 = (*a2 * *b0) + (*a0 * *b2) + (*a1 * *b1); /* Coefficient of x^2  */

	x1 = (*a1 * *b0) + (*a0 * *b1); /* Coefficient of x  */

	x0= (*a0 * *b0); /* The constant number  */

	*a3 = x6; /* Assigns coefficient of x^6 to a3 pointer to return   */

	*a2 = x5; /* Assigns coefficient of x^5 to a2 pointer to return   */

	*a1 = x4; /* Assigns coefficient of x^4 to a1 pointer to return   */

	*a0 = x3; /* Assigns coefficient of x^3 to a0 pointer to return   */

	*b3 = x2; /* Assigns coefficient of x^2 to b3 pointer to return   */

	*b2 = x1; /* Assigns coefficient of x^1 to b2 pointer to return   */

	*b1 = x0; /* Assigns the constant number to b1 pointer to return  */
}

void operate_polynomials  (double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0, char op){
	if(op=='+') addpolynomials(a3, a2, a1, a0, b3, b2, b1, b0); /* If operator is plus operator, calls addpolynomials function. */

	else if(op=='-') substractpolynomials (a3, a2, a1, a0, b3, b2, b1, b0); /* If operator is minus operator, calls substractpolynomials function. */

	else if(op=='*') multiplypolynomials (a3, a2, a1, a0, b3, b2, b1, b0); /* If operator is multiply opeator, calls multiplypolynomials function. */
}

/*----------------------------------------------------------------------------------------------------------------------------------*/

void gets_vector(double * x, double * y, double * z, double * w, int * cursor){ /* Gets inputs from the user until correct input is entered. */
	int logicvalue=0; 

	while(logicvalue!=4){

		printf("Enter the vector (a b c d): ");

		logicvalue=scanf("%lf %lf %lf %lf",x,y,z,w);

	}
	if((*x)!=-1 && (*y)!=-1 && (*z)!=-1 && (*w)!=-1) (*cursor)+=1; /* Increases the cursor by one. */
}

void increase_mean(double x , double y, double z, double w, double* sum_a0, double* sum_a1, double* sum_a2, double* sum_a3){
	if(x!=-1 && y!=-1 && z!=-1 && w!=-1){
		(*sum_a0) += x;
		(*sum_a1) += y;
		(*sum_a2) += z;
		(*sum_a3) += w;
	}
}

void four_d_vectors (double* mean_a0, double* mean_a1, double* mean_a2, double* mean_a3, double* longest_distance, int N){

	double x1,y1,z1,w1;

	double x2,y2,z2,w2;

	double euclidian_distance;

	double sum_a0,sum_a1,sum_a2,sum_a3;

	int cursor=0;

	*longest_distance=0;
	
	printf("Enter the number of vectors:");
	
	scanf("%d",&N);
	
	if(N>0)	gets_vector(&x1, &y1, &z1, &w1, &cursor); /* If N is greater than 0, continue. */

	increase_mean(x1 , y1, z1, w1, &sum_a0, &sum_a1, &sum_a2, &sum_a3); /* Increases mean. */

	if(x1!=-1 && y1!=-1 && z1!=-1 && w1!=-1){ /* If first vector does not equal to exit vector, continue. */

		while(1){
			if(cursor>=N) break; /* If N times vectors are taken, break the loop. */
			
			gets_vector(&x2, &y2, &z2, &w2, &cursor); /* Gets new vector. */

			increase_mean(x2 , y2, z2, w2, &sum_a0, &sum_a1, &sum_a2, &sum_a3); /* Increases mean. */

			if(x2==-1 && y2==-1 && z2==-1 && w2==-1) break; /* If vector equals to exit vector, break. */

			distance_between_4d_points(x2-x1,y2-y1,z2-z1,w2-w1,&euclidian_distance); /* Finds distance between points. */

			if((euclidian_distance) > (*longest_distance)) *longest_distance = euclidian_distance; /* If the distance is biggest than longest distance, assign it to longest distance. */

			if(cursor>=N) break; /* If N times vectors are taken, break the loop. */

			gets_vector(&x1, &y1, &z1, &w1, &cursor); /* Gets new vector. */
			
			if(x1==-1 && y1==-1 && z1==-1 && w1==-1) break; /* If vector equals to exit vector, break. */ 

			increase_mean(x1 , y1, z1, w1, &sum_a0, &sum_a1, &sum_a2, &sum_a3); /* Increases mean. */

			distance_between_4d_points(x2-x1,y2-y1,z2-z1,w2-w1,&euclidian_distance); /* Finds distance between points. */

			if((euclidian_distance) > (*longest_distance)) *longest_distance = euclidian_distance; /* If the distance is biggest than longest distance, assign it to longest distance. */
		}

	}
	/* This blocks divides sum to cursor to find mean. */

	if(cursor>0){
	
		*mean_a0=sum_a0/cursor;
	
		*mean_a1=sum_a1/cursor;
	
		*mean_a2=sum_a2/cursor;
	
		*mean_a3=sum_a3/cursor;
		}
}

void distance_between_4d_points (double d0, double d1, double d2, double d3, double* euclidian_distance)
{
	/* Euclidian distance equals square root of sum of the square of the points distance sqrt((x2-x1)^2+(y2-y1)^2+(z2-z1)^2+(w2-w1)^2) */
	
   	*euclidian_distance=pow(d0,2)+pow(d1,2)+pow(d2,2)+pow(d3,2); 

   	*euclidian_distance= sqrt(*euclidian_distance);
}

/*----------------------------------------------------------------------------------------------------------------------------------*/

int whichGreater(int x1, int x2){ /* Gets two variable and returns the greatest one. */
	if(x1>=x2) return x1;

	else return x2;
}

void dhondt_method (int* partyA, int* partyB, int* partyC, int* partyD, int* partyE, int numberOfSeats)
{
	int max1,max2,max3,MAX;

	int divisorA=1,divisorB=1,divisorC=1,divisorD=1,divisorE=1;

	int seatA=0, seatB=0, seatC=0, seatD=0, seatE=0;

	int tempA,tempB,tempC,tempD,tempE;

	while(1){

		if(seatA+seatB+seatC+seatD+seatE==numberOfSeats){ /* If all seats are full, election ends. */
			break;
		}

		tempA=(*partyA)/divisorA;

		tempB=(*partyB)/divisorB;

		tempC=(*partyC)/divisorC;

		tempD=(*partyD)/divisorD;

		tempE=(*partyE)/divisorE;

		/*--------This blocks find the highest votes------------*/

		max1=whichGreater(tempA,tempB);

		max2=whichGreater(tempC,tempD);

		max3=whichGreater(max1,max2);

		MAX=whichGreater(max3,tempE);

		if(MAX==tempA){ /* If partyA has highest votes, increases number of seats of A by one. */
			seatA+=1;
			divisorA++;
		}

		else if(MAX==tempB){ /* If partyB has highest votes, increases number of seats of B by one. */
			seatB+=1;
			divisorB++;
		}

		else if(MAX==tempC){ /* If partyC has highest votes, increases number of seats of C by one. */
			seatC+=1;
			divisorC++;
		}

		else if(MAX==tempD){ /* If partyD has highest votes, increases number of seats of D by one. */
			seatD+=1;
			divisorD++;
		}

		else if(MAX==tempE){ /* If partyE has highest votes, increases number of seats of E by one. */
			seatE+=1;
			divisorE++;
		}
		
	}	
	*partyA=seatA; /* Assigns seatA to partyA to return. */

	*partyB=seatB; /* Assigns seatB to partyB to return. */

	*partyC=seatC; /* Assigns seatC to partyC to return. */

	*partyD=seatD; /* Assigns seatD to partyD to return. */

	*partyE=seatE; /* Assigns seatE to partyE to return. */
}

/*----------------------------------------------------------------------------------------------------------------------------------*/

double find_quadrants(double x1, double y1){ /* This function finds quadrant of point in cartesian coordinate system. */

	double quadrant=0.0;

	if(y1>0){

		if(x1>0) quadrant=1;

		else if(x1<0) quadrant=2;

		else quadrant=1.5; /* If the point on the positive y-axis quadrant will be 1.5 */
	}

	else if(y1<0){

		if(x1>0) quadrant=4;

		else if(x1<0) quadrant=3;
		
		else quadrant=3.5; /* If the point on the negative y-axis, quadrant will be 3.5 */
	}

	else{
		if(x1>0) quadrant=0.5; /* If the point on the positive x-axis, quadrant will be 0.5 */

		else if(x1<0) quadrant=2.5; /* If the point on the negative x-axis, quadrant will be 2.5 */
	}

	return quadrant;
}

void swap(double * x1, double *y1, double * x2, double * y2, double * p1, double * p2){ /* This function swaps the points order. */
		double tempx,tempy;

		tempx = *x1; /* Keeps x1's value. */

		tempy = *y1; /* Keeps y1's value. */

		*x1 = *x2; 

		*y1 = *y2;

		*x2 = tempx;

		*y2 = tempy;

		*p1=find_quadrants(*x1, *y1); /* Finds quadrants of new points. */

		*p2=find_quadrants(*x2, *y2); /* Finds quadrants of new points. */
}

void check_first(double * x1, double *y1, double * x2, double * y2, double *p1, double *p2){
	
	if((*p1) > (*p2)) swap(x1,y1,x2,y2,p1,p2); /* If quadrants of point 1 is greater than quadrants of point 2, swaps their order. */
	
	
	else if((*p1) == (*p2)){ /* If quadrants of point equals, continue. */

		if(*p1==1 || *p1==4 || *p1==2 || *p1==3){ /* If the points are in one of the quadrant, continue. */
			
			if((*y1)/(*x1) > (*y2)/(*x2)) swap(x1,y1,x2,y2,p1,p2); /* If point1 has greatest y/x rate, swaps their order. */
		}
		
		else if(*p1==0.5 || *p1==2.5){ /* If the points are in 0.5th or 2.5th quadrant, continue. */

			if((*x2) > (*x1)) swap(x1,y1,x2,y2,p1,p2); /* In 0.5th and 2.5th quadrant, if point2 has greatest x component, swaps their order. */ 
		}

		else if(*p1=1.5 || *p1==3.5){ /* If the points are in 1.5th or 3.5th quadrant, continue. */

			if((*y1) > (*y2)) swap(x1,y1,x2,y2,p1,p2); /* In 1.5th and 3.5th quadrant, if point1 has greatest x component, swaps their order. */ 
		}

		if((*y1) == (*y2)){ /* If the points have same y components, continue */

			if((*p1)==1 || (*p1)==2){ /* If the points are in first or second quadrant, continue. */

				if((*x1) < (*x2)) swap(x1,y1,x2,y2,p1,p2); /* In first and second quadrant, if point2 has greatest x component, swaps their order. */
			}

			else if((*p1)==3 || (*p1)==4){ /* If the points are in third or fourth quadrant, continue. */

				if((*x1) > (*x2)) swap(x1,y1,x2,y2,p1,p2); /* In third and fourth quadrant, if point1 has greatest x component, swaps their order. */
				
			}
		}
	}

}

void order_2d_points_cc (double* x1, double* y1, double* x2, double* y2, double* x3, double* y3){

	double p1,p2,p3;

	/* This blocks finds quadrants of points */

	p1=find_quadrants(*x1,*y1); 

	p2=find_quadrants(*x2,*y2);

	p3=find_quadrants(*x3,*y3);

	/* This blocks orders the points */
	
	check_first(x1,y1,x2,y2,&p1,&p2);

	check_first(x2,y2,x3,y3,&p2,&p3);

	check_first(x1,y1,x2,y2,&p1,&p2);
	
}

/*----------------------------------------------------------------------------------------------------------------------------------*/

void divide(int * number,int * divisor, char * a){ /* Converts the decimal number to binary number. */
	if((*number)/(*divisor)>=1){ /* If the number is greater than divisor, char a will be '1' */

		(*a)=49;

		(*number)-=*divisor; /* Substracts divisor from the number. */

	}
	else (*a)=48; /* If the number is less than divisor, char a will be '0' */
	
	(*divisor)/=2;
}

void multiply(int * number, int * multiplier, char  a){ /* Converts the binary number to decimal number. */

	if(a==49) (*number)+=(*multiplier);

	(*multiplier)*=2;

}

void number_encrypt (unsigned char* number){
	
	char b7='-', b6='-', b5='-', b4='-', b3='-', b2='-', b1='-', b0='-';

	get_number_components (*number, &b7, &b6, &b5, &b4, &b3, &b2, &b1, &b0);

	reconstruct_components (number, b7, b6, b5, b4, b3, b2, b1, b0);
}

void get_number_components (unsigned char number, char* b7, char* b6, char* b5, char* b4, char* b3, char* b2, char* b1, char* b0){	
	int input, divisor=128;

	input=(int)(number);

	/* This blocks converts decimal number to binary. */

	divide(&input, &divisor, b7);

	divide(&input, &divisor, b6);

	divide(&input, &divisor, b5);

	divide(&input, &divisor, b4);

	divide(&input, &divisor, b3);

	divide(&input, &divisor, b2);

	divide(&input, &divisor, b1);

	divide(&input, &divisor, b0);
}

void reconstruct_components (unsigned char* number, char b7, char b6, char b5, char b4, char b3, char b2, char b1, char b0){
	int input=0,multiplier=1;

	/* This blocks converts binary number to decimal. */

	multiply(&input, &multiplier, b3);

	multiply(&input, &multiplier, b2);

	multiply(&input, &multiplier, b5);

	multiply(&input, &multiplier, b4);

	multiply(&input, &multiplier, b7);

	multiply(&input, &multiplier, b6);

	multiply(&input, &multiplier, b1);

	multiply(&input, &multiplier, b0);

	*number=(unsigned char)input;

}
