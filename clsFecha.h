#ifndef CLSFECHA_H_INCLUDED
#define CLSFECHA_H_INCLUDED
#include <iostream>
#include <ctime>
using namespace std;

bool validarFecha(int d, int m, int a, bool siAnioFutu);

class Fecha {
    private:
        int _dia, _mes, _anio;
    public:
        Fecha(int dia=0, int mes=0, int anio=0){
            _dia=dia;
            _mes=mes;
            _anio=anio;
        }
        void Mostrar();
        void Cargar(bool siAnioFuturo=false);
        int fConsolidada(){return ((_anio*10000)+(_mes*100)+(_dia));}
        ///gets()
        int getDia(){return _dia;}
        int getMes(){return _mes;}
        int getAnio(){return _anio;}
        ///sets()
        void setDia(int d){if(d>=1 && d<=31){ _dia=d;}else{_dia=0;_mes=0;_anio=0;}}
        void setMes(int m){if(m>=1 && m<=12){ _mes=m;}else{_dia=0;_mes=0;_anio=0;}}
        void setAnio(int a){if(a>=1920){_anio=a;}else{_dia=0;_mes=0;_anio=0;}}
        bool operator== (Fecha f){
            if (f.getDia()==_dia && f.getMes()==_mes && f.getAnio()==_anio){return true;}
            return false;
        }
};

void Fecha::Mostrar(){
    if (getDia()<10){
        cout<<"0"<<getDia();
    }else{
        cout<<getDia();
    }
    cout<<"/";
    if (getMes()<10){
        cout<<"0"<<getMes();
    }else{
        cout<<getMes();
    }
    cout<<"/"<<getAnio()<<endl;
}

void Fecha::Cargar(bool siAnioFuturo){
    int dia, mes, anio;

    cout<<"INGRESE EL DIA:             ";
    cin>>dia;

    cout<<"INGRESE EL MES:             ";
    cin>>mes;

    cout<<"INGRESE EL A√ëO (4 digitos): ";
    cin>>anio;


    while (!validarFecha(dia, mes, anio, siAnioFuturo)){
        cout<<"Fecha incorrecta, ingrÈsela nuevamente: ";
        cout<<"INGRESE EL DIA:             ";
        cin>>dia;

        cout<<"INGRESE EL MES:             ";
        cin>>mes;

        cout<<"INGRESE EL A—O (4 digitos): ";
        cin>>anio;
    }
    
    setDia(dia);setMes(mes);setAnio(anio);

}
/********************FUNCIONES FECHA********************/

bool validarFecha(int d, int m, int a, bool siAnioFutu){
    bool bandera=true;
    int v[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int anioActual;

    //chequear dia segun mes
    if(d>v[m-1]){
        if (d==29 && m==2 && a%4==0) {
            //chequear febrero y a√±o bisiesto
            if (a%100==0 && a%400!=0){bandera=false;}
            else{ bandera=true;}
        }else{bandera=false;}
    }

    //chequear mes
    if (m<1 || m>12){bandera=false;}

    if (siAnioFutu==false) {
        //chequear a√±o
        time_t fechaActual;
        time(&fechaActual);
        struct tm *pST_tiempo = localtime(&fechaActual);
        anioActual=pST_tiempo->tm_year+1900;
        if (a<1920 || a>anioActual) {bandera=false;}
    }else{if (a<1920){bandera=false;}}

    return bandera;
}

void devuelveFechaActualSistema(Fecha *f){
    time_t fechaActual;
    time(&fechaActual);
    struct tm *pST_tiempo = localtime(&fechaActual);
    f->setAnio(pST_tiempo->tm_year+1900);
    f->setMes(pST_tiempo->tm_mon+1);
    f->setDia(pST_tiempo->tm_mday);
}

#endif // CLSFECHA_H_INCLUDED
