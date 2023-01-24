#include <iostream>
#include <algorithm>

#include "Matrix3D.h"

using namespace std;

struct customType {

    int _a;
    double _b;
    char _c;

    customType() : _a(0), _b(0), _c('a') {}

    customType(int a, double b, char c) : _a(a), _b(b), _c(c) {};

    customType(const customType &other) {
        _a = other._a;
        _b = other._b;
        _c = other._c;
    }

    customType(char c) : _a(0), _b(0), _c(c) {}

    customType &operator=(const customType &other) {
        if(this!=&other) {
            customType tmp(other);
            swap(_a, tmp._a);
            swap(_b, tmp._b);
            swap(_c, tmp._c);
        }

        return *this;
    }

    ~customType() {};

    bool operator==(const customType &other) const {
        return _a == other._a && _b == other._b && _c == other._c;
    }

    bool operator!=(const customType &other) const {
        return !(*this == other);
    }

    friend ostream &operator<<(std::ostream &os, const customType &custom) {
        
        os << "(" << custom._a << "," << custom._b << "," << custom._c << ")";

        return os;
    }

    void increase(int a, double b, int c) {
        _a += a;
        _b += b;
        _c += c;

    }

    void init(int a, double b, char c) {
        _a = a;
        _b = b;
        _c = c;
    }

};

void test_default_constructor() {

    // COSTRUTTORE DI DEFAULT

    cout << "---- COSTRUTTORE DI DEFAULT ----" << endl;

    Matrix3D<int> mat_int;
    assert(mat_int.getFloors() == 0 && mat_int.getRows() == 0 && mat_int.getColumns() == 0);

    Matrix3D<char> mat_char;
    assert(mat_char.getFloors() == 0 && mat_char.getRows() == 0 && mat_char.getColumns() == 0);

    Matrix3D<customType> mat_custom;
    assert(mat_custom.getFloors() == 0 && mat_custom.getRows() == 0 && mat_custom.getColumns() == 0);

    cout << endl;
}

void test_secondary_constructor() {

    // COSTRUTTORE SECONDARIO

    cout << "---- COSTRUTTORE SECONDARIO ----" << endl;

    Matrix3D<int> uninitialized_mat_int(3, 3, 3);
    assert(uninitialized_mat_int.getFloors() == 3 && uninitialized_mat_int.getRows() == 3 && uninitialized_mat_int.getColumns() == 3);

    Matrix3D<char> uninitialized_mat_char(1, 10, 20);
    assert(uninitialized_mat_char.getFloors() == 1 && uninitialized_mat_char.getRows() == 10 && uninitialized_mat_char.getColumns() == 20);

    Matrix3D<customType> uninitialized_mat_custom(2, 3, 10);
    assert(uninitialized_mat_custom.getFloors() == 2 && uninitialized_mat_custom.getRows() == 3 && uninitialized_mat_custom.getColumns() == 10);

    cout << endl;
}

