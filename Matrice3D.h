#ifndef OLIST_H
#define OLIST_H

#include <iostream>
#include <algorithm> //swap

#include <cassert>

/**
  @brief Classe Matrice3D

  Classe templata che implementa una matrice a 3 dimensioni di celle 
  contenete dati di tipo T.
*/

template <typename Q>
struct default_functor
{
	bool operator()(Q a, Q b) const {
		return a == b;
	}
};

template <typename T, typename F = default_functor<T>>
class Matrice3D {

	T* _matrix; ///< puntatore alla prima cella della matrice 3D

	unsigned int _floors; ///< numero di piani della matrice 3D
	unsigned int _rows; ///< numero di righe della matrice 3D
	unsigned int _columns; ///< numero di colonne della matrice 3D

	F _equals; //< funtore usato per controllare se due dati di tipo T sono uguali

public:

	/**
	    @brief Costruttore di default

	    Il costruttore di default serve a inizializzare i dati membro
	    per rappresentare una matrice 3D vuota.

	    @post _matrix = nullptr
	    @post _floors == 0
	    @post _rows == 0
	    @post _column == 0
	*/
	Matrice3D() : _matrix(nullptr), _floors(0), _rows(0), _columns(0) {}

	/**
	    @brief Costruttore secondario (z, y, x)

	    Costruttore secondario che serve a costruire una matrice 3D in base 
	    alle dimensioni date. Le celle della matrice non sono inizializzate.

	    @param z numero di piani della matrice 3D da creare
	    @param y numero di righe della matrice 3D da creare
	    @param x numero di colonne della matrice 3D da creare

	    @pre z!=0 && y!=0 && x!=0

	    @post _matrix != nullptr
	    @post _floors == z
	    @post _rows == y
	    @post _column == x

	    @throw std::bad_alloc possibile eccezione di allocazione
	*/
	Matrice3D(int z, int y, int x) : _matrix(nullptr), _floors(z), _rows(y), _columns(x) {

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
	    @brief Costruttore secondario (z, y, x, value)

	    Costruttore secondario che serve a costruire una matrice 3D in base 
	    alle dimensioni date, e che inizializza ogni cella della matrice al 
	    valore di tipo T value passato.

	    @param z numero di piani della matrice 3D da creare
	    @param y numero di righe della matrice 3D da creare
	    @param x numero di colonne della matrice 3D da creare
	    @param value valore del tipo della matrice con cui inizializzarne le celle

	    @pre z!=0 && y!=0 && x!=0

	    @post _matrix != nullptr
	    @post _floors == z
	    @post _rows == y
	    @post _column == x

	    @throw std::bad_alloc possibile eccezione di allocazione
	*/
	Matrice3D(int z, int y, int x, const T &value) : _matrix(nullptr), _floors(z), _rows(y), _columns(x) {

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

	    Costruttore di copia. Serve a creare un oggetto come copia di un 
	    altro oggetto. I due oggetti devono essere indipendenti.

	    @param other Matrice3D sorgente da copiare
	    
	    @post _matrix != nullptr
	    @post _floors == other._floors
	    @post _rows == other._rows
	    @post _column == other._column

	    @throw std::bad_alloc possibile eccezione di allocazione
	*/
	Matrice3D(const Matrice3D &other) : _matrix(nullptr), _floors(other._floors), _rows(other._rows), _columns(other._columns) {
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
	    @brief Operatore di assegnamento

	    L'operatore di assegnamento serve a copiare il contenuto di un oggetto
	    in un altro oggetto dello stesso tipo. I due oggetti devono essere
	    indipendenti.

	    @param other Matrice3D sorgenete da copiare

	    @return un reference all'oggetto corrente

	    @post _matrix != nullptr
	    @post _floors == other._floors
	    @post _rows == other._rows
	    @post _column == other._column 
	*/
	Matrice3D &operator=(const Matrice3D &other) {
		if(this != &other) {
            Matrice3D tmp(other);
            this->swap(tmp);
        }

        return *this;
	}

	/**
	    @brief Accesso al numero di piani della matrice 3D

	    Metodo per ottenere il numero di piani della matrice 3D.

    	@return numero di piani della matrice 3D
	*/
	unsigned int getFloors() const {
		return _floors;
	}

	/**
	    @brief Accesso al numero di righe della matrice 3D

	    Metodo per ottenere il numero di righe della matrice 3D.

    	@return numero di righe della matrice 3D
	*/
	unsigned int getRows() const {
		return _rows;
	}

	/**
	    @brief Accesso al numero di colonne della matrice 3D

	    Metodo per ottenere il numero di colonne della matrice 3D.

    	@return numero di colonne della matrice 3D
	*/
	unsigned int getColumns() const {
		return _columns;
	}

	/**
	    @brief Metodo swap

	    Funzione che scambia il contenuto e le dimensioni di due Matrici 3D.

	    @param other la Matrice3D con cui scambiare il contenuto
	*/
	void swap(Matrice3D &other) {
        std::swap(_matrix, other._matrix);
        std::swap(_rows, other._rows);
        std::swap(_columns, other._columns);
        std::swap(_floors, other._floors);
    }

    /**
    	@brief Metodo clear

    	Funzione che svuota la Matrice3D, deallocando la memoria allocata sullo heap,
    	e portando i dati membro ad uno stato coerente.

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
	    @brief Distruttore

	    Distruttore della classe. Il distruttore deve rimuovere tutte 
	    le risorse usate dalla classe. In questo caso l'array allocato 
	    sullo heap deve essere deallocato e gli altri dati membro vanno
	    riportati a uno stato coerente.

	    @post _matrix == nullptr
	    @post _floors == 0
	    @post _rows == 0
	    @post _column == 0
	*/
    ~Matrice3D() {
        clear();
    }

	/**
	    @brief Getter/Setter della cella (z, y, x)-esima

	    Metodo che permette di leggere e/o scrivere la cella (z, y, x)-esima della matrice.

	    @param z indice del piano della matrice 3D in cui si trova la cella
	    @param y indice della riga della matrice 3D in cui si trova la cella
	    @param x indice della colonna della matrice 3D in cui si trova la cella

	    @return reference alla cella (z, y, x)-esima della matrice 3D

	    @pre z < _floors && y < _rows && x < _columns
	*/
    T& operator()(int z, int y, int x) {
    	assert(z >= 0 && y >= 0 && x >= 0);
    	assert(z < _floors && y < _rows && x < _columns);
    	return _matrix[(z * _rows * _columns) + (y * _columns) + x];
    }

    /**
	    @brief Getter della cella (z, y, x)-esima

	    Metodo che permette di leggere la cella (z, y, x)-esima della matrice.

	    @param z indice del piano della matrice 3D in cui si trova la cella
	    @param y indice della riga della matrice 3D in cui si trova la cella
	    @param x indice della colonna della matrice 3D in cui si trova la cella

	    @return reference alla cella (z, y, x)-esima della matrice 3D

	    @pre z < _floors && y < _rows && x < _columns
	*/
    const T& operator()(int z, int y, int x) const {
    	assert(z >= 0 && y >= 0 && x >= 0);
    	assert(z < _floors && y < _rows && x < _columns);
    	return _matrix[(z * _rows * _columns) + (y * _columns) + x];
    }

    /**
    @brief Metodo slice

	    Metodo che ritorna una sotto-Matrice3D contenente i valori negli intervalli di 
	    coordinate z1-z2, y1-y2 e x1-x2.

	    @param z1 indice del piano da cui iniziare lo slicing della matrice 3D originale
	    @param y1 indice della riga da cui iniziare lo slicing della matrice 3D originale
	    @param x1 indice della colonna da cui iniziare lo slicing della matrice 3D originale
	    @param z2 indice del piano in cui terminare lo slicing della matrice 3D originale
	    @param y2 indice della riga in cui terminare lo slicing della matrice 3D originale
	    @param x2 indice della colonna in cui terminare lo slicing della matrice 3D originale

	    @return sotto-Matrice3D contenente i valori negli intervalli specificati

	    @pre z1 < _floors && z2 < _floors && y1 < _rows && y2 < _rows && x1 < _columns && x2 < _columns
	*/
    Matrice3D slice(int z1, int z2, int y1, int y2, int x1, int x2) const {

    	assert(z1 >= 0 && z2 >= 0 && y1 >= 0 && y2 >= 0 && x1 >= 0 && x2 >= 0);
    	assert(z1 < _floors && z2 < _floors && y1 < _rows && y2 < _rows && x1 < _columns && x2 < _columns);
    	assert(z2 >= z1 && y2 >= y1 && x2 >= x1);

    	Matrice3D sliced_matrix(z2-z1+1, y2-y1+1, x2-x1+1);

    	for(unsigned int z = z1; z <= z2; ++z) 
        	for(unsigned int y = y1; y <= y2; ++y) 
        		for(unsigned int x = x1; x <= x2; ++x) 
        			sliced_matrix((z - z1), (y - y1), (x - x1)) = (*this)(z, y, x);

        return sliced_matrix;

    }

    /**
	    @brief Operatore di uguaglianza

	    L'operatore di uguaglianza serve a controllare che due Matrici3D aventi le
	    stesse dimensioni siano uguali e contengano dunque gli stessi valori in tutte le
	    celle corrispondenti.
	    Per il confronto viene utilizzato il funtore _equals, funtore membro il cui tipo può 
	    essere definito in fase di creazione della matrice per maggiore flessibilità. 
	    Se non definito il funtore di default utilizza l'operatore == ed è necessario quindi 
	    che eventuali tipi di dato custom lo ridefiniscano a loro volta.

	    @param other Matrice3D sorgente da confrontare

	    @return true se le matrici sono uguali, false altrimenti

	    @pre _floors == other._floors && _rows == other._rows && _columns == other._columns
	*/
    bool operator==(const Matrice3D &other) const {

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
	    @brief Operatore di disuguaglianza

	    L'operatore di disuguaglianza serve a controllare che due Matrici3D aventi le
	    stesse dimensioni siano diverse e che contengano dunque valori diversi anche solo
	    in alcune celle corrispondenti.
	    Sfrutta l'operatore di uguaglianza e ritorna il valore booleano opposto.

	    @param other Matrice3D sorgente da confrontare

	    @return true se le matrici sono diverse, false altrimenti
	*/
    bool operator!=(const Matrice3D &other) const {

        return !((*this) == other);
        			
    }

    // Implementazione di iteratori di tipo random access tramite trucco con puntatori,
	// essendo la struttura interna array-based.

    typedef T *iterator;

    // Ritorna l'iteratore all'inizio della sequenza dati
	iterator begin() {
		return _matrix;
	}

	// Ritorna l'iteratore alla fine della sequenza dati
	iterator end() {
		return _matrix + (_rows * _columns * _floors);
	}

	typedef const T *const_iterator;

	// Ritorna l'iteratore all'inizio della sequenza dati
	const_iterator begin() const {
		return _matrix;
	}
	
	// Ritorna l'iteratore alla fine della sequenza dati
	const_iterator end() const {
		return _matrix + (_rows * _columns * _floors);
	}

	/**
	    @brief Metodo fill

	    Metodo generico che permette di riempire una Matrice3D con valori presi da una 
	    sequenza di dati identificata da iteratori generici. 
	    Il riempimento avviene nell’ordine di iterazione dei dati della matrice, e si ferma
	    nel caso in cui la matrice da riempire non è più in grado di contenere dati ma
	    la sequenza passata non è terminata.
	    I vecchi valori sono sovrascritti.

	    @param b l'iteratore che indica l'inizio della sequenza di dati
	    @param b l'iteratore che indica la fine della sequenza di dati
	*/
    template<typename Iter>
    void fill(Iter b, Iter e) {

    	Matrice3D tmp(*this);

    	int i = 0;
    	while(b != e && i != _floors * _rows * _columns){ // riempie finchè può
    		tmp._matrix[i] = static_cast<T>(*b);
    		++b;
    		++i;
    	}

    	*this = tmp;
    }

    /**
	    @brief Costruttore di conversione (implicita/esplicita)

	    Il costruttore di conversione crea un oggetto Matrice3D<T, F> a partire da un
	    oggetto Matrice3D<U, Q>.
	    Permette la conversione di una Matrice3D definita su un certo tipo a una 
	    Matrice3D definita su un tipo differente (dove il cast è possibile).

	    @param other la Matrice3D di tipo <U, Q> da cui creare il nuovo oggetto

	    @throw std::bad_alloc possibile eccezione di allocazione
	*/
    template <typename U, typename Q>
	Matrice3D(const Matrice3D<U, Q> &other) : _matrix(nullptr), _floors(other.getFloors()), _rows(other.getRows()), _columns(other.getColumns()) {
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
	    @brief ridefinizione operatore di stream

	    Funzione GLOBALE che ridefinisce l'operatore di stream per scrivere una
	    Matrice3D su uno stream di output.
    	La funzione è dichiarata friend perchè accediamo ai dati privati di Matrice3D.

	    Ridefinizione dell'operatore di stream 

	    @param os stream di output (operando di sinistra)
	    @param m Matrice3D da scrivere (operando di destra)

	    @return reference allo stream di output
	*/
    friend std::ostream &operator<<(std::ostream &os, const Matrice3D &m) {
        
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
    @brief Funzione globale trasform

    Funzione generica che permette di ottenere, a partire da una Matrice3D passata,
    una nuova matrice sui cui elementi è stato applicato un determinato funtore, anch'esso
    passato. Il tipo T della Matrice 3D di ritorno, di norma quello restituito dal funtore
    passato, va specificato dal chiamante.
    E' possibile specificare anche il tipo di funtore H usato per l'operatore di uguaglianza 
    della matrice di ritorno.

    @param A la matrice 3D di partenza
    @param functor il funtore da applicare ai dati nelle celle della matrice 3D

    @return la matrice 3D ottenuta applicando il funtore ai dati della matrice di partenza
*/
template <typename Q, typename F, typename H = default_functor<Q>, typename G, typename T>
Matrice3D<Q> trasform(const Matrice3D<T, G> &A) {

	Matrice3D<Q, H> B(A.getFloors(), A.getRows(), A.getColumns());

	F functor;

	for (unsigned int z = 0; z < A.getFloors(); ++z)
        for (unsigned int y = 0; y < A.getRows(); ++y)
            for (unsigned int x = 0; x < A.getColumns(); ++x)
            	B(z, y, x) = functor(A(z, y, x));

	return B;
}


#endif