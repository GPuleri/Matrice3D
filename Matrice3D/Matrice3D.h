#ifndef MATRICE3D_H
#define MATRICE3D_H

#include "Matrice2D.h"
#include <iostream>
#include <algorithm>
#include <ostream> // std::ostream
#include <cstddef> // std::ptrdiff_t
#include <iterator> 
#include <cassert>

typedef unsigned int size_type;

/**
	@file Matrice3D.h 
	@brief Dichiarazione della classe Matrice3D
**/

/**
	@brief Matrice tridimensionale templata

	Classe che rappresenta un matrice tridimensionale templata.
**/
template <typename T>
class Matrice3D {
	
	/**
		@brief Struttura cell ausiliaria

		Struttura utilizzata per rappresentare le "celle" della matrice.
		È composta da un valore T, un campo bool per tenere traccia delle celle avvalorate e due costruttori.
	**/ 
	struct cell {
		T value;
		bool filled;
		cell(): value(), filled() {}
		cell(const T& val): value(val), filled(true) {}
	};

private:

	cell ***_matrix3D;///< Puntatore a puntatore a puntatore a cell
	int _z;			  ///< Numero piani
	int _y;			  ///< Numero righe
	int _x;			  ///< Numero colonne
	size_type _size;  ///< Dimensione della matrice
	
public:

	/**
		Costruttore di default
		*/
	Matrice3D(): _matrix3D(0), _z(0), _y(0), _x(0), _size(0) {}
	
	/**
		Costruttore secondario
		
		@param z Numero piani
		@param y Numero righe
		@param x Numero colonne
		*/
	Matrice3D(int z, int y, int x): _matrix3D(0), _z(z), _y(y), _x(x), _size(z*y*x) {

		_matrix3D = new cell**[z];
		try {
			_matrix3D[0] = new cell*[z*y];
			try {
				_matrix3D[0][0] = new cell[_size];
				for (int i = 0; i < z; i++)
				{
					_matrix3D[i] = &_matrix3D[0][i*y];
					for (int j = 0; j < y; j++)
					{
						_matrix3D[i][j] = &_matrix3D[0][0][i*y*x + j*x];
					}
				}
			}
			catch(...) {
				delete[] _matrix3D[0];
				throw;
			}
		}
		catch(...) {
			delete[] _matrix3D;
			_matrix3D = 0;
			_z = 0;
			_y = 0;
			_x = 0;
			_size = 0;
			throw;
		}
	}
	