void test_secondary_constructor_with_init() {

    // COSTRUTTORE SECONDARIO CON INIZIALIZZAZIONE

    cout << "---- COSTRUTTORE SECONDARIO CON INIZIALIZZAZIONE ----" << endl;

    bool value_correctly_initialized = true;

    Matrix3D<int> initialized_mat_int(3, 3, 3, 0);
    assert(initialized_mat_int.getFloors() == 3 && initialized_mat_int.getRows() == 3 && initialized_mat_int.getColumns() == 3);

    value_correctly_initialized = true;
    for (int z = 0; z < initialized_mat_int.getFloors(); ++z)
        for (int y = 0; y < initialized_mat_int.getRows(); ++y)
            for (int x = 0; x < initialized_mat_int.getColumns(); ++x)
                if(initialized_mat_int(z, y, x) != 0)
                    value_correctly_initialized = false;

    assert(value_correctly_initialized);

    cout << "Stampa della Matrix3D<int> dopo costruttore di inizializzazione con valore 0" << endl;
    cout << initialized_mat_int << endl;


    Matrix3D<int> initialized_mat_int_five(3, 3, 3, 5);
    assert(initialized_mat_int_five.getFloors() == 3 && initialized_mat_int_five.getRows() == 3 && initialized_mat_int_five.getColumns() == 3);

    value_correctly_initialized = true;
    for (int z = 0; z < initialized_mat_int_five.getFloors(); ++z)
        for (int y = 0; y < initialized_mat_int_five.getRows(); ++y)
            for (int x = 0; x < initialized_mat_int_five.getColumns(); ++x)
                if(initialized_mat_int_five(z, y, x) != 5)
                    value_correctly_initialized = false;

    assert(value_correctly_initialized);

    cout << "Stampa della Matrix3D<int> dopo costruttore di inizializzazione con valore 5" << endl;
    cout << initialized_mat_int_five << endl;


    Matrix3D<char> initialized_mat_char(1, 10, 20, 'f');
    assert(initialized_mat_char.getFloors() == 1 && initialized_mat_char.getRows() == 10 && initialized_mat_char.getColumns() == 20);

    value_correctly_initialized = true;
    for (int z = 0; z < initialized_mat_char.getFloors(); ++z)
        for (int y = 0; y < initialized_mat_char.getRows(); ++y)
            for (int x = 0; x < initialized_mat_char.getColumns(); ++x)
                if(initialized_mat_char(z, y, x) != 'f')
                    value_correctly_initialized = false;

    assert(value_correctly_initialized);

    cout << "Stampa della Matrix3D<char> dopo costruttore di inizializzazione con valore 'f'" << endl;
    cout << initialized_mat_char << endl;


    customType custom(8, 42, 'x');

    Matrix3D<customType> initialized_mat_custom(2, 3, 10, custom);
    assert(initialized_mat_custom.getFloors() == 2 && initialized_mat_custom.getRows() == 3 && initialized_mat_custom.getColumns() == 10);

    value_correctly_initialized = true;
    for (int z = 0; z < initialized_mat_custom.getFloors(); ++z)
        for (int y = 0; y < initialized_mat_custom.getRows(); ++y)
            for (int x = 0; x < initialized_mat_custom.getColumns(); ++x)
                if(initialized_mat_custom(z, y, x) != custom)
                    value_correctly_initialized = false;

    assert(value_correctly_initialized);

    cout << "Stampa della Matrix3D<customType> dopo costruttore di inizializzazione con valore " << custom << endl;
    cout << initialized_mat_custom << endl;

    cout << endl;
}

void test_copy_constructor() {

    // COPY CONSTRUCTOR

    cout << "---- COPY CONSTRUCTOR ----" << endl;

    Matrix3D<int> initialized_mat_int(3, 3, 3, 0);
    Matrix3D<char> initialized_mat_char(1, 10, 20, 'f');
    customType custom(8, 42, 'x');
    Matrix3D<customType> initialized_mat_custom(2, 3, 10, custom);


    Matrix3D<int> copy_mat_int(initialized_mat_int);
    assert(copy_mat_int.getFloors() == initialized_mat_int.getFloors() 
        && copy_mat_int.getRows() == initialized_mat_int.getRows() 
        && copy_mat_int.getColumns() == initialized_mat_int.getColumns());

    assert(copy_mat_int == initialized_mat_int);

    cout << "Stampa della Matrix3D<int> creata a partire dalla precedente" << endl;
    cout << copy_mat_int << endl;


    Matrix3D<char> copy_mat_char(initialized_mat_char);
    assert(copy_mat_char.getFloors() == initialized_mat_char.getFloors() 
        && copy_mat_char.getRows() == initialized_mat_char.getRows() 
        && copy_mat_char.getColumns() == initialized_mat_char.getColumns());

    assert(copy_mat_char == initialized_mat_char);

    cout << "Stampa della Matrix3D<char> creata a partire dalla precedente" << endl;
    cout << copy_mat_char << endl;


    Matrix3D<customType> copy_mat_custom(initialized_mat_custom);
    assert(copy_mat_custom.getFloors() == initialized_mat_custom.getFloors() 
        && copy_mat_custom.getRows() == initialized_mat_custom.getRows() 
        && copy_mat_custom.getColumns() == initialized_mat_custom.getColumns());

    assert(copy_mat_custom == initialized_mat_custom);

    cout << "Stampa della Matrix3D<customType> creata a partire dalla precedente" << endl;
    cout << copy_mat_custom << endl;

    cout << endl;
}

