#ifndef gtuvector
#define gtuvector

#include <iostream>
#include <memory>
#include "gtuiterator.cpp"
#include "gtuiteratorconst.cpp"
#include "iterable.cpp"

using namespace std;
using namespace cayci_hw6;
namespace cayci_hw6{
	template <typename T>
	class GTUVector: public Iterable<T>{
	private:
		shared_ptr<T> vec;
		int vec_size;
	public:
		/********** Constructors. **********/
		GTUVector(): vec_size(0){ /* No parameter constructor. */
			vec = nullptr;
		}
		GTUVector(const GTUVector& copy): vec_size(copy.vec_size){ /* Copy constructor. */
			shared_ptr<T> temp(new T[vec_size]); /* Creates a temp variable. */
			GTUIterator<T> it(temp, 0); /* Creates an iterator to keep the address of the temp variable. */
			for(auto it_copy = copy.cbegin(); it_copy != copy.cend(); ++it_copy){ /* Makes deep copy. */
				*it = *it_copy;
				++it;
			}
			vec = temp; /* Assigns temp to vec. */
		}
		GTUVector(GTUVector&& copy): vec_size(copy.vec_size){ /* Move constructor. */
			vec = copy.vec; /* Copies the vector. */
			copy.vec = nullptr; /* Deletes the copy object. */
			copy.vec_size = 0; /* Deletes the copy object. */
		}
		GTUVector(initializer_list<T> copy){ /* Provides to create a vector with list. */
			int size_of_list = 0, rank = 0;
			for(auto i = copy.begin(); i != copy.end(); i++){
				size_of_list++; /* Calculates the size of the list. */
			}
			vec_size = size_of_list; /* Assigns size of the list to vector size. */
			shared_ptr<T> temp(new T[vec_size]); /* Creates a temp variable. */
			GTUIterator<T> it_temp(temp, 0); /* Creates an iterator to keep the address of the temp variable. */
			for(auto it_copy = copy.begin(); it_copy != copy.end(); ++it_copy){ /* Makes deep copy. */
				*it_temp = *it_copy;
				++it_temp;
			}
			vec = temp;  /* Assigns temp to vec. */
		}
		/********** Destructor. **********/
		~GTUVector(){ /* Destruct the object. */
			vec_size = 0;
			vec = nullptr;
		}
		/********** Assignment operators. **********/
		GTUVector& operator=(const GTUVector& copy){ /* Assignment operator. */
			if(this != &copy) /* If the object are not the same, copies it. */
				vec_size = copy.vec_size; /* Copies the vector size. */
				vec = copy.vec; /* Copies the vector. */
			return *this;
		}
		GTUVector& operator=(GTUVector&& copy){ /* Move assignment operator. */
			if(this != &copy){  /* If the object are not the same, copies it. */
				vec_size = copy.vec_size; /* Copies the vector size. */
				vec = copy.vec; /* Copies the vector. */
				copy.vec_size = 0; /* Deletes the copy object. */
				copy.vec = nullptr; /* Deletes the copt object. */
			}
			return *this;
		}
		/********** Modifiers. **********/
		void push_back(T t1){ /* Adds a value to vector. */
			shared_ptr<T> temp(new T[vec_size+1]); /* Creates a temp variable. */
			GTUIterator<T> it_temp(temp, 0); /* Creates an iterator to keep the address of the temp variable. */
			GTUIterator<T> it_vec(vec, 0); /* Creates an iterator to keep the address of the current vector. */
			for(int i = 0; i < vec_size; i++){ /* Makes deep copy. */
				*it_temp = *it_vec;
				++it_temp;
				++it_vec;
			}
			*it_temp = t1; /* Last element of the vector is new value. */
			vec = temp; /* Assigns temp to vec. */
			vec_size+=1; /* Increases the size of the vector. */
		}
		void pop_back(){ /* Deletes an element at the beginning of the vector. */
			shared_ptr<T> temp(new T[vec_size-1]); /* Creates a temp variable. */
			GTUIterator<T> it_temp(temp, 0); /* Creates an iterator to keep the address of the temp variable. */
			GTUIterator<T> it_vec(vec, 0); /* Creates an iterator to keep the address of the current vector. */
			for(int i = 0; i < vec_size-1; i++){ /* Makes deep copy. */
				*it_temp = *it_vec;
				++it_temp;
				++it_vec;
			}
			vec = temp; /* Assigns temp tp vec. */
			vec_size-=1; /* Decreases the size of the vector. */
		}
		void clear(){ /* Clears the vector. */
			vec = nullptr;
			vec_size = 0;
		}
		void erase(GTUIterator<T> iterator){ /* Erase the element by the given iterator. */
			bool contain = false;
			int index = 0, rank = 0;
			for(auto it = this->begin(); it != this->end() && contain == false; ++it, rank++){ 
				if(it == iterator){ /* Checks the vector contains that iterator and if it has, keeps the index of it. */
					contain = true;
					index = rank;
				}
			}
			if(contain == true){ /* If vector contain that element, delete it. */
				shared_ptr<T> temp(new T[vec_size-1]); /* Creates a temp variable. */
				GTUIterator<T> it_temp(temp, 0); /* Creates an iterator to keep the address of the temp variable. */
				GTUIterator<T> it_vec(vec, 0); /* Creates an iterator to keep the address of the current vector. */
				for(int i = 0; i < vec_size-1; i++){ /* Makes deep copy except the given element. */
					if(i == index)
						++it_vec;
					*it_temp = *it_vec;
					++it_temp;
					++it_vec;
				}
				vec = temp; /* Assigns temp to vec. */
				vec_size = vec_size-1; /* Decreases the size of the vector. */
			}
		}
		/*********** Iterators. ***********/
		GTUIterator<T> begin(){ /* Returns iterator of first element. */
			return GTUIterator<T>(vec, 0);
		}
		GTUIterator<T> end(){ /* Returns iterator of next element of the last element. */
			return GTUIterator<T>(vec, vec_size);
		}
		GTUIteratorConst<T> cbegin() const{ /* Returns constant iterator of first element. */
			return GTUIteratorConst<T>(vec, 0);
		}
		GTUIteratorConst<T> cend() const{ /* Returns constant iterator of next element of the last element. */
			return GTUIteratorConst<T>(vec, vec_size);
		}
		/*********** Element access. ***********/
		T& operator[](int index){ /* Returns the indexth element of the vector. */
			GTUIterator<T> it_vec(vec, index);
			return *it_vec;
		}
		void print(){ /* Prints the vector pretty. */
			GTUIterator<T> it_vec(vec, 0);
			cout << '{';
			for(int i = 0; i < vec_size; i++){
				cout << *it_vec;
				if(i != vec_size-1)
					cout << ',';
				++it_vec;
			}
			cout << '}' << endl;
		}
		/*********** Capacity. ***********/
		bool empty(){ /* Checks the vector is empty or not. */
			return (vec_size == 0);
		}
		int size(){ /* Returns the size of the vector. */
			return vec_size;
		}
	};
}

#endif // gtuvector