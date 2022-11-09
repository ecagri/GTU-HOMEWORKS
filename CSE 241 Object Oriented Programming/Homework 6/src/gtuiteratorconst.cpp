#ifndef gtuiteratorconst
#define gtuiteratorconst

#include <iostream>
#include <memory>

using namespace std;

namespace cayci_hw6{
	template <typename T>
	class GTUIteratorConst{
	private:
		const shared_ptr<T> ptr; /* Keeps the pointer. */
		int index;
	public:
		GTUIteratorConst(shared_ptr<T> copy, int rank): ptr(copy), index(rank){/* EMPTY */} /* No parameter constructor */
		bool operator!=(GTUIteratorConst other){ /* Checks two GTUIterator are the same or not. */
			bool equals = true;
				if(ptr != other.ptr || index != other.index){ /* Controls their pointer and size. */
					equals = false;
				}
				return !(equals);
		}
		bool operator==(GTUIteratorConst other){ /* Returns the negative of the not equal operator. */
			return !(*this != other);
		}
		const T& operator*(){ /* Returns the current index of the pointer as constant. */
			return ptr.get()[index];
		}
		GTUIteratorConst* operator->(){ /* Arrow operator to access member function of GTUIterator class. */
			return this;
		}
		GTUIteratorConst operator+(int x){ /* Returns x. index of the pointer. */
			return GTUIteratorConst(ptr, x);
		}
		GTUIteratorConst operator++(){ /* Increases index and returns the object. */
			index += 1;
			return *this;
		}
		GTUIteratorConst operator--(){ /* Decreases index and returns the object. */
			index -= 1;
			return *this;
		}
	};
}

#endif // gtuiteratorconst