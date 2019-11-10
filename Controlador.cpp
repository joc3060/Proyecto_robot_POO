#include "Controlador.h"

void Controlador::input_robots(){
    int n;
    cout << "Numero de robots: ";
    cin >> n;

    for (int i=0; i<n; i++){
        // Declarar variables a utilizar
        int origen1, origen2;

        // Pedir datos
        cout << "Origen del robot #" << i << " (fila columna): ";
        cin >> origen1 >> origen2;

        // Verificar si coordenada existe
        if (almacen.coordEsValida(origen1, origen2)){
            // Agregar robot
            Robot robot(i, origen1, origen2, &almacen);
            robots.push_back(robot);
        }
        else{
            cout << "La coordenada no es valida. Las dimensiones del almacen son de " << almacen.getFilas() << "x" << almacen.getColumnas() << endl;
            i--; // dar otra oportunidad para introducir una coordenada correcta
        }
    }
}

void Controlador::input_instrucciones(){
    int n;
    cout << endl << "Numero de instrucciones: ";
    cin >> n;

    for (int i=0; i<n; i++){
        // Declarar variables a utilizar
        int num_robot, destino_fila, destino_col, cantidad;
        string operacion, producto;

        cout << endl << "Instruccion #" << i << endl;

        // Pedir datos
        cout << "Numero de robot: ";
        cin >> num_robot;
        cout << "Operacion: ";
        cin >> operacion;
        cout << "Destino (fila columna): ";
        cin >> destino_fila >> destino_col;
        cout << "Producto (tipo): ";
        cin >> producto;
        cout << "Producto (cantidad): ";
        cin >> cantidad;

        // Verificar si el # de robot existe
        if (0>num_robot && num_robot>=robots.size()){ // numero no existe
            cout << "El numero de robot no existe. Ingresar la instruccion de nuevo" << endl;
            i--; // dar otra oportunidad para introducir una instruccion correcta
        }
        else if (!almacen.coordEsValida(destino_fila, destino_col)){
            cout << "La coordenada no existe. Ingresar la instruccion de nuevo" << endl;
            i--;
        }
        else if (operacion != "ingreso" && operacion != "retiro"){
            cout << "La operacion debe ser 'ingreso' o 'retiro'. Ingresar la instruccion de nuevo" << endl;
            i--;
        }
        else if (cantidad <= 0){
            cout << "La cantidad no puede ser menor o igual a cero. Ingresar la instruccion de nuevo" << endl;
            i--;
        }
        else{
            Instruccion instruccion(i, operacion, destino_fila, destino_col, producto, cantidad);
            robots[num_robot].agregarInstruccion(instruccion);
        }
    }
}

void Controlador::ejecutar_instrucciones(){
    bool instCompletadas;
    do{
        instCompletadas = true;
        for (int i=0; i<robots.size(); i++){
            robots[i].siguienteInstruccion();
            instCompletadas = instCompletadas && robots[i].termino();

            cout << "\n\n";
            cout << "Contenido del almacen" << endl;
            almacen.mostrarContenido();
            cout << "\nPosición de los robots" << endl;
            almacen.mostrarPosRobots();
            cout << "\n\n";
        }
        
    } while (!instCompletadas);
}

void Controlador::informacion_robots(){
    for (auto& robot : robots){ robot.informacion(); }
}

void Controlador::informacion_almacen(){
    almacen.mostrarContenido();
}
