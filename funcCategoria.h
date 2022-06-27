#ifndef FUNCCATEGORIA_H_INCLUDED
#define FUNCCATEGORIA_H_INCLUDED

#include <string.h>
#include "clsCategoria.h"
#include "clsMovimiento.h"

using namespace std;

//PROTITPOS
void copiarArchivoCategoriasAlArray(Categoria *arrayCategorias);
int generarVectorDinamicoCategorias(Categoria *arrayCategorias);  //crea vector dinamico categ - func global
void mostrarEgresosArrayCategorias(Categoria *arrayCategorias, int cantidad);
void mostrarEgresosArrayCategoriasAcotado(Categoria *arrayCategorias, int cantidad);
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
        cout<<"      2) MODIFICAR CATEGORIA"<<endl;
        cout<<"      3) LISTAR CATEGORIA POR ID"<<endl;
        cout<<"      4) LISTAR TODAS LAS CATEGORIAS"<<endl;
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

            //2. MODIFICAR CATEGORIA
            case 2: cout<<"Ingrese el codigo de la categoria a modificar: ";
                cin>>cod;
                mensajeOperacion(modificarCategoria(cod));
                break;

            //3. LISTAR CATEGORIA POR ID
            case 3: cout<<"Ingrese el codigo de la categoria a mostrar: ";
                cin>>cod;
                cout<<endl;
                if(listarCategoriaPorId(cod)==-1){
                    cout<<"No existe ese codigo de categoria!"<<endl;
                }
                break;

            //4. LISTAR TODAS LAS VENTAS
            case 4: contador=listarCategorias();
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
    cargarCadena(auxChar,19);    
    while (esRepetido(auxChar)){
        cout<<"Ha ingresado una categoria repetida, ingresela nuevamente: "<<endl;
        cout<<"CATEGORIA: ";
        cargarCadena(auxChar,19);    
    }    

    reg.Cargar(auxInt, auxChar);
    mensajeOperacion(reg.grabarEnDisco());
    cout<<endl;
    mensajesListados("REGISTRO AGREGADO");
    reg.Mostrar();
}
int buscarCategoriaCodigo(int codCateg){
    int i=0;
    Categoria cate;

    while (cate.leerDeDisco(i)==1) {
        if (cate.getId()==codCateg) {
            return i;
        }
        i++;
    }

    return -1;
}
bool modificarCategoria(int codCateg){
    int opc=0;
    char nombreCateg[20];
    Categoria reg;

    if(codCateg==0){
        cout<<"Proceso cancelado!"<<endl;
        return 0;
    }

    int posDisco=buscarCategoriaCodigo(codCateg);

    while(posDisco==-1){
        cout<<"No existe el codigo de categoria seleccionado. Escribalo nuevamente: ";
        cin>>opc;
        posDisco=buscarCategoriaCodigo(opc);
    }
    reg.leerDeDisco(posDisco);

    cout<<"Seleccione 1 para modificar el tipo de gasto o 2 para modificar el nombre de la categoria (0 para salir): "<<endl;
    cin>>opc;
    if(opc==1){
        cout<<"Ingrese 1 para ingreso, 2 para egreso: ";
        cin>>opc;
        while(opc!=1 && opc!=2){
            cout<<"Opcion ingresada inválida. Escrí­bala nuevamente: ";
            cin>>opc;
        }
        reg.setTipoMov(opc);
    }
    else{
        if(opc==2){
            cout<<"Escriba el nombre de la categoria: ";
            cargarCadena(nombreCateg,19);
            reg.setNombre(nombreCateg);
        }
    }
    return(reg.grabarEnDisco(posDisco));

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
void mostrarEgresosArrayCategoriasAcotado(Categoria *arrayCategorias, int cantidad){
    Categoria cate;

    cout<<"CATEGORIAS: "<<endl;
    for (int i=0; i<cantidad; i++){
        if(arrayCategorias[i].getTipoMov()==2){
            cout<<arrayCategorias[i].getId()<<", ";
            cout<<arrayCategorias[i].getNombre()<<endl;
        }
    }
    cout<<endl;
}
void listarCategoriasAcotado(){
    int i=0;
    Categoria cate;

    cout<<"CATEGORIAS: "<<endl;
    while (cate.leerDeDisco(i)==1) {
        cout<<cate.getId()<<", ";
        cout<<cate.getNombre()<<endl;
        i++;
    }
}
int buscarTipoCategoria(int categoria){
    Categoria cate;
    int i=0;

    while(cate.leerDeDisco(i)==1) {
        if (cate.getId()==categoria) {
            return cate.getTipoMov();
        }
        i++;
    }
    return 0;
}


//FIN FUNCIONES


#endif // FUNCCATEGORIA_H_INCLUDED