void test_assignment_operator() {

    // OPERATORE D'ASSEGNAMENTO

    cout << "---- OPERATORE D'ASSEGNAMENTO ----" << endl;

    Matrix3D<int> initialized_mat_int(3, 3, 3, 0);
    Matrix3D<char> initialized_mat_char(1, 10, 20, 'f');
    customType custom(8, 42, 'x');
    Matrix3D<customType> initialized_mat_custom(2, 3, 10, custom);


    Matrix3D<int> assigned_mat_int;
    assigned_mat_int = initialized_mat_int;
    assert(assigned_mat_int.getFloors() == initialized_mat_int.getFloors() 
        && assigned_mat_int.getRows() == initialized_mat_int.getRows() 
        && assigned_mat_int.getColumns() == initialized_mat_int.getColumns());

    assert(assigned_mat_int == initialized_mat_int);

    cout << "Stampa della Matrix3D<int> a cui è stata assegnata la precedente" << endl;
    cout << assigned_mat_int << endl;

    Matrix3D<char> assigned_mat_char;
    assigned_mat_char = initialized_mat_char;
    assert(assigned_mat_char.getFloors() == initialized_mat_char.getFloors() 
        && assigned_mat_char.getRows() == initialized_mat_char.getRows() 
        && assigned_mat_char.getColumns() == initialized_mat_char.getColumns());

    assert(assigned_mat_char == initialized_mat_char);

    cout << "Stampa della Matrix3D<char> a cui è stata assegnata la precedente" << endl;
    cout << assigned_mat_char << endl;

    Matrix3D<customType> assigned_mat_custom;
    assigned_mat_custom = initialized_mat_custom;
    assert(assigned_mat_custom.getFloors() == initialized_mat_custom.getFloors() 
        && assigned_mat_custom.getRows() == initialized_mat_custom.getRows() 
        && assigned_mat_custom.getColumns() == initialized_mat_custom.getColumns());

    assert(assigned_mat_custom == initialized_mat_custom);

    cout << "Stampa della Matrix3D<customType> a cui è stata assegnata la precedente" << endl;
    cout << assigned_mat_custom << endl;

    cout << endl;
}

void test_getter_setter() {

    // ACCESSO IN LETTURA E SCRITTURA SULLA (Z, Y, X)-ESIMA CELLA

    cout << "---- ACCESSO IN LETTURA E SCRITTURA SULLA (Z, Y, X)-ESIMA CELLA ----" << endl;

    Matrix3D<int> initialized_mat_int(3, 3, 3, 0);
    Matrix3D<char> initialized_mat_char(1, 10, 20, 'f');
    customType custom(8, 42, 'x');
    Matrix3D<customType> initialized_mat_custom(2, 3, 10, custom);


    initialized_mat_int(1, 1, 1) = 5;
    assert(initialized_mat_int(1, 1, 1) == 5);
    cout << "Stampa della Matrix3D<int> a cui è stato modificato il valore in posizione (1, 1, 1) in 0" << endl;
    cout << initialized_mat_int << endl;

    initialized_mat_char(0, 4, 7) = 'x';
    assert(initialized_mat_char(0, 4, 7) == 'x');
    cout << "Stampa della Matrix3D<char> a cui è stato modificato il valore in posizione (0, 4, 7) in 'x'" << endl;
    cout << initialized_mat_char << endl;

    customType custom_zero(0, 0.0, 'O');

    initialized_mat_custom(1, 2, 9) = custom_zero;
    assert(initialized_mat_custom(1, 2, 9) == custom_zero);
    cout << "Stampa della Matrix3D<customType> a cui è stato modificato il valore in posizione (1, 2, 9) in " << custom_zero << endl;
    cout << initialized_mat_custom << endl;

    cout << endl;
}

