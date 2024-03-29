#include "../include/quienesquien.h"
#include <sstream>
#include <iostream>
#include <iterator>
#include <math.h>
#include <algorithm>
#include <limits>

QuienEsQuien::QuienEsQuien(){
	//TODO :) No se pone nada
}
QuienEsQuien::QuienEsQuien(const QuienEsQuien &quienEsQuien){
	copia(quienEsQuien);
}
QuienEsQuien& QuienEsQuien::operator= (const QuienEsQuien &quienEsQuien){
	if(this != &quienEsQuien){
		copia(quienEsQuien);
	}
	return *this;
}

void QuienEsQuien::copia(const QuienEsQuien &quienEsQuien){
	personajes = quienEsQuien.personajes;
	atributos = quienEsQuien.atributos;
	tablero = quienEsQuien.tablero;
	arbol = quienEsQuien.arbol;
	jugada_actual = quienEsQuien.jugada_actual;
}

QuienEsQuien::~QuienEsQuien(){
	this->limpiar();
}

void QuienEsQuien::limpiar(){
	//TODO :) No se pone nada
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
  if ( !v.empty() ) {
    out << '[';
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
    out << "\b\b]";
  }
  return out;
}

void QuienEsQuien::mostrar_estructuras_leidas(){
	cout << "personajes: "<< (this->personajes) << endl;
	cout << "atributos:  "<< (this->atributos)  << endl;
	cout << "tablero:    "<< endl;


	// Escribe la cabecera del tablero
	for(vector<string>::iterator it_atributos = this->atributos.begin();
		it_atributos != this->atributos.end();
		it_atributos++){
		cout << *it_atributos << "\t";
	}
	cout <<endl;

	int indice_personaje = 0;
	for(vector<vector<bool>>::iterator it_tablero_atributos = tablero.begin();
		it_tablero_atributos!= tablero.end();
		it_tablero_atributos++){

		string personaje = this->personajes[indice_personaje];
		int indice_atributo = 0;
		for(vector<bool>::iterator it_atributos_personaje = (*it_tablero_atributos).begin();
			it_atributos_personaje != (*it_tablero_atributos).end();
			it_atributos_personaje++){

			cout << *it_atributos_personaje<<"\t";

			indice_atributo++;
		}

		cout << personaje << endl;

		indice_personaje++;
	}

}

/**
  * @brief Devuelve una copia de la cadena original sin las subcadenas no deseadas.
  * 
  * @param cadena_original Cadena de la que se eliminan las subcadenas no deseadas.
  * @param cadena_a_eliminar Subcadena que se busca y se elimina.
  *
  * @return Copia de la cadena original sin las subcadenas no deseadas.
  */
string limpiar_string(string cadena_original,string cadena_a_eliminar){
	string linea(cadena_original);

	while(linea.find_first_of(cadena_a_eliminar) != std::string::npos){
		linea.erase(linea.find_first_of(cadena_a_eliminar),cadena_a_eliminar.length());
	}

	return linea;
}

istream& operator >> (istream& is, QuienEsQuien &quienEsQuien) {
	quienEsQuien.limpiar();
	
  	if(is.good()){
  		string linea;
    	getline(is, linea, '\n');

    	linea = limpiar_string(linea,"\r");
    	
    	while(linea.find('\t') != string::npos ){
    		string atributo = linea.substr(0,linea.find('\t'));
			quienEsQuien.atributos.push_back(atributo);
    		linea = linea.erase(0,linea.find('\t')+1);
    	}

		assert(linea ==  "Nombre personaje");
	}
	
    while( is.good() ) {
    	string linea;
    	getline(is, linea, '\n');
    	linea = limpiar_string(linea,"\r");

    	//Si la linea contiene algo extrae el personaje. Si no lo es, la ignora.
    	if(linea != ""){;
	    	vector<bool> atributos_personaje;
	    	
	    	int indice_atributo=0;
	    	while(linea.find('\t') != string::npos){
	    		string valor = linea.substr(0,linea.find('\t'));
	    		
	    		assert(valor == "0" || valor == "1");
	    		
	    		bool valor_atributo = valor == "1";
	    		
	    		atributos_personaje.push_back(valor_atributo);
				
	    		linea = linea.erase(0,linea.find('\t')+1);
	    		indice_atributo++;
			}
			
			string nombre_personaje = linea;
	    	
	    	quienEsQuien.personajes.push_back(nombre_personaje);
	    	quienEsQuien.tablero.push_back(atributos_personaje);
	    }
  	}
  	
	return is;
}

