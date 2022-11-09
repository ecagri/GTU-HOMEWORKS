#include <iostream>
#include <algorithm>
#include <memory>
#include "gtuset.cpp"
#include "gtuvector.cpp"
#include "gtuarray.cpp"
using namespace std;
using namespace cayci_hw6;

namespace{
	void test_set(){
		/*********** CONSTRUCTORS AND ASSIGNMENT OPERATOR TEST ***********/
		GTUSet<int> set1, set2 = {1, 2, 3, 4}, set3(set2);
		cout <<"\nset1 = ";
		set1.print();
		cout << "set2 = ";
		set2.print();
		cout << "set3 = ";
		set3.print();
		cout << "moving set2 to set4...";
		GTUSet<int> set4(move(set2));
		cout << "\nset2 = ";
		set2.print();
		cout << "set4 = ";
		set4.print();
		cout << "Assigned set4 to set5...";
		GTUSet<int> set5 = set4;
		cout << "\nset5 = ";
		set5.print();
		cout << "set4 = ";
		set4.print();
		cout << "Move assigned set4 to set6...";
		GTUSet<int> set6 = move(set4);
		cout << "\nset6 = ";
		set6.print();
		cout << "set4 = ";
		set4.print();
		/*********** MODIFIERS TEST. ***********/
		/* Add function */
		cout << "Add 5 to set5...";
		set5.add(5);
		cout << "\nset5 = ";
		set5.print();
		/* Erase function */
		cout << "Erase second element of set5...";
		set5.erase(set5.begin()+1);
		cout << "\nset5 = ";
		set5.print();
		/* Clear function */
		cout << "Clear set5...";
		set5.clear();
		cout << "\nset5 = ";
		set5.print();
		/* Search function. */
		cout << "Search 5 in set3...";
		cout << "\nset3 = ";
		set3.print();
		if(set3.search(5) == true){
			cout << "The element is found.\n";
		}
		else{
			cout << "The element couldn't found.\n";
		}
		cout << "Search 2 in set3...";
		cout << "\nset3 = ";
		set3.print();
		if(set3.search(2) == true){
			cout << "The element is found.\n";
		}
		else{
			cout << "The element couldn't found.\n";
		}
		/********** SET OPERATIONS **********/
		GTUSet<char> first_set = {'a', 'b', 'c'}, second_set = {'c', 'd', 'e', 'f'};
		cout <<"\nfirst_set = ";
		first_set.print();
		cout << "second_set = ";
		second_set.print();
		/* Union function */
		cout << "Union of two set = ";
		GTUSet<char> unionoftwo = unionSet(first_set, second_set);
		unionoftwo.print();
		/* Intersection function */
		cout << "Intersection of two set: ";
		GTUSet<char> intersectoftwo = intersectSet(first_set, second_set);
		intersectoftwo.print();
		/********** CAPACITY TEST **********/
		GTUSet<double> s1 = {1.1, 2.2}, s2 = {};
		cout <<"\ns1 = ";
		s1.print();
		cout << "s2 = ";
		s2.print();
		cout << "size of s1: " << s1.size() << "\nis s1 empty: " << s1.empty() << endl;
		cout << "size of s2: " << s2.size() << "\nis s2 empty: " << s2.empty() << endl;
	}
	void test_vector(){
		/*********** CONSTRUCTORS AND ASSIGNMENT OPERATOR TEST ***********/
		GTUVector<int> vector1, vector2 = {1, 2, 3, 4}, vector3(vector2);
		cout <<"\nvector1 = ";
		vector1.print();
		cout << "vector2 = ";
		vector2.print();
		cout << "vector3 = ";
		vector3.print();
		cout << "moving vector2 to vector4...";
		GTUVector<int> vector4(move(vector2));
		cout << "\nvector2 = ";
		vector2.print();
		cout << "vector4 = ";
		vector4.print();
		cout << "Assigned vector4 to vector5...";
		GTUVector<int> vector5 = vector4;
		cout << "\nvector5 = ";
		vector5.print();
		cout << "vector4 = ";
		vector4.print();
		cout << "Move assigned vector4 to vector6...";
		GTUVector<int> vector6 = move(vector4);
		cout << "\nvector6 = ";
		vector6.print();
		cout << "vector4 = ";
		vector4.print();
		/*********** MODIFIERS TEST. ***********/
		/* Push_back function */
		cout << "Push 5 to vector5...";
		vector5.push_back(5);
		cout << "\nvector5 = ";
		vector5.print();
		/* Pop_back function */
		cout << "Pop_back an element from vector5...";
		vector5.pop_back();
		cout << "\nvector5 = ";
		vector5.print();
		/* Erase function */
		cout << "Erase second element of the vector5...";
		vector5.erase(vector5.begin()+1);
		cout << "\nvector5 = ";
		vector5.print();
		/* Clear function */
		cout << "Clear vector5...";
		vector5.clear();
		cout << "\nvector5 = ";
		vector5.print();
		/*********** ELEMENT ACCESS ***********/
		GTUVector<int> new_vec = {1, 2, 3, 4};
		cout << "Prints the third element of the new_vec...";
		cout << "\nnew_vec = ";
		new_vec.print();
		cout << "Third element of the new_vec: " << new_vec[2] << endl;
		/********** CAPACITY TEST **********/
		GTUVector<double> v1 = {1.1, 2.2}, v2 = {};
		cout <<"\nv1 = ";
		v1.print();
		cout << "v2 = ";
		v2.print();
		cout << "size of v1: " << v1.size() << "\nis v1 empty: " << v1.empty() << endl;
		cout << "size of v2: " << v2.size() << "\nis v2 empty: " << v2.empty() << endl;
	}
	void test_array(){
		/*********** CONSTRUCTORS AND ASSIGNMENT OPERATOR TEST ***********/
		GTUArray<int, 3> arr1, arr2 = {1, 2, 3}, arr3(arr2);
		cout <<"\narr1 = ";
		arr1.print();
		cout << "arr2 = ";
		arr2.print();
		cout << "arr3 = ";
		arr3.print();
		cout << "moving arr2 to arr4...";
		GTUArray<int, 3> arr4(move(arr2));
		cout << "\narr2 = ";
		arr2.print();
		cout << "arr4 = ";
		arr4.print();
		cout << "Assigned arr4 to arr5...";
		GTUArray<int, 3> arr5 = arr4;
		cout << "\narr5 = ";
		arr5.print();
		cout << "arr4 = ";
		arr4.print();
		cout << "Move assigned arr4 to arr6...";
		GTUArray<int, 3> arr6 = move(arr4);
		cout << "\narr6 = ";
		arr6.print();
		cout << "arr4 = ";
		arr4.print();
		/*********** MODIFIERS TEST. ***********/
		/* Fill function */
		cout << "fill arr5 with 19...";
		arr5.fill(19);
		cout << "\narr5 = ";
		arr5.print();
		/* Erase function */
		cout << "Erase second element of the arr5...";
		arr5.erase(arr5.begin()+1);
		cout << "\narr5 = ";
		arr5.print();
		/* Clear function */
		cout << "Clear arr5...";
		arr5.clear();
		cout << "\narr5 = ";
		arr5.print();
		/*********** ELEMENT ACCESS ***********/
		GTUArray<char, 4> first_arr = {'a', 'b', 'c', 'd'};
		cout << "\nfirst_arr = ";
		first_arr.print();
		cout << "The second element of first_arr: " << first_arr[1] << endl;
		cout << "The first element of first_arr: " << first_arr.at(0) << endl;
		cout << "Front element of first_arr: " << first_arr.front() << endl;
		cout << "Back element of first_arr: " << first_arr.back() << endl;
		/********** CAPACITY TEST **********/
		GTUArray<double, 2> a1 = {1.1, 2.2};
		GTUArray<double, 0> a2;
		cout <<"\na1 = ";
		a1.print();
		cout << "a2 = ";
		a2.print();
		cout << "size of a1: " << a1.size() << "\nis a1 empty: " << a1.empty() << endl;
		cout << "size of v2: " << a2.size() << "\nis a2 empty: " << a2.empty() << endl;
	}
	void find_test(){
		GTUArray<int, 5> arr = {1, 3, 5, 7, 9};
		GTUVector<int> vec = {0, 2, 4, 6, 8};
		cout << "\narr = ";
		arr.print();
		cout << "vec = ";
		vec.print();
		cout << "Search 3 on arr...\n";
		if(find(arr.begin(), arr.end(), 3) != arr.end())
			cout << "it found.\n";
		else
			cout << "it couldn't find.\n";
		cout << "Search 1 on vec...\n";
		if(find(vec.begin(), vec.end(), 1) != vec.end())
			cout << "it found.\n";
		else
			cout << "it couldn't find.\n";
	}
	void test_for_each(){
		GTUArray<int, 5> arr = {1, 3, 5, 7, 9};
		GTUVector<int> vec = {0, 2, 4, 6, 8};
		auto print = [](const int& value){ cout << value << ',';};
		cout << "\narr = ";
		arr.print();
		cout << "vec = ";
		vec.print();
		cout << "\narr = ";
		for_each(arr.begin(), arr.end(), print);
		cout << "vec = ";
		for_each(vec.begin(), vec.end(), print);
	}
	void range_for_loop(){
		GTUArray<int, 5> arr = {1, 3, 5, 7, 9};
		GTUVector<int> vec = {0, 2, 4, 6, 8};
		cout << "\narr = ";
		arr.print();
		cout << "vec = ";
		vec.print();
		cout << "\narr = ";
		for(auto it : arr){
			cout << it << ',';
		}
		cout << "vec = ";
		for(auto it : vec){
			cout << it << ',';
		}
	}
}

int main(){
	cout << "\nTESTING SET FUNCTIONS...";
	test_set();
	cout << "\n\nTESTING VECTOR FUNCTIONS...";
	test_vector();
	cout << "\n\nTESTING ARRAY FUNCTIONS...";
	test_array();
	cout << "\n\nTESTING FIND FUNCTION...";
	find_test();
	cout << "\n\nTESTING FOR_EACH FUNCTION...";
	test_for_each();
	cout << "\n\nTESTING RANGE BASED FOR LOOP FUNCTION...";
	range_for_loop();
	return 0;
}