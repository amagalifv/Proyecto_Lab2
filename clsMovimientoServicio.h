#ifndef CLSMOVIMIENTOSERVICIO_H_INCLUDED
#define CLSMOVIMIENTOSERVICIO_H_INCLUDED
# include<cstring>

#include "prototipos.h"
#include "clsNombreServicio.h"
#include "funcNombreServicio.h"

const string uniMedida[4] = {"kw","min","m3","n/a"};
class MovimientoServicio{
    private:
        int _id;
        //char _descripcion[15];
        int _codNombreServ;
        float _consumo;
        int _medida;
        bool _estado; //tiene que ser igual a Movimiento
        void setId (int d){_id=d;};

    public:
        void Mostrar();
        void Cargar(int id);
        int leerDeDisco(int pos);
        int leerDeDisco(int pos, const char *nombreArchivo);
        int grabarEnDisco();
        int modificarDeDisco(int pos);

        //GETTERS
        int getId(){return _id;}
        //const char *getDescripcion(){return _descripcion;}
        int getCodNombre(){return _codNombreServ;}
        int getConsumo(){return _consumo;}
        int getMedida(){return _medida;}
        int getEstado(){return _estado;}
        //SETTERS
        //void setDescripcion(const char *desc){strcpy(_descripcion, desc);}
        void setCodNombre(int pCod){_codNombreServ=pCod;}
        void setConsumo( float c){_consumo=c;}
        void setMedida(int m){_medida=m;}
        void setEstado(bool es){_estado=es;}
};

void MovimientoServicio::Mostrar(){
    int pos=0;
    NombreServicio reg;

    cout<<"DETALLE DEL SERVICIO  :\n";
    cout<<"\t\t\tID: "<<getId()<<endl;
    //cout<<"\t\t\tDESCRIPCION:  "<<getDescripcion()<<endl;
    pos=buscarNombreServPorCodigo(getCodNombre());
    reg.leerDeDisco(pos);
    cout<<"\t\t\tDESCRIPCION:  "<<reg.getDescripcion()<<endl;
    cout<<"\t\t\tCONSUMO:  "<<getConsumo()<<endl;
    cout<<"\t\t\tMEDIDA:  "<<uniMedida[getMedida()-1]<<endl;
}

void MovimientoServicio::Cargar(int id){
    int aux;
    char texto[15];
    int codigo;

    cout<<"\nCARGA DE SERVICIO:  \n\n";
    setId(id);

    cout<<"\tSELECCIONES UN SERVICIO:  "<<endl;
    listarNombreServicios();
    cout<<"Codigo del servicio: ";
    cin>>codigo;
    while(!codServicioValido(codigo)){
        cout<<"El codigo ingresado no existe, ingr�selo nuevamente: ";
        cin>>codigo;        
    }
    setCodNombre(codigo);

    cout<<"\tCONSUMO:  ";
    cin>>aux;
    setConsumo(aux);

    cout<<"\tMEDIDA (1-kw, 2-min, 3-m3, 4-n/a):  ";
    cin>>aux;
    setMedida(aux);

    setEstado(true);
}

/*******************************************************
devuelve -1 si no lo pudo abrir archivo
carga en el obj de la cls la info que leyo y devuelve 1
Si no pudo leer devuelve 0
********************************************************/
int MovimientoServicio::leerDeDisco(int pos){
    FILE *pServ;
    int leyo;

    pServ=fopen(AR_MOVIMIENTOSERVICIOS,"rb");
    if (pServ==NULL){return -1;}

    fseek(pServ, sizeof(MovimientoServicio)*pos,SEEK_SET);
    leyo=fread(this ,sizeof(MovimientoServicio),1,pServ);
    fclose(pServ);

    return leyo;
}

/*******************************************************
devuelve -1 si no lo pudo abrir archivo
carga en el obj de la cls la info que leyo y devuelve 1
Si no pudo leer devuelve 0
********************************************************/
int MovimientoServicio::leerDeDisco(int pos, const char *nombreArchivo){
    FILE *pServ;
    int leyo;

    pServ=fopen(nombreArchivo,"rb");
    if (pServ==NULL){return -1;}

    fseek(pServ, sizeof(MovimientoServicio)*pos,SEEK_SET);
    leyo=fread(this ,sizeof(MovimientoServicio),1,pServ);
    fclose(pServ);

    return leyo;
}

/*********************************
-1 error de apertura de archivo
 0 error fwrite
 1 si escribió exitosamente
**********************************/
int MovimientoServicio::grabarEnDisco(){
    FILE *pServ;
    bool escribio;

    pServ=fopen(AR_MOVIMIENTOSERVICIOS,"ab");
    if (pServ==NULL){return -1;}

    escribio=fwrite(this ,sizeof(MovimientoServicio),1,pServ);
    fclose(pServ);
    return escribio;
}

/***************************
-1 si no pudo abrir
0 si no pudo escribir
1 si escribió exitosamente
****************************/
int MovimientoServicio::modificarDeDisco(int pos){
    FILE *pServ;
    int escribio;

    pServ=fopen(AR_MOVIMIENTOSERVICIOS,"rb+");
    if (pServ==NULL){return -1;}

    fseek(pServ, pos * sizeof(MovimientoServicio),SEEK_SET);
    escribio=fwrite(this,sizeof (MovimientoServicio),1,pServ);

    fclose(pServ);
    return escribio;
}

#endif // CLSMOVIMIENTOSERVICIO_H_INCLUDED
