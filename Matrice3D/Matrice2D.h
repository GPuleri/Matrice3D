#ifndef MATRICE2D_H
#define MATRICE2D_H

#include <iostream>
#include <algorithm>
#include <ostream> // std::ostream
#include <cstddef> // std::ptrdiff_t
#include <iterator> 
#include <cassert>

typedef unsigned int size_type;

/**
	@file Matrice2D.h 
	@brief Dichiarazione della classe Matrice2D
**/

/**
	@brief Matrice bidimensionale templata

	Classe che rappresenta un matrice bidimensionale templata.
**/
template <typename T>
class Matrice2D {
	
	/**
		@brief Struttura cell ausiliaria

		Struttura utilizzata per rappresentare le "celle" della matrice.
		È composta da un valore T, un campo bool per tenere traccia delle celle avvalorate e due costruttori.
	**/ 
	struct cell {
		T value;
		bool filled;
		cell(): value(), filled(false) {}
		cell(const T& val): value(val), filled(true) {}
	};

protected:

	cell **_matrix2D; ///< Puntatore a puntatore a cell
	int _y;			  ///< Numero righe
	int _x;			  ///< Numero colonne
	size_type _size;  ///< Dimensione della matrice
	
public:

	/**
		Costruttore di default
		*/
	Matrice2D(): _matrix2D(0), _y(0), _x(0), _size(0) {}
	
	/**
		Costruttore secondario
		
		@param y Numero righe
		@param x Numero colonne
		*/
	Matrice2D(int y, int x): _matrix2D(0), _y(y), _x(x), _size(y*x) {
		
		_matrix2D = new cell*[y];
		try {
			_matrix2D[0] = new cell[_size];
			for (int i = 0; i < y; i++)
			{
				_matrix2D[i] = &_matrix2D[0][i*x];
			}
		}
		catch(...) {
			delete[] _matrix2D;
			_matrix2D = 0;
			_y = 0;
			_x = 0;
			_size = 0;
			throw;
		}
	}
	
	/**
		Costruttore secondario
		
		@param y Numero righe
		@param x Numero colonne
		@param value Valore da assegnare a ogni cella
		*/
	Matrice2D(int y, int x, const T &value) : _matrix2D(0), _y(y), _x(x), _size(y*x) {
		
		_matrix2D = new cell*[y];
		try {
			_matrix2D[0]= new cell[_size];
			for (int i = 0; i < y; i++)
			{
				_matrix2D[i] = &_matrix2D[0][i*x];
				for (int j = 0; j < x; j++)
				{
					_matrix2D[i][j].value = value;
					_matrix2D[i][j].filled = true;
				}
			}
		}
		catch(...) {
			delete[] _matrix2D;
			_matrix2D = 0;
			_y = 0;
			_x = 0;
			_size = 0;
			throw;
		}
	}
	
	/**
		Costruttore di copia

		@param other matrice da copiare
		*/
	Matrice2D(const Matrice2D &other) : _matrix2D(0), _y(other._y), _x(other._x), _size(other._size) {
		
		_matrix2D = new cell*[_y];
		try {
			_matrix2D[0] = new cell[_size];
			for (int i = 0; i < _y; i++)
			{
				_matrix2D[i] = &_matrix2D[0][i*_x];
				for (int j = 0; j < _x; j++)
				{
					if(other.is_filled(i,j))
					{
						_matrix2D[i][j].value = other(i,j);
						_matrix2D[i][j].filled = true;
					}
				}
			}
		}
		catch(...) {
			delete[] _matrix2D;
			_matrix2D = 0;
			_y = 0;
			_x = 0;
			_size = 0;
			throw;
		}
	}
	
	/**
		Costruttore template

		@param other matrice da copiare
		*/ 
	template <typename U> 
	Matrice2D(const Matrice2D<U> &other) : _matrix2D(0), _y(other.get_y()), _x(other.get_x()), _size(other.get_size()) {

		_matrix2D = new cell*[_y];
		try {
			_matrix2D[0] = new cell[_size];
			for (int i = 0; i < _y; i++)
			{
				_matrix2D[i] = &_matrix2D[0][i*_x];
				for (int j = 0; j < _x; j++)
				{
					if(other.is_filled(i,j))
					{
						_matrix2D[i][j].value = static_cast<T>(other(i,j));
						_matrix2D[i][j].filled = true;
					}
				}
			}
		}
		catch(...) {
			delete[] _matrix2D;
			_matrix2D = 0;
			_y = 0;
			_x = 0;
			_size = 0;
			throw;
		}
	}
	
