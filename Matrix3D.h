#ifndef MAT3D_H
#define MAT3D_H

#include <iostream>
#include <algorithm> //swap

#include <cassert>

/**
  @brief Matrix3D Class

  Template class implementing a 3-dimensional array of cells
  containing data of type T.
*/

template <typename Q>
struct default_functor
{
	bool operator()(Q a, Q b) const {
		return a == b;
	}
};

template <typename T, typename F = default_functor<T>>
class Matrix3D {

	T* _matrix; ///< pointer to the first cell of the 3D array

	unsigned int _floors; ///< number of floors of the 3D matrix
	unsigned int _rows; ///< number of rows of the 3D matrix
	unsigned int _columns; ///< number of columns of the 3D matrix

	F _equals; //< functor used to check if two data of type T are equal

public:

	/**
	    @brief Default constructor

	    The default constructor is used to initialize member data
	    to represent an empty 3D array.

	    @post _matrix = nullptr
	    @post _floors == 0
	    @post _rows == 0
	    @post _column == 0
	*/
	Matrix3D() : _matrix(nullptr), _floors(0), _rows(0), _columns(0) {}

	/**
	    @brief Secondary constructor (z, y, x)

	    Secondary constructor used to construct a 3D matrix based on 
	    the given dimensions. The cells of the array are not initialized.

	    @param z number of floors of the 3D matrix to create
	    @param y number of rows of the 3D matrix to create
	    @param x number of columns of the 3D matrix to create

	    @pre z!=0 && y!=0 && x!=0

	    @post _matrix != nullptr
	    @post _floors == z
	    @post _rows == y
	    @post _column == x

	    @throw std::bad_alloc possible allocation exception
	*/
	Matrix3D(int z, int y, int x) : _matrix(nullptr), _floors(z), _rows(y), _columns(x) {

		assert(z > 0 && y > 0 && x > 0);

		try {
			_matrix = new T[z * y * x];
		}
		catch(...) {
			clear();
			throw;
		}

	}

	/**
	    @brief Secondary constructor (z, y, x, value)

	    Secondary constructor which is used to construct a 3D matrix based on 
	    the given dimensions, and which initializes each cell of the matrix to 
	    the value of type T value passed.

	    @param z number of floors of the 3D matrix to create
	    @param y number of rows of the 3D matrix to create
	    @param x number of columns of the 3D matrix to create
	    @param value value of the type of the array with which to initialize the cells

	    @pre z!=0 && y!=0 && x!=0

	    @post _matrix != nullptr
	    @post _floors == z
	    @post _rows == y
	    @post _column == x

	    @throw std::bad_alloc possible allocation exception
	*/
	Matrix3D(int z, int y, int x, const T &value) : _matrix(nullptr), _floors(z), _rows(y), _columns(x) {

		assert(z > 0 && y > 0 && x > 0);

		try {
			_matrix = new T[z * y * x];
			for (unsigned int i = 0; i < _floors * _rows * _columns; ++i)
				_matrix[i] = value;
		}
		catch(...) {
			clear();
			throw;
		}

	}

	/**
	    @brief Copy Constructor

	    Copy constructor. It is used to create an object as a copy of 
	    another object. The two objects must be independent.

	    @param other source Matrix3D to copy
	    
	    @post _matrix != nullptr
	    @post _floors == other._floors
	    @post _rows == other._rows
	    @post _column == other._column

	    @throw std::bad_alloc possible allocation exception
	*/
	Matrix3D(const Matrix3D &other) : _matrix(nullptr), _floors(other._floors), _rows(other._rows), _columns(other._columns) {
		try {
			_matrix = new T[other._floors * other._rows * other._columns];
			for (unsigned int i = 0; i < _floors * _rows * _columns; ++i)
				_matrix[i] = other._matrix[i];
		}
		catch(...) {
			clear();
			throw;
		}
		
	}

