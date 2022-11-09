/*
** hw2_lib.c:
**
** The source file implementing library functions.
**
*/

#include <stdio.h>
#include <math.h>
#include "hw2_lib.h"


int find_weekday_of_data(int day, int month, int year)
{	
	int daysofmonths[]={31,28,31,30,31,30,31,31,30,31,30,31};
	
    	/* (Year Code + Month Code + Century Code + Date Number -Leap Year Code)mod 7 */
    	int MonthCodes[]={0,3,3,6,1,4,6,2,5,0,3,5};
    	
    	int CenturyCodes[]={6,4,2,0};
    	
    	int YearCode=((year%100)+(year%100)/4)%7;
    	
    	int DateNumber=day;
    	
    	int indexofcentury=(year/100)%4;
    	
    	int LeapCode;
    	
    	int NameofDay;
    	
    	if((year%4==0 && year%100!=0) || year%400==0){
    		daysofmonths[1]=29; /* The days of February */
    		
    		if(month<=2){
			LeapCode=1; /* Leap year code checker */
			}
		}
	else{
		LeapCode=0;
		}
		
	NameofDay=(YearCode+MonthCodes[month-1]+CenturyCodes[indexofcentury]+DateNumber-LeapCode)%7;
	
	if(NameofDay==0){
		NameofDay+=7;
		}
		
	if(year<=0 || month>12 || month<=0 || day<=0 || day>daysofmonths[month-1]){ /* If there is no day, print error */
		printf("ERROR! The date is not real.");
		return -1111;
		}
		
	else{
    		return NameofDay;
    		}
  
}

int count_day_between_dates(int start_day, int start_month, int start_year, int end_day, int end_month, int end_year)
{
    int monthdiff=0, yeardiff, daydiff, leapyearfirst, leapyearlast, leapyeardiff, sumofdifference, i, j;
    
    int daysofmonths[]={31,28,31,30,31,30,31,31,30,31,30,31}; /* The days of the months of start date */
    
    int daysofmonths2[]={31,28,31,30,31,30,31,31,30,31,30,31}; /* The days of the months of end date */
    
    leapyearfirst=(start_year/4) + (start_year/400) - (start_year/100); /* The number of leap years in first date. */
    
    leapyearlast=(end_year/4) + (end_year/400) - (end_year/100); /* The number of leap years in last date */
    
    leapyeardiff=(leapyearlast * 366) - (leapyearfirst * 366); /* The number of days in leap years. */ 
    
    yeardiff=((end_year -leapyearlast) * 365) - ((start_year - leapyearfirst) * 365); /* The number of days in non-leap years. */
    
    daydiff=end_day - start_day; 
    
    for(i=1;i<end_month;i++){ /* Days of months for last date */
    	monthdiff+=daysofmonths[i-1];
    	}
    for(j=1;j<start_month;j++){ /* Days of months for first date */
    	monthdiff-=daysofmonths[j-1];
    	}
    
    sumofdifference=yeardiff+monthdiff+daydiff+leapyeardiff; /* Sum of number of days in between two dates */
    
    if(start_month<2 || (start_month==2 && start_day<=28)){
    
    	if((start_year%4 == 0 && start_year%100!=0) || start_year%400==0){
    	
    		sumofdifference+=1; /* Adds 1 days (29 February) to sumofdifference if start_month less than 2 and start_year is a leap year */
    		}
    		
    	}
    	
    if(end_month<2 || (start_month==2 && start_day<=28)){
    
   	if((end_year%4 == 0 && end_year%100!=0) || end_year%400==0){

    		sumofdifference-=1; /* Substracts 1 days (29 February) from sumofdifference if end_month less than 2 and end_year is a leap year */
    		}
    		
    	}
    	
    if((start_year%4==0 && start_year%100!=0) || start_year%400==0){
    		daysofmonths[1]=29; /* The days of February */
    		}
    if((end_year%4==0 && end_year%100!=0) || end_year%400==0){
    		daysofmonths2[1]=29; /* The days of February */
    		}
    	
    		
    if(start_year<=0 || end_year<=0|| start_month>12 || end_month>12 || start_month<=0 || end_month<=0 || start_day<=0  || end_day<=0){ /* Checks dates */
		printf("ERROR! The date is not real.");
		return -1111;
		}
    else if(start_day>daysofmonths[start_month-1]){ /* Check dates */
    		printf("ERROR! The date is not real.");
		return -1111;
		}
    else if(end_day>daysofmonths2[end_month-1]){ /* Check dates */
    		printf("ERROR! The date is not real.");
		return -1111;
		}
    else{
    		return sumofdifference;
    		}
    
}


double find_angle(double a, double b, double c)
{
    double Vb,Vc,cosA,angleA;
    
    Vb=sqrt((a * a + c * c - (b * b) / 2) / 2); /* Median b = square root of (a^2 + c^2 - (b^2)/2) */
    
    Vc=sqrt((a * a + b * b - (c * c) / 2) / 2); /* Median c = square root of (a^2 + b^2 - (c^2)/2) */
    
    Vb/=(double)3/2; /* The long part of median b */
    
    Vc/=(double)3/2;  /* The long part of median c */
   
    
    cosA=((Vb * Vb) + (Vc * Vc) - (a * a)) / (2* Vb * Vc); /* (Edge1)^2+(Edge2)^2-(Edge3)^2 = 2* (Edge1) * (Edge2) * (cosA) */ 
    
    angleA=acos(cosA); /* Takes inverse of cosA. */
    
    return angleA;
}

void helpertabulated(char border, int repetitions){ /* Helper function to print borders. */
    while (repetitions>0){
    	printf("%c",border);
    	repetitions--;
    	}
    }
void doublechecker(double r){ /* Helper function to get rid of tralling zeros */
	int rprime=((int)(r*100));
	if((rprime)%10>=1){
    		printf("|%.2f\t\t\t",r);
    		}
    	else if((rprime%100)==0){
    		printf("|%.0f\t\t\t",r);
    		}
    	else if((rprime)%10==0){
    		printf("|%.1f\t\t\t",r);
    		}
}
void positivechecker(int r){ /* Helper function to print '+' sign if the number is positive */
	if(r>0){
		printf("|+%d\t\t\t|\n  ",r); 
		}
	else{
		printf("|%d\t\t\t|\n  ",r);
		} 
	}
    	


void print_tabulated(unsigned int r11, double r12, int r13, 
                     unsigned int r21, double r22, int r23, 
                     unsigned int r31, double r32, int r33, char border)
{
    
    printf("  ┌"); /* Corner character */
    
    helpertabulated(border,77); /* Print first border */
    
    printf("┐\n"); /* Corner character */
    
    printf("  |           Row 101           |      Row ABCDEFG      |      Row XYZ123       |\n  ");
    
    helpertabulated(border,79);/* Print second border */
    
    printf("\n  |\t\t%u\t\t",r11);
    
    doublechecker(r12);

    positivechecker(r13);
    
    helpertabulated(border,79); /* Print third border */
    
    printf("\n  |\t\t%u\t\t",r21);
    
    doublechecker(r22);
    
    positivechecker(r23);
    
    helpertabulated(border,79); /* Print last border */
    
    printf("\n  |\t\t%u\t\t",r31);
    
    doublechecker(r32);
    
    positivechecker(r33);
    
    printf("└"); /* Corner character */
    
    helpertabulated(border,77);
    
    printf("┘\n"); /* Corner character */
}