	/**
		Operatore di assegnamento
		
		@param other matrice da copiare
		@return reference a this

		*/
	Matrice2D &operator=(const Matrice2D &other) {
		if (this != &other) {  
			Matrice2D tmp(other);
			this->swap(tmp);
		}
		return *this;
	}
	
	/**
		Operatore di assegnamento template
		
		@param other matrice da copiare
		@return reference a this

		*/
	template <typename Q> Matrice2D<Q> &operator=(const Matrice2D &other) {
		if (this != &other) {  
			Matrice2D tmp(other);
			this->swap(tmp);
		}
		return *this;
	}
	
	/**
		Distruttore
		*/
	~Matrice2D() {
		
		if(&_matrix2D[0] != NULL)
			delete[] _matrix2D[0];
		
		delete[] _matrix2D;
		_matrix2D = 0;
		_y = 0;
		_x = 0;
		_size = 0;
	}
	
	/**
		Ritorna la dimensione della matrice
			
		@return un size_type
		*/
	size_type get_size() const {
		return _size;
	}
	
	/**
		Ritorna il numero di colonne
			
		@return un int
		*/
	int get_y() const {
		return _y;
	}
	
	/**
		Ritorna il numero di righe
			
		@return un int
		*/
	int get_x() const {
		return _x;
	}
	
	/**
		Ritorna true se la cella data è avvalorata, false altrimenti
		
		@param y numero della colonna	
		@param x numero della riga
		@return tipo bool
		*/
	bool is_filled(int y, int x) const {
		assert(y < _y);
		assert(x < _x);
		
		return _matrix2D[y][x].filled;
	}
	
	/**
		Ridefinizione operator () per la lettura
		
		@param y numero della colonna	
		@param x numero della riga
		@return valore della cella
		*/
	const T &operator()(int y, int x) const {
		assert(y < _y);
		assert(x < _x);
		assert(_matrix2D[y][x].filled); //controlla se è possibile accedere al valore della cella
		
		return _matrix2D[y][x].value;
	}
	
	/**
		Ridefinizione operator () per la scrittura
		
		@param y numero della colonna	
		@param x numero della riga
		@return valore della cella
		*/
	T &operator()(int y, int x) {
		assert(y < _y);
		assert(x < _x);
		
		_matrix2D[y][x].filled = true;

		return _matrix2D[y][x].value;
	}
	
	
	void swap(Matrice2D &other) {	
		std::swap(other._matrix2D, this->_matrix2D);
		std::swap(other._y, this->_y);
		std::swap(other._x, this->_x);
		std::swap(other._size, this->_size);
	}

	
	class const_iterator;  //forward declaration
	
	
	/**
		Iteratore della matrice

		@brief Iteratore della matrice
		*/
	class iterator {
		cell *ptr;

	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef T*                        pointer;
		typedef T&                        reference;
	
		iterator() : ptr(0) {
		}
		
		iterator(const iterator &other) : ptr(other.ptr) {
		}

		iterator& operator=(const iterator &other) {
			ptr = other.ptr;
			return *this;
		}

		~iterator() {
			ptr = 0;
		}
		
		// Ritorna true se la cella data è avvalorata, false altrimenti
		bool is_filled() const {
			return ptr->filled;
		}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
			return ptr->value;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return &(ptr->value);
		}

		// Operatore di iterazione post-incremento
		iterator operator++(int) {
			iterator tmp(*this);
			++ptr;
			return tmp;
		}

		// Operatore di iterazione pre-incremento
		iterator& operator++() {
			++ptr;
			return *this;
		}

		// Operatore di iterazione post-decremento
		const_iterator operator--(int) {
			const_iterator tmp(*this);
			--ptr;
			return tmp;
		}
		
		// Operatore di iterazione pre-decremento
		iterator& operator--() {
			--ptr;
			return *this;
		}
				
		reference operator[](int index) const {
			return (ptr+index)->value;
		}
		
		iterator& operator+=(const ptrdiff_t& movement) {
			ptr += movement;
			return *this;
		}
				
		iterator& operator-=(const ptrdiff_t& movement)  {
			ptr -= movement;
			return *this;
		}
		
		iterator operator+(int n) const {
			iterator tmp = (*this);
			return tmp += n;
		}

		iterator operator-(int n) {
			iterator tmp = (*this);
			return tmp -= n;
		}
		
		// Uguaglianza
		bool operator==(const iterator &other) const {
			return ptr == other.ptr;
		}

		// Diversita'
		bool operator!=(const iterator &other) const {
			return ptr != other.ptr;
		}
		