ostream& operator << (ostream& os, const QuienEsQuien &quienEsQuien){

	//Escribimos la cabecera, que contiene los atributos y al final una columna para el nombre
	for(vector<string>::const_iterator it_atributos = quienEsQuien.atributos.begin();
		it_atributos != quienEsQuien.atributos.end();
		it_atributos++){

		os  << *it_atributos << "\t";
	}
	os << "Nombre personaje" << endl;

	//Rellenamos con ceros y unos cada l�nea y al final ponemos el nombre del personaje.
	for(int indice_personaje=0;indice_personaje<quienEsQuien.personajes.size();indice_personaje++){
		for(int indice_atributo=0;indice_atributo<quienEsQuien.atributos.size();indice_atributo++){

			os  << quienEsQuien.tablero[indice_personaje][indice_atributo] << "\t";
		}
		os  << quienEsQuien.personajes[indice_personaje] << endl;
	}

	return os;
}

/**
  * @brief Convierte un n�mero a un vector de bool que corresponde 
  *        con su representaci�n en binario con un numero de digitos
  *        fijo.
  *
  * @param n N�mero a convertir en binario.
  * @param digitos N�mero de d�gitos de la representaci�n binaria.
  *
  * @return Vector de booleanos con la representaci�n en binario de @e n 
  *      con el n�mero de elementos especificado por @e digitos. 

  */
vector<bool> convertir_a_vector_bool(int n, int digitos) {
  vector<bool> ret;
  while(n) {
    if (n&1){
      ret.push_back(true);
    } else{
      ret.push_back(false);
    }
    n>>=1;  
  }

  while(ret.size()<digitos){
  	ret.push_back(false);
  }

  reverse(ret.begin(),ret.end());
  return ret;
}

bintree<Pregunta> QuienEsQuien::crear_arbol()
{
	set<int> pers;
	set<int> preg;
	for(int i = 0; i < personajes.size(); i++)
		pers.insert(i);
	for(int i = 0; i < atributos.size(); i++)
		preg.insert(i);

	int pregunta = MejorPregunta(pers, preg);
	Pregunta nodo(atributos[pregunta], personajes.size());
	preg.erase(pregunta);
	bintree<Pregunta> arbol(nodo);
	creacion(pers, preg, arbol.root(), pregunta);

	return arbol;
}

void QuienEsQuien::creacion(set<int> personajes_restantes, set<int> preguntas_restantes, bintree<Pregunta>::node n, int n_pregunta ){
	set<int> pers_izq = cumplenPregunta(personajes_restantes, n_pregunta, true);
	set<int> pers_der = cumplenPregunta(personajes_restantes, n_pregunta, false);

	if(pers_izq.size() > 1){

		int pregunta_izq = MejorPregunta(pers_izq, preguntas_restantes);
		Pregunta nodo_izq(atributos[pregunta_izq], pers_izq.size());
		arbol.insert_left(n, nodo_izq);

		set<int> preg_izq = preguntas_restantes;
		preg_izq.erase(pregunta_izq);
		creacion(pers_izq, preg_izq, n.left(), pregunta_izq);
		
	}else if(pers_izq.size() == 1) {
		Pregunta nodo_izq(personajes[*(pers_izq.begin())], 1);
		arbol.insert_left(n, nodo_izq);
	}

	if(pers_der.size() > 1){

		int pregunta_der = MejorPregunta(pers_der, preguntas_restantes);
		Pregunta nodo_der(atributos[pregunta_der], pers_der.size());
		arbol.insert_right(n, nodo_der);

		set<int> preg_der = preguntas_restantes;
		preg_der.erase(pregunta_der);
		creacion(pers_der, preg_der, n.right(), pregunta_der);
		
	}else if(pers_der.size() == 1) {
		Pregunta nodo_der(personajes[*(pers_der.begin())], 1);
		arbol.insert_right(n, nodo_der);
	}

	

}

set<int> QuienEsQuien::cumplenPregunta(set<int> personajes, int n_pregunta, bool cumple){
	set<int> devolver;
	for (std::set<int>::iterator it = personajes.begin() ; it != personajes.end(); ++it){
		if(tablero[*it][n_pregunta] == cumple)
			devolver.insert(*it);
	}
	return devolver;
}