void test_slice() {

    // SLICE

    cout << "---- SLICE ----" << endl;

    Matrix3D<int> initialized_mat_int(3, 3, 3, 0);
    Matrix3D<char> initialized_mat_char(1, 10, 20, 'f');
    customType custom(8, 42, 'x');
    Matrix3D<customType> initialized_mat_custom(2, 3, 10, custom);

    initialized_mat_int(1, 1, 1) = 5;
    initialized_mat_char(0, 4, 7) = 'x';
    customType custom_zero(0, 0.0, 'O');
    initialized_mat_custom(1, 2, 9) = custom_zero;


    Matrix3D<int> sliced_mat_int = initialized_mat_int.slice(1, 2, 0, 1, 0, 2);
    assert(sliced_mat_int.getFloors() == 2 && sliced_mat_int.getRows() == 2 && sliced_mat_int.getColumns() == 3);
    cout << "Stampa della Matrix3D<int> slice-ata agli indici (1, 2, 0, 1, 0, 2) dalla matrice precedente" << endl;
    cout << sliced_mat_int << endl;

    Matrix3D<char> sliced_mat_char = initialized_mat_char.slice(0, 0, 3, 6, 5, 12);
    assert(sliced_mat_char.getFloors() == 1 && sliced_mat_char.getRows() == 4 && sliced_mat_char.getColumns() == 8);
    cout << "Stampa della Matrix3D<char> slice-ata agli indici (0, 0, 3, 6, 5, 12) dalla matrice precedente" << endl;
    cout << sliced_mat_char << endl;

    Matrix3D<customType> sliced_mat_custom = initialized_mat_custom.slice(1, 1, 1, 2, 5, 9);
    assert(sliced_mat_custom.getFloors() == 1 && sliced_mat_custom.getRows() == 2 && sliced_mat_custom.getColumns() == 5);
    cout << "Stampa della Matrix3D<customType> slice-ata agli indici (1, 1, 1, 2, 5, 9) dalla matrice precedente" << endl;
    cout << sliced_mat_custom << endl;

    cout << endl;
}

void increasing_matrixes_with_getter() {

    // INCREASING MATRIXES WITH GETTER

    cout << "---- INCREASING MATRIXES WITH GETTER ----" << endl;

    Matrix3D<int> increasing_mat_int(2, 5, 5);

    int j = 0;

    for (int z = 0; z < increasing_mat_int.getFloors(); ++z)
        for (int y = 0; y < increasing_mat_int.getRows(); ++y)
            for (int x = 0; x < increasing_mat_int.getColumns(); ++x) {
                increasing_mat_int(z, y, x) = j;
                ++j;
            }

    cout << "Stampa della Matrix3D<int> crescente creata tramite getter/setter che parte da 0" << endl;
    cout << increasing_mat_int << endl;


    Matrix3D<char> increasing_mat_char(2, 5, 5);

    char c = 'a';

    for (int z = 0; z < increasing_mat_char.getFloors(); ++z)
        for (int y = 0; y < increasing_mat_char.getRows(); ++y)
            for (int x = 0; x < increasing_mat_char.getColumns(); ++x) {
                increasing_mat_char(z, y, x) = c;
                ++c;
            }

    cout << "Stampa della Matrix3D<char> crescente creata tramite getter/setter che parte da 'a'" << endl;
    cout << increasing_mat_char << endl;


    Matrix3D<customType> increasing_mat_custom(2, 5, 5);

    customType custom_to_increase(0, 0, 'a');

    for (int z = 0; z < increasing_mat_custom.getFloors(); ++z)
        for (int y = 0; y < increasing_mat_custom.getRows(); ++y)
            for (int x = 0; x < increasing_mat_custom.getColumns(); ++x) {
                increasing_mat_custom(z, y, x) = custom_to_increase;
                custom_to_increase.increase(1, -0.1, 1);
            }

    cout << "Stampa della Matrix3D<customType> crescente creata tramite getter/setter che parte da (0, 0, 'a')" << endl;
    cout << increasing_mat_custom << endl;

    cout << endl;
}

