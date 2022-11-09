#include <iostream>
#include <vector>
#include <string>
#include "hw4_lib.h"
using namespace std;
using namespace DATES;

namespace DATES{
	/* Constructors of DayofYear class... */
	DayofYearSet::DayofYear::DayofYear(int day_of_year, int month_of_year): day(day_of_year), month(month_of_year){ /* 2 parameter constructor. */
		set_day();
		set_month();
	};
	DayofYearSet::DayofYear::DayofYear(int day_of_year): day(day_of_year), month(1){ /* One parameter constructor. Sets month to 1. */
		set_day();
	};
	DayofYearSet::DayofYear::DayofYear(): day(1), month(1){}; /* No parameter constructor. Sets day and month to 1. */
	/* ----------------------------------------------------------------------- */

	/* Constructors of DayofYearSet class... */
	DayofYearSet::DayofYearSet(){/* Intentionally empty. */};
	DayofYearSet::DayofYearSet(vector <DayofYearSet::DayofYear> all_dates){ /* A constructor for DayofYear vector. */
		for(long unsigned int i = 0; i < all_dates.size(); i++) 
			add(all_dates[i].get_day(), all_dates[i].get_month()); /* Add i. element of vector to days. */
	}
	DayofYearSet::DayofYearSet(DayofYearSet& all_dates){ /* Copy constructor. */
		delete[] days; /* Clears the array. */
		days = new DayofYear[all_dates.size_of_array]; /* Allocs days array. */
		size_of_array = all_dates.size_of_array; /* Sets the size of the array. */
		for(int i = 0; i < size_of_array; i++){
			days[i] = all_dates.days[i]; /* Copies each element of all dates object to days array. */
		}
	}
	/* ----------------------------------------------------------------------- */

	/* Destructors of DayofYearSet class... */
	DayofYearSet::~DayofYearSet(){delete[] days; days = nullptr;}; /* Destructor. Deletes array and assign it to nullptr to avoid dangling. */
	/* ----------------------------------------------------------------------- */

	/* IMPLEMENTATIONS FOR OPERATORS... */

	/* Assingment operator... */
	DayofYearSet& DayofYearSet::operator=(const DayofYearSet& all_dates){
		delete[] days; /* Clears array. */
		days = new DayofYearSet::DayofYear[all_dates.size_of_array]; /* Allocs days array. */
		size_of_array = all_dates.size_of_array; /* Sets the size of the array. */
		for(int i = 0; i < all_dates.size_of_array; i++)
			days[i] = all_dates.days[i]; /* Copies each element of all dates object to days array. */
		return *this; /* Returns this. */
	}

	/* Logic operators... */
	bool operator==(DayofYearSet::DayofYear d1, DayofYearSet::DayofYear d2){ /* Compares two DayofYear objects, if they are equal returns true. */
		bool is_equal = false;
		if(d1.get_month() == d2.get_month() && d1.get_day() == d2.get_day()) /* Compares day and month of the objects. */
			is_equal = true;
		return is_equal;
	}
	bool operator==(DayofYearSet first_set, DayofYearSet second_set){ /* Compates two DayofYearSet objects, if they are equal returns true. */
		bool is_equal;
		if(first_set.get_size() != second_set.get_size()) /* Compares their size, if it is different returns false. */
			is_equal = false;
		else
			is_equal = true;
		for(auto i = 0; i < first_set.get_size() && is_equal == true; i++){ /* If their size equal, compares elements of DayofYearSet objects. */
			is_equal = false;
			for(decltype(i) j = 0; j < second_set.get_size() && is_equal == false; j++){ /* Provides control the equality without caring the order. */
				if(first_set.days[i] == second_set.days[j])
					is_equal = true;
			}
		}
		return is_equal;
	}
	bool operator!=(DayofYearSet first_set, DayofYearSet second_set){ /* Compates two DayofYearSet objects, if they are equal returns true. */
		return !(first_set==second_set); /* Returns negative of equality operator. */
	}
	/* ----------------------------------------------------------------------- */

