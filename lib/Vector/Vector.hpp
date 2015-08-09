/*

		Dynamic Vector

		

		Alberto Sola - 2015

*/

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

//////////////////////////
//
// 		PROTOTYPES
//
//////////////////////////

template <typename T>
class Vector{

private:
	static const int MIN_CAPACITY = 100;

	int max_elements;
	int used_elements;

	T * vector;

	int 	NewCapacity( int i_size) const;
	void 	Increase( int i_size );
	void 	Init( int i_size );
	void 	Copy( const Vector<T> &i_copy );
	void 	Delete();

public:
	Vector();
	Vector( int i_size );
	Vector( const Vector<T> &i_copy );
	~Vector();

	int 	GetMaxElements() const;
	int 	GetUsedElements() const;
	T 		GetElement( int index ) const;

	void 	SetSize( int i_size );
	void 	SetElement( int index, T i_data );

	void 	AddElement( T i_data );
	void 	DelElement( int index );

	void 	Clear();

	void 	Swap( int first_index, int second_index );
	void 	Invert();

	int 	Min( int first_index, int last_index ) const;
	int 	Max( int first_index, int last_index ) const;

	// OVERLOAD
	Vector<T> & operator=( const Vector<T> &i_copy );
	Vector<T> & operator+=( const Vector<T> &i_copy );

	T & operator[]( int index );
	const T & operator[]( int index ) const;

};




template <typename T>
void Vector<T>::Init( int i_size ){
	/*
		Reserva espacio en memoria.
	*/

	// Initmos
	used_elements 	= 0;
	max_elements 		= NewCapacity( i_size );

	// Reservamos memoria
	vector = new T [ max_elements ];

}

template <typename T>
Vector<T>::Vector(){
	/*
		Constructor

		Reserva espacio para max_elements = N*2^k tal que
		max_elements > i_size.

		El parámtro es opcional, por defecto es 0 y reervará
		espacio para 100 elementos.

	*/

	max_elements = MIN_CAPACITY;

	Init( 0 );
	
}

template <typename T>
Vector<T>::Vector( int i_size ){
	/*
		Constructor

		Reserva espacio para max_elements = N*2^k tal que
		max_elements > i_size.

		El parámtro es opcional, por defecto es 0 y reervará
		espacio para 100 elementos.

	*/

	max_elements = MIN_CAPACITY;

	Init( i_size );
	
}

template <typename T>
void Vector<T>::Copy( const Vector<T> &i_copy ){
	/*
		Crea un objeto nuevo que contiene una copia del contenido
		del objeto pasado como parámetro.
	*/

	// Obtenemos los parámetros
	max_elements = i_copy.GetMaxElements();
	used_elements = i_copy.GetUsedElements();

	// Reservamos nuevo espacio en memoria
	vector = new T [ max_elements ];

	// Initmos los valores
	for( int i = 0; i < used_elements; i++ ){

		SetElement( i, i_copy.GetElement(i) );

	}
	
}

template <typename T>
Vector<T>::Vector( const Vector<T> &i_copy ){
	/*
		Constructor de Copy

		Crea un nuevo objeto copia del first.

	*/

	Copy( i_copy );
	
}

template <typename T>
void Vector<T>::Delete(){
	/*
		Elimina la memoria reservada dinámicamente.
	*/

	delete [] vector;

}

template <typename T>
Vector<T>::~Vector(){
	/*
		Destructor

		Libera el espacio reservado en memoria.
	*/

	Delete();	
}

template <typename T>
void Vector<T>::Clear(){
	/*
		Reinicia el vector.

		No pone a 0 los valores.
	*/
	used_elements = 0;
	
}

template <typename T>
int Vector<T>::GetMaxElements() const{
	/*
		Devuelve la CAPACIDAD máxima del vector.
	*/
	return max_elements;
	
}

template <typename T>
int Vector<T>::GetUsedElements() const{
	/*
		Devuelve el número de elementos utilizados.
	*/
	return used_elements;
	
}


// Prec: 0 <= index < used_elements
template <typename T>
T Vector<T>::GetElement( int index ) const{
	/*
		Devuelve el elemento en la poición
		índice.
	*/
	return vector[index];
	
}

template <typename T>
void Vector<T>::SetSize( int i_size ){
	/*
		Establece un nuevo tamaño útil para el
		vector.
		Si no hay suficiente espacio reserva uno
		nuevo con el doble de pacidad.
	*/

	// Si no hay suficientes elementos
	if( i_size > max_elements ){
		Increase( i_size );
	}
	
	// Actualizamos
	used_elements = i_size;
	
}