void increasing_matrixes_with_iterators() {

    // INCREASING MATRIXES WITH ITERATORS (PRINTED AS A SEQUENCE THROUGH ITERATORS AS WELL)

    cout << "---- INCREASING MATRIXES WITH ITERATORS (PRINTED AS A SEQUENCE THROUGH ITERATORS AS WELL) ----" << endl;

    Matrix3D<int> iterators_mat_int(2, 5, 5);
    
    int j = 0;

    for (Matrix3D<int>::iterator i = iterators_mat_int.begin(); i != iterators_mat_int.end(); ++i) {
        (*i) = j;
        ++j;
    }

    // stampo diversamente per distinguerle da quelle riempite con il getter

    cout << "Stampa della Matrix3D<int> crescente creata tramite iteratori che parte da 0" << endl;
    for (Matrix3D<int>::iterator i = iterators_mat_int.begin(); i != iterators_mat_int.end(); ++i) {
        cout << (*i) << " ";
    }
    cout << endl << endl;


    Matrix3D<char> iterators_mat_char(2, 5, 5);
    
    char c = 'a';

    for (Matrix3D<char>::iterator i = iterators_mat_char.begin(); i != iterators_mat_char.end(); ++i) {
        (*i) = c;
        ++c;
    }

    cout << "Stampa della Matrix3D<char> crescente creata tramite iteratori che parte da 'a'" << endl;
    for (Matrix3D<char>::iterator i = iterators_mat_char.begin(); i != iterators_mat_char.end(); ++i) {
        cout << (*i) << " ";
    }
    cout << endl << endl;


    Matrix3D<customType> iterators_mat_custom(2, 5, 5);

    customType custom_to_increase(0, 0, 'a');

    for (Matrix3D<customType>::iterator i = iterators_mat_custom.begin(); i != iterators_mat_custom.end(); ++i) {
        (*i) = custom_to_increase;
        custom_to_increase.increase(1, -0.1, 1);
    }

    cout << "Stampa della Matrix3D<customType> crescente creata tramite iteratori che parte da (0, 0, 'a')" << endl;
    for (Matrix3D<customType>::iterator i = iterators_mat_custom.begin(); i != iterators_mat_custom.end(); ++i) {
        cout << (*i) << " ";
    }
    cout << endl << endl;

    cout << endl;
}

