#include "FechaHistorica.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

//Constructor del Nodo con string
NodoFecha::NodoFecha(string acont){
    	acontecimiento = acont;
	siguiente = NULL;
}

//Constructor por defecto del Nodo
NodoFecha::NodoFecha(){
	acontecimiento = "";
	siguiente = NULL;
}

//Constructor por defecto de FechaHistorica
FechaHistorica::FechaHistorica(){
	puntero = NULL;	
	primera = NULL;
	ultima = NULL;
	anio = 0;
}

//Constructor con parámetros de año
FechaHistorica::FechaHistorica(int anio){
	puntero = primera = ultima = NULL;
	this->anio = anio;
}

//Constructor con parámetros de año y acontecimiento
FechaHistorica::FechaHistorica(int anio, string acont){
	puntero = new NodoFecha(acont);
	primera = ultima = puntero;
	this->anio = anio;
}

//Construcotr de copia
FechaHistorica::FechaHistorica(const FechaHistorica &copia){
	this->anio = copia.anio;
	NodoFecha * auxiliar = copia.primera;
	primera = ultima = NULL;
	while ( auxiliar != NULL){	
		InsertarFinal(auxiliar->acontecimiento);		
		auxiliar = auxiliar->siguiente;	
	}
}

//Destructor
FechaHistorica::~FechaHistorica(){
	Liberar();
}

//Destruye la memoria dinámica creada
void FechaHistorica::Liberar(){
	if ( !Vacia() ){ 				
		NodoFecha *actual = primera;
		NodoFecha *aux;
	
		while ( actual != ultima ){			
		    aux = actual;
		    actual = actual->siguiente;
		    delete aux;
		}
		delete actual;
    }
}

//Devuelve el año
int FechaHistorica::getAnio(){
	return anio;
}

//Establece/Cambia el año
void FechaHistorica::setAnio(int valor){
	anio = valor;
}

//Insertar al principio
void FechaHistorica::InsertarPrimero(string acont){
	if( Vacia() ){						//Diferenciamos si la lista esta vacia o no
		NodoFecha *nuevo = new NodoFecha(acont);		
		primera = nuevo;					//Asignamos punteros
		ultima = nuevo;
    
	}else{							//Si no esta vacía
		NodoFecha *nuevo = new NodoFecha(acont);
		nuevo->siguiente = primera;				
		primera = nuevo;					//Cambiamos el puntero primera al nuevo insertado
    }
}

//Insertar al final
void FechaHistorica::InsertarFinal(string acont){
	if( Vacia() ){					//Diferenciamos si la lista esta vacia o no
		NodoFecha *nuevo = new NodoFecha(acont);
		primera = nuevo;				//Asignamos punteros
		ultima = nuevo;
    
	}else{						//Si no esta vacía
		NodoFecha *nuevo = new NodoFecha(acont);
		ultima->siguiente = nuevo;
		ultima = nuevo;						//Cambiamos el puntero ultima al nuevo insertado
	}
}

//Imprime en pantalla la FechaHistorica
void FechaHistorica::Imprimir(){
	if( Vacia() )			//En caso de que este vacía
		cout << "La lista esta vacia." << endl;

	else{
		NodoFecha *actual = primera;

		cout << "Los acontecimientos en " << anio << " son: ";

		while(actual != NULL){ 					//Iteramos sobre los eventos imprimiendolos.
		    cout << actual->acontecimiento << "///";
		    actual = actual->siguiente; 		//Nos movemos al siguiente nodo.
		}
	
		cout << endl;
	    }
}

//Comprobación si la lista esta vacía
bool FechaHistorica::Vacia(){
	if (primera == 0 && ultima == 0) 
		return 1;
	else
		return 0;
}

//Busca un string entre todos los eventos de la FechaHistorica
FechaHistorica FechaHistorica::Buscar(string clave){ 
	NodoFecha* nodo;
	FechaHistorica auxiliar;
	auxiliar.setAnio(anio);
	nodo = primera;

	while (nodo != NULL){		 					//Iteramos sobre la lista
		if (BuscarEnAcontecimientos(clave, nodo->acontecimiento)) 	//Si el string se encuentra en el evento lo añadimos
			auxiliar.InsertarFinal(nodo->acontecimiento);
		nodo = nodo->siguiente; 					//Nos movemos al siguiente nodo
	}

	return auxiliar;	
}

//Devuelve si una cadena se encuentra dentro de otra
bool FechaHistorica::BuscarEnAcontecimientos(string a_buscar, string acont){
	if (acont.find(a_buscar)!=std::string::npos)
		return true;
	else
		return false;
	
}

