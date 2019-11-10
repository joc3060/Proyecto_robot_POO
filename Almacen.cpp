#include "Almacen.h"

// Constructor
Almacen::Almacen(){
    // Iniciar con un almacen vacio
    for (int i=0; i<f; i++){
        for (int j=0; j<c; j++){
            Slot slot;
            slots[i][j] = slot;
        }
    }

    // Iniciar sin ningun robot
    for (int i=0; i<f; i++){
        for (int j=0; j<c; j++){
            posRobots[i][j] = -1;
        }
    }
}

// Metodos de acceso
int Almacen::getFilas(){
    return filas;
}

int Almacen::getColumnas(){
    return columnas;
}


// Validacion
bool Almacen::coordEsValida(int coord1, int coord2){
    return (0<=coord1 && coord1<f) && (0<=coord2 && coord2<c);
}

bool Almacen::productoExiste(int coord1, int coord2, string producto, int cantidad){
    return slots[coord1][coord2].producto == producto &&
            slots[coord1][coord2].cantidad >= cantidad;
}

bool Almacen::slotDisponibleCompatible(int coord1, int coord2, string producto){
    // Se considera que puede ingresarse un producto si
    //    1. El slot esta vacio
    //    2. El slot tiene un producto del mismo tipo a almacenar
    return slots[coord1][coord2].cantidad == 0 ||
           slots[coord1][coord2].producto == producto;
}

bool Almacen::validarInstruccion(Instruccion instruccion){
    if (instruccion.operacion == "retiro"){
        // verificar que el producto que se quiere retirar exista
        return productoExiste(instruccion.destino[0], instruccion.destino[1], instruccion.producto, instruccion.cantidad);
    }
    else{
        // verificar que el slot tenga espacio para ingresar un producto o que el slot sea compatible
        return slotDisponibleCompatible(instruccion.destino[0], instruccion.destino[1], instruccion.producto);
    }
}


// Modificar slots
void Almacen::ingresarProducto(int coord1, int coord2, string producto, int cantidad){
    slots[coord1][coord2].producto = producto;
    slots[coord1][coord2].cantidad += cantidad;
}

void Almacen::retirarProducto(int coord1, int coord2, int cantidad){
    slots[coord1][coord2].cantidad -= cantidad;
    if (slots[coord1][coord2].cantidad==0) {slots[coord1][coord2].producto = "";}
}


// Estado de robots
bool Almacen::robotEn(int coord1, int coord2){
    return posRobots[coord1][coord2] != -1;
}

void Almacen::marcarRobot(int num_robot, int coord1, int coord2){
    posRobots[coord1][coord2] = num_robot;
}

void Almacen::desmarcarRobot(int coord1, int coord2){
    posRobots[coord1][coord2] = -1;
}


// Mostrar contenido de slots
void Almacen::mostrarContenido(){
    cout << " ";
    for (int i=0; i<filas; i++) cout << setw(15) << i;
    cout << endl;
    for (int i=0; i<filas; i++){
        cout << i;
        for (int j=0; j<columnas; j++){
            if (slots[i][j].cantidad==0) cout << setw(15) << " ";
            else cout << setw(15) << slots[i][j].producto << "(" << slots[i][j].cantidad << ")";
        }
        cout << endl;
    }
}

void Almacen::mostrarPosRobots(){
    cout << " ";
    for (int i=0; i<filas; i++) cout << setw(15) << i;
    cout << endl;
    for (int i=0; i<filas; i++){
        cout << i;
        for (int j=0; j<columnas; j++){
            if (posRobots[i][j] != -1) {cout << setw(15) << posRobots[i][j];}
            else {cout << setw(15) << " ";}
        }
        cout << endl;
    }
}