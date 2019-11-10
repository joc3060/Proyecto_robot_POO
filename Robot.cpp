#include "Robot.h"

Robot::Robot(int _numero, int _origen1, int _origen2, Almacen* _almacen){
    numero = _numero;
    origen[0] = _origen1;
    origen[1] = _origen2;
    coordActual[0] = _origen1;
    coordActual[1] = _origen2;
    almacen = _almacen;

    almacen->marcarRobot(_numero, _origen1, _origen2);
}

void Robot::agregarInstruccion(Instruccion instruccion){
    instrucciones.push_back(instruccion);
}

// Movimiento
int Robot::direccion(int actual, int destino){
    if (destino > actual){ // se debe avanzar (ir abajo o a la derecha)
        return 1;
    }
    else{ // se debe retroceder (arriba o izquierda)
        return -1;
    }
}

bool Robot::moverse(int dest1, int dest2){ // y x
    almacen->desmarcarRobot(coordActual[0], coordActual[1]); // borrar la marca actual porque se actualizara despues
    int avanzarY = Robot::direccion(coordActual[0], dest1);
    // avanzar mientras que no se haya llegado a la altura del destino
    while (coordActual[0] != dest1){
        cout << "CoordActual: " << coordActual[0] << " " << coordActual[1] << endl;
        if ( almacen->robotEn(coordActual[0] + avanzarY, coordActual[1])) { // colision
            cout << "Colision en Y. Robot en " << coordActual[0] + avanzarY << " " << coordActual[1] << endl;
            almacen->marcarRobot(numero, coordActual[0], coordActual[1]);
            return false;
        }
        coordActual[0] += avanzarY;
    }

    int avanzarX = Robot::direccion(coordActual[1], dest2);
    // avanzar mientras que no haya llegado al destino
    while (coordActual[1] != dest2){
        cout << "CoordActual: " << coordActual[0] << " " << coordActual[1] << endl;
        if ( almacen->robotEn(coordActual[0], coordActual[1] + avanzarX)) { // colision
            cout << "Colision en X. Robot en " << coordActual[0] << " " << coordActual[1] + avanzarX << endl; 
            almacen->marcarRobot(numero, coordActual[0], coordActual[1]);
            return false;
        }
        coordActual[1] += avanzarX;
    }

    // se llego al objetvo
   almacen->marcarRobot(numero, coordActual[0], coordActual[1]); // actualizar posicion del robot en el almacen
    return true;
}

bool Robot::siguienteInstruccion(){
    // IMPORTANTE: Si devuelve false por colision, se debe updatear la instruccion para evitar que haga cosas repetidas.

    if (termino()){
        return true;
    }

    // Para verificar si una instruccion es correcta:
    // En Almacen: verificar si el producto a retirar existe o
    //             verificar si el slot del producto a ingresar tenga espacio 
    //                          o sea del mismo tipo que el producto que esta ocupando espacio

    // Instruccion no valida
    while (!almacen->validarInstruccion(instrucciones[proximaInstruccion])){
        cout << "Instruccion #" << proximaInstruccion << "no es valida, salteando" << endl;
        proximaInstruccion++;
        return siguienteInstruccion();
    }

    // Instruccion valida
    string operacionIns = instrucciones[proximaInstruccion].operacion;
    int destinoIns[2] = {
                    instrucciones[proximaInstruccion].destino[0],
                    instrucciones[proximaInstruccion].destino[1]
                };
    string productoIns = instrucciones[proximaInstruccion].producto;
    int productoCant = instrucciones[proximaInstruccion].cantidad;


    // volver al origen si hay algun paquete que dejar
    if (operacionIns=="ingreso"){
        if (!moverse(origen[0], origen[1])) { return false; }
        llevaProducto = true; // recogio producto
    }

    // ir al destino
    if (!moverse(destinoIns[0], destinoIns[1])) { return false; }

    if (operacionIns=="ingreso") {
        llevaProducto = false; // dejo producto

        // actualizar almacen, el producto se ha dejado ahi
        almacen->ingresarProducto(destinoIns[0], destinoIns[1], productoIns, productoCant);
    }
    else{
        llevaProducto = true; // recogio producto

        // actualizar almacen, el producto ya no esta ahi
        almacen->retirarProducto(destinoIns[0], destinoIns[1], productoCant);
    }
    
    // volver al origen si hay algun paquete que entregar
    if (operacionIns=="retiro"){
        if (!moverse(origen[0], origen[1])) { return false; }
        
        llevaProducto = false; // dejo producto
    }

    cout << "Se ejecuto la instruccion #" << instrucciones[proximaInstruccion].numero << endl;
    proximaInstruccion++;

    if (termino()){ // volver a home
        cout << "Robot volviendo a home" << endl;
        if (!moverse(origen[0], origen[1])) { return false; }
    }
    return true; // no hubo colision

}


bool Robot::termino(){
    return instrucciones.empty() || proximaInstruccion >= instrucciones.size();
}

void Robot::informacion(){
    cout << "\n=============================================================";
    cout << "\n# robot: " << numero;
    cout << "\nOrigen: " << origen[0] << " " << origen[1];
    cout << "\nDimensiones almacen: " << almacen->getFilas() << " " << almacen->getColumnas();
    cout << "\nInstrucciones----";
    for (int i=0; i<instrucciones.size(); i++){
        cout << "\nOperacion: " << instrucciones[i].operacion;
        cout << "\nDestino: " << instrucciones[i].destino[0] << " " << instrucciones[i].destino[1];
        cout << "\nProducto: " << instrucciones[i].producto;
    }
}