int QuienEsQuien::MejorPregunta(set<int> personajes_restantes, set<int> preguntas_restantes){
	int devolver, n_falsos = 0, n_verdaderos = 0;
	int total = personajes.size();
	for (std::set<int>::iterator it2 = preguntas_restantes.begin() ; it2 != preguntas_restantes.end(); ++it2){
		for(std::set<int>::iterator it = personajes_restantes.begin() ; it != personajes_restantes.end(); ++it){
			if( tablero[(*it)][(*it2)] == true)
				++n_verdaderos;
			else
				++n_falsos;
		}
		if (total > abs(n_verdaderos - n_falsos)){
			total = abs(n_verdaderos - n_falsos);
			devolver = *it2;
		}
		n_falsos = n_verdaderos = 0;
	}
	return devolver;
}

void QuienEsQuien::usar_arbol(bintree<Pregunta> arbol_nuevo){
	arbol = arbol_nuevo;
}

void QuienEsQuien::iniciar_juego(){
	jugada_actual = arbol.root();
	string respuesta = "";
	set<string> afirmacion = {"si", "s" , "yes", "y"}, personajes_levantados;

	while((*jugada_actual).es_pregunta()){

		personajes_levantados = informacion_jugada(jugada_actual);

		cout << "\nLos personajes que quedan levantados son: "; 
		for(std::set<string>::iterator it = personajes_levantados.begin(); it != personajes_levantados.end(); ++it)
			cout << *it << ", ";
		cout << endl;

		cout << (*jugada_actual).obtener_pregunta() << endl;
		std::getline(cin, respuesta, '\n');
		transform(respuesta.begin(), respuesta.end(), respuesta.begin(),(int (*)(int))tolower);
		if(afirmacion.count(respuesta) == 1)
			jugada_actual = jugada_actual.left();
		else
			jugada_actual = jugada_actual.right();
		
	}
	preguntas_formuladas(jugada_actual);
	
	cout << "�Ya lo s�! Tu personaje es: " << (*jugada_actual).obtener_personaje() << endl;
}

set<string> QuienEsQuien::informacion_jugada(bintree<Pregunta>::node jugada_actual){
	set<string> personajes_levantados;
	bintree<Pregunta> subarbol;
	subarbol.assign_subtree(arbol, jugada_actual);

	for(bintree<Pregunta>::preorder_iterator it = subarbol.begin_preorder(); it != subarbol.end_preorder(); ++it){
		if( (*it).es_personaje() ){
			personajes_levantados.insert((*it).obtener_personaje());
		}
	}

	return personajes_levantados;
}

void escribir_esquema_arbol(ostream& ss, const bintree<Pregunta>& a, bintree<Pregunta>::node n, string& pre){

	if (n.null()){
	    ss << pre << "-- x" << endl;
	} else {
	    ss << pre << "-- " << (*n) << endl;
	    if ( !n.right().null() || !n.left().null()) {// Si no es una hoja
			pre += "   |";
	    	escribir_esquema_arbol(ss,a, n.right(), pre);
	     	pre.replace(pre.size()-4, 4, "    ");
	      	escribir_esquema_arbol (ss,a, n.left(), pre);
	      	pre.erase(pre.size()-4, 4);    
	    }
  	}
}

void QuienEsQuien::escribir_arbol_completo() const{
	string pre = "";
	if(arbol.root().null())
		cout << "si";
	escribir_esquema_arbol(cout,this->arbol,this->arbol.root(),pre);
}

void QuienEsQuien::eliminar_nodos_redundantes(){
	// TODO ^^ El arbol se crea directamente sin nodos redundantes
}

float QuienEsQuien::profundidad_promedio_hojas(){
	if(arbol.empty())
		return -1;
	else{
		vector<int> profundidad;
		float total = 0;

		for(bintree<Pregunta>::preorder_iterator it = arbol.begin_preorder(); it != arbol.end_preorder(); ++it){
			if( (~it).left().null() && (~it).right().null()){
				profundidad.push_back(arbol.depth(~it));
			}
		}

		for(std::vector<int>::iterator it = profundidad.begin() ; it != profundidad.end(); ++it)
			total += *it;
		
		total = total / (float) profundidad.size();
		return total;

	}
}

void QuienEsQuien::preguntas_formuladas(bintree<Pregunta>::node jugada_actual){
	cout << "El personaje oculto tiene las siguientes caracter�sticas: " << endl;
	while(jugada_actual != arbol.root()){
		cout << (*(jugada_actual.parent())).obtener_pregunta() << " - ";
		if(jugada_actual == jugada_actual.parent().left())
			cout << "si" << endl;
		else
			cout << "no" << endl;
		jugada_actual = jugada_actual.parent();
	}

	cout << "Pero a�n no s� cu�l es." << endl;
}

