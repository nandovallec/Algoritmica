/**
  * @file FechaHistorica.h
  * @brief Fichero cabecera del TDA FechaHistorica
  *
  */

#ifndef FECHAH_H
#define FECHAH_H

#include <iostream>
#include <string>

using namespace std;

/**
  *  @brief T.D.A. FechaHistorica
  *
  * Una instancia @e fecha del tipo de datos abstracto @c FechaHistorica es un objeto
  * que almacena un año y uno o mas acontecimientos que sucedieron en ese año, de tal
  * forma que se almacenen en un struct @c NodoFecha formado por un string con el 
  * acontecimiento y un puntero hacia otro NodoFecha.
  *
  * Un ejemplo de su uso:
  * @include pruebacronologia.cpp
  *
  * @author Jose Mª y Fernando Vallecillos
  * @date Octubre 2017
  */

struct NodoFecha{

	string acontecimiento; /**<string del acontecimiento del NodoFecha */
	NodoFecha *siguiente; /**<puntero al siguiente NodoFecha */

/**
  * @brief Constructor por defecto del struct.
  */
	NodoFecha();

/**
  * @brief Constructor con un acontecimiento
  * @param acont acontecimiento a insertar
  */
	NodoFecha(string acont);
};



class FechaHistorica{

    private:

/**
  * @brief Quita los repetidos de una fecha historica
  * @param otra_fecha fecha a la que quitar los repetidos
  */
		void QuitarRepetidos(FechaHistorica &otra_fecha);	

/**
  * @brief Vacia
  * @return Devuelve si la fecha historica esta vacia
  */
		bool Vacia();

/**
  * @brief Elimina los punteros liberando la memoria
  * @pre La lista no puede estar vacia
  */
		void Liberar();

	
    public:
		NodoFecha *puntero; /**< puntero para moverse por los acontecimientos */
		NodoFecha *primera; /**< puntero al primer acontecimiento */
		NodoFecha *ultima; /**< puntero al ultimo acontecimiento */
		int anio; /**< año */
/**
  * @brief Constructor por defecto de la clase. Inicializa los punteros en NULL
  */
		FechaHistorica();

/**
  * @brief Constructor de la clase
  * @param anio año de la fecha historica a construir
  * @return Crea una fecha historica con los punteros en NULL y el año del parametro
  */
		FechaHistorica(int anio);

/**
  * @brief Constructor de la clase
  * @param anio año de la fecha historica a construir
  * @param acont acontecimiento unico para esta fecha historica
  * @return Crea una fecha historica con los punteros en este acontecimiento y el año del parametro
  */
		FechaHistorica(int anio, string acont);

/**
  * @brief Constructor de copia
  * @param copia fecha historica a copiar
  * @return Crea una fecha historica igual a la que hemos pasado
  */
		FechaHistorica(const FechaHistorica &copia);

/**
  * @brief Destructor de la clase.
  */
		~FechaHistorica();

/**
  * @brief Obtener año
  * @return Año de la fecha historica
  */
		int getAnio();

/**
  * @brief Cambiar año
  * @param valor nuevo año elegido
  */
		void setAnio(int valor);

/**
  * @brief Imprime el contenido de una fecha historica en el formato año///acont1///acont2///...///
  */
		void Imprimir();

/**
  * @brief Busca un string dentro de los acontecimientos de la fecha historica
  * @param clave string a buscar
  * @return Devuelve un puntero al NodoFecha donde esta el string a buscar
  */
		FechaHistorica Buscar(string clave);

/**
  * @brief Busca un string dentro de un acontecimiento
  * @param a_buscar string a buscar
  * @param acont acontecimiento donde buscarla
  * @return Devuelve si la palabra se encuentra dentro del acontecimiento
  */
		bool BuscarEnAcontecimientos(string a_buscar, string acont);

/**
  * @brief Inserta un acontecimiento al principio de la fecha historica
  * @param acont acontecimiento a insertar
  */
		void InsertarPrimero(string acont);

/**
  * @brief Inserta un acontecimiento al final de la fecha historica
  * @param acont acontecimiento a insertar
  */
		void InsertarFinal(string acont);

/**
  * @brief Sobrecarga del operador <
  * @param otra_fecha segunda fecha historica a comparar con el objeto implícito
  * @return Devuelve si el año es menor que el objeto implicito
  */ 
		bool operator<(const FechaHistorica &otra_fecha);

/**
  * @brief Sobrecarga del operador >
  * @param otra_fecha segunda fecha historica a comparar con el objeto implícito
  * @return Devuelve si el año es mayor que el objeto implicito
  */ 
		bool operator>(const FechaHistorica &otra_fecha);

/**
  * @brief Sobrecarga del operador ==
  * @param otra_fecha segunda fecha historica a comparar con el objeto implícito
  * @return Devuelve si el año es el mismo en las dos fechas historicas
  */ 
		bool operator==(const FechaHistorica &otra_fecha);

/**
  * @brief Sobrecarga del operador =
  * @param copia fecha historica a copiar
  * @return Crea una fecha historica igual a la que hemos pasado
  */ 
		FechaHistorica& operator=(const FechaHistorica &copia);

/**
  * @brief Sobrecarga del operador >>
  * @param flujo istream de entrada
  * @param m objeto que recibe los valores
  * @return Devuelve el flujo que hemos ido insertando
  */ 
		friend istream& operator>>(istream &flujo, FechaHistorica &m);

/**
  * @brief Sobrecarga del operador <<
  * @pre La lista esta o no vacia
  * @param flujo ostream de salida
  * @param m objeto que da los valores
  * @return Devuelve el flujo que vamos a mostrar
  */ 
		friend ostream& operator<<(ostream &flujo, FechaHistorica &m);

/**
  * @brief Sobrecarga del operador +
  * @param fecha1 primera fecha historica a sumar
  * @param fecha2 segunda fecha historica a sumar
  * @return Devuelve la suma de las dos fechas
  */ 
		friend FechaHistorica operator+(FechaHistorica &fecha1, FechaHistorica &fecha2);


};

/**
  * @brief Sobrecarga del operador >>
  * @param flujo istream de entrada
  * @param m objeto que recibe los valores
  * @return Devuelve el flujo que hemos ido insertando
  */ 
istream& operator>>(istream &flujo, FechaHistorica &m);

/**
  * @brief Sobrecarga del operador <<
  * @pre La lista esta o no vacia
  * @param flujo ostream de salida
  * @param m objeto que da los valores
  * @return Devuelve el flujo que vamos a mostrar
  */ 
ostream& operator<<(ostream &flujo, FechaHistorica &m);

/**
  * @brief Funcion que salva una fecha historica en un archivo
  * @param nombre archivo que recibe los datos
  * @param m objeto del que coge los datos
  * @return Devuelve si se ha completado correctamente
  */ 
bool Salvar(string nombre, FechaHistorica &m);

/**
  * @brief Funcion que carga una fecha historica de un archivo
  * @param nombre archivo del que coger los datos
  * @param m objeto que recibe los datos
  * @return Devuelve si se ha completado correctamente
  */
bool Cargar(string nombre, FechaHistorica &m);

#endif 
