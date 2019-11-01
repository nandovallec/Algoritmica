#include "Cronologia.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

NodoCrono::NodoCrono(FechaHistorica fecha){
	fecha_his = fecha;
	sig = NULL;
}

NodoCrono::NodoCrono(){
	FechaHistorica fecha;
	sig = NULL;
}

Cronologia::Cronologia(){
	first = NULL;
	last = NULL;
}


Cronologia::~Cronologia()
{
	if ( !Vacia() )
   {    
      liberar();
   }
}

Cronologia::Cronologia(const Cronologia &m){
	NodoCrono * auxiliar = m.first;
	first = last = NULL;
	while ( auxiliar != NULL){
		insertEnd(auxiliar->fecha_his);	
		auxiliar = auxiliar->sig;	
	}
		
}

void Cronologia::liberar(){
	NodoCrono *currentPtr = first;
     	NodoCrono *tempPtr;

      while ( currentPtr != NULL ) // delete remaining nodes
      {  
         tempPtr = currentPtr;
         currentPtr = currentPtr->sig;
         delete tempPtr;
      }
}

Cronologia& Cronologia::operator=(const Cronologia &copia){
	if(&copia != this){
		liberar();
		NodoCrono * auxiliar = copia.first;
		first = last = NULL;
		while ( auxiliar != NULL){
			insertEnd(auxiliar->fecha_his);	
			auxiliar = auxiliar->sig;	
		}
	}
	return *this;
}

bool Cronologia::Vacia()
{
	if(first == NULL && last == NULL) //if the start pointer and end pointer are NULL then the list is empty
		return 1;
	else
		return 0;
}


void Cronologia::insertBegin(FechaHistorica &fecha)
{
	if(Vacia()) //if the list is empty create first element of the list
	{
		NodoCrono * newPtr = new NodoCrono(); //creates new node
		newPtr -> fecha_his = fecha;
		first = newPtr; //start and end pointer are same becuase there is only one object in list
		last = newPtr;
	}else //if node(s) exist in list insert additional object before the first
	{
		NodoCrono * newPtr = new NodoCrono();
		newPtr -> fecha_his = fecha;
		newPtr->sig = first; //the next pointer of the new node points to the node that was previously first
		first = newPtr; //the pointer for the new node is now the starting node
	}
}

void Cronologia::insertEnd(FechaHistorica &fecha)
{
	if(Vacia()) //if the list is empty create first element of the list (same as first case in insert at begin)
	{
		NodoCrono *newPtr = new NodoCrono();
		newPtr -> fecha_his = fecha;
		first = newPtr;
		last = newPtr;
	}else //if node(s) exist in the list then insert new node at the end of the list
	{
		NodoCrono *newPtr = new NodoCrono();
		newPtr -> fecha_his = fecha;
		last->sig = newPtr; //the current last node's next pointer points to the new node
		last = newPtr; //the new node is now the last node in the list
	}
}




//Hay que reimplementarla bien

void Cronologia::insertNewNode(FechaHistorica fecha) //general funtionn to insert new node the proper order in the list
{
	if(Vacia()) //if there is no nodes in the list simply insert at beginning
	{
		insertBegin(fecha);
	}else //otherwise
	{
		if(fecha < first->fecha_his) //if the fecha_his of the new object is less than than the fecha_his of first node in list insert at beginning
		{
			insertBegin(fecha);
		}
		else if(fecha > last->fecha_his) //if the fecha_his of the new object is greater than than the fecha_his of last node in list insert at end
		{
			insertEnd(fecha);
		}
		else //the new node is being inserted in order but not at the beginning or end
		{
			NodoCrono * currentPtr = first;
			NodoCrono * newPtr = new NodoCrono(); //creates new node
			newPtr-> fecha_his = fecha;
			bool insertado = false;
			while(!insertado) //runs until the end of the list is reached
			{
				if((newPtr->fecha_his < currentPtr->sig->fecha_his) ){ //if the fecha_his of the new node is less the fecha_his in the next node and greater than the fecha_his in the current node, insert after current node 				
					if (newPtr->fecha_his > currentPtr->fecha_his){
						insertado = true;
						NodoCrono * next = currentPtr->sig; 
						currentPtr->sig = newPtr; //current nodes next pointer now points to the new node
						newPtr->sig = next; //the new nodes next pointer now points the node previously after the current node
					}
					else if(newPtr->fecha_his == currentPtr->fecha_his){
						insertado = true;
						currentPtr->fecha_his + newPtr -> fecha_his;
					}
				}
				currentPtr = currentPtr->sig; //moves to the next node in the list
			}
		}
	}
}

void Cronologia::print()
{
	if(Vacia())
	{
		cout << "La lista esta vacia." << endl;
	
	}else
	{
		NodoCrono * currentPtr = first;

		cout << "El contenido de la lista es: ";
		while(currentPtr != NULL) //prints until the end of the list is reached
		{
			cout << "\nEl año es: " << currentPtr->fecha_his.anio << endl;
			currentPtr->fecha_his.Imprimir() ;
			currentPtr = currentPtr->sig; //moves to next node in list
		}
		cout << endl;
	}
}


