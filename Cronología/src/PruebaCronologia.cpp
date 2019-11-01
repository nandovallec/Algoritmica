#include "Cronologia.h"
#include "FechaHistorica.h"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char * argv[]){
	
	// ENTRADA DE DATOS

	   if (argc!=2){
	      cout<<"Dime el nombre del fichero con la cronologia"<<endl;
	      return 0;
	   }

	   ifstream f1 ("datos/Acontecimientos1.txt");
	   if (!f1){
	    cout<<"No puedo abrir el fichero Acontecimientos1" << endl;
	    return 0;
	   }

	   ifstream f2 ("datos/Acontecimientos2.txt");
	   if (!f2){
	    cout<<"No puedo abrir el fichero Acontecimientos2" << endl;
	    return 0;
	   }
	   
	   Cronologia crono;
	   if(!Cargar(argv[1], crono)){
	    cout<<"No puedo abrir el fichero "<<argv[1]<<endl;
	    return 0;
	   }
	   
	   // OPERACIONES Y SALIDA DE DATOS
	   FechaHistorica fecha1, fecha2, fecha_suma;
	   f1>>fecha1;
	   f2>>fecha2;

	   cout << endl << "------------Primera fecha historica insertada------------" << endl;
	   fecha1.Imprimir();
	   cout << endl << "-----------Segunda fecha historica insertada----------------" << endl;
	   fecha2.Imprimir();

	   cout << endl << "--------Suma de las dos fechas historicas insertadas-----------" << endl;
	   fecha_suma = fecha1 + fecha2;
	   cout << fecha_suma;

	   cout << endl << "---------Mostramos los acontecimientos que tienen su palabra clave (en este caso British)----------" << endl;
	   FechaHistorica fecha_b = fecha_suma.Buscar("British");
	   cout << fecha_b;

	   cout << endl << "**********************************************************************************" << endl;	   

	   // -------------------------------------------------------------- //

	   Cronologia crono1, crono2, crono3;
	   
	   // Cambio de años para hacer la cronologia
	  fecha1.setAnio(1990);
	   crono1.insertNewNode(fecha1);

	   fecha2.setAnio(1991);
	   crono1.insertNewNode(fecha2);

	   cout << endl << "--------- Cronología 1 formada por las dos fechas historicas anteriores ----------" << endl << crono1 << endl;
	   
	   fecha_suma.setAnio(1992);
	   crono2.insertNewNode(fecha_suma);

	   cout << endl << "--------- Cronología 2 formada por la fecha historica suma ----------" << endl << crono2 << endl;

	   cout << endl << "---------- Suma de las cronologias anteriores ----------- " << endl;
 	   Cronologia crono_suma = crono1 + crono2;
	   cout << crono_suma << endl;
	   
	   cout << endl << "------------ La cronologia entre los años 1990 y 1992 ------------------ " << endl;
	   Cronologia crono_entre_anios(crono_suma.entreAnios(1990,1992));
	   cout << crono_entre_anios << endl;
	
	   
	   crono3 =  crono.entreAnios(1989,1991);
	   cout << endl << "------------ La cronologia entre los años 1989 y 1991 ------------------ " << endl;
	   cout << crono3 << endl;

           cout << endl << "---------- Suma ordenada de las cronologias anteriores ----------- " << endl;
	   crono_entre_anios = crono_entre_anios + crono3;
	   cout << crono_entre_anios;

	   cout << endl << "---------- Mostramos un evento gracias al operador [] ----------- " << endl;
	   crono_entre_anios[1990].Imprimir();

	   cout << endl << "---------- Cronología con todos los eventos que contienen \" and \" ----------- " << endl;
	   Cronologia crono_buscar (crono.buscarEventos(" and "));
	   crono_buscar.print();

}