void test_comparison_operators() {

    // OPERATORE DI CONFRONTO (==)

    cout << "---- OPERATORE DI CONFRONTO (==) ----" << endl;

    Matrix3D<int> increasing_mat_int(2, 5, 5);
    int j = 0;
    for (int z = 0; z < increasing_mat_int.getFloors(); ++z)
        for (int y = 0; y < increasing_mat_int.getRows(); ++y)
            for (int x = 0; x < increasing_mat_int.getColumns(); ++x) {
                increasing_mat_int(z, y, x) = j;
                ++j;
            }


    Matrix3D<char> increasing_mat_char(2, 5, 5);
    char c = 'a';
    for (int z = 0; z < increasing_mat_char.getFloors(); ++z)
        for (int y = 0; y < increasing_mat_char.getRows(); ++y)
            for (int x = 0; x < increasing_mat_char.getColumns(); ++x) {
                increasing_mat_char(z, y, x) = c;
                ++c;
            }


    Matrix3D<customType> increasing_mat_custom(2, 5, 5);
    customType custom_to_increase(0, 0, 'a');
    for (int z = 0; z < increasing_mat_custom.getFloors(); ++z)
        for (int y = 0; y < increasing_mat_custom.getRows(); ++y)
            for (int x = 0; x < increasing_mat_custom.getColumns(); ++x) {
                increasing_mat_custom(z, y, x) = custom_to_increase;
                custom_to_increase.increase(1, -0.1, 1);
            }


    Matrix3D<int> iterators_mat_int(2, 5, 5);
    j = 0;
    for (Matrix3D<int>::iterator i = iterators_mat_int.begin(); i != iterators_mat_int.end(); ++i) {
        (*i) = j; ++j;
    }

    Matrix3D<char> iterators_mat_char(2, 5, 5);
    c = 'a';
    for (Matrix3D<char>::iterator i = iterators_mat_char.begin(); i != iterators_mat_char.end(); ++i) {
        (*i) = c; ++c;
    }

    Matrix3D<customType> iterators_mat_custom(2, 5, 5);
    custom_to_increase.init(0, 0, 'a');
    for (Matrix3D<customType>::iterator i = iterators_mat_custom.begin(); i != iterators_mat_custom.end(); ++i) {
        (*i) = custom_to_increase;
        custom_to_increase.increase(1, -0.1, 1);
    }



    Matrix3D<int> edited_mat_int(increasing_mat_int);
    edited_mat_int(0, 2, 2) = 0;

    assert(increasing_mat_int == iterators_mat_int);
    assert(increasing_mat_int == increasing_mat_int);
    assert(increasing_mat_int != edited_mat_int);
    assert(increasing_mat_int != increasing_mat_char);

    cout << "Stampa del controllo di uguaglianza tra le Matrici3D<int> crescenti create con getter/setter e iteratori" << endl;
    cout << (increasing_mat_int == iterators_mat_int) << endl;
    cout << "Stampa del controllo di uguaglianza di una Matrix3D<int> crescente con sè stessa" << endl;
    cout << (increasing_mat_int == increasing_mat_int) << endl;
    cout << "Stampa del controllo di uguaglianza tra una Matrix3D<int> crescente e una sua copia modificata" << endl;
    cout << (increasing_mat_int == edited_mat_int) << endl;
    // qui entra in gioco la conversione automatica ma i numeri nella matrice non corrispondono ai numeri ottenuti castando i char a int
    cout << "Stampa del controllo di uguaglianza tra una Matrix3D<int> crescente e una Matrix3D<char> crescente" << endl;
    cout << (increasing_mat_int == increasing_mat_char) << endl;

    cout << endl;


    Matrix3D<char> edited_mat_char(increasing_mat_char);
    edited_mat_char(0, 2, 2) = '0';

    assert(increasing_mat_char == iterators_mat_char);
    assert(increasing_mat_char == increasing_mat_char);
    assert(increasing_mat_char != edited_mat_char);
    assert(increasing_mat_char != increasing_mat_int);

    cout << "Stampa del controllo di uguaglianza tra le Matrici3D<char> crescenti create con getter/setter e iteratori" << endl;
    cout << (increasing_mat_char == iterators_mat_char) << endl;
    cout << "Stampa del controllo di uguaglianza di una Matrix3D<char> crescente con sè stessa" << endl;
    cout << (increasing_mat_char == increasing_mat_char) << endl;
    cout << "Stampa del controllo di uguaglianza tra una Matrix3D<char> crescente e una sua copia modificata" << endl;
    cout << (increasing_mat_char == edited_mat_char) << endl;
    cout << "Stampa del controllo di uguaglianza tra una Matrix3D<char> crescente e una Matrix3D<int> crescente" << endl;
    cout << (increasing_mat_char == increasing_mat_int) << endl;

    cout << endl;


    Matrix3D<customType> edited_mat_custom(increasing_mat_custom);
    customType custom_zero(0, 0.0, 'O');
    edited_mat_custom(0, 2, 2) = custom_zero;

    assert(increasing_mat_custom == iterators_mat_custom);
    assert(increasing_mat_custom == increasing_mat_custom);
    assert(increasing_mat_custom != edited_mat_custom);
    assert(increasing_mat_custom != increasing_mat_char);

    cout << "Stampa del controllo di uguaglianza tra le Matrici3D<customType> crescenti create con getter/setter e iteratori" << endl;
    cout << (increasing_mat_custom == iterators_mat_custom) << endl;
    cout << "Stampa del controllo di uguaglianza di una Matrix3D<customType> crescente con sè stessa" << endl;
    cout << (increasing_mat_custom == increasing_mat_custom) << endl;
    cout << "Stampa del controllo di uguaglianza tra una Matrix3D<customType> crescente e una sua copia modificata" << endl;
    cout << (increasing_mat_custom == edited_mat_custom) << endl;
    cout << "Stampa del controllo di uguaglianza tra una Matrix3D<customType> crescente e una Matrix3D<char> crescente" << endl;
    cout << (increasing_mat_custom == increasing_mat_char) << endl;

    cout << endl;
}

