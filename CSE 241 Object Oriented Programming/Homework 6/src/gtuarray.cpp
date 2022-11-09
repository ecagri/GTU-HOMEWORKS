#ifndef gtuarray
#define gtuarray

#include <iostream>
#include <memory>
#include "gtuiterator.cpp"
#include "gtuiteratorconst.cpp"
#include "iterable.cpp"

using namespace std;
using namespace cayci_hw6;

namespace cayci_hw6{
	template <typename T, int SIZE>
	class GTUArray: public Iterable<T>{
	private:
		shared_ptr<T> arr;
		int arr_size;
	public:
		/********** Constructors. **********/
		GTUArray(){ /* No parameter constructors. */
			shared_ptr<T> temp(new T[SIZE]);
			arr_size = SIZE;
			arr = temp;
		}
		GTUArray(const GTUArray& copy): arr_size(copy.arr_size){ /* Copy constructor. */
			shared_ptr<T> temp(new T[arr_size]); /* Create a temp variable. */
			GTUIterator<T> it(temp, 0); /* Create an iterator which keeps the adress of temp. */
			for(auto it_copy = copy.cbegin(); it_copy != copy.cend(); ++it_copy){ /* Makes deep copy. */
				*it = *it_copy;
				++it;
			}
			arr = temp; /* Assigns temp to arr. */
		}
		GTUArray(GTUArray&& copy): arr_size(copy.arr_size){ /* Move constructor. */
			arr = copy.arr; /* Copies the arr. */
			copy.arr = nullptr; /* Deletes the copy object. */
			copy.arr_size = 0; /* Deletes the copy object. */
		}
		GTUArray(initializer_list<T> copy){ /* Provides to create a array with list. */
			int size_of_list = 0;
			for(auto it_copy = copy.begin(); it_copy != copy.end(); ++it_copy){ /* Counts the number of elements of list. */
				size_of_list++;
			}
			arr_size = size_of_list; /* Assigns size of list to size of array. */
			shared_ptr<T> temp(new T[arr_size]); /* Creates a temp variable. */
			GTUIterator<T> it_temp(temp, 0); /* Creates an iteratator which keeps the address of temp. */
			for(auto it_copy = copy.begin(); it_copy != copy.end(); ++it_copy){ /* Makes deep copy. */
				*it_temp = *it_copy;
				++it_temp;
			}
			arr = temp; /* Assigns temp to arr. */
		}
		/********** Destructor. **********/
		~GTUArray(){ /* Destruct the array objects. */
			arr_size = 0;
			arr = nullptr;
		}
		/********** Assignment operator. **********/
		GTUArray& operator=(const GTUArray& copy){ /* Assignment operator. */
			if(this != &copy) /* If the object are not the same, copies it. */
				arr_size = copy.arr_size;
				arr = copy.arr;
			return *this;
		}
		GTUArray& operator=(GTUArray&& copy){ /* Move assignment operator. */
			if(this != &copy){ /* If the object are not the same, copies it. */
				arr_size = copy.arr_size; 
				arr = copy.arr;
				copy.arr_size = 0; /* Deletes the copy object. */
				copy.arr = nullptr; /* Deletes the copt object. */
			}
			return *this;
		}
		/********** Modifiers. **********/
		void fill(const T& value){ /* Fills the array with the value. */
			GTUIterator<T> it_arr(arr, 0); /* Creates an iterator for current array. */
			for(int i = 0; i < arr_size; i++){ /* Assigns value to every element of the array. */
				*it_arr = value;
				++it_arr;
			}
		}
		void clear(){ /* Clears the array. */
			arr_size = 0;
			arr = nullptr;
		}
		void erase(GTUIterator<T> iterator){ /* Deletes the element by given iterator. */
			cout << "ERASE FUNCTION IS NOT FULLY COMPATIBLE WITH ARRAY BECAUSE SIZE OF ARRAY IS FIXED.\n";
			for(auto it = this->begin(); it != this->end(); ++it){ 
				if(it == iterator){ /* Finds the element. */
					*it = 0; /* Assigns it to 0. Because we cannot free space in fixed size array. */
				}
			}
		}
		/********** Element access. **********/
		T& operator[](int index){ /* Returns the indexth element of the array. */
			GTUIterator<T> it_arr(arr, index); /* Creates an iterator for current array. */
			return *it_arr;
		}
		T& at(int index){ /* Returns the indexth element of the array. Contrary to index operator, at function checks the borders.  */
			try{
				if(-1 < index && index < arr_size){ 
					GTUIterator<T> it_arr(arr, index);
					return *it_arr;
				}
				else
					throw index;
			}
			catch(T index){
				cout << "OUT OF BORDERS!";
				exit(1);
			}
		}
		T& front(){ /* Returns first element of the array. */
			GTUIterator<T> it_arr(arr, 0);
			return *it_arr;
		}
		T& back(){ /* Returns last element of the array. */
			GTUIterator<T> it_arr(arr, arr_size-1);
			return *it_arr;
		}
		void print(){ /* Prints the array pretty. */
			GTUIterator<T> it_arr(arr, 0);
			cout << '{';
			for(int i = 0; i < arr_size; i++){
				cout << *it_arr;
				if(i != arr_size-1)
					cout << ',';
				++it_arr;
			}
			cout << '}' << endl;
		}
		/*********** Iterators. ***********/
		GTUIterator<T> begin(){ /* Returns iterator of first element. */
			return GTUIterator<T>(arr, 0);
		}
		GTUIterator<T> end(){ /* Returns iterator of next element of the last element. */
			return GTUIterator<T>(arr, arr_size);
		}
		GTUIteratorConst<T> cbegin() const{ /* Returns constant iterator of first element. */
			return GTUIteratorConst<T>(arr, 0);
		}
		GTUIteratorConst<T> cend() const{ /* Returns constant iterator of next element of the last element. */
			return GTUIteratorConst<T>(arr, arr_size);
		}
		/*********** Capacity. ***********/
		bool empty(){ /* Checks the arr is empty or not. */
			return (arr_size == 0);
		}
		int size(){ /* Returns the size of the arr. */
			return arr_size;
		}
	};
}

#endif // gtuarray