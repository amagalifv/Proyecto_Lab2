#ifndef FUNCCATEGORIA_H_INCLUDED
#define FUNCCATEGORIA_H_INCLUDED

#include <string.h>

using namespace std;

//PROTOTIPOS

//FIN PROTOTIPOS


//FUNCIONES
bool validarMovimiento(int mov){
    if(mov==1 || mov==2){
        return true;
    }

    cout<<"Ha ingresado un tipo de movimiento inválido, ingreselo nuevamente: "<<endl;
    cout<<"TIPO DE MOVIMIENTO (1- INGRESO, 2- EGRESO): ";
    return false;
} 
//FIN FUNCIONES


#endif // FUNCCATEGORIA_H_INCLUDED
