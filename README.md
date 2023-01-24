# Matrice 3D
> A template class representing a 3D matrix data structure for any type of data written in C++.

The three-dimensional array has been implemented as a template class having 5 data members:

```cpp
- T* _matrix;
- unsigned int _floors;
- unsigned int _rows;
- unsigned int_columns;
- F _equals;
```

Where `_matrix` is the array that will be generated dynamically when the object is constructed and which will contain the data of the matrix, `_floor`, `_rows` and `_column` are the 3 dimensions of the matrix and `_equals` is a functor whose type can be specified when creating an object `Matrix3D`, and which is used to test the equality of individual data of type `T` in the `operator==`.

_Note: it is possible not to specify the functor when instantiating a Matrix3D object by specifying instead only the data type: in that case a template functor using the `==` operator is used as the default value, but it is therefore necessary that in case the type passed is a possible custom type, it redefines this operator in turn. The ability to specify it was added to make the class more flexible._

Logically, therefore, the three-dimensional matrix is broken down into cells which are then reassembled into a single long array containing the data. So, to give a minimal example, like this:

![Matrix implementation logic](screenshots/matrix.png?raw=true "Matrix implementation logic")

The size of the array thus composed is equal to the total number of cells, and therefore to the product of the 3 dimensions of the matrix.
In order to access the right data based on its three-dimensional coordinates, it is therefore necessary to carry out a simple calculation which allows, starting from the 3 given coordinates, to go back to the single index necessary to find the data in the array.

Let's take for example the box present in the 2nd floor, in the 2nd row and in the 1st column and therefore of place `(1, 1, 0)`, which in the array is at index 7.
Looking at the graph, it is easy to understand how, to find the index of the data in the array, you have to add:
- all previous rows in the same plane (number given by the index of the row in which it is located) multiplied by the number of columns of the matrix (and so the cells that are in each row)
- all floors preceding the one in which the data is found (number given by the index of the floor in which it is found), multiplied by the number of cells they contain which is given by the multiplication of the 2 dimensions, therefore `rows*columns`.

In this way it is possible to find the number of boxes preceding the row in which the data is in the array, to which by finally adding the remaining index of the corresponding column, one reaches the very cell containing the data one was looking for.

The calculation then turns out to be: 

$$i_{array}=(i_{floor}*n_{rows}*n_{columns})+(i_{row}*n_{columns})+i_{column}$$

As confirmation, the element at indices `(1, 1, 0)` is found in the array in position `(1*2*2) + (1*2) + 1 = 4 + 3 + 1 = 7`, as previously mentioned.

## Fundamental methods
### Default manufacturer
The default constructor creates an empty `Matrix3D` object simply by setting the values of the 3 dimensions to `0` and the array pointer to `nullptr`.
### Copy constructor
The copy constructor takes as input another `Matrix3D` object to be copied as a constant reference for efficiency reasons, after which it creates a new identical but distinct object by setting the dimensions to the dimensions of the passed `Matrix3D`, dynamically allocating an array that has a total size equal to the product of the size of the passed matrix and copying the data one by one from the `_matrix` array of the passed matrix into the newly allocated array.
Since both `new` (although rarely) and copying the data into the newly allocated array may fail (since the data type may be a custom type and the type-redefined assignment operator is not guaranteed to be safe, but it may allocate memory or needing resources and therefore throwing exceptions), these 2 operations are inserted in a try catch block which, in addition to re-throwing the exception to the caller, returns the matrix to a coherent state, canceling any changes made by relying on a `clear()` function defined in the classroom.
### Assignment operator
The assignment operator takes as input parameter another `Matrix3D` object as a constant reference for efficiency reasons, as for the copy constructor. After checking that the object being assigned to is not the same one you are trying to assign, it creates a temporary `Matrix3D` copy of the passed one using the copy constructor, after which it relies on a `swap()` function which calls on `this` by passing the temporary array as a parameter. The latter takes care of exchanging member data between the 2 objects. Finally, it returns the dereference of the this pointer to the object.
### Destroyer
Called whenever a `Matrix3D` object needs to be destroyed, it does nothing but call the `clear()` function in turn.

