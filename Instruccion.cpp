#include "Instruccion.h"

Instruccion::Instruccion(int _numero, string _operacion, int coord1_dest, int coord2_dest, string _producto, int _cantidad){
    numero = _numero;
    operacion = _operacion;
    destino[0] = coord1_dest;
    destino[1] = coord2_dest;
    producto = _producto;
    cantidad = _cantidad;
}