void test_fill() {

    // FILL

    cout << "---- FILL ----" << endl;

    Matrix3D<int> increasing_mat_int(2, 5, 5);
    int j = 0;
    for (Matrix3D<int>::iterator i = increasing_mat_int.begin(); i != increasing_mat_int.end(); ++i) {
        (*i) = j; ++j;
    }

    Matrix3D<char> increasing_mat_char(2, 5, 5);
    char c = 'a';
    for (Matrix3D<char>::iterator i = increasing_mat_char.begin(); i != increasing_mat_char.end(); ++i) {
        (*i) = c; ++c;
    }

    Matrix3D<customType> increasing_mat_custom(2, 5, 5);
    customType custom_to_increase(0, 0, 'a');
    for (Matrix3D<customType>::iterator i = increasing_mat_custom.begin(); i != increasing_mat_custom.end(); ++i) {
        (*i) = custom_to_increase;
        custom_to_increase.increase(1, -0.1, 1);
    }


    Matrix3D<int> filled_mat_int(1, 5, 5);

    filled_mat_int.fill(increasing_mat_int.begin(), increasing_mat_int.end());

    cout << "Stampa della Matrix3D<int> (1, 5, 5) riempita con valori presi dalla matrice crescente" << endl;
    cout << filled_mat_int << endl;


    Matrix3D<char> filled_mat_char(1, 5, 5);

    cout << "Stampa della Matrix3D<char> (1, 5, 5) riempita con valori presi dalla matrice crescente" << endl;
    filled_mat_char.fill(increasing_mat_char.begin(), increasing_mat_char.end());

    cout << filled_mat_char << endl;


    Matrix3D<customType> filled_mat_custom(1, 5, 5);

    cout << "Stampa della Matrix3D<customType> (1, 5, 5) riempita con valori presi dalla matrice crescente" << endl;
    filled_mat_custom.fill(increasing_mat_custom.begin(), increasing_mat_custom.end());

    cout << filled_mat_custom << endl;

    cout << endl;
}

void test_trasform() {

    // TRASFORM

    cout << "---- TRASFORM ----" << endl;

    Matrix3D<int> increasing_mat_int(2, 5, 5);
    int j = 0;
    for (Matrix3D<int>::iterator i = increasing_mat_int.begin(); i != increasing_mat_int.end(); ++i) {
        (*i) = j; ++j;
    }


    struct tochar
    {
        char operator()(int a) {
            return static_cast<char>(a);
        }
    };

    struct weird_functor
    {
        bool operator()(char a, char b) const {
            return a > b;
        }
    };

    Matrix3D<char, weird_functor> trasformed_mat_char = trasform<char, tochar>(increasing_mat_int);

    Matrix3D<char> copy_trasformed_mat_char(trasformed_mat_char);

    assert(trasformed_mat_char != copy_trasformed_mat_char); // because it uses the weird_functor for the comparison

    for (int z = 0; z < trasformed_mat_char.getFloors(); ++z)
        for (int y = 0; y < trasformed_mat_char.getRows(); ++y)
            for (int x = 0; x < trasformed_mat_char.getColumns(); ++x) 
                assert(trasformed_mat_char(z, y, x) == static_cast<char>(increasing_mat_int(z, y, x)));

    cout << "Stampa della Matrix3D<int> crescente trasformata convertendo i suoi valori a char" << endl;
    cout << trasformed_mat_char << endl;


    struct invert
    {
        int operator()(int a) {
            return -a;
        }
    };

    Matrix3D<int> inverted_mat_int = trasform<int, invert>(increasing_mat_int);

    for (int z = 0; z < inverted_mat_int.getFloors(); ++z)
        for (int y = 0; y < inverted_mat_int.getRows(); ++y)
            for (int x = 0; x < inverted_mat_int.getColumns(); ++x) 
                assert(inverted_mat_int(z, y, x) == -increasing_mat_int(z, y, x));

    cout << "Stampa della Matrix3D<int> crescente trasformata invertendo i suoi valori di segno" << endl;
    cout << inverted_mat_int << endl;

    cout << endl;
}

