/*
** hw5_lib.h:
**
** The header file declaring library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.02.23.55
** 
*/


void operate_polynomials  (double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0, char op);


void four_d_vectors (double* mean_a0, double* mean_a1, double* mean_a2, double* mean_a3, double* longest_distance, int N);


void distance_between_4d_points (double d0, double d1, double d2, double d3, double* euclidian_distance);


void dhondt_method (int* partyA, int* partyB, int* partyC, int* partyD, int* partyE, int numberOfSeats);


void order_2d_points_cc (double* x1, double* y1, double* x2, double* y2, double* x3, double* y3);


void number_encrypt (unsigned char* number);


void get_number_components (unsigned char number, char* b7, char* b6, char* b5, char* b4, char* b3, char* b2, char* b1, char* b0);


void reconstruct_components (unsigned char* number, char b7, char b6, char b5, char b4, char b3, char b2, char b1, char b0);

void addpolynomials(double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0);

void substractpolynomials (double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0);

void multiplypolynomials (double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0);

void gets_vector(double * x, double * y, double * z, double * w, int * cursor);

void increase_mean(double x , double y, double z, double w, double* sum_a0, double* sum_a1, double* sum_a2, double* sum_a3);

int whichGreater(int x1, int x2);

double find_quadrants(double x1, double y1);

void swap(double * x1, double *y1, double * x2, double * y2, double * p1, double * p2);

void check_first(double * x1, double *y1, double * x2, double * y2, double *p1, double *p2);

void divide(int * number,int * divisor, char * a);

void multiply(int * number, int * multiplier, char  a);
