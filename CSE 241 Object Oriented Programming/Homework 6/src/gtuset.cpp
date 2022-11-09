#ifndef gtuset
#define gtuset

#include <iostream>
#include <memory>
#include "gtuiterator.cpp"
#include "gtuiteratorconst.cpp"
#include "iterable.cpp"

using namespace std;
using namespace cayci_hw6;

namespace cayci_hw6{
	template<typename T>
	class GTUSet: public Iterable<T>{
	private:
		shared_ptr<T> set;
		int set_size;
	public:
		/********** Constructors. **********/
		GTUSet(): set_size(0){ /* No parameter constructor. */
			set = nullptr;
		}
		GTUSet(const GTUSet& copy): set_size(copy.set_size){ /* Copy constructor. */
			shared_ptr<T> temp(new T[set_size]); /* Creates a temp variable. */
			GTUIterator<T> it(temp, 0); /* Creates an iterator to keep the address of temp. */
			for(auto it_copy = copy.cbegin(); it_copy != copy.cend(); ++it_copy){ /* Makes deep copy. */
				*it = *it_copy;
				++it;
			}
			set = temp; /* Assings temp to set. */
		}
		GTUSet(GTUSet&& copy): set_size(copy.set_size){ /* Move constructor. */
			set = copy.set; /* Copies the set. */
			copy.set = nullptr; /* Deletes the copy object. */
			copy.set_size = 0; /* Deletes the copy object. */
		}
		GTUSet(initializer_list<T> copy): set_size(0){ /* Provides to create a set with list. */
			for(auto i = copy.begin(); i != copy.end(); i++){
				add(*i); /* Add every element of the list to the set. */
			}
		}
		/********** Destructor. **********/
		~GTUSet(){  /* Destructs the GTUSet objects. */
			set_size = 0;
			set = nullptr;
		}
		/********** Assignment operator. **********/
		GTUSet& operator=(const GTUSet& copy){ /* Assignment operator. */
			if(this != &copy) /* If the object are not the same, copies it. */
				set_size = copy.set_size; /* Copies the set size. */
				set = copy.set; /* Copies the set. */
			return *this;
		}
		GTUSet& operator=(GTUSet&& copy){ /* Move assignment operator. */
			if(this != &copy){
				set_size = copy.set_size; /* Copies the set size. */
				set = copy.set; /* Copies the set. */
				copy.set_size = 0; /* Deletes the copy object. */
				copy.set = nullptr; /* Deletes the copy object. */
			}
			return *this;
		}
		/********** Modifiers. **********/
		void add(const T& value){ /* Adds the value to set. */
			if(search(value) == false){ /* Checks the value exist or not, if it does not exist, continue. */
				shared_ptr<T> temp(new T[set_size+1]); /* Creates a temp variable. */
				GTUIterator<T> it_temp(temp, 0); /* Creates an iterator to keep the address of temp variable. */
				GTUIterator<T> it_set(set, 0); /* Creates an iterator to keep the adress of current object. */
				for(int i = 0; i < set_size; i++){ /* Makes deep copy. */
					*it_temp = *it_set;
					++it_temp;
					++it_set;
				}
				*it_temp = value; /* Last element of the set is new value. */
				set = temp; /* Assigns temp to set. */
				set_size+=1; /* Increases the size of the set. */
			}
		}
		void erase(GTUIterator<T> iterator){ /* Erase the element by the given iterator. */
			bool contain = false;
			int index = 0, rank = 0;
			for(auto it = this->begin(); it != this->end() && contain == false; ++it, rank++){  /* Checks the set has that iterator and if it has, keeps the index of it. */
				if(it == iterator){
					contain = true;
					index = rank;
				}
			}
			if(contain == true){ /* If set contain that element, delete it. */
				shared_ptr<T> temp(new T[set_size-1]); /* Creates a temp variable. */
				GTUIterator<T> it_temp(temp, 0); /* Creates an iterator to keep the address of the temp variable. */
				GTUIterator<T> it_set(set, 0); /* Creates an iterator to keep the adress of current object. */
				for(int i = 0; i < set_size-1; i++){ /* Makes deep copy except the given element. */
					if(i == index)
						++it_set;
					*it_temp = *it_set;
					++it_temp;
					++it_set;
				}
				set = temp; /* Assigns temp to set. */
				set_size = set_size-1; /* Decreases the size of the set. */
			}
		}
		void erase(const T& value){ /* Overloading erase function. Deletes the element by given value. */
			bool is_found = false;
			for(auto it = cbegin(); it != cend() && is_found == false; ++it){ /* Checks the set has that iterator and if it has, erase it*/
				if(*it == value){
					is_found = true;
					erase(it);
				}
			}
		}
		void clear(){ /* Clears the set. */
			set_size = 0;
			set = nullptr;
		}
		/********** Set Operations. **********/
		bool search(const T& value){ /* Search the value in the set. */
			bool exist = false;
			for(auto it = this->cbegin(); it != this->cend(); ++it){
				if(*it == value)
					exist = true;
			}
			return exist;
		}

		friend GTUSet intersectSet(const GTUSet& first, const GTUSet& second){ /* Find intersection of two set and returns it. */
			GTUSet intersection;
			bool is_found;
			for(auto it_first = first.cbegin(); it_first != first.cend(); ++it_first){
				is_found = false;
				for(auto it_second = second.cbegin(); it_second !=  second.cend() && is_found == false; ++it_second){
					if(*it_first == *it_second){ /* If both sets has same element, add it to intersection set. */
						is_found = true;
						intersection.add(*it_first);
					}
				}
			}
			return intersection;
		}
		friend GTUSet unionSet(const GTUSet& first, const GTUSet& second){ /* Find union of two set and returns it. */
			GTUSet unionset;
			for(auto it_first = first.cbegin(); it_first != first.cend(); ++it_first){ /* Adds first set elements to the list. */
				unionset.add(*it_first);
			}
			for(auto it_second = second.cbegin(); it_second != second.cend(); ++it_second){ /* Adds first set elements to the list. */
				unionset.add(*it_second);
			}
			return unionset;
		}
		/*********** Iterators. ***********/
		GTUIterator<T> begin(){ /* Returns iterator of first element. */
			return GTUIterator<T>(set, 0);
		}
		GTUIterator<T> end(){ /* Returns iterator of next element of the last element. */
			return GTUIterator<T>(set, set_size);
		}
		GTUIteratorConst<T> cbegin() const{ /* Returns constant iterator of first element. */
			return GTUIteratorConst<T>(set, 0);
		}
		GTUIteratorConst<T> cend() const{ /* Returns constant iterator of next element of the last element. */
			return GTUIteratorConst<T>(set, set_size);
		}
		/*********** Capacity. ***********/
		bool empty(){ /* Checks the set empty or not. */
			return (set_size == 0);
		}
		int size(){ /* Returns size of the set. */
			return set_size;
		}
		/*********** Element access. ***********/
		void print(){ /* Prints the set pretty. */
			GTUIterator<T> it_set(set, 0);
			cout << '{';
			for(int i = 0; i < set_size; i++){
				cout << *it_set;
				if(i != set_size-1)
					cout << ',';
				++it_set;
			}
			cout << '}' << endl;
		}
	};
}

#endif // gtuset