Cronologia Cronologia::buscarEventos(string clave){
	Cronologia aux;
	FechaHistorica a_aniadir;
	for (NodoCrono *iterador = first; iterador != NULL; iterador = iterador -> sig){
		a_aniadir = iterador->fecha_his.Buscar(clave);
		if (a_aniadir.primera != NULL)
			aux.insertEnd(a_aniadir);
	}

	return aux;
}

FechaHistorica Cronologia::getEventos(int anio){
	FechaHistorica a_dev;
	bool encontrado = false;
	for (NodoCrono *iterador = first; iterador -> sig != NULL && !encontrado; iterador = iterador -> sig){
		if(iterador->fecha_his.getAnio() == anio){		
			a_dev = iterador -> fecha_his;
			encontrado = true;
		}
	}
	return a_dev;
}

Cronologia Cronologia::entreAnios(int inicio, int final){
	Cronologia aux;
	inicio--;
	final++;
	for (NodoCrono *iterador = first; iterador != NULL && iterador->fecha_his.getAnio() < final; iterador = iterador -> sig)
		if(iterador->fecha_his.getAnio() > inicio && iterador->fecha_his.getAnio() < final)
			aux.insertEnd(iterador -> fecha_his);
	return aux;
}

FechaHistorica& Cronologia::operator[](int anio){
	FechaHistorica *a_dev = new FechaHistorica;
	bool encontrado = false;
	for (NodoCrono *iterador = first; iterador != NULL && !encontrado; iterador = iterador -> sig){
		if(iterador->fecha_his.getAnio() == anio){		
			return iterador->fecha_his;
		}
	}
	return *a_dev;
}

Cronologia Cronologia::operator+(Cronologia &otra_crono){
	Cronologia *resultado = new Cronologia();
	NodoCrono *newPtr = new NodoCrono();
	newPtr = first;
	NodoCrono *newPtr2 = new NodoCrono();
	newPtr2 = otra_crono.first;
	while(newPtr != NULL && newPtr2 != NULL){
		if(newPtr->fecha_his.getAnio() < newPtr2->fecha_his.getAnio()){
			resultado->insertEnd(newPtr->fecha_his);
			newPtr = newPtr->sig;
		}
		else if(newPtr->fecha_his.getAnio() > newPtr2->fecha_his.getAnio()){
			resultado->insertEnd(newPtr2->fecha_his);
			newPtr2 = newPtr2->sig;
		}
		else{
			FechaHistorica aniade = (newPtr->fecha_his)+(newPtr2->fecha_his);
			cout << "micarro";
			resultado->insertEnd(aniade);
			newPtr = newPtr->sig;
			newPtr2 = newPtr2->sig;
		}
	}
	if(newPtr == NULL){
		while(newPtr2!= NULL){
			resultado->insertEnd(newPtr2->fecha_his);
			newPtr2 = newPtr2->sig;
		}
	}
	else if(newPtr2 == NULL){
		while(newPtr != NULL){
			resultado->insertEnd(newPtr->fecha_his);
			newPtr = newPtr->sig;
		}
	}
	return *resultado;
}

istream& operator>>(istream &flujo, Cronologia &m){
	unsigned int i;
	std::string acon, aux="";
	FechaHistorica aniadir;
	cout << "\nIntroduza el año y los acontecimientos separados por #"<<endl;
	getline(flujo, acon, '\n');
	while(acon != ""){
		aux="";
		for(i = 0; acon[i] != '#';i++)
			aux.push_back(acon[i]);
		aniadir.setAnio(stoi(aux));
		i++;
		while(i < acon.length()){
			aux = "";
			while(acon[i]!='#' && i != acon.length()-1){
				aux.push_back(acon[i]);
				i++;
			}
			i++;
			aniadir.InsertarFinal(aux);
		}
		m.insertEnd(aniadir);
		aniadir = FechaHistorica();
		getline(flujo, acon, '\n');
	}	
	return flujo;
}

bool Cargar(string nombre, Cronologia &m){
	ifstream fi(nombre.c_str());
	if (fi){
		fi >> m;
		fi.close();
		return true;
	}
	else
		return false;
}

ostream& operator<<(ostream &flujo, Cronologia &m){
	NodoCrono *newPtr = m.first;
	NodoFecha *aux;
	while(newPtr != NULL){
		flujo << newPtr->fecha_his.getAnio() <<'#';
		aux = newPtr->fecha_his.primera;
		while(aux->siguiente != NULL){
			flujo << aux->acontecimiento << '#';
			aux = aux-> siguiente;
		}
		newPtr = newPtr->sig;
		flujo << endl;
	}
	return flujo;
}

bool Salvar(string nombre, Cronologia &m){
	ofstream fo(nombre.c_str(), ios::out);
	if(fo){
		fo << m;
		fo.close();
		return true;
	}
	else
		return false;
}










