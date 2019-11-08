//
// Created by USUARIO on 8/11/2019.
//

#ifndef POO1_PERSONA_H
#define POO1_PERSONA_H
#include <string>
#include <iostream>
using namespace std;

class persona {
    private: //atributos
        int    edad;
        string nombre;
    public: //metodos
        persona(int, string);//constructor --> inicializar variables y atributos.
        void leer();
        void correr();
};


#endif //POO1_PERSONA_H
