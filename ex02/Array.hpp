#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <cstddef>
#include <exception>
template <typename T>
class Array
{
private:
	std::size_t _size;
	T *_arr;
public:
	class RangeException : public std::exception {
		public :
			const char *what(void) const throw() {
				return "Out of Range";
			}
	};

	Array() : _size(0), _arr(NULL) {}
	Array(std::size_t n) : _size(n), _arr(NULL) {
		if (_size) _arr = new T[_size];
	}
	Array(const Array& ref) : _size(ref._size), _arr(NULL) {
		if (_size) _arr = new T[_size];
		for (std::size_t i=0; i<_size; i++)
			_arr[i] = ref[i];
	}
	~Array() {
		if (_size) {
			delete[] _arr;
			_arr = NULL;
			_size = 0;
		}
	}

	Array&	operator=(const Array& ref) {
		if (this != &ref) {
			this->_size = ref._size;
			this->_arr = NULL;
			if (this->_size) {
				for (std::size_t i=0; i<_size ; i++)
					this->arr[i] = ref[i];
			}
		}
		return *this;
	}
	
	const	T& operator[](std::size_t i) const {
		if (i >= _size)
			throw RangeException();
		return _arr[i];
	}

	std::size_t	size(void) const {
		return _size;
	}
};

#endif