	/**
		Costruttore secondario
		
		@param z Numero piani
		@param y Numero righe
		@param x Numero colonne
		@param value Valore da assegnare a ogni cella
		*/
	Matrice3D(int z, int y, int x, const T &value) : _matrix3D(0), _z(z), _y(y), _x(x), _size(z*y*x) {
		
		_matrix3D = new cell**[z];
		try {
			_matrix3D[0] = new cell*[z*y];
			try {
				_matrix3D[0][0] = new cell[_size];
				for (int i = 0; i < z; i++)
				{
					_matrix3D[i] = &_matrix3D[0][i*y];
					for (int j = 0; j < y; j++)
					{
						_matrix3D[i][j] = &_matrix3D[0][0][i*y*x + j*x];
						for (int k = 0; k < x; k++)
						{
							_matrix3D[i][j][k].value = value;
							_matrix3D[i][j][k].filled = true;
						}
					}
				}
			}
			catch(...) {
				delete[] _matrix3D[0];
				throw;
			}
		}
		catch(...) {
			delete[] _matrix3D;
			_matrix3D = 0;
			_z = 0;
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
	Matrice3D(const Matrice3D &other) : _matrix3D(0), _z(other._z), _y(other._y), _x(other._x), _size(other._size) {
		
		_matrix3D = new cell**[_z];
		try {
			_matrix3D[0] = new cell*[_z*_y];
			try {
				_matrix3D[0][0] = new cell[_size];
				for (int i = 0; i < _z; i++)
				{
					_matrix3D[i] = &_matrix3D[0][i*_y];
					for (int j = 0; j < _y; j++)
					{
						_matrix3D[i][j] = &_matrix3D[0][0][i*_y*_x + j*_x];
						for (int k = 0; k < _x; k++)
						{
							if(other.is_filled(i,j,k))
							{
								_matrix3D[i][j][k].value = other(i,j,k);
								_matrix3D[i][j][k].filled = true;
							}
						}
					}
				}
			}
			catch(...) {
				delete[] _matrix3D[0];
				throw;
			}
		}
		catch(...) {
			delete[] _matrix3D;
			_matrix3D = 0;
			_z = 0;
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
	Matrice3D(const Matrice3D<U> &other) : _matrix3D(0), _z(other.get_z()), _y(other.get_y()), _x(other.get_x()), _size(other.get_size()) {

		_matrix3D = new cell**[_z];
		try {
			_matrix3D[0] = new cell*[_z*_y];
			try {
				_matrix3D[0][0] = new cell[_size];
				for (int i = 0; i < _z; i++)
				{
					_matrix3D[i] = &_matrix3D[0][i*_y];
					for (int j = 0; j < _y; j++)
					{
						_matrix3D[i][j] = &_matrix3D[0][0][i*_y*_x + j*_x];
						for (int k = 0; k < _x; k++)
						{
							if(other.is_filled(i,j,k))
							{
								_matrix3D[i][j][k].value = static_cast<T>(other(i,j,k));
								_matrix3D[i][j][k].filled = true;
							}
						}
					}
				}
			}
			catch(...) {
				delete[] _matrix3D[0];
				throw;
			}
		}
		catch(...) {
			delete[] _matrix3D;
			_matrix3D = 0;
			_z = 0;
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
	Matrice3D &operator=(const Matrice3D &other) {
		if (this != &other) {  
			Matrice3D tmp(other);
			this->swap(tmp);
		}
		return *this;
	}
	
	/**
		Operatore di assegnamento template
		
		@param other matrice da copiare
		@return reference a this

		*/
	template <typename Q> Matrice3D<Q> &operator=(const Matrice3D &other) {
		if (this != &other) {  
			Matrice3D tmp(other);
			this->swap(tmp);
		}
		return *this;
	}
	
	/**
		Distruttore
		*/
	~Matrice3D() {
		
		if(&_matrix3D[0] != NULL)
			if(&_matrix3D[0][0] != NULL)
				delete[] _matrix3D[0][0];
		
		if(&_matrix3D[0] != NULL)
			delete[] _matrix3D[0];
	
		delete[] _matrix3D;
		
		_matrix3D = 0;
		_z = 0;
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
		Ritorna il numero di piani
			
		@return un int
		*/
	int get_z() const {
		return _z;
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
		
		@param z numero del piano
		@param y numero della colonna	
		@param x numero della riga
		@return tipo bool
		*/
	bool is_filled(int z, int y, int x) const {
		assert(z < _z);
		assert(y < _y);
		assert(x < _x);
		
		return _matrix3D[z][y][x].filled;
	}
	
	/**
		Ridefinizione operator () per la lettura
		
		@param z numero del piano
		@param y numero della colonna	
		@param x numero della riga
		@return valore della cella
		*/
	const T &operator()(int z, int y, int x) const {
		assert(z < _z);
		assert(y < _y);
		assert(x < _x);
		assert(_matrix3D[z][y][x].filled); //controlla se è possibile accedere al valore della cella
		
		return _matrix3D[z][y][x].value;
	}
	
	/**
		Ridefinizione operator () per la scrittura
		
		@param z numero del piano
		@param y numero della colonna	
		@param x numero della riga
		@return valore della cella
		*/
	T &operator()(int z, int y, int x) {
		assert(z < _z);
		assert(y < _y);
		assert(x < _x);
		
		_matrix3D[z][y][x].filled = true;

		return _matrix3D[z][y][x].value;
	}
	
	
	void swap(Matrice3D &other) {	
		std::swap(other._matrix3D, this->_matrix3D);
		std::swap(other._z, this->_z);
		std::swap(other._y, this->_y);
		std::swap(other._x, this->_x);
		std::swap(other._size, this->_size);
	}

	/**
		Metodo che dato un piano ritorna la matrice2D contentente tutte le celle del piano.
		
		@param z numero del piano
		@return Matrice2D
		* /
	Matrice2D<T> slice(int z) {
		assert(z < _z);
		
		Matrice2D<T> tmp(get_y(), get_x());
		for (int i = 0; i < get_y(); i++)
			for (int j = 0; j < get_x(); j++)
				tmp(i,j) = _matrix3D[z][i][j].value;
		return tmp;
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
		
		//Ritorna true se la cella data è avvalorata, false altrimenti
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
		friend class Matrice3D;

		iterator(cell *p) : ptr(p) { 
		}
		
	}; // classe iterator
	
	// Ritorna l'iteratore all'inizio della sequenza dati
	iterator begin() {
		return iterator(**_matrix3D);
	}
	
	// Ritorna l'iteratore alla fine della sequenza dati
	iterator end() {
		return iterator(**_matrix3D+_size);
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

		//Ritorna true se la cella data è avvalorata, false altrimenti
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
		friend class Matrice3D; 

		const_iterator(const cell *p) : ptr(p) { 
			 
		}
		
	}; // classe const_iterator
	
	// Ritorna l'iteratore costante all'inizio della sequenza dati
	const_iterator cbegin() const {
		return const_iterator(**_matrix3D);
	}
	
	// Ritorna l'iteratore costante alla fine della sequenza dati
	const_iterator cend() const {
		return const_iterator(**_matrix3D+_size);
	}
	
}; //class Matrice3D

/**
	Funzione che, data una Matrice3D A (su tipi T) e un funtore F, 
	ritorna una nuova Matrice3D B (su tipi Q) i cui elementi sono ottenuti 
	applicando il funtore agli elementi di A.
	
	@param A matrice su tipi T
	@param F funtore da applicare
	
	@return B matrice su tipi Q
*/
template <typename Q, typename T, typename Fun>
Matrice3D<Q> trasforma(Matrice3D<T> &A, const Fun &F)	
{
	typename Matrice3D<T>::iterator i, ie;

	for (i = A.begin(), ie = A.end(); i!=ie; ++i)
		if(i.is_filled())
			*i = F(*i);
		
	Matrice3D<Q> B(A);
	return B;
}

/**
	@brief Operatore di stream 
	
	Permette di spedire su uno stream di output il contenuto della matrice.

	@param os oggetto stream di output
	@param m matrice3D

	@return reference allo stream di output
*/
template <typename T>
std::ostream& operator<<(std::ostream &os, const Matrice3D<T> & m) {
	
	std::cout<<std::endl;
	for(int i = 0; i<m.get_z(); i++)
		for(int j = 0; j<m.get_y(); j++) 
			for(int k = 0; k<m.get_x(); k++) {
				if(m.is_filled(i,j,k))
					os << "matrix3D("<<i<<","<<j<<","<<k<<") = "<< m(i,j,k) << std::endl;
			}
	
	std::cout<<std::endl;
	
	return os;
}

#endif