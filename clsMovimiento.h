#ifndef CLSMOVIMIENTO_H_INCLUDED
#define CLSMOVIMIENTO_H_INCLUDED
#include <iostream>
using namespace std;

#include "prototipos.h"
#include "clsFecha.h"

class Movimiento {
    private:
        int _id;
        Fecha _fecha;
        float _importe;
        int _categoria;
        bool _siGastoFijo;
        bool _estado;
        int autogenerarId();

    public:
        void Mostrar();
        void Cargar();
        int grabarEnDisco();
        int leerDeDisco(int pos);
        int leerDeDisco(int pos, const char *nombreArchivo);
        int modificarDeDisco(int pos);
    //GETTERS
        int getId(){return _id;}
        Fecha getFecha(){return _fecha;}
        float getImporte(){return _importe;}
        int getCategoria(){return _categoria;}
        bool getSiGastoFijo(){return _siGastoFijo;}
        bool getEstado(){return _estado;}
    //SETTERS
        /*void setId(int id){_id=id;}ID NO TIENE SETTER BORRAR*/
        void setFecha(Fecha f){_fecha=f;}
        void setImporte(float imp){_importe=imp;}
        void setCategoria(int cate){_categoria=cate;}
        void setSiGastoFijo(bool siG){_siGastoFijo=siG;}
        void setEstado(bool est){_estado=est;}

};

 /**********************
   AUTOGENERA EL ID
 -1 si error de archivo
  0 si error de fread
  1 si está vacio el archivo
**********************/
/*
int Movimiento::autogenerarId(){
    int posDisco=0;
    int contador=0;

    //leerDeDisco(8);
    while(leerDeDisco(posDisco++)==1){
        contador++;
    }
    //return this->getId()+1;
    return contador+1;
}
 */
int Movimiento::autogenerarId(){
    int id;
    int aux;
    FILE *pMov;

    pMov=fopen(AR_MOVIMIENTOS,"ab+");
    if (pMov==NULL){return -1;} //error de apertura de archivo

    fseek(pMov, 0 ,SEEK_END);
    if (ftell(pMov)==0){return 1;}// si está vacio el archivo

    fseek(pMov, (-1)*sizeof(Movimiento) ,SEEK_END);
    aux=fread(this ,sizeof(Movimiento),1,pMov);
    if (aux!=1){return -2;} // error de fread

    id=this->getId();
    id++;

    return id;
}
void Movimiento::Cargar(){
    int auxI,id;
    float auxF;
    //bool est;
    char resp;

    id=this->autogenerarId();
    if (id>0) {
        _id=id;
    }

    cout<<"FECHA DE LA OPERACION: "<<endl;
    _fecha.Cargar();

    cout<<"INGRESE EL IMPORTE: ";
    cin>>auxF;
    setImporte(auxF);

    //LISTAR CATEGORIAS!!!! categoria y descripcion unicamente!!
    cout<<"INGRESE LA CATEGORIA DESEADA: ";
    cin>>auxI;
    setCategoria(auxI);
    if (auxI==7) {
        crearRegistroServicio(_id);
    }

    /* SOLO PREGUNTAR SI ES UN EGRESO Y SEGÚN CATEGORIA INGRESADA ¡¡¡¡CHARLAR!!! */
    if (auxI==1 || auxI==2 || auxI==3) {
        _siGastoFijo=false;
    }else{
        cout<<"ES UN GASTO FIJO (S PARA SI Y N PARA NO): ";
        resp=toupper(cin.get());
        //cin>>toupper(resp);
        //if (resp=='s' || resp=='S'){_siGastoFijo=true;}
        if (resp=='S'){_siGastoFijo=true;}
        else {_siGastoFijo=false;}
    }

    /* PARA LA CARGA MANUAL(solo programadores)
    cout<<"Estado               :";
    cin>>est;
    setEstado(est);*/
    setEstado(true);
}

void Movimiento::Mostrar(){
    cout<<"ID                    :";
    cout<<getId()<<endl;
    cout<<"FECHA DE LA OPERACION :";
    _fecha.Mostrar();
    cout<<"IMPORTE               : $";
    cout<<getImporte()<<endl;
    cout<<"CATEGORIA             :";
    cout<<getCategoria()<<endl;
    
    if (getCategoria()==7) {
        mostrarServicio(getId());
    }
    cout<<endl;
}

/*******************************************************
devuelve -1 si no lo pudo abrir archivo
carga en el obj de la cls la info que leyo y devuelve 1
Si no pudo leer devuelve 0
********************************************************/
int Movimiento::leerDeDisco(int pos){
    FILE *pMov;
    int leyo;

    pMov=fopen(AR_MOVIMIENTOS,"rb");
    if (pMov==NULL){return -1;}

    fseek(pMov, sizeof(Movimiento)*pos,SEEK_SET);
    leyo=fread(this ,sizeof(Movimiento),1,pMov);
    fclose(pMov);

    return leyo;
}

/*******************************************************
devuelve -1 si no lo pudo abrir archivo
carga en el obj de la cls la info que leyo y devuelve 1
Si no pudo leer devuelve 0
********************************************************/
int Movimiento::leerDeDisco(int pos, const char *nombreArchivo){
    FILE *pMov;
    int leyo;

    pMov=fopen(nombreArchivo,"rb");
    if (pMov==NULL){return -1;}

    fseek(pMov, sizeof(Movimiento)*pos,SEEK_SET);
    leyo=fread(this ,sizeof(Movimiento),1,pMov);
    fclose(pMov);

    return leyo;
}

/*********************************
-1 error de apertura de archivo
 0 error fwrite
 1 si escribió exitosamente
**********************************/
int Movimiento::grabarEnDisco(){
    FILE *pMov;
    bool escribio;

    pMov=fopen(AR_MOVIMIENTOS,"ab");
    if (pMov==NULL){return false;}

    escribio=fwrite(this ,sizeof(Movimiento),1,pMov);
    fclose(pMov);
    return escribio;
}

/***************************
-1 si no pudo abrir
0 si no pudo escribir
1 si escribió exitosamente
****************************/
int Movimiento::modificarDeDisco(int pos){
    FILE *pMov;
    int escribio;

    pMov=fopen(AR_MOVIMIENTOS,"rb+");
    if (pMov==NULL){return -1;}

    fseek(pMov, pos * sizeof(Movimiento),SEEK_SET);
    escribio=fwrite(this,sizeof (Movimiento),1,pMov);

    fclose(pMov);
    return escribio;
}

#endif // CLSMOVIMIENTO_H_INCLUDED