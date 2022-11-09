#ifndef iterable
#define iterable

#include <iostream>
#include "gtuiterator.cpp"
#include "gtuiteratorconst.cpp"

using namespace std;
using namespace cayci_hw6;

namespace cayci_hw6{
	template <typename T>
	class Iterable{
	public:
		virtual bool empty() = 0;
		virtual int size() = 0;
		virtual void clear() = 0;
		friend class GTUIterator<T>;
		virtual GTUIterator<T> begin() = 0;
		virtual GTUIterator<T> end() = 0;
		friend class GTUIteratorConst<T>;
		virtual GTUIteratorConst<T> cbegin() const = 0;
		virtual GTUIteratorConst<T> cend() const = 0;
		virtual void erase(GTUIterator<T>) = 0;
	};
}

#endif // iterable