	/**
	    @brief Assignment operator

	    The assignment operator is used to copy the contents of one 
	    object into another object of the same type. 
	    The two objects must be independent.

	    @param other source Matrix3D to copy

	    @return a reference to the current object

	    @post _matrix != nullptr
	    @post _floors == other._floors
	    @post _rows == other._rows
	    @post _column == other._column 
	*/
	Matrix3D &operator=(const Matrix3D &other) {
		if(this != &other) {
			Matrix3D tmp(other);
			this->swap(tmp);
		}

		return *this;
	}

	/**
	    @brief Access to the number of floors of the 3D matrix

	    Method to obtain the number of floors of the 3D matrix.

    	@return number of floors of the 3D matrix
	*/
	unsigned int getFloors() const {
		return _floors;
	}

	/**
	    @brief Access to the number of rows of the 3D matrix

	    Method to obtain the number of rows of the 3D matrix.

    	@return number of rows of the 3D matrix
	*/
	unsigned int getRows() const {
		return _rows;
	}

	/**
	    @brief Access to the number of columns of the 3D matrix

	    Method to obtain the number of columns of the 3D matrix.

    	@return number of columns of the 3D matrix
	*/
	unsigned int getColumns() const {
		return _columns;
	}

	/**
	    @brief swap method

	    Function that swaps the contents and dimensions of two 3D matrixes.

	    @param other the Matrix3D with which to exchange content
	*/
	void swap(Matrix3D &other) {
        std::swap(_matrix, other._matrix);
        std::swap(_rows, other._rows);
        std::swap(_columns, other._columns);
        std::swap(_floors, other._floors);
    }

    /**
    	@brief clear method

    	Function that empties the Matrix3D, deallocating the memory allocated 
    	on the heap, and bringing member data to a coherent state.

    	@post _matrix == nullptr
	    @post _floors == 0
	    @post _rows == 0
	    @post _column == 0
    */

	void clear() {
		delete[] _matrix;
        _matrix = nullptr;
        _rows = 0;
        _columns = 0;
        _floors = 0;
    }

    /**
	    @brief Destructor

	    Class destructor. The destructor must remove all resources used 
	    by the class. In this case the heap-allocated array must be deallocated 
	    and the other data members must be returned to a coherent state.

	    @post _matrix == nullptr
	    @post _floors == 0
	    @post _rows == 0
	    @post _column == 0
	*/
    ~Matrix3D() {
        clear();
    }

	/**
	    @brief Getter/Setter of the (z, y, x)-th cell

	    Method that allows to read and/or write the (z, y, x)-th cell of the matrix.

	    @param z floor index of the 3D matrix in which the cell is located
	    @param y row index of the 3D matrix where the cell is located
	    @param x column index of the 3D matrix where the cell is located

	    @return reference to the (z, y, x)-th cell of the 3D matrix

	    @pre z < _floors && y < _rows && x < _columns
	*/
    T& operator()(int z, int y, int x) {
    	assert(z >= 0 && y >= 0 && x >= 0);
    	assert(z < _floors && y < _rows && x < _columns);
    	return _matrix[(z * _rows * _columns) + (y * _columns) + x];
    }

    /**
	    @brief Getter of the (z, y, x)-th cell

	    Method which allows to read the (z, y, x)-th cell of the matrix.

	    @param z floor index of the 3D matrix in which the cell is located
	    @param y row index of the 3D matrix where the cell is located
	    @param x column index of the 3D matrix where the cell is located

	    @return reference alla cella (z, y, x)-esima della matrice 3D

	    @pre z < _floors && y < _rows && x < _columns
	*/
    const T& operator()(int z, int y, int x) const {
    	assert(z >= 0 && y >= 0 && x >= 0);
    	assert(z < _floors && y < _rows && x < _columns);
    	return _matrix[(z * _rows * _columns) + (y * _columns) + x];
    }

