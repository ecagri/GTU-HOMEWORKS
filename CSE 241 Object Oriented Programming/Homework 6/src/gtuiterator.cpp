#ifndef gtuiterator
#define gtuiterator

#include <iostream>
#include <memory>

using namespace std;

namespace cayci_hw6{
	template <typename T>
	class GTUIterator: public iterator<forward_iterator_tag, T>{ /* Creating GTUIterator class from iterator class to use stl functions. */
	private:
		shared_ptr<T> ptr; /* Keeps the pointer. */
		int index;
	public:
		/********** Constructors. **********/
		GTUIterator(shared_ptr<T> copy, int rank): ptr(copy), index(rank){/* EMPTY */} /* No parameter constructor. */
		/********** Operators. **********/
		bool operator!=(GTUIterator other){ /* Checks two GTUIterator are the same or not. */
			bool equals = true;
				if(ptr != other.ptr || index != other.index){ /* Controls their pointer and index. */
					equals = false;
				}
				return !(equals);
		}
		bool operator==(GTUIterator other){ /* Returns the negative of the not equal operator. */
			return !(*this != other);
		}
		T& operator*(){ /* Returns the current index of the pointer. */
			return ptr.get()[index];
		}
		GTUIterator operator+(int x){ /* Returns x. index of the pointer. */
			return GTUIterator(ptr, x);
		}
		GTUIterator operator++(){ /* Increases index and returns the object. */
			index += 1;
			return *this;
		}
		GTUIterator operator--(){ /* Decreases index and returns the object. */
			index -= 1;
			return *this;
		}
		GTUIterator* operator->(){ /* Arrow operator to access member function of GTUIterator class. */
			return this;
		}
		void print(){ /* Print function to use arrow operator. */
			cout << ptr[index] << ',';
		}
	};
}

#endif // gtuiterator