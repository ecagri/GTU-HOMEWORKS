#include <iostream>
#include <vector>
#include "hw4_lib.h"
using namespace std;
using namespace DATES; 
/* CONSTRUCTORS. */
void test_constructors(){
	cout << "\nTEST CONSTURCTOR FUNCTION IS WORKING\n";
	int month, day;
	cout << "Enter day and month(like 3 5): ";
	cin >> day >> month;
	DayofYearSet::DayofYear temp(day, month); /* Calls object with two parameter. */
	cout << "Enter day:";
	cin >> day;
	DayofYearSet::DayofYear temp2(day); /* Calls object with one parameter. */
	DayofYearSet::DayofYear temp3; /* Calls object with no parameter. */
	cout << "2 parameter constructor: " << temp << "\n1 parameter constructor: " << temp2 << "\nNo parameter constructor: " << temp3 << endl;
}
void test_constructors_2(DayofYearSet& s1, DayofYearSet& s2, DayofYearSet& s3){
	cout << "\nTEST CONSTURCTOR2 FUNCTION IS WORKING\n";
	vector<DayofYearSet::DayofYear> vector_of_days;
	for(int i = 0; i < 12; i++){ /* Creates a vector of DayofYear objects, and fill it. */
		DayofYearSet::DayofYear temp(i+1, i+1);
		vector_of_days.push_back(temp);
	}
	DayofYearSet vector_parameter(vector_of_days); /* Calls object with vector parameter. */

	DayofYearSet reference_object; 
	reference_object.add(1, 1); /* Fills reference_object. */
	reference_object.add(23, 4); /* Fills reference_object. */
	DayofYearSet reference_parameter(reference_object); /* Calls object with reference of object parameter. */

	DayofYearSet no_parameter_object; /* Calls object with no parameter. */
	no_parameter_object.add(30, 8); /* Fills no_parameter_object. */

	cout << "Vector parameter constructor: \n" << vector_parameter << endl; 
	cout << "Reference parameter constructor: \n" << reference_parameter << endl;
	cout <<  "No parameter constructor: \n" << no_parameter_object << endl;
	s1 = vector_parameter; /* Assigns vector_parameter object to s1. */
	s2 = reference_parameter; /* Assigns reference_parameter object to s1. */
	s3 = no_parameter_object; /* Assigns no_parameter_object to s1. */
}
/* ----------------------------------------------------------------------- */

/* LOGİC OPERATORS. */
void test_de_morgan(DayofYearSet s1, DayofYearSet s2){
	cout << "\nDE MORGAN FUNCTION IS WORKING\n";
	DayofYearSet s3, s4; /* Creates temp objects. */
	s3 = s1; /* Assigns s3 to s1. */
	s4 = s2; /* Assigns s4 to s2. */
	if((!(s1 + s2)) == ((!s3) ^ (!s4))) /* Applies the De Morgan Rule. */
		cout << "They are equal.\n\n";
	else
		cerr << "ERROR\n\n";
}
void test_logic_operators(DayofYearSet& s1, DayofYearSet& s2, DayofYearSet& s3){ /* Test equality operators. */
	cout << "\nTEST LOGİC OPERATORS FUNCTION IS WORKING\n";
	cout << "s1 != s2: "<< (s1 != s2) << endl;
	cout << "s1 != s3: "<< (s1 != s3) << endl;
	cout << "s1 == s2: "<< (s1 == s2) << endl;
	cout << "s1 == s3: "<< (s1 == s3) << endl;
}
void test_intersection(DayofYearSet s1, DayofYearSet s2){
	cout << "\nTEST INTERSECTION FUNCTION IS WORKING\n";
	cout << "\nThe intersection of them: \n" << (s1^s2);
}
void test_complement(DayofYearSet s1){
	cout << "\nTEST COMPLEMENT FUNCTION IS WORKİNG\n";
	cout << "\nThe complement set of it: \n" << (!s1);
}
/* ----------------------------------------------------------------------- */

/* TEST OBJECTS OPERATIONS. */
void test_plus_operator(DayofYearSet s1, DayofYearSet s2){
	cout << "\nTEST PLUS OPERATORS FUNCTION IS WORKING\n";
	cout << "\nThe sum of them: \n" << (s1+s2);
}
void test_minus_operator(DayofYearSet s1, DayofYearSet s2){
	cout << "\nTEST MINUS OPERATORS FUNCTION IS WORKING\n";
	cout << "\nThe difference of them: \n" << (s1-s2);
}
void test_index_operator(DayofYearSet s1){ /* Gets an index and prints the object in that index. */
	cout << "\nTEST INDEX OPERATORS FUNCTION IS WORKING\n";
	int index;
	cout << "Enter the index less than " << s1.get_size() << ": ";
	cin >> index;
	cout << s1[index-1];
}
void test_assign_operator(DayofYearSet s1){ /* Assigns an objects to another one. */
	cout << "\nTEST ASSİGNMENT OPERATORS FUNCTION IS WORKING\n";
	DayofYearSet new_version;
	new_version.add(15,9);
	new_version.add(3,12);
	cout << "Old version of s1: \n" << s1 << endl;
	s1 = new_version;
	cout << "New version of s1: \n" << s1 << endl;;
}
/* ----------------------------------------------------------------------- */

/* TEST SET OPERATIONS. */
void test_add_func(DayofYearSet s1){ /* Gets a DayofYearSet object and adds a day to it. */
	cout << "\nTEST ADD FUNCTION IS WORKING\n";
	s1.add(21,10);
	cout << "The new version of it is: \n" << s1 << endl;
}
void test_remove_func(DayofYearSet s1){ /* Gets a DayofYearSet object and removes a day from it. */
	cout << "\nTEST REMOVE FUNCTION IS WORKING\n";
	s1.remove(1,1);
	cout << "The new version of it is: \n" << s1 << endl;
}
void test_size_func(DayofYearSet s1){ 
	cout << "\nTEST SIZE FUNCTION IS WORKING\n";
	cout << "Size of it is: " << s1.get_size() << endl;
}
/* ----------------------------------------------------------------------- */

void test_static_func(){ /* Adds some days to sets, and prints the total number of alive objects. */
	cout << "\nTEST STATİC FUNCTION IS WORKING\n";
	DayofYearSet s1, s2;
	s1.add(30,8);
	cout << "An object is added to set\n";
	s1.add(19,5);
	cout << "An object is added to set\n";
	s1.add(23,4);
	cout << "An object is added to set\n";
	s2.add(19,5);
	cout << "An object is added to set\n";
	s2.add(30,8);
	cout << "An object is added to set\n";
	s1.announce();
	s2.remove(30,8);
	cout << "An object is removed to set\n";
	s1.announce();
}
int DayofYearSet::number_of_elements = 0; /* Sets the static variable to 0. */
int main(){
	test_static_func();
	DayofYearSet s1, s2, s3;
	test_constructors();
	test_constructors_2(s1, s2 ,s3);
	test_size_func(s1);
	test_logic_operators(s1, s2, s3);
	test_complement(s1);
	test_add_func(s1);
	test_de_morgan(s1, s2);
	test_assign_operator(s1);
	test_index_operator(s1);
	test_plus_operator(s1, s2);
	test_minus_operator(s1, s2);
	test_intersection(s1, s2);
}
	