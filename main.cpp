#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prototipos.h"
#include "clsMovimiento.h"
#include "clsMovimientoServicio.h"
#include "funcMovimiento.h"
#include "funcMovimientoServicio.h"
#include "funcCategoria.h"
#include "funcAhorro.h"
#include "funcConfiguracion.h"

using namespace std;

/***************************************************************
****************************************************************
POR HACER
CODIGO AUTOINCREMENTABLE (HECHO)
VALIDAR CODIGO TIPO OPERACION 1 Y 2 (HECHO)
PASAR A MAYUSCULAS LAS CADENAS (HECHO)
VALIDAR QUE NO HAYA REPETIDOS (HECHO)
LISTAR CATEGORIAS (HECHO)
LISTAR CATEGORIAS POR ID (HECHO)
CREAR DATOS DE INICIO (HECHO)
CREAR FUNCION DATOS DE INCIO (HECHO)
***************************************************************
***************************************************************/

// A REVISAR:
//  - MUESTRA ERRONEAMENTE LOS MOVIMIENTOS SERVICIOS, BUCLE Y NO SIGUE LISTANDO
 

int main () {
    // Movimiento reg;
    // for(int i=0; i<17; i++){
    //     reg.Cargar();
    //     reg.grabarEnDisco();
    // }
    // carga masiva de categorias
    // for(int i=0; i<13; i++){
    //     agregarCategoria();
    // }
    // system("pause");

    // Ahorro reg;
    // int posDisco=0;
    // while(reg.leerDeDisco(posDisco++)==1){
    //     reg.Mostrar();
    // }

    // system("pause");

    int opc;

    while(true){
        system("cls");
        cout<<"****************************"<<endl;
        cout<<"****** MENU PRINCIPAL ******"<<endl;
        cout<<"****************************"<<endl;
        cout<<"    1. MENU MOVIMIENTO"<<endl;
        cout<<"    2. MENU CATEGORIAS"<<endl;
        cout<<"    3. MENU KAKEBO"<<endl;
        cout<<"    4. INFORMES"<<endl;
        cout<<"    5. CONFIGURACION"<<endl;
        cout<<"    0. FIN DEL PROGRAMA"<<endl;
        cout<<"****************************"<<endl;
        cout<<"SELECCIONE UNA DE LAS OPCIONES: ";
        cin>>opc;
        system("cls");

        switch(opc){
            //1. MENU MOVIMIENTOS
            case 1: menuMovimientos();
                break;

            //2. MENU CATEGORIAS
            case 2: menuCategorias();
                break;

            //3. MENU KAKEBO
            case 3: menuKakebo();
                break;

            //4. MENU INFORMES
            // case 4: menuInformes();
            //     break;

            //5. MENU CONFIGURACION
            case 5: menuConfiguracion();
                break;

            default:
                return 0;
                break;
        }
        cout<<endl;
        system("cls");
    }

    system("pause");
    return 0;
}
