/* This code is written by Çağrı Çaycı. */
/* To run this code, ./filename < input_file_name.txt in linux */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class set{
private:
	char name; /* Keeps name of the set. */
	vector <string> elements; /* Keeps elements of the set. */
	bool repetition_check(){ /*Checks whether is there a repetition. */ 
		int repetition;
		bool is_repetitive = false;
		/* This parts calculates repetitons. */
		for(auto element1 : elements){
			repetition = 0;
			for(auto element2 : elements){
				if(element1 == element2)
					repetition+=1;
			}
			if(repetition > 1) /* If an element in the set repeats more than one, there is a repetition. */
				is_repetitive = true;
		}
		return is_repetitive;
	}
	bool function_check(set s1){ /* Checks validty of the function. */
		bool is_function = true;

		if(elements.size() > s1.elements.size()) /* If one of the elements of the Domain is not related to any element of the Codomain, this function is not valid. */ 
			is_function = false;
		if(repetition_check()) /* Any element of the domain cannot be related to more than one element of the Codomain. */
			is_function = false;
		return is_function;
	}
	bool one_to_one_check(set s1){ /* Checks whether the function is one to one or not. */
		bool is_one_to_one = false;
		if(elements.size() <= s1.elements.size()){ /* If number of the elements of the Codomain is bigger than domain, continue. */
			if(s1.repetition_check() == false) /* If the Codomain set does not contain any repetition, this function is one to one. */
				is_one_to_one = true;
		}
		return is_one_to_one;
	}
	bool onto_check(set s1){ /* Checks whether the function is onto or not. */
		bool is_onto = false;
		if(elements.size() == s1.elements.size()){ /* If the number of element of the Codomain is equal to number of domain, the function is onto. */
			is_onto = true;
		}
		return is_onto;
	}
public:
	set(){ /* Constructor. */
		/* Empty */
	}
	void add_element(string element_of_set){ /* Provides adding new element to set. */
		elements.push_back(element_of_set);
	}

	void create_name(char name_of_set){ /* Sets the name of the set. */
		name = name_of_set;
	}
	void clear_set(){ /* Clears the set. */
		elements.clear();
	}
	void determine_func_type(set s1){ /* Finds function type and prints it. */
		bool is_onto = onto_check(s1), is_function = function_check(s1), is_one_to_one = one_to_one_check(s1);

		if(is_function == false)
			cout << " not a function" << endl;
		else{
			if(is_onto == true && is_one_to_one == true)
				cout << " bijective" << endl;
			else if(is_onto == true && is_one_to_one == false)
				cout << " onto but not one to one" << endl;
			else if(is_onto == false && is_one_to_one == true)
				cout << " one to one but not onto" << endl;
			else
				cout << " neither onto nor one to one" << endl;
		}
		cout << endl;
	}
};

vector <string> get_inputs(){ /* Gets inputs and keeps them in a string vector. */
	vector <string> all_inputs;
	string input;
	do{
		input.clear();
		cin >> input;
		if(input.size() > 0)
			all_inputs.push_back(input);
	}while(input.size() > 0);
	return all_inputs;
}

int main(){
	vector <string> all_inputs;

	vector <set> all_set;

	set temp;

	all_inputs = get_inputs(); /* Gets all inputs. */

	bool saved = true;;

	for(auto input: all_inputs){
		if(input.size() == 1 && 'A' <= input[0] && input[0] <= 'Z'){ /* If input is a name for set, continue. */
			if(saved == false){ /* If the set is not saved to all_set vector, saves it. */
				all_set.push_back(temp);
				saved = true;
			}
			temp.clear_set(); /* Clears the temp set. */
			temp.create_name(input[0]); /* Sets the name of the set. */
		}
		else{
			temp.add_element(input); /* Adds the input to the elements of the temp set. */
			saved = false;
		}
	}
	all_set.push_back(temp);

	for(long unsigned int i = 0; i+1 < all_set.size(); i++){ /* Prints types of the functions and inverse functions. */
		cout << "f" << i+1 << ':';
		all_set[i].determine_func_type(all_set[i+1]);
		cout << "Inverse of f" << i+1 << ':';
		all_set[i+1].determine_func_type(all_set[i]);
	}

	if(all_set.size() > 2){ /* Prints type of the composition of the functions if the file has more than 2 set. */
		for(long unsigned int i = 0; i < all_set.size(); i++){
			cout << "(f" << all_set.size() - i << ')';
			if(i != all_set.size()-1){
				cout << 'o';
			}
		}
		cout << " is: ";
		all_set[0].determine_func_type(all_set[int(all_set.size())-1]);
	}

	return 0;
}