void QuienEsQuien::aniade_personaje(string nombre, vector <bool> caracteristicas){
	bintree<Pregunta>::node n = arbol.root();
	int i;
	bool encontrada =  false;
	set <int> preg_usadas;
	while((*n).es_pregunta()){
		for(i = 0; i < atributos.size() && !encontrada; ++i){
			if((*n).obtener_pregunta() == atributos[i]){
				encontrada = true;
				preg_usadas.insert(i);
			}
		}
		i--;
		if(caracteristicas[i])
			n = n.left();
		else
			n = n.right();

		encontrada = false;
	}
	int num_personaje;
	for(num_personaje = 0; i < personajes.size() && !encontrada; ++i)
		if (personajes[num_personaje] == (*n).obtener_personaje())
			encontrada = true;

	encontrada =  false;

	for(i = 0; i < atributos.size() && !encontrada; ++i)	//Encontramos la primera pregunta que no hayamos usado
		if(preg_usadas.count(i) == 0){
			if (!(caracteristicas[i]) && tablero[num_personaje][i])
				encontrada = true;
			else if (caracteristicas[i] && !(tablero[num_personaje][i]))
				encontrada = true;
		}
	--i; //El bucle le esta sumando 1 en la ultima iteracion

	Pregunta nueva_preg(atributos[i], 2);
	Pregunta nuevo(nombre, 1), antiguo(*n);
	if(n.parent().left() == n){
		n = n.parent();
		arbol.insert_left(n, nueva_preg);
		n = n.left();
	}else{
		n = n.parent();
		arbol.insert_right(n, nueva_preg);
		n = n.right();
	}

	if(caracteristicas[i]){
		arbol.insert_left(n, nuevo);
		arbol.insert_right(n, antiguo);
	}else{
		arbol.insert_left(n, antiguo);
		arbol.insert_right(n, nuevo);
	}
	
}

void QuienEsQuien::elimina_personaje(string nombre){
	bool encontrado = false;
	bintree<Pregunta>::preorder_iterator it = arbol.begin_preorder();
	while( it != arbol.end_preorder() && !encontrado){
		if((*it).es_personaje()){
			if((*it).obtener_personaje() == nombre)
				encontrado = true;
			else
				++it;
		}
		else
			++it;
			
	}

	bintree<Pregunta>::node n = ~it;
	Pregunta aux;

	if(n.parent().left() == n){	//Obtenemos la pregunta que hay que conservar
		n = n.parent();
		aux = *(n.right());
	}else{
		n = n.parent();
		aux = *(n.left());
	}

	if(n.parent().left() == n){
		n = n.parent();
		arbol.insert_left(n, aux);
	}else{
		n = n.parent();
		arbol.insert_right(n, aux);
	}

}

/**
 * @brief Genera numero enteros positivos aleatorios en el rango [min,max).
**/

int generaEntero(int min, int max){
    int tam= max -min;
    return ((rand()%tam)+min);
}

void QuienEsQuien::tablero_aleatorio(int numero_de_personajes){
	srand(0);

	this->limpiar();

	float log_2_numero_de_personajes = log(numero_de_personajes)/log(2);

	int numero_de_atributos = ceil(log_2_numero_de_personajes);

	cout << "Petici�n para generar "<< numero_de_personajes<<" personajes ";
	cout << "con "<<numero_de_atributos<< " atributos"<<endl;
	cout << "Paso 1: generar "<< pow(2,numero_de_atributos) << " personajes"<<endl;

	//Fase 1: completar el tablero con todos los personajes posibles
	//Completo el tablero y los nombres de personajes a la vez
	for(int indice_personaje=0;indice_personaje< pow(2,numero_de_atributos);indice_personaje++){
		vector<bool> atributos_personaje = convertir_a_vector_bool(indice_personaje,numero_de_atributos);
		string nombre_personaje = "Personaje_"+to_string(indice_personaje);

		this->personajes.push_back(nombre_personaje);
		this->tablero.push_back(atributos_personaje);
	}

	// Completo los nombres de los atributos.
	for(int indice_atributo=0;indice_atributo<numero_de_atributos;indice_atributo++){
		string nombre_atributo = "Atr_"+to_string(indice_atributo);
		this->atributos.push_back(nombre_atributo);
	}

	cout << "Paso 2: eliminar "<< (pow(2,numero_de_atributos)-numero_de_personajes) << " personajes"<<endl;
	//Fase 2. Borrar personajes aleatoriamente hasta que quedan solo los que hemos pedido.
	while(personajes.size()>numero_de_personajes){
		int personaje_a_eliminar = generaEntero(0,personajes.size());

		personajes.erase(personajes.begin()+personaje_a_eliminar);
		tablero.erase(tablero.begin()+personaje_a_eliminar);
	}
}
