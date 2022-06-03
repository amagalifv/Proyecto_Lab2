#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clsCategoria.h"

using namespace std;

/*
POR HACER
CODIGO AUTOINCREMENTABLE (HECHO)
VALIDAR CODIGO TIPO OPERACION 1 Y 2 (HECHO)
PASAR A MAYUSCULAS LAS CADENAS (HECHO)
VALIDAR QUE NO HAYA REPETIDOS

*/

int main () {

    Categoria reg;

    reg.Cargar();
    reg.Mostrar();
    reg.grabarEnDisco();



    system("pause");

    return 0;
}
