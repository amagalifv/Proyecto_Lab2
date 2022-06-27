#ifndef CLSCATEGORIA_H_INCLUDED
#define CLSCATEGORIA_H_INCLUDED
#include "prototipos.h"

#include <string.h>
#include <iostream>

using namespace std;

//LA CLASE CATEGORIA NO TIENE EL CAMPO ESTADO PORQUE NO SE PUEDE DAR DE BAJA LA CATEGORIA 
//ASIGNADA A UN REGISTRO, DE ESTA FORMA SE MANTIENE LA INTEGRIDAD DE LOS MOVIMIENTOS CARGADOS.
class Categoria{
    private:
        int _id;                 // autoincrementable
        int _tipoMovimiento;     //1 para ingreso, 2 para egreso
        char _nombre[20];    //supermercado, servicio, indumentaria, farmacia, restaurante, ocio, viajes , educación, etc

        //METODOS
        int proximoId();

    public:
        //CONSTRUCTOR CON VALORES POR OMISION
        Categoria(int id=0, int tipoMovimiento=0, const char *pNombre="nada"){
            _id=id;
            _tipoMovimiento=tipoMovimiento;
            strcpy(_nombre, pNombre);
        }

        //SETTERS
        void setId(int proxId){_id=proxId;}
        void setTipoMov(int tipoMov){_tipoMovimiento=tipoMov;}
        void setNombre(const char *pNombre){strcpy(_nombre, pNombre);}

        //GETTERS
        int getId(){return _id;}
        int getTipoMov(){return _tipoMovimiento;}
        const char *getNombre(){return _nombre;}

        //METODOS
        void Cargar(int aTipo, const char *pNombre);
        void Mostrar();
        int leerDeDisco(int pos);
        int grabarEnDisco(int pos=-1);
};
void Categoria::Cargar(int aTipo, const char *pNombre){
    int id=proximoId();

    setId(id);
    setTipoMov(aTipo);
    setNombre(pNombre);
    cout<<endl;
}
void Categoria::Mostrar(){
    cout<<"ID CATEGORIA: "<<getId()<<endl;
    cout<<"TIPO DE MOVIMIENTO: ";
    if(getTipoMov()==1){
        cout<<getTipoMov()<<"-INGRESO"<<endl;   
    }
    else{
        cout<<getTipoMov()<<"-EGRESO"<<endl;
    }
    cout<< "NOMBRE DE LA CATEGORIA: "<<getNombre()<<endl<<endl;
}
int Categoria::leerDeDisco(int pos){
    /******************************************
     Valores que retorna leerDeDisco(int pos):
     -1: NO ENCONTRÓ EL ARCHIVO
      1: LEYO EL ARCHIVO
      2:
      NOTA: SI PARAMETRO == -8, LEE DESDE EL FINAL AL INICIO DEL ARCHIVO
    ******************************************/
    FILE *archivo;
    int leyo=-1;

    archivo=fopen(AR_CATEGORIAS,"rb");

    if(archivo==NULL){
        return -1;
    }

    if( pos == -8){
        fseek(archivo, 0 ,SEEK_END);
        fseek(archivo, -sizeof(Categoria), SEEK_END);
        leyo=fread(this, sizeof(Categoria), 1, archivo);
    }
    else{
        fseek(archivo, pos*sizeof(Categoria), 0);
        leyo=fread(this, sizeof(Categoria), 1, archivo);
    }

    fclose(archivo);
    return leyo;
}
int Categoria::grabarEnDisco(int pos){
    /******************************************
     Valores que retorna grabarEnDisco(int pos):
     -1: NO PUDO GRABAR EN EL ARCHIVO
      1: ESCRIBIÓ EL ARCHIVO
      2:
    ******************************************/
FILE *archivo;
    int escribio;

    if(pos==-1){
        archivo=fopen(AR_CATEGORIAS, "ab");
        if(archivo==NULL){
            return -1;
        }
    }
    else{
        archivo=fopen(AR_CATEGORIAS, "rb+");
        if(archivo==NULL){
            return -1;
        }
        fseek(archivo, sizeof(Categoria)*pos, 0);
    }

    escribio=fwrite(this, sizeof(Categoria), 1, archivo);
    fclose(archivo);
    return escribio;
}
int Categoria::proximoId(){
    ///DEVUELVE EL PROXIMO NRO DE ID (AUTOINCREMENTABLE)
    
    leerDeDisco(-8);
    return getId()+1;
}

#endif // CLSCATEGORIA_H_INCLUDED