	/* Output operators... */
	ostream& operator<<(ostream& out, DayofYearSet& all_dates){ /* Prints the DayofYearSet objects. */
		out << "{";
		for(int i = 0; i < all_dates.get_size(); i++){
			out << all_dates.days[i];
			if(i != all_dates.get_size()-1)
				out << ", ";
		}
		out << "}" << endl;
		return out;
	}
	ostream& operator<<(ostream& out, DayofYearSet::DayofYear one_day){ /* Prints the DayofYear objects. */
		out << '(' << one_day.get_day() << ',' <<  one_day.get_month() << ')';
		return out;
	}
	/* ----------------------------------------------------------------------- */

	/* Object operators .*/

	DayofYearSet& operator-(DayofYearSet& first_set, DayofYearSet second_set){ /* Substracts second_set from the first_set and return it. */
		for(int i = 0; i < second_set.get_size(); i++) /* Removes all elements of second_set from the first_set. */
			first_set.remove(second_set.days[i].get_day(), second_set.days[i].get_month());
		return first_set;
	}
	DayofYearSet& operator+(DayofYearSet& first_set, DayofYearSet second_set){ /* Adds the second_set to the first_set and return it. */
		for(int i = 0; i < second_set.get_size();i++) /* Adds all elements of second_set to the first_set. */
			first_set.add(second_set.days[i].get_day(), second_set.days[i].get_month());
		return first_set;
	}

	DayofYearSet& operator^(DayofYearSet& first_set, DayofYearSet second_set){ /* Finds the intersection of the first and the second. */
		DayofYearSet intersection; /* Creates a DayofYearSet object. */
		for(int i = 0; i < first_set.get_size(); i++){
			for(int j = 0; j < second_set.get_size(); j++){	
				if(first_set.days[i] == second_set.days[j])
					intersection.add(first_set.days[i].get_day(), first_set.days[i].get_month()); /* Adds an element to the intersection object, if both first_set and second_set has that element. */
			}
		}
		first_set = intersection; /* Assigns intersection to first_set. */
		return first_set;
	}

	DayofYearSet& operator!(DayofYearSet& first_set){ /* Gets a set as a parameter and substracts it from the DayofYearset object has 365 days. */
		vector<int> days_of_months = {31,28,31,30,31,30,31,31,30,31,30,31};
		DayofYearSet complement_set; /* Creates a DayofYearSet object. */
		for(long unsigned int i = 0; i < days_of_months.size(); i++){
			for(int j = 0; j < days_of_months[i]; j++)
				complement_set.add(j+1,i+1); /* Fills it from the first day of the first month to the last day of the last month. */
		}
		first_set = complement_set - first_set; /* Substracts first_set from the complement_set and assigns it to the first_set. */
		return first_set;
		
	}
	/* ----------------------------------------------------------------------- */

	/* Index operator... */
	DayofYearSet::DayofYear DayofYearSet::operator[](int index) const{
		DayofYear specific_day; /* Creates a DayofYearSet object. */
		if(index < size_of_array && index > 0) /* If index is less than size_of_array, returns the object which has that order. */
		 	specific_day = days[index];
		else{ 
			cout << "There is no element... The program is being terminated." << endl;
			exit(1);
		}
		return specific_day;
	}

	/* ----------------------------------------------------------------------- */

	/* OTHER FUNCTİONS... */

	/* Set Operations... */