		friend class const_iterator;

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
			return ptr == other.ptr;
		}

		// Diversita'
		bool operator!=(const const_iterator &other) const {
			return ptr != other.ptr;
		}


	private:
		friend class Matrice2D;

		iterator(cell *p) : ptr(p) { 
		}
		
	}; // classe iterator
	
	// Ritorna l'iteratore all'inizio della sequenza dati
	iterator begin() {
		return iterator(*_matrix2D);
	}
	
	// Ritorna l'iteratore alla fine della sequenza dati
	iterator end() {
		return iterator(*_matrix2D+_size);
	}
	
	
	/**
		Iteratore costante della matrice

		@brief Iteratore costante della matrice
		*/
	class const_iterator {
		const cell *ptr;	
	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;

	
		const_iterator() : ptr(0) {
		}
		
		const_iterator(const const_iterator &other) 
			: ptr(other.ptr) {
			
		}

		const_iterator(const iterator &other) 
			: ptr(other.ptr) {
			
		}

		const_iterator& operator=(const const_iterator &other) {
			ptr = other.ptr;
			return *this;
		}

		const_iterator& operator=(const iterator &other) {
			ptr = other.ptr;
			return *this;
		}

		~const_iterator() {
			ptr = 0;
		}

		// Ritorna true se la cella data è avvalorata, false altrimenti
		bool is_filled() const {
			return ptr->filled;
		}
		
		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
			return ptr->value;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return &(ptr->value);
		}
		
		// Operatore di iterazione post-incremento
		const_iterator operator++(int) {
			const_iterator tmp(*this);
			++ptr;
			return tmp;
		}

		// Operatore di iterazione pre-incremento
		const_iterator& operator++() {
			++ptr;
			return *this;
		}

		// Operatore di iterazione post-decremento
		const_iterator operator--(int) {
			const_iterator tmp(*this);
			--ptr;
			return tmp;
		}
		
		// Operatore di iterazione pre-decremento
		const_iterator& operator--() {
			--ptr;
			return *this;
		}
				
		reference operator[](int index) const {
			return (ptr+index)->value;
		}
		
		const_iterator& operator+=(const ptrdiff_t& movement) {
			ptr += movement;
			return (*this);
		}
				
		const_iterator& operator-=(const ptrdiff_t& movement)  {
			ptr -= movement;
			return (*this);
		}
		
		const_iterator operator+(int n) const {
			const_iterator tmp = (*this);
			return tmp += n;
		}

		const_iterator operator-(int n) {
			const_iterator tmp = (*this);
			return tmp -= n;
		}
		
		// Uguaglianza
		bool operator==(const const_iterator &other) const {
			return ptr == other.ptr;
		}
		
		// Diversita'
		bool operator!=(const const_iterator &other) const {
			return ptr != other.ptr;
		}

		
		friend class iterator;

		// Uguaglianza
		bool operator==(const iterator &other) const {
			return ptr == other.ptr;
		}

		// Diversita'
		bool operator!=(const iterator &other) const {
			return ptr != other.ptr;
		}


	private:
		friend class Matrice2D; 

		const_iterator(const cell *p) : ptr(p) { 
			 
		}
		
	}; // classe const_iterator
	
	// Ritorna l'iteratore costante all'inizio della sequenza dati
	const_iterator cbegin() const {
		return const_iterator(*_matrix2D);
	}
	
	// Ritorna l'iteratore costante alla fine della sequenza dati
	const_iterator cend() const {
		return const_iterator(*_matrix2D+_size);
	}
	
}; //class Matrice2D

/**
	Funzione che, data una Matrice2D A (su tipi T) e un funtore F, 
	ritorna una nuova Matrice2D B (su tipi Q) i cui elementi sono ottenuti 
	applicando il funtore agli elementi di A.
	
	@param A matrice su tipi T
	@param F funtore da applicare
	
	@return B matrice su tipi Q
*/
template <typename Q, typename T, typename Fun>
Matrice2D<Q> trasforma(Matrice2D<T> &A, const Fun &F)	
{
	typename Matrice2D<T>::iterator i, ie;

	for (i = A.begin(), ie = A.end(); i!=ie; ++i)
		if(i.is_filled())
			*i = F(*i);
		
	Matrice2D<Q> B(A);
	return B;
}

/**
	@brief Operatore di stream 
	
	Permette di spedire su uno stream di output il contenuto della matrice.

	@param os oggetto stream di output
	@param m matrice2D

	@return reference allo stream di output
*/
template <typename T>
std::ostream& operator<<(std::ostream &os, const Matrice2D<T> & m) {
	
	std::cout<<std::endl;
	for(int i = 0; i<m.get_y(); i++)
		for(int j = 0; j<m.get_x(); j++) {
			if(m.is_filled(i,j))
				os << "matrix2D("<<i<<","<<j<<") = "<< m(i,j) << std::endl;
		}
	
	std::cout<<std::endl;
	
	return os;
}

#endif