void test_std_algorithm_sort() {

    // SORT (ASCENDING) - FROM STD::ALGORITHM THROUGH ITERATORS

    cout << "---- SORT (ASCENDING) - FROM STD::ALGORITHM THROUGH ITERATORS ----" << endl;

    Matrix3D<int> increasing_mat_int(2, 5, 5);
    int j = 0;
    for (Matrix3D<int>::iterator i = increasing_mat_int.begin(); i != increasing_mat_int.end(); ++i) {
        (*i) = j; ++j;
    }

    struct invert
    {
        int operator()(int a) {
            return -a;
        }
    };

    Matrix3D<int> inverted_mat_int = trasform<int, invert>(increasing_mat_int);


    sort(inverted_mat_int.begin(), inverted_mat_int.end());

    cout << "Stampa della Matrix3D<int> con valori negativi riordinata in ordine crescente" << endl;
    cout << inverted_mat_int << endl;

    cout << endl;
}

void test_conversion() {

    // CONVERSIONE

    cout << "---- CONVERSIONE IMPLICITA/ESPLICITA ----" << endl;

    Matrix3D<int> increasing_mat_int(2, 5, 5);
    int j = 0;
    for (Matrix3D<int>::iterator i = increasing_mat_int.begin(); i != increasing_mat_int.end(); ++i) {
        (*i) = j; ++j;
    }

    Matrix3D<char> increasing_mat_char(2, 5, 5);
    char c = 'a';
    for (Matrix3D<char>::iterator i = increasing_mat_char.begin(); i != increasing_mat_char.end(); ++i) {
        (*i) = c; ++c;
    }

    struct weird_functor
    {
        bool operator()(char a, char b) const {
            return a > b;
        }
    };


    // implicita
    Matrix3D<char> converted_mat_char = increasing_mat_int;

    cout << "Stampa della Matrix3D<int> convertita implicitamente a Matrix3D<char>" << endl;
    cout << converted_mat_char << endl;

    // esplicita
    converted_mat_char = static_cast<Matrix3D<char>>(increasing_mat_int);

    cout << "Stampa della Matrix3D<int> convertita esplicitamente a Matrix3D<char>" << endl;
    cout << converted_mat_char << endl;

    cout << endl;

    // implicita
    Matrix3D<customType> converted_mat_custom = increasing_mat_char;

    cout << "Stampa della Matrix3D<char> convertita implicitamente a Matrix3D<customType>" << endl;
    cout << converted_mat_custom << endl;

    // esplicita
    converted_mat_custom = static_cast<Matrix3D<char, weird_functor>>(increasing_mat_char);

    cout << "Stampa della Matrix3D<char> convertita esplicitamente a Matrix3D<customType>" << endl;
    cout << converted_mat_custom << endl;


    cout << endl;
}


int main() {

    test_default_constructor();

    test_secondary_constructor();

    test_secondary_constructor_with_init();

    test_copy_constructor();

    test_assignment_operator();

    test_getter_setter();

    test_slice();

    increasing_matrixes_with_getter();

    increasing_matrixes_with_iterators();

    test_comparison_operators();

    test_fill();

    test_trasform();

    test_std_algorithm_sort();

    test_conversion();

    return 0;

}