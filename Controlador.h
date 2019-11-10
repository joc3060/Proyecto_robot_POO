#include <iostream>
#include "Robot.h" // Incluye Almacen e Instruccion

using namespace std;

class Controlador{
    private:
        Almacen almacen;
        vector<Robot> robots;
    public:
        void input_robots();
        void input_instrucciones();
        void ejecutar_instrucciones();
        void informacion_robots(); // Borrar
        void informacion_almacen(); // Borrar
};