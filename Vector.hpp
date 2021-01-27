#pragma once
#include <vector>

namespace ft {
	template<class T>
	struct v_iterator {
	};

	template<class T> // pass any type and compiler auto generate Vector parametrized with this type
	class Vector {
	public:
		Vector() {
			data = nullptr;
			currentSize = 0;
			capacity = 0;
			Realloc(2);
		}
		Vector(T arr[], int n) {
			data = new T[n];
			for (int i = 0; i < n; i++) {
				data[i] = arr[i];
			}
		}
		~Vector() {
			clear();
			::operator delete(data, capacity * sizeof(T)); // to not call any destructors
//    	delete[] data;
		}

		void push_back(const T& val) throw() {
			if (currentSize >= capacity) {
				Realloc(capacity * 2);
			}

			data[currentSize] = val;
			currentSize++;
		}

		void pop_back() throw() {
			if (currentSize > 0) {
				currentSize--;
				data[currentSize].~T();
			}
		}

		void clear() throw() {
			for (size_t i = 0; i < currentSize; i++) {
				data[i].~T();
			}
			currentSize = 0;
		}

		size_t size() const throw() { return currentSize; }

		const T&	operator[](size_t idx) const throw() {
			return data[idx];
		}

		T&	operator[](size_t idx) throw() {
			return data[idx];
		}

	private:
		void	Realloc(size_t newCapacity) throw() {
			T*	newBlock = (T*)::operator new(newCapacity * sizeof(T)); // we don't want to call a constructor at all

			size_t	allocSize = currentSize;
			if (newCapacity < allocSize) {
				allocSize = newCapacity;
			}

			for (size_t i = 0; i < allocSize; i++) {
				newBlock[i] = data[i];
			}

			for (size_t i = 0; i < currentSize; i++) { // clear, but don't set size to zero
				data[i].~T();
			}

			::operator delete(data, capacity * sizeof(T));
			data = newBlock;
			capacity = newCapacity;
		}

	private:
		T*  data;

		size_t	currentSize;
		size_t	capacity;

	};
}