    /**
    @brief slice method

	    Method that returns a sub-Matrix3D containing the values in the coordinate 
	    intervals z1-z2, y1-y2 and x1-x2.

	    @param z1 floor index from which to start the slicing of the original 3D matrix
	    @param y1 row index from which to start the slicing of the original 3D matrix
	    @param x1 column index from which to start the slicing of the original 3D matrix
	    @param z2 floor index from which to end the slicing of the original 3D matrix
	    @param y2 row index from which to end the slicing of the original 3D matrix
	    @param x2 column index from which to end the slicing of the original 3D matrix

	    @return sub-Matrix3D containing the values in the specified ranges

	    @pre z1 < _floors && z2 < _floors && y1 < _rows && y2 < _rows && x1 < _columns && x2 < _columns
	*/
    Matrix3D slice(int z1, int z2, int y1, int y2, int x1, int x2) const {

    	assert(z1 >= 0 && z2 >= 0 && y1 >= 0 && y2 >= 0 && x1 >= 0 && x2 >= 0);
    	assert(z1 < _floors && z2 < _floors && y1 < _rows && y2 < _rows && x1 < _columns && x2 < _columns);
    	assert(z2 >= z1 && y2 >= y1 && x2 >= x1);

    	Matrix3D sliced_matrix(z2-z1+1, y2-y1+1, x2-x1+1);

    	for(unsigned int z = z1; z <= z2; ++z) 
        	for(unsigned int y = y1; y <= y2; ++y) 
        		for(unsigned int x = x1; x <= x2; ++x) 
        			sliced_matrix((z - z1), (y - y1), (x - x1)) = (*this)(z, y, x);

        return sliced_matrix;

    }

    /**
	    @brief Equality operator

	    The equality operator is used to check that two Matrices 3D having the same dimensions 
	    are equal and therefore contain the same values in all the corresponding cells.
		For the comparison, the _equals functor is used, a member functor whose type can be 
		defined when creating the matrix for greater flexibility.
		If not defined, the default functor uses the == operator and it is therefore necessary 
		that any custom data types redefine it in turn.

	    @param other source Matrix3D to compare

	    @return true if the matrixes are equal, false otherwise

	    @pre _floors == other._floors && _rows == other._rows && _columns == other._columns
	*/
    bool operator==(const Matrix3D &other) const {

    	assert(_floors == other._floors && _rows == other._rows && _columns == other._columns);

    	if(this != &other) {
    		for(unsigned int z = 0; z < _floors; ++z)
	        	for(unsigned int y = 0; y < _rows; ++y) 
	        		for(unsigned int x = 0; x < _columns; ++x)
	        			if(!(_equals(other(z, y, x), (*this)(z, y, x))))
	        				return false;
    	}    	

        return true;
        			
    }

    /**
	    @brief Inequality operator

	    The inequality operator is used to check that two Matrices 3D having the same 
	    dimensions are different and therefore contain different values even in only 
	    some corresponding cells.
		Use the equality operator and return the opposite boolean value.

	    @param other source Matrix3D to compare

	    @return true if the matrixes are equal, false otherwise
	*/
    bool operator!=(const Matrix3D &other) const {

        return !((*this) == other);
        			
    }

    // Implementation of random access iterators through the pointer trick,
	// being the internal structure array-based.

    typedef T *iterator;

    // Return the iterator to the start of the data sequence
	iterator begin() {
		return _matrix;
	}

	// Return the iterator at the end of the data sequence
	iterator end() {
		return _matrix + (_rows * _columns * _floors);
	}

	typedef const T *const_iterator;

	// Return the iterator to the start of the data sequence
	const_iterator begin() const {
		return _matrix;
	}
	
	// Return the iterator at the end of the data sequence
	const_iterator end() const {
		return _matrix + (_rows * _columns * _floors);
	}

