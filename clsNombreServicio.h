#ifndef CLSNOMBRESERVICIO_H_INCLUDED
#define CLSNOMBRESERVICIO_H_INCLUDED

# include<cstring>
#include "prototipos.h"

using namespace std;

class NombreServicio{
    private:
        int id;
        char descripcion[15];
        bool estado;

        //METODOS
        int proximoIdNombreServ();
    public:
        //CONSTRUCTOR POR OMISION
        NombreServicio(int pCod=0, const char *pDes="nada", bool pEst=false){
            id=pCod;
            strcpy(descripcion,pDes);
            estado=pEst;
        }
        //SETTERS
        void setId(int pCod){id=pCod;}
        void setDescripcion(const char *pDesc){strcpy(descripcion,pDesc);}
        void setEstado(bool pEst){estado=pEst;}
        //GETTERS
        int getId(){return id;}
        const char *getDescripcion(){return descripcion;}
        bool getEstado(){return estado;}
        //METODOS
        void Cargar(char *descrip);
        void Mostrar();
        int leerDeDisco(int pos);
        int grabarEnDisco(int pos=-1);
};
void NombreServicio::Cargar(char *descrip){
    int id=proximoIdNombreServ();
    //char pNombre[15];

    setId(id);

    setDescripcion(descrip);

    setEstado(true);

    cout<<endl;
}
void NombreServicio::Mostrar(){
    cout<<"CODIGO DEL SERVICIO: "<<getId()<<endl;
    cout<<"NOMBRE DEL SERVICIO: "<<getDescripcion()<<endl<<endl;
}
int NombreServicio::leerDeDisco(int pos){
    /******************************************
     Valores que retorna leerDeDisco(int pos):
     -1: NO ENCONTRÓ EL ARCHIVO
      1: LEYO EL ARCHIVO
      2:
      NOTA: SI PARAMETRO == -8, LEE DESDE EL FINAL AL INICIO DEL ARCHIVO
    ******************************************/
    FILE *archivo;
    int leyo=-1;

    archivo=fopen(AR_NOMBRESERVICIOS,"rb");

    if(archivo==NULL){
        return -1;
    }

    if( pos == -8){
        fseek(archivo, 0 ,SEEK_END);
        fseek(archivo, -sizeof(NombreServicio), SEEK_END);
        leyo=fread(this, sizeof(NombreServicio), 1, archivo);
    }
    else{
        fseek(archivo, pos*sizeof(NombreServicio), 0);
        leyo=fread(this, sizeof(NombreServicio), 1, archivo);
    }

    fclose(archivo);
    return leyo;
}
int NombreServicio::grabarEnDisco(int pos){
    /******************************************
     Valores que retorna grabarEnDisco(int pos):
     -1: NO PUDO GRABAR EN EL ARCHIVO
      1: ESCRIBIÓ EL ARCHIVO
      2:
    ******************************************/
FILE *archivo;
    int escribio;

    if(pos==-1){
        archivo=fopen(AR_NOMBRESERVICIOS, "ab");
        if(archivo==NULL){
            return -1;
        }
    }
    else{
        archivo=fopen(AR_NOMBRESERVICIOS, "rb+");
        if(archivo==NULL){
            return -1;
        }
        fseek(archivo, sizeof(NombreServicio)*pos, 0);
    }

    escribio=fwrite(this, sizeof(NombreServicio), 1, archivo);
    fclose(archivo);
    return escribio;
}
int NombreServicio::proximoIdNombreServ(){
    ///DEVUELVE EL PROXIMO NRO DE ID (AUTOINCREMENTABLE)
    
    leerDeDisco(-8);
    return getId()+1;
}


#endif // CLSNOMBRESERVICIO_H_INCLUDED
