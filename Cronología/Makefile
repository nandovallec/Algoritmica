SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
CPPFLAGS = -Wall -g  -I$(INC) -c -std=c++11


all: $(BIN)/pruebacronologia clean
# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

	
# ************ Compilación de módulos ************
$(BIN)/pruebacronologia: $(OBJ)/PruebaCronologia.o $(OBJ)/FechaHistorica.o $(OBJ)/Cronologia.o
	g++ -o $@ $^

$(OBJ)/PruebaCronologia.o: $(SRC)/PruebaCronologia.cpp
	g++ -o $@ $^ $(CPPFLAGS)

$(OBJ)/FechaHistorica.o: $(SRC)/FechaHistorica.cpp $(INC)/FechaHistorica.h
	g++ -o $@ $< $(CPPFLAGS)

$(OBJ)/Cronologia.o: $(SRC)/Cronologia.cpp $(INC)/Cronologia.h
	g++ -o $@ $< $(CPPFLAGS)
	


# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
