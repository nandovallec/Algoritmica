/**
  * @file Cronologia.h
  * @brief Fichero cabecera del TDA Cronologia
  *
  */

#ifndef CRONO_H
#define CRONO_H

#include <iostream>
#include <string>
#include "FechaHistorica.h"

using namespace std;

/**
  *  @brief T.D.A. Cronologia
  *
  * Escribir tu descripcion por si quieres hcerlo mejor
  *
  * Un ejemplo de su uso:
  * @include pruebacronologia.cpp
  *
  * @author Jose Mª Sanchez Guerrero y Fernando Vallecillos Ruiz
  * @date Octubre 2017
  */


struct NodoCrono{

	FechaHistorica fecha_his; /**<variable del tipo Fecha Historica */
	NodoCrono* sig; /**<puntero al siguiente NodoCrono */

/**
  * @brief Constructor por defecto del struct.
  */
	NodoCrono();

/**
  * @brief Constructor con una fecha
  * @param fecha fecha historica a insertar
  */
	NodoCrono(FechaHistorica fecha);
};



class Cronologia{

    public:

/**
  * @brief Constructor por defecto de la clase. Inicializa los punteros en NULL
  */
	Cronologia();

/**
  * @brief Destructor de la clase.
  */
	~Cronologia();

/**
  * @brief Constructor de copia
  * @param m cronologia a copiar
  */
	Cronologia(const Cronologia &m);

/**
  * @brief Sobrecarga del operador <<
  * @pre La lista esta o no vacia
  * @param flujo ostream de salida
  * @param m objeto que da los valores
  * @return Devuelve el flujo que vamos a mostrar
  */ 
	friend ostream& operator<<(ostream &flujo, Cronologia &m);

/**
  * @brief Sobrecarga del operador >>
  * @param flujo istream de entrada
  * @param m objeto que recibe los valores
  * @return Devuelve el flujo que hemos ido insertando
  */ 
	friend istream& operator>>(istream &flujo, Cronologia &m);

/**
  * @brief Inserta un nuevo nodo en la cronologia
  * @param fecha fecha historica a insertar
  */
	void insertNewNode(FechaHistorica fecha);

/**
  * @brief Imprime el contenido de una cronologia en el formato año///acont1///acont2///...///
  */
	void print();
	
/**
  * @brief Busca un evento dentro de los acontecimientos de la cronologia
  * @param clave string a buscar
  * @return Devuelve una cronologia de los acontecimientos donde esta el string a buscar
  */
	Cronologia buscarEventos(string clave);

/**
  * @brief Da la fecha historica del año dado
  * @param anio donde buscar los eventos
  * @return Devuelve una fecha historica
  */
	FechaHistorica getEventos(int anio);

/**
  * @brief Da las fechas historicas que hay entre los años dados
  * @param inicio principio de las fechas historicas
  * @param final final de las fechas historicas
  * @return Devuelve una cronologia con las fechas dadas
  */
	Cronologia entreAnios(int inicio, int final);

/**
  * @brief Sobrecarga del operador []
  * @param i numero de la fecha historica
  * @return Devuelve la i-esima fecha historica
  */
	FechaHistorica& operator[](int i);

/**
  * @brief Sobrecarga del operador +
  * @param otra_crono cronologia a sumar
  * @return Devuelve la suma de las dos cronologias
  */ 
	Cronologia operator+(Cronologia &otra_crono);

/**
  * @brief Sobrecarga del operador =
  * @param m es la cronologia a copiar
  * @return Crea una cronologia igual a la que hemos pasado
  */ 
	Cronologia& operator=(const Cronologia &m);
	

private:
/**
  * @brief Inserta un acontecimiento al principio de la cronologia
  * @param fecha la fecha historica a insertar
  */
	void insertBegin(FechaHistorica &fecha);

/**
  * @brief Inserta un acontecimiento al final de la cronologia
  * @param fecha la fecha historica a insertar
  */
	void insertEnd(FechaHistorica &fecha);

/**
  * @brief Elimina los punteros liberando la memoria
  * @pre La lista no puede estar vacia
  */
	void liberar();


	NodoCrono *first; /**< puntero al primer nodo de la cronologia */
	NodoCrono *last; /**< puntero al ultimo nodo de la cronologia */

/**
  * @brief Vacia
  * @return Devuelve si la cronologia esta vacia
  */
	bool Vacia();
	
};

/**
  * @brief Sobrecarga del operador <<
  * @pre La lista esta o no vacia
  * @param flujo ostream de salida
  * @param m objeto que da los valores
  * @return Devuelve el flujo que vamos a mostrar
  */
ostream& operator<<(ostream &flujo, Cronologia &m);


/**
  * @brief Sobrecarga del operador >>
  * @param flujo istream de entrada
  * @param m objeto que recibe los valores
  * @return Devuelve el flujo que hemos ido insertando
  */ 
istream& operator>>(istream &flujo, Cronologia &m);


/**
  * @brief Funcion que carga una cronologia de un archivo
  * @param nombre archivo del que coger los datos
  * @param m objeto que recibe los datos
  * @return Devuelve si se ha completado correctamente
  */ 
bool Cargar(string nombre, Cronologia &m);

/**
  * @brief Funcion que salva una cronologia en un archivo
  * @param nombre archivo que recibe los datos
  * @param m objeto del que coge los datos
  * @return Devuelve si se ha completado correctamente
  */ 
bool Salvar(string nombre, Cronologia &m);

#endif 
