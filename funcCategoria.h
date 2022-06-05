#ifndef FUNCCATEGORIA_H_INCLUDED
#define FUNCCATEGORIA_H_INCLUDED

#include <string.h>

using namespace std;

//PROTOTIPOS
int menuCategorias();
int proximoId();
void agregarCategoria();
bool esMovimientoValido(int mov);
bool esRepetido(const char *pNombre);
int listarCategorias();
int listarCategoriaPorId(int cod);
//FIN PROTOTIPOS


//FUNCIONES
int menuCategorias(){
    int opc=0;
    int cod=0;
    int contador=0;

    while(true){
        cout<<"*************************************"<<endl;
        cout<<"********** MENU CATEGORIAS **********"<<endl;
        cout<<"*************************************"<<endl;
        cout<<"    1. LISTAR TODAS LAS CATEGORIAS"<<endl;
        cout<<"    2. AGREGAR CATEGORIA"<<endl;
        cout<<"    3. LISTAR CATEGORIA POR ID"<<endl;
        cout<<"    0. VOLVER AL MENU PRINCIPAL"<<endl;
        cout<<"*************************************"<<endl;
        cout<<"SELECCIONE UNA DE LAS OPCIONES: ";
        cin>>opc;
        system("cls");

        switch (opc){
            //1. LISTAR TODAS LAS VENTAS
            case 1: contador=listarCategorias();
                cout<<"Total de categorias: "<<contador<<endl;
                break;

            //2. AGREGAR CATEGORIA
            case 2: agregarCategoria();
                break;

            //3. LISTAR CATEGORIA POR ID
            case 3: cout<<"Ingrese el codigo de la categoria a mostrar: ";
                cin>>cod;
                cout<<endl;
                if(listarCategoriaPorId(cod)==-1){
                    cout<<"No existe ese codigo de categoria!"<<endl;
                }
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
int proximoId(){
    ///DEVUELVE EL PROXIMO NRO DE ID (AUTOINCREMENTABLE)
    Categoria reg;
    
    reg.leerDeDisco(-8);
    return reg.getId()+1;
}
void agregarCategoria(){
    Categoria reg;
    int id=0;
    int auxInt=0;
    char auxChar[20];

    id=proximoId();

    //consultar la siguiente duda:
    //La validación del dato ingresado, lo hago acá en la función externa o en el setter???
    //si lo hago en el setter, entonces esMovimientoValido es una función de la clase Categoría?
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

    reg.Cargar(id, auxInt, auxChar);
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
//FIN FUNCIONES


#endif // FUNCCATEGORIA_H_INCLUDED