template <typename T>
int Vector<T>::NewCapacity( int i_size ) const{
	/*
		Calcula la capacidad máxima del vector
		atendiendo a la fórmula capacidad = N*2^k.

	*/
	int nueva_capacidad = max_elements;

	while( i_size >= nueva_capacidad )
		nueva_capacidad = nueva_capacidad * 2;
	
	return nueva_capacidad;
}

template <typename T>
void Vector<T>::Increase( int i_size ){
	/*
		Reserva uno nuevo en memoria, copia el antiguo
		y lo elimina.
	*/

	// Calculamos el nuevo tamaño
	int nueva_capacidad = NewCapacity( i_size );

	// Reservamos en memoria
	T * nuevo_vector = new T [ nueva_capacidad ];

	// Copymos el vector antiguo

	for( int i = 0; i < used_elements; i++ ){

		nuevo_vector[i] = GetElement(i);

	}

	// Eliminamos
	delete [] vector;

	// Actualizamos el puntero
	vector = nuevo_vector;

}

// Prec: 0 <= index < used_elements
template <typename T>
void Vector<T>::SetElement( int index, T i_data ){
	/*
		Modifica el contenido del elemento en la posición
		especificada.
	*/

	vector[ index ] = i_data;

}

template <typename T>
void Vector<T>::AddElement( T i_data ){
	/*
		Añade un elemento al final de la lista.

		Si no hay espacio suficiente lo redimensiona.
	*/

	// Comprobamos el espacio
	if( used_elements == max_elements ){
		Increase( max_elements );
	}

	// Añadimos al final
	vector[ used_elements ] = i_data;

	// Actualizamos
	used_elements++;
}

// Prec: 0 <= index < used_elements
template <typename T>
void Vector<T>::DelElement( int index ){

}

// Prec: 0 <= index < used_elements
template <typename T>
void Vector<T>::Swap( int first_index, int second_index ){
	/*
		Swap el contenido de dos elementos.
	*/
	T aux = GetElement( first_index );
	SetElement( first_index, GetElement( second_index ) );
	SetElement( second_index, aux );

}


template <typename T>
void Vector<T>::Invert(){
	/*

	*/
	int max 		= used_elements - 1;
	int mitad 	= used_elements / 2;

	for( int i = 0; i < mitad; i++ )
		Swap( i, max - i );

}

template <typename T>
int Vector<T>::Min( int inicio, int fin ) const{
	/*

	*/
	int min = GetElement( 0 );
	int next;

	for( int i = 1; i < used_elements; i++ ){
		
		next = GetElement( i );

		if( next < min )
			min = next;

	}

	return min;
}

template <typename T>
int Vector<T>::Max( int inicio, int fin ) const{
	/*

	*/

	int max = GetElement( 0 );
	int next;

	for( int i = 1; i < used_elements; i++ ){
		
		next = GetElement( i );

		if( next > max )
			max = next;

	}

	return max;
}


//////////////////////////
//
// 		OVERLOAD
//
//////////////////////////


template <typename T>
Vector<T> & Vector<T>::operator=( const Vector<T> &i_copy ){
	/*
		Operador de asignación

		Elimina el contenido previo si lo hay
		y crea una copia del objeto.

	*/

	// Borramos el contenido
	Delete();

	// Creamos la copia
	Copy( i_copy );

	return *this;

}

template <typename T>
Vector<T> & Vector<T>::operator+=( const Vector<T> &i_copy ){
	/*
		Operador +=

		Concatena el contenido de dos vectores en el first.

	*/

	int max = i_copy.GetUsedElements();

	for( int i = 0; i < max; i++ )
		AddElement( i_copy[i] );

	return *this;

}

template <typename T>
std::ostream & operator<<( std::ostream & os, const Vector<T> &dato ){
	/*
		Sobrecarga del operador << de la biblioteca
		'ostream'.
	*/

	int total_utilizados = dato.GetUsedElements();

	for( int i = 0; i < total_utilizados; i++ ){
		os << dato.GetElement( i ) << " ";
	}

	return os;
}

/*
template <typename T>
std::istream & operator>>( std::istream & is, const Vector<T> &dato ){
	/*
		Sobrecarga del operador >> de la biblioteca
		'istream'.
	/



	while(){

	}

	return is;
}
*/


template <typename T>
T & Vector<T>::operator[]( int index ){
	/*
		Sobrecarga del operador [] para objetos
		no constantes.
	*/
	return vector[ index ];
}

template <typename T>
const T & Vector<T>::operator[]( int index ) const{
	/*
		Sobrecarga del operador [] para objetos
		constantes.
	*/
	return vector[ index ];
}

#endif