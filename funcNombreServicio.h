#ifndef FUNCNOMBRESERVICIO_H_INCLUDED
#define FUNCNOMBRESERVICIO_H_INCLUDED

using namespace std;

#include "clsNombreServicio.h"

int buscarNombreServPorCodigo(int codigoNombre){
    NombreServicio reg;
    int posDisco=0;

    while(reg.leerDeDisco(posDisco)==1){
        if(reg.getEstado()){
            if(reg.getId()==codigoNombre){
                return posDisco;
            }
        }
        posDisco++;
    }
    posDisco=-1;
    return posDisco;
}
void listarNombreServicios(){
    NombreServicio reg;
    int posDisco=0;

    while(reg.leerDeDisco(posDisco)==1){
        if(reg.getEstado()){
            reg.Mostrar();
        }
        posDisco++;
    }
    cout<<endl;
}
void listarNombreServiciosAcotado(){
    NombreServicio reg;
    int posDisco=0;

    while(reg.leerDeDisco(posDisco)==1){
        if(reg.getEstado()){
            cout<<"\n"<<reg.getId()<<" - "<<reg.getDescripcion();
        }
        posDisco++;
    }
    cout<<endl;
}
bool codServicioValido(int cod){
    NombreServicio reg;
    int posDisco=0;

    while(reg.leerDeDisco(posDisco)==1){
        if(reg.getEstado()){
            if(reg.getId()==cod){
                return true;
            }
        }        
        posDisco++;
    }
    return false;
}
int buscarNombreServicioCodigo(int codNombreServicio){
    NombreServicio reg;
    int posDisco=0;

    while(reg.leerDeDisco(posDisco)==1){
        if(reg.getId()==codNombreServicio){
            return posDisco;
        }
        posDisco++;
    }
    posDisco=-1;
    return posDisco;
}
bool esRepetidoNombreServicio(const char *pNombre){
    NombreServicio reg;
    int posDisco=0;

    while(reg.leerDeDisco(posDisco++)==1){
        if(strcmp(reg.getDescripcion(),pNombre)==0){
            return true;
        }
    }
    return false;
}
void agregarNombreServicio(){
    NombreServicio reg;
    int auxInt=0;
    char auxChar[20];

    mensajesListados("AGREGAR SERVICIO");
    
    cout<<"NOMBRE DEL SERVICIO: ";
    cargarCadena(auxChar,14);    
    while (esRepetidoNombreServicio(auxChar)){
        cout<<"Ha ingresado un nombre de servicio repetido, ingreselo nuevamente: "<<endl;
        cout<<"NOMBRE DEL SERVICIO: ";
        cargarCadena(auxChar,14);    
    }    

    reg.Cargar(auxChar);
    mensajeOperacion(reg.grabarEnDisco());
    cout<<endl;
    mensajesListados("REGISTRO AGREGADO");
    reg.Mostrar();
}
bool modificarNombreServicio(int codNombreServicio){
    char nombreServicio[15];
    NombreServicio reg;

    if(codNombreServicio==0){
        cout<<"Proceso cancelado!"<<endl;
        system("pause");
        return 0;
    }

    int posDisco=buscarNombreServicioCodigo(codNombreServicio);

    while(posDisco==-1){
        cout<<"No existe el codigo de servicio seleccionado. Escribalo nuevamente: ";
        cin>>codNombreServicio;
        posDisco=buscarNombreServicioCodigo(codNombreServicio);
    }

    reg.leerDeDisco(posDisco);

    cout<<"Escriba el nuevo nombre del servicio: ";
    cargarCadena(nombreServicio,14);
    reg.setDescripcion(nombreServicio);        
    
    return(reg.grabarEnDisco(posDisco));
}
int contarRegistrosNombreServicios(){
    NombreServicio reg;
    int posDisco=0;
    int contador=0;

    while(reg.leerDeDisco(posDisco++)==1){     
        contador++;
    }
    
    return contador;
}

#endif // FUNCNOMBRESERVICIO_H_INCLUDED
