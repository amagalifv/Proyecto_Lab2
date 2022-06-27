#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> // Añade paquete de idiomas

#include "prototipos.h"
#include "clsMovimiento.h"
#include "clsMovimientoServicio.h"
#include "clsNombreServicio.h"
#include "funcMovimiento.h"
#include "funcMovimientoServicio.h"
#include "funcCategoria.h"
#include "funcAhorro.h"
#include "funcConfiguracion.h"
#include "funcInformes.h"
#include "funcNombreServicio.h"

using namespace std;

int main () {
    setlocale(LC_ALL, "spanish");
    system ("color 57");
    /**********************************
     maneja tamaño de la ventana sin
     limitar el buffer de la consola
     tb permite que se pueda mover
    **********************************/
    HWND hWnd=GetConsoleWindowNT();
    MoveWindow(hWnd,0,0,1250,500,TRUE);

    //carga masiva nombres servicios
    // NombreServicio regNom;
    // for(int i=0; i<7; i++){
    //     agregarNombreServicio();
    // }

    // //carga masiva movimientos
    // Movimiento reg;
    // for(int i=0; i<56; i++){
    //     reg.Cargar();
    //     reg.grabarEnDisco();
    // }

    // carga masiva de categorias
    // for(int i=0; i<13; i++){
    //     agregarCategoria();
    // }
    // system("pause");

    // carga masiva de ahorro
    // for(int i=0; i<14; i++){
    //     definirAhorroMes();
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
        cout<<"************************************\n";
        cout<<"           MENU PRINCIPAL           \n";
        cout<<"************************************\n";
        cout<<"      1) MENU MOVIMIENTOS           \n";
        cout<<"      2) MENU CATEGORIAS            \n";
        cout<<"      3) MENU KAKEBO                \n";
        cout<<"      4) MENU INFORMES              \n";
        cout<<"      5) MENU CONFIGURACION         \n";
        cout<<"************************************\n";
        cout<<"      0) FIN DEL PROGRAMA           \n";
        cout<<"************************************\n";
        cout<<endl;
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
            case 4: menuInformes();
                break;

            //5. MENU CONFIGURACION
            case 5: menuConfiguracion();
                break;

            default:
                return 0;
                break;
        }
        cout<<endl;
        //system("pause");
        system("cls");
    }

    system("pause");
    return 0;
}