	void DayofYearSet::add(int day_of_year, int month_of_year){
		DayofYear new_day(day_of_year, month_of_year); /* Creates a DayofYear object. */

		if(!is_exist(new_day)){ /* If the object does not exist in the days array, continue. */

			DayofYear * new_dates_array; /* Creates a DayofYear object pointer. */
			new_dates_array = new DayofYear[size_of_array+1]; /* Allocs new_dates_array. */

			for(int i = 0; i < size_of_array; i++) /* Copies each element of days array to new_dates_array. */
				new_dates_array[i] = days[i];

			new_dates_array[size_of_array] = new_day; /* Assign new_day to the last element of the new_dates_array. */
			delete[] days; /* Deletes days array. */
			days = new DayofYear[size_of_array+1]; /* Allocs days array. */

			for(int i = 0; i < size_of_array+1; i++) /* Copies each element of new_dates_array to days array. */
				days[i] = new_dates_array[i];

			delete[] new_dates_array; /* Deletes new_dates_array. */

			size_of_array += 1; /* Increases size_of_array variable by one. */
			number_of_elements += 1; /* Increases static variable by one. */
		}
	}
	void DayofYearSet::remove(int day_of_year, int month_of_year){
		int index = -1, j = 0;
		bool is_exist = false;
		DayofYear remove_day(day_of_year, month_of_year); /* Creates a DayofYear object. */

		for(int i = 0; i < size_of_array; i++){ /* Checks every element of days array whether it has that day or not. */
			if(days[i] == remove_day){ /* If it has that day, gets the index of the day. */
				is_exist = true;
				index = i;
			}	
		}
		if(is_exist){ /* If it has that day, continue. */
			DayofYear * new_dates_array; /* Creates a DayofYear object pointer. */
			new_dates_array = new DayofYear[size_of_array-1]; /* Allocs new_dates_array. */
			for(int i = 0; i < size_of_array; i++){
				if(i != index){ /* If i is not index, assigns the day to new_dates_array. */
					new_dates_array[j] = days[i];
					j++;
				}
			}
			delete[] days; /* Deletes days array. */

			days = new DayofYear[size_of_array-1]; /* Allocs days array. */

			for(int i = 0; i < size_of_array-1; i++) /* Copies each element of new_dates_array to days array. */
				days[i] = new_dates_array[i];

			delete[] new_dates_array; /* Deletes new_dates_array. */
			size_of_array -= 1; /* Decreases size_of_array variable by one. */
			number_of_elements -= 1; /* Decreases static variable by one. */
		}
	}

	/* ----------------------------------------------------------------------- */

	/* GETTERS AND SETTERS... */

	/* Getter for DayofYearSet... */
	int DayofYearSet::get_size() const{ /* Gets size of array. */
		return size_of_array;
	}

	/* ----------------------------------------------------------------------- */

	/* Getters for DayofYear... */
	int DayofYearSet::DayofYear::get_day() const{ /* Gets day. */
		return day;
	}
	int DayofYearSet::DayofYear::get_month() const{ /* Gets month. */
		return month;
	}

	/* ----------------------------------------------------------------------- */

	/* Setters for DayofYear... */
	void DayofYearSet::DayofYear::set_day(){ /* Sets day variable of DayofYear objects. */
		vector<int> days_of_months = {31,28,31,30,31,30,31,31,30,31,30,31};
		if(1 > day || day > days_of_months[get_month()-1]){ /* If day is less than one or bigger than upper limit, set it to be 29 October. */
			cerr << "Invalid Day..." << endl << "Date set to 29 october" << endl;
			day = 29;
			month = 10;
		}
	}
	void DayofYearSet::DayofYear::set_month(){ /* Sets month variable of DayofYear objects. */
		if(1 > month || month > 12){ /* If month is less than one or bigger than upper limit, set it to be 29 October. */
			cerr << "Invalid Month..." << endl << "Date set to 29 october" << endl;
			day = 29;
			month = 10;
		}
	}

	/* ----------------------------------------------------------------------- */

	/* Static function... */
	void DayofYearSet::announce(){ /* Announce static variable. */
		cout << "The total number of DayofYear object is: " << number_of_elements << endl;
	}

	/* ----------------------------------------------------------------------- */

	/* Helper function... */

	bool DayofYearSet::is_exist(DayofYearSet::DayofYear one_day) const{ /* Checks the day repeated or not. */
		bool is_repeat = false;

		for(int i = 0; i < size_of_array; i++) /* If days has one_day object, is_reapet is true. */
			if(one_day == days[i])
				is_repeat = true;
		return is_repeat;
	}
	/* ----------------------------------------------------------------------- */
}