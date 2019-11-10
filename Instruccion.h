#include <iostream>
#include <string>
using namespace std;

class Instruccion{
    public:
        int numero;
        string operacion;
        int destino[2];
        string producto;
        int cantidad;

        Instruccion(int _numero, string _operacion, int coord1_dest, int coord2_dest, string producto, int _cantidad);
};