## Getters
Getters are methods that allow you to obtain the dimensions of a `Matrix3D` object. They are all `const` methods in that none of the methods modify the state of the array but simply return a copy of a specific data member related to a dimension.
1. **getFloors():** returns the number of floors of a matrix.
2. **getRows():** returns the number of rows of a matrix
3. **getColumns():** returns the number of columns of a matrix.

## Secondary constructors
### Secondary constructor (z, y, x)
This secondary constructor takes the 3 dimensions of the matrix as input parameter and creates a `Matrix3D` object by allocating a dynamic array whose dimension is equal to the product of the 3 dimensions passed.
For the same reasons listed above, `new` is placed in a try catch block.
However, the constructor leaves the data in the cells uninitialized.
### Secondary constructor (z, y, x, value)
This secondary constructor does everything the previous one does, but in addition it has as a fourth parameter a constant reference to a value of type `T` which it uses to initialize the matrix, assigning it to all its cells.
For the same reasons listed for the copy constructor, `new` and assignments are also placed in a try catch block.

## Required member functions:
### Conversion Constructor
The constructor in question is a template constructor, which takes as input another 3D matrix of any type as a constant reference, then creates the new matrix of type `<T, F>` setting its dimensions to those of the passed matrix and allocating even memory to that used by the passed matrix.
Finally, he fills it with the data of the passed matrix converted to type `T` via static_cast, using the data access operator through the 3 indexes that identify the position of a cell.
The dimensions of the passed array are obtained through the public getters as it is considered a different data type (since it could be of any type).
As with the copy constructor, memory allocation and assignment are inside a try catch block, which returns the array to a consistent state in case new, assignment, or conversion to type `T` fails .
### Getter/setter of data in a cell [operator()(z, y, x)]
The getter/setter retrieves the data from the vector `_matrix` given member by calculating its index based on the dimensions passed through the previously specified calculation, and returns it to the caller as a reference for efficiency reasons, as the data type can be any.
It is assumed that no coordinates negative or greater than the maximum ones of the matrix on which it is applied are passed for a correct use of the class and therefore there are some assertions in this regard.
There is an identical constant version (const) which acts as a getter only to allow its use also on constant 3D Matrixes.
### slice(int z1, int z2, int y1, int y2, int x1, int x2)
This function takes as input a set of coordinates formed by 6 integers, which in order correspond to:
- `z1`: coordinate of the plane from which to start cutting
- `z2`: coordinate of the plane from which to start cutting
- `y1`: coordinate of the line from which to start cutting
- `y2`: coordinate of the line from which to start cutting
- `x1`: coordinate of the column from which to start cutting
- `x2`: coordinate of the column from which to start cutting

