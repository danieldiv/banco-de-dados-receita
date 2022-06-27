APPS = ./apps
BIN = ./bin
INCLUDE = ./include
LIB = ./lib
OBJ = ./obj
SRC = ./src

FLAGS = -O3 -Wall
LIBS = -lm -led -L $(LIB) -lmysqlclient

all: libed myapps

libed: \
	$(OBJ)/util.o \
	$(OBJ)/mytime.o \
	$(OBJ)/control.o \
	$(OBJ)/etapa.o \
	$(OBJ)/ingrediente.o \
	$(OBJ)/passo.o \
	$(OBJ)/receita.o \
	$(OBJ)/usuario.o
	ar -rcs $(LIB)/libed.a $(OBJ)/*.o


myapps: clean_apps \
	$(BIN)/main

$(OBJ)/%.o: $(SRC)/%.cpp $(INCLUDE)/%.hpp
	g++ $(FLAGS) -c $< -I $(INCLUDE) -o $@

$(BIN)/%: $(APPS)/%.cpp
	g++ $(FLAGS) $< $(LIBS) -I $(INCLUDE) -o $@

run:
	$(BIN)/main

clean:
	rm -rf $(BIN)/* $(LIB)/* $(OBJ)/*

clean_apps:
	rm -rf $(BIN)/*