//Quita los repetidos de una fecha en otra.
void FechaHistorica::QuitarRepetidos(FechaHistorica &otra_fecha){
	puntero = primera;
	NodoFecha *auxiliar;
		
	while (puntero != NULL){
		otra_fecha.puntero = otra_fecha.primera;	
		while (otra_fecha.puntero != NULL){
			
			if (puntero->acontecimiento == otra_fecha.primera->acontecimiento){
				auxiliar = otra_fecha.primera;
				otra_fecha.primera = otra_fecha.primera->siguiente;
				delete auxiliar;
			}
			
			if (puntero->acontecimiento == otra_fecha.ultima->acontecimiento){
				auxiliar = otra_fecha.primera;
				while(auxiliar->siguiente != otra_fecha.ultima)
					auxiliar = auxiliar -> siguiente;
				delete auxiliar->siguiente;
				auxiliar->siguiente = NULL;
				otra_fecha.ultima = auxiliar;
			}
			
			if (puntero->acontecimiento == (otra_fecha.puntero->siguiente)->acontecimiento){
				auxiliar = otra_fecha.puntero->siguiente;
				otra_fecha.puntero->siguiente = otra_fecha.puntero->siguiente->siguiente;
				delete auxiliar;
			}

			otra_fecha.puntero = otra_fecha.puntero->siguiente;
		}
		
		puntero = puntero->siguiente;
	}
} 

//Operado < para comparar años de las fechas
bool FechaHistorica::operator<(const FechaHistorica &otra_fecha){
	if ( anio < otra_fecha.anio )
		return true;
	else
		return false;
}

//Operador > para comparar años de las fechas
bool FechaHistorica::operator>(const FechaHistorica &otra_fecha){
	if ( anio > otra_fecha.anio )
		return true;
	else
		return false;
}

//Operador == para comparar años de las fechas
bool FechaHistorica::operator==(const FechaHistorica &otra_fecha){
	if ( anio == otra_fecha.anio )
		return true;
	else
		return false;
}

//Operador de asignación
FechaHistorica& FechaHistorica::operator=(const FechaHistorica &copia){
	if(&copia != this){
		Liberar();	//Liberamos el espacio por si acaso
		this->anio = copia.anio;
		NodoFecha * auxiliar = copia.primera;
		primera = ultima = NULL;
		while ( auxiliar != NULL){	
			InsertarFinal(auxiliar->acontecimiento);
			auxiliar = auxiliar->siguiente;	
		}
		
	}
	return *this;
}

//Operador +, fusiona dos fechas devolviendo otra con ambos eventos sin repeticiones
FechaHistorica operator+(FechaHistorica &fecha1, FechaHistorica &fecha2){	
	if ( fecha1.getAnio() == fecha2.getAnio() ){	
		FechaHistorica suma = fecha1;
		fecha2.puntero = fecha2.primera;
		bool aparece = false;
		while(fecha2.puntero != NULL){
			
			suma.puntero = suma.primera;
			while (suma.puntero != NULL){
				if (fecha2.puntero->acontecimiento == suma.puntero->acontecimiento)
					aparece = true;
				suma.puntero = suma.puntero->siguiente;
			}
			if(!aparece)
				suma.InsertarFinal(fecha2.puntero->acontecimiento);
			fecha2.puntero = fecha2.puntero->siguiente;
		}
	
		return suma;
			
	}

	else
		return -1;
}


//Operador >> para introducir el flujo en las FechasHistoricas
istream& operator>>(istream &flujo, FechaHistorica &m){
	m.Liberar();

	string cadena, subcadena;
	getline(flujo, cadena, '\n');
    
	unsigned int contador = 0;
	while (cadena[contador] != '#'){
		subcadena[contador] = cadena[contador];
		contador++;
	}    	
	m.setAnio( atoi(subcadena.c_str()) );
	contador++;
    
	int contador_acont = 0;
	while ( contador < cadena.size() ){
		if (cadena[contador] != '#' && contador != cadena.size() - 1)
    			subcadena.push_back( cadena[contador] );
		else{
			m.InsertarFinal(subcadena);
			subcadena.clear();
			contador_acont = -1;
		}
    	contador++;
	contador_acont++;
	
	}
	
	return flujo;
}


//Funcion que carga un archivo (con el formato correcto) en una FechaHistorica
bool Cargar(string nombre, FechaHistorica &m){
	ifstream fi(nombre.c_str());
	if (fi){
		fi >> m;
		fi.close();
		return true;
	}
	else
		return false;
}


//Operador << para mostrar las fechas de una forma mas facil.
ostream& operator<<(ostream &flujo, FechaHistorica &m){
	if( m.Vacia() )
		flujo << "La lista esta vacia." << endl;

	else{
		NodoFecha *actual = m.primera;

		flujo << "Los acontecimientos en " << m.anio << " son: ";

		while(actual != NULL){
		    flujo << actual->acontecimiento << "///";
		    actual = actual->siguiente;
		}
	
		flujo << endl;
	    }	
	return flujo;	
}


//Funcion que guarda en un archivo externo una fecha historica
bool Salvar(string nombre, FechaHistorica &m){
	ofstream fo(nombre.c_str(), ios::out);
	if(fo){
		fo << m;
		fo.close();
		return true;
	}
	else
		return false;
}