	/**
	    @brief fill method

	    Generic method that allows to fill a Matrix3D with values taken 
	    from a sequence of data identified by generic iterators.
		Filling takes place in the order of iteration of the matrix data, 
		and stops in case the matrix to be filled is no longer able to contain 
		data but the passed sequence is not ended yet.
		The old values are overwritten.

	    @param b l'iteratore che indica l'inizio della sequenza di dati
	    @param b l'iteratore che indica la fine della sequenza di dati
	*/
    template<typename Iter>
    void fill(Iter b, Iter e) {

    	Matrix3D tmp(*this);

    	int i = 0;
    	while(b != e && i != _floors * _rows * _columns){ // fills while it can
    		tmp._matrix[i] = static_cast<T>(*b);
    		++b;
    		++i;
    	}

    	*this = tmp;
    }

    /**
	    @brief Conversion constructor (implicit/explicit)

	    The conversion constructor creates a Matrix3D<T, F> object from a
		Matrix3D<U, Q> object.
		Allows the conversion of a Matrix3D defined on one type to a Matrix3D 
		defined on a different type (where casting is possible).

	    @param other the Matrix3D of type <U, Q> from which to create the new object

	    @throw std::bad_alloc possible allocation exception
	*/
    template <typename U, typename Q>
	Matrix3D(const Matrix3D<U, Q> &other) : _matrix(nullptr), _floors(other.getFloors()), _rows(other.getRows()), _columns(other.getColumns()) {
		try {
			_matrix = new T[other.getFloors() * other.getRows() * other.getColumns()];
			for (unsigned int z = 0; z < _floors; ++z)
				for (unsigned int y = 0; y < _rows; ++y)
					for (unsigned int x = 0; x < _columns; ++x)
						(*this)(z, y, x) = static_cast<U>(other(z, y, x));
		}
		catch(...) {
			clear();
			throw;
		}
		
	}

    /**
	    @brief stream operator redefinition

	    Global function that redefines the stream operator to write a Matrix3D 
	    to an output stream.
    	The function is declared friend because we access the private data of Matrix3D.

	    @param os output stream (left operand)
	    @param m Matrix3D to write (right operand)

	    @return reference to the output stream
	*/
    friend std::ostream &operator<<(std::ostream &os, const Matrix3D &m) {
        
        os << "rows: " << m._rows << std::endl;
        os << "columns: " << m._columns << std::endl;
        os << "floors: " << m._floors << std::endl;

        os << "matrix: " << std::endl;

        for(unsigned int z = 0; z < m._floors; ++z) {

        	os << z+1 << "° floor: " << z << std::endl;

        	for(unsigned int y = 0; y < m._rows; ++y) {

        		for(unsigned int x = 0; x < m._columns; ++x)
        			os << m(z, y, x) << " ";

        		os << std::endl;
        	}

        	os << std::endl;

        }

        return os;
    }

};

/**
    @brief Global function transform

    Generic function that allows to obtain, starting from a passed Matrix3D, 
    a new matrix on whose elements a specific functor, also passed, has been applied. 
    The type T of the return 3D Matrix, normally the one returned by the passed functor, 
    must be specified by the caller.
	It is also possible to specify the type of functor H used for the equality operator 
	of the return matrix.

    @param A the starting 3D matrix
    @param functor the functor to apply to the data in the cells of the 3D array

    @return the 3D matrix obtained by applying the functor to the data of the starting matrix
*/
template <typename Q, typename F, typename H = default_functor<Q>, typename G, typename T>
Matrix3D<Q> trasform(const Matrix3D<T, G> &A) {

	Matrix3D<Q, H> B(A.getFloors(), A.getRows(), A.getColumns());

	F functor;

	for (unsigned int z = 0; z < A.getFloors(); ++z)
		for (unsigned int y = 0; y < A.getRows(); ++y)
			for (unsigned int x = 0; x < A.getColumns(); ++x)
				B(z, y, x) = functor(A(z, y, x));

	return B;
}


#endif