Logically, the function must return an array that is the part of the array it is applied to that is between the passed coordinates, including the end coordinates.
It then creates a matrix with dimensions equal to `(z2-z1+1, y2-y1+1, x2-x1+1)`, which it fills with the corresponding data taken from the starting matrix, and returns it to the caller.
The assignment can fail, but on failure and throwing an exception the array is not returned and the object it was called on is not changed, so there is no need to return it to a consistent state.
The function is const in that it does not change the state of the object on which it is called.
It is assumed that no coordinates negative or greater than the maximum ones of the matrix on which it is applied are passed. It is also assumed that no start coordinates greater than the end coordinates are passed for correct use of the class. Therefore, there are assertions in this regard.
### Equality operator [operator==(const Matrix3D &other)]
Operator that takes as input a `Matrix3D` other as a constant reference, and that if the object with which it is being compared is different from itself, checks that the 2 matrixes have the same data in all the corresponding cells. If so, it returns `true`, vice versa `false`. If the object passed in is also the one it is being compared to, it returns `true` directly. The function must obviously be called on matrixes with identical dimensions in order to carry out the comparison, therefore within the method there is an assert that controls this, as calling the function on 2 matrixes of different dimensions is considered an incorrect use of the class.
### 5.fill()
Template function that takes as input 2 iterators of any type that indicate the start and end of a data sequence.
With the `fill` function it is possible to fill a matrix with the data of the sequence identified by the iterators, starting from the first cell of the matrix.
The function is programmed to fill the matrix on which it is applied in any case, in case the sequence of data is less than the number of cells the filling stops when there is no more data to insert in the matrix, in the case in which instead the data sequence is greater than the number of cells, the fill fills the array up to its last cell, leaving out the rest of the data in the sequence.
In the simplest case where the data sequence has the same size as the number of cells in the array, the array is completely filled with the entire data sequence.
Since the passed iterators can point to any data type, during the assignment of the data to the cell of the matrix, a static cast is first made to the data `T` that the matrix can contain.
The function does not directly fill the matrix it is called on, but creates a temporary copy matrix starting from `*this`, fills that, then assigns it to `*this` itself. This is necessary so that in case the assignment fails or the conversion is not possible, the original matrix remains in its previous state.

## Required global functions:
### transform(const Matrix3D<T, G> &A)
Template global function that has 5 typenames, which correspond respectively to the type of data contained by the matrix to return, to the type of the functor to be used on the passed matrix for data transformation, the type of functor of the return matrix (if not specified, it uses again the default one), that of the passed 3D matrix and its data type (being passed as a parameter, the latter 2 are automatically deduced by the compiler).
The function instantiates a functor of the type passed, and creates a new matrix with the same dimensions as the matrix passed but of the type to be returned passed, after which it assigns it all the data present in the matrix passed after applying the functor to it.
Finally returns the matrix thus created.

## Iterators
Given the nature of the data structure, the iterators implemented are of the **random access iterator** type.
Since the internal structure of the `Matrix3D` class is an array, the implementation was done using the pointer trick whereby it is sufficient to remap the `iterator` and `const_iterator` types with `typedef` to pointers to the template data type, and then implement the `begin()` and `end()` functions which expose the iterators of start and end of the data sequence correctly, making them respectively return the pointer to the first data of the array, already present as data member (`_matrix`), and the one pointing to the end of the sequence of data data, i.e. to the cell following the last cell in the array. The position of the last cell corresponds to the initial position to which the size of the array is added (product of the 3 dimensions).
Although this cell is not part of the matrix array and it is not known what data it contains, this is perfectly safe, as the pointer returned by the `end()` function will only be used for comparisons to understand when the end of the sequence has been reached, and will never be dereferenced.

## Support member functions:
### swap()
The function takes as input a 3D matrix as a reference for efficiency reasons, and exploits the `swap` function of the language present in the standard algorithm library to exchange the member data of the passed matrix with those of the object on which it is called.
### clear()
The function empties the `Matrix3D` object on which it is called, deallocating any memory allocated calling `delete[]` on the array pointer, setting the aforementioned pointer to `nullptr` and resetting the 3 dimensions to `0`.
### Inequality operator [operator!=(const Matrix3D &other)]
Not required but easily implemented, it relies on the equality operator and returns the opposite result.

## Other global functions implemented
### stream operator (operator<<)
The redefinition of the stream operator allows direct printing on a stream of a 3D matrix, printing its dimensions and each floor of the matrix with the data it contains.
It is implemented as a global `friend` function of the class in order to directly access the member data of the matrix to be printed.

## Test:
In the `main.cpp` file various tests were carried out on both primitive and custom data for each of the methods listed.

## Information:
The executable has been successfully compiled and tested with no compile or memory errors on Linux Mint 64-bit with the following versions of:
- g++: 9.4.0
- valgrind: 3.15.0
- doxygen: 1.8.17