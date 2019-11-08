//
// Created by USUARIO on 8/11/2019.
//

#include "persona.h"
#include <string>
persona::persona(int _edad,string _nombre){
    edad = _edad;
    nombre = _nombre;
}
void persona::leer() {
    cout<<"soy "<<nombre<<" y estoy leyendo"<<endl;
}
void persona::correr() {
    cout<<"soy "<<nombre<<" y estoy corriendo a mis "<<edad<<" anios";
}