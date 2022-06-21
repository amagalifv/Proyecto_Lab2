#ifndef FUNCCATEGORIA_H_INCLUDED
#define FUNCCATEGORIA_H_INCLUDED

#include <string.h>
#include "clsCategoria.h"

using namespace std;

//PROTITPOS
void copiarArchivoCategoriasAlArray(Categoria *arrayCategorias);
int generarVectorDinamicoCategorias(Categoria *arrayCategorias);  //crea vector dinamico categ - func global
void mostrarEgresosArrayCategorias(Categoria *arrayCategorias, int cantidad);
void mostrarIngesosArrayCategorias(Categoria *arrayCategorias, int cantidad);
bool esEgreso(Categoria *arrayCategorias, int codCateg);
//FIN PROTOTIPOS

//FUNCIONES
int menuCategorias(){
    int opc=0;
    int cod=0;
    int contador=0;

    while(true){
        cout<<"***************************************"<<endl;
        cout<<"            MENU CATEGORIAS            "<<endl;
        cout<<"***************************************"<<endl;
        cout<<"      1) AGREGAR CATEGORIA"<<endl;
        cout<<"      2) LISTAR CATEGORIA POR ID"<<endl;
        cout<<"      3) LISTAR TODAS LAS CATEGORIAS"<<endl;
        cout<<"***************************************"<<endl;
        cout<<"      0) VOLVER AL MENU PRINCIPAL"<<endl;
        cout<<"***************************************"<<endl;
        cout<<"SELECCIONE UNA DE LAS OPCIONES: ";
        cin>>opc;
        system("cls");

        switch (opc){
            //1. AGREGAR CATEGORIA
            case 1: agregarCategoria();
                break;

            //2. LISTAR CATEGORIA POR ID
            case 2: cout<<"Ingrese el codigo de la categoria a mostrar: ";
                cin>>cod;
                cout<<endl;
                if(listarCategoriaPorId(cod)==-1){
                    cout<<"No existe ese codigo de categoria!"<<endl;
                }
                break;

            //3. LISTAR TODAS LAS VENTAS
            case 3: contador=listarCategorias();
                cout<<"Total de categorias: "<<contador<<endl;
                break;

            default:
                return 0;
                break;
        }
        cout<<endl;
        system("pause");
        system("cls");
    }
    return 0;
}
void agregarCategoria(){
    Categoria reg;
    int auxInt=0;
    char auxChar[20];

    mensajesListados("AGREGAR CATEGORIA");
    cout<<"TIPO DE MOVIMIENTO (1- INGRESO, 2- EGRESO): ";
    cin>>auxInt;
    while(!esMovimientoValido(auxInt)){
        cout<<"Ha ingresado un tipo de movimiento invalido, ingreselo nuevamente: "<<endl;
        cout<<"TIPO DE MOVIMIENTO (1- INGRESO, 2- EGRESO): ";
        cin>>auxInt;
    }
    
    cout<<"NOMBRE CATEGORIA: ";
    cargarCadena(auxChar,20);    
    while (esRepetido(auxChar)){
        cout<<"Ha ingresado una categoria repetida, ingresela nuevamente: "<<endl;
        cout<<"CATEGORIA: ";
        cargarCadena(auxChar,20);    
    }    

    reg.Cargar(auxInt, auxChar);
    mensajeOperacion(reg.grabarEnDisco());
    cout<<endl;
    mensajesListados("REGISTRO AGREGADO");
    reg.Mostrar();
}
bool esMovimientoValido(int mov){
    if(mov==1 || mov==2){
        return true;
    }
    return false;
} 
bool esRepetido(const char *pNombre){
    Categoria reg;
    int posDisco=0;

    while(reg.leerDeDisco(posDisco++)==1){
        if(strcmp(reg.getNombre(),pNombre)==0){
            return true;
        }
    }
    return false;
}
int listarCategorias(){
    Categoria reg;
    int posDisco=0;
    int contador=0;

    while(reg.leerDeDisco(posDisco++)==1){
        reg.Mostrar();
        contador++;
    }
    return contador;
}
int listarCategoriaPorId(int cod){
    Categoria reg;
    int posDisco=0;

    while(reg.leerDeDisco(posDisco++)==1){
        if(reg.getId()==cod){
            mensajesListados("CATEGORIA ENCONTRADA");
            reg.Mostrar();
            return posDisco;
        }
    }
    return -1;
}
bool esEgreso(Categoria *arrayCategorias, int codCateg){

    if(arrayCategorias[codCateg-1].getTipoMov()==2){
        return true;
    }

    return false;
    
}
bool esGastoFijo(int anio, int mes, int codCateg){
    Movimiento reg;
    int posDisco=0;

    while(reg.leerDeDisco(posDisco++)==1){
        if(reg.getFecha().getAnio()==anio){
            if(reg.getFecha().getMes()==mes){
                if(reg.getCategoria()==codCateg){
                    if(reg.getSiGastoFijo()){
                        return true;
                    }
                }
            }
        }
    }
    return false;    
}
int calcularCantidadCategorias(){
    Categoria reg;
    int posDisco=0;
    int contador=0;

    while(reg.leerDeDisco(posDisco++)==1){
        contador++;
    }

    return contador;
}
void copiarArchivoCategoriasAlArray(Categoria *arrayCategorias){
    Categoria reg;
    int posDisco=0;

    while(reg.leerDeDisco(posDisco)==1){
        arrayCategorias[reg.getId()-1].leerDeDisco(posDisco);
        posDisco++;
    }
}
int generarVectorDinamicoCategorias(Categoria *arrayCategorias){

    int cantidad=calcularCantidadCategorias();
    if (cantidad<=0){
        exit (1);
    }
    arrayCategorias = new Categoria[cantidad];

    if(arrayCategorias==NULL){
        cout<<"NO SE PUDO ASIGNAR LA MEMORIA PARA CREAR EL ARRAY DE CATEGORIAS"<<endl;
        cantidad=-1;
        exit(2);
    }

    copiarArchivoCategoriasAlArray(arrayCategorias);

    return cantidad;

}
void mostrarIngesosArrayCategorias(Categoria *arrayCategorias, int cantidad){
    for (int i=0; i<cantidad; i++){
        if(arrayCategorias[i].getTipoMov()==1){
            arrayCategorias[i].Mostrar();
        }
    }
}
void mostrarEgresosArrayCategorias(Categoria *arrayCategorias, int cantidad){
    for (int i=0; i<cantidad; i++){
        if(arrayCategorias[i].getTipoMov()==2){
            arrayCategorias[i].Mostrar();
        }
    }
}
//FIN FUNCIONES


#endif // FUNCCATEGORIA_H_INCLUDED
