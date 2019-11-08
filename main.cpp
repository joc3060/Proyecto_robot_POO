#include <iostream>
#include "persona.h"
#include <string>

using namespace std;
int main(){
    persona p1 = persona(20, "Raul");
    p1.leer();cout<<endl;
    persona p2 = persona(40, "María");
    p2.correr();cout<<endl;
    persona p3 = persona(10,"Juan");
    p3.leer();cout<<endl;
    p3.correr();cout<<endl;
    return 0;
}