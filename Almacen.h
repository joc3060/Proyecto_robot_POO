#include <iostream>
#include <string>
#include <iomanip>

#include "Instruccion.h"
#include "Slot.h"
using namespace std;

// Dimensiones del almacen
const int f = 5;
const int c = 5;

class Almacen{
    private:
        Slot slots[f][c];
        int posRobots[f][c]; // Posiciones de los robots
        int filas = f;
        int columnas = c;

        bool productoExiste(int coord1, int coord2, string producto, int cantidad); // validar #1
        // verificar que el slot almacene productos del mismo tipo o que este vacio
        bool slotDisponibleCompatible(int coord1, int coord2, string producto); // validar #2
    public:
        Almacen();
        ~Almacen(){};

        int getFilas();
        int getColumnas();

        bool coordEsValida(int coord1, int coord2);
        bool validarInstruccion(Instruccion instruccion); // verificar validar #1 y #2

        void ingresarProducto(int coord1, int coord2, string producto, int cantidad);
        void retirarProducto(int coord1, int coord2, int cantidad);

        bool robotEn(int coord1, int coord2);
        void marcarRobot(int num_robot, int coord1, int coord2);
        void desmarcarRobot(int coord1, int coord2);

        void mostrarContenido(); // BORRAR, tiene que pasar a archivo
        void mostrarPosRobots(); // BORRAR
};