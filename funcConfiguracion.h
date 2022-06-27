#ifndef FUNCCONFIGURACION_H_INCLUDED
#define FUNCCONFIGURACION_H_INCLUDED

#include <string.h>
#include "clsMovimiento.h"
#include "clsMovimientoServicio.h"
#include "clsCategoria.h"
#include "clsAhorro.h"
#include "prototipos.h"

using namespace std;


//FUNCIONES
int menuConfiguracion(){
    int opc=0;

    while(true){
        cout<<"****************************************"<<endl;
        cout<<"           MENU CONFIGURACION           "<<endl;
        cout<<"****************************************"<<endl;
        cout<<"      1) BACKUP COMPLETO DEL SISTEMA"<<endl;
        cout<<"      2) BACKUP MOVIMIENTOS"<<endl;
        cout<<"      3) BACKUP AHORRO"<<endl;
        cout<<"      4) RESTAURAR TODO EL SISTEMA"<<endl;
        cout<<"      5) RESTAURAR MOVIMIENTOS"<<endl; //BORRAR TAMBIEN MOVIMIENTOSSERVICIOS!!!
        cout<<"      6) RESTAURAR AHORRO"<<endl;
        cout<<"      ------- OPCIONES PROG --------- "<<endl;
        cout<<"      7) CARGAR DATOS DE INICIO"<<endl;
        cout<<"      8) GENERAR DATOS DE INICIO"<<endl;
        cout<<"      9) BACKUP CATEGORIAS"<<endl;
        cout<<"      10) RESTAURAR CATEGORIAS"<<endl;
        cout<<"      11) BKP NOMBRES SERVICIOS"<<endl;
        cout<<"      10) RESTAURAR NOMBRES SERVICIOS"<<endl;
        cout<<"****************************************"<<endl;
        cout<<"      0) VOLVER AL MENU PRINCIPAL"<<endl;
        cout<<"****************************************"<<endl;
        cout<<"SELECCIONE UNA DE LAS OPCIONES: ";
        cin>>opc;
        system("cls");

        switch (opc){
            //1. BACKUP COMPLETO DEL SISTEMA
            case 1: mensajeOperacion(bkpCompletoSistema());
                break;

            //2. BACKUP MOVIMIENTOS
            case 2: mensajeOperacion(bkpMovimientos());
                break;

            //3. BACKUP AHORRO
            case 3: mensajeOperacion(bkpAhorro());
                break;

            //4. RESTAURAR TODO EL SISTEMA
            case 4: mensajeOperacion(restaurarCompletoSistema());
                break;

            //5. RESTAURAR MOVIMIENTOS
            case 5: mensajeOperacion(restaurarBkpMovimientos());
                break;

            //6. RESTAURAR AHORRO
            case 6: mensajeOperacion(restaurarBkpAhorros());
               break;

            //7. CARGAR DATOS DE INICIO
            case 7: mensajeOperacion(cargarDatosDeInicio());
                break;

            //8. GENERAR DATOS DE INICIO
            case 8: mensajeOperacion(generarArchivoDatosInicio());
                break;

            //9. BACKUP CATEGORIAS
            case 9: mensajeOperacion(bkpCategorias());
                break;

            //10. RESTAURAR BKP CATEGORIAS
            case 10: mensajeOperacion(restaurarBkpCategorias());
                break;

            //1. BACKUP NOMBRES SERVICIOS
            case 11: mensajeOperacion(bkpCategorias());
                break;

            //12. RESTAURAR BKP NOMBRES SERVICIOS
            case 12: mensajeOperacion(restaurarBkpCategorias());
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
//BACKUP
bool bkpMovimientos(){
    FILE *movimientoBkp;
    movimientoBkp=fopen(BKP_MOVIMIENTOS,"wb");
    bool resultado=true;

    Movimiento reg;
    int posDisco=0;

    if(movimientoBkp==NULL){
        resultado=false;
    }

    while(reg.leerDeDisco(posDisco++)==1){
        fwrite(&reg, sizeof (Movimiento), 1, movimientoBkp);
    }

    if (!bkpMovimientosServicios() || posDisco==0){
        resultado=false;
    }

    fclose(movimientoBkp);
    return resultado;
}
bool bkpMovimientosServicios(){
    FILE *movimientoServicioBkp;
    movimientoServicioBkp=fopen(BKP_MOVIMIENTOSERVICIOS,"wb");
    bool resultado=true;

    MovimientoServicio reg;
    int posDisco=0;

    if(movimientoServicioBkp==NULL){
        resultado=false;
    }

    while(reg.leerDeDisco(posDisco++)==1){
        fwrite(&reg, sizeof (MovimientoServicio), 1, movimientoServicioBkp);
    }

    if (posDisco==0){
        resultado=false;
    }

    fclose(movimientoServicioBkp);
    return resultado;
}
bool bkpCategorias(){
    FILE *categoriasBkp;
    categoriasBkp=fopen(BKP_CATEGORIAS,"wb");
    bool resultado=true;

    Categoria reg;
    int posDisco=0;

    if(categoriasBkp==NULL){
        resultado=false;
    }

    while(reg.leerDeDisco(posDisco++)==1){
        fwrite(&reg, sizeof (Categoria), 1, categoriasBkp);
    }

    if (posDisco==0){
        resultado=false;
    }

    fclose(categoriasBkp);
    return resultado;
}
bool bkpAhorro(){
    FILE *ahorrosBkp;
    ahorrosBkp=fopen(BKP_AHORRO,"wb");
    bool resultado=true;

    Ahorro reg;
    int posDisco=0;

    if(ahorrosBkp==NULL){
        resultado=false;
    }

    while(reg.leerDeDisco(posDisco++)==1){
        fwrite(&reg, sizeof (Ahorro), 1, ahorrosBkp);
    }

    if (posDisco==0){
        resultado=false;
    }

    fclose(ahorrosBkp);
    return resultado;
}
bool bkpNombresServicios(){
    FILE *nomServBkp;
    nomServBkp=fopen(BKP_NOMBRESERVICIOS,"wb");
    bool resultado=true;

    NombreServicio reg;
    int posDisco=0;

    if(nomServBkp==NULL){
        resultado=false;
    }

    while(reg.leerDeDisco(posDisco++)==1){
        fwrite(&reg, sizeof (NombreServicio), 1, nomServBkp);
    }

    if (posDisco==0){
        resultado=false;
    }

    fclose(nomServBkp);
    return resultado;
}
bool bkpCompletoSistema(){

    if(bkpMovimientos()){
        if(bkpCategorias()){
            if(bkpAhorro()){
                if(bkpNombresServicios()){
                    return true;
                }
            }
        }
    }
    return false;
}

//RESTAURAR
bool restaurarBkpMovimientos(){
    FILE *restaurarArchivoBkp;
    FILE *eliminarArchivoOrigen;
    Movimiento reg;
    int posDisco=0;
    bool resultado=true;

    //eliminarArchivoOrigen=fopen("movimientos.dat", "wb");
    eliminarArchivoOrigen=fopen(AR_MOVIMIENTOS, "wb");
    fclose(eliminarArchivoOrigen);

    //restaurarArchivoBkp=fopen("movimientos.bkp","rb");
    restaurarArchivoBkp=fopen(BKP_MOVIMIENTOS,"rb");

    if(restaurarArchivoBkp==NULL){
        resultado=false;
    }

    while(fread(&reg, sizeof reg, 1, restaurarArchivoBkp)==1){
        //ver esto, porque es mejor unificar el tema de grabar por bkp.
        //reg.grabarEnDisco(posDisco++);
        posDisco=reg.grabarEnDisco();
    }

    if (!restaurarBkpMovimientosServicios() || posDisco==0){
        resultado=false;
    }

    fclose(restaurarArchivoBkp);
    return resultado;
}
bool restaurarBkpMovimientosServicios(){
    FILE *restaurarArchivoBkp;
    FILE *eliminarArchivoOrigen;
    MovimientoServicio reg;
    int posDisco=0;
    bool resultado=true;

    //eliminarArchivoOrigen=fopen("movimientosServicios.dat", "wb");
    eliminarArchivoOrigen=fopen(AR_MOVIMIENTOSERVICIOS, "wb");
    fclose(eliminarArchivoOrigen);

    ///restaurarArchivoBkp=fopen("movimientosServicios.bkp","rb");
    restaurarArchivoBkp=fopen(BKP_MOVIMIENTOSERVICIOS,"rb");

    if(restaurarArchivoBkp==NULL){
        resultado=false;
    }

    while(fread(&reg, sizeof reg, 1, restaurarArchivoBkp)==1){
        //reg.grabarEnDisco(posDisco++);
        posDisco=reg.grabarEnDisco();
    }

    if (posDisco==0){
        resultado=false;
    }

    fclose(restaurarArchivoBkp);
    return resultado;
}
bool restaurarBkpCategorias(){
    FILE *restaurarArchivoBkp;
    FILE *eliminarArchivoOrigen;
    Categoria reg;
    int posDisco=0;
    bool resultado=true;

    //eliminarArchivoOrigen=fopen("categorias.dat", "wb");
    eliminarArchivoOrigen=fopen(AR_CATEGORIAS, "wb");
    fclose(eliminarArchivoOrigen);

    //restaurarArchivoBkp=fopen("categorias.bkp","rb");
    restaurarArchivoBkp=fopen(BKP_CATEGORIAS,"rb");

    if(restaurarArchivoBkp==NULL){
        resultado=false;
    }

    while(fread(&reg, sizeof reg, 1, restaurarArchivoBkp)==1){
        reg.grabarEnDisco(posDisco++);
    }

    if (posDisco==0){
        resultado=false;
    }

    fclose(restaurarArchivoBkp);
    return resultado;
}
bool restaurarBkpAhorros(){
    FILE *restaurarArchivoBkp;
    FILE *eliminarArchivoOrigen;
    Ahorro reg;
    int posDisco=0;
    bool resultado=true;

    //eliminarArchivoOrigen=fopen("ahorro.dat", "wb");
    eliminarArchivoOrigen=fopen(AR_AHORRO, "wb");
    fclose(eliminarArchivoOrigen);

    //restaurarArchivoBkp=fopen("ahorro.bkp","rb");
    restaurarArchivoBkp=fopen(BKP_AHORRO,"rb");

    if(restaurarArchivoBkp==NULL){
        resultado=false;
    }

    while(fread(&reg, sizeof reg, 1, restaurarArchivoBkp)==1){
        reg.grabarEnDisco(posDisco++);
    }

    if (posDisco==0){
        resultado=false;
    }

    fclose(restaurarArchivoBkp);
    return resultado;
}
bool restaurarBkpNombreServicios(){
    FILE *restaurarArchivoBkp;
    FILE *eliminarArchivoOrigen;
    NombreServicio reg;
    int posDisco=0;
    bool resultado=true;

    eliminarArchivoOrigen=fopen(AR_NOMBRESERVICIOS, "wb");
    fclose(eliminarArchivoOrigen);

    restaurarArchivoBkp=fopen(BKP_NOMBRESERVICIOS,"rb");

    if(restaurarArchivoBkp==NULL){
        resultado=false;
    }

    while(fread(&reg, sizeof reg, 1, restaurarArchivoBkp)==1){
        reg.grabarEnDisco(posDisco++);
    }

    if (posDisco==0){
        resultado=false;
    }

    fclose(restaurarArchivoBkp);
    return resultado;
}
bool restaurarCompletoSistema(){

    if(restaurarBkpMovimientos()){
        if(restaurarBkpCategorias()){
            if(restaurarBkpAhorros()){
                if(restaurarBkpNombreServicios()){
                    return true;
                }
            }
        }
    }
    return false;
}

//GENERAR ARCHIVOS DE DATOS DE INICIO
bool datosInicioMovimientos(){
    FILE *movimientoIni;
    //movimientoIni=fopen("movimientos.ini","wb");
    movimientoIni=fopen(INI_MOVIMIENTOS,"wb");
    bool resultado=true;

    Movimiento reg;
    int posDisco=0;

    if(movimientoIni==NULL){
        resultado=false;
    }

    while(reg.leerDeDisco(posDisco++)==1){
        fwrite(&reg, sizeof (Movimiento), 1, movimientoIni);
    }

    if (!datosInicioMovimientosServicios() || posDisco==0){
        resultado=false;
    }

    fclose(movimientoIni);
    return resultado;
}
bool datosInicioMovimientosServicios(){
    FILE *movimientosServiciosIni;
    //movimientosServiciosIni=fopen("movimientosServicios.ini","wb");
    movimientosServiciosIni=fopen(INI_MOVIMIENTOSERVICIOS,"wb");
    bool resultado=true;

    MovimientoServicio reg;
    int posDisco=0;

    if(movimientosServiciosIni==NULL){
        resultado=false;
    }

    while(reg.leerDeDisco(posDisco++)==1){
        fwrite(&reg, sizeof (MovimientoServicio), 1, movimientosServiciosIni);
    }

    if (posDisco==0){
        resultado=false;
    }

    fclose(movimientosServiciosIni);
    return resultado;
}
bool datosInicioCategorias(){
    FILE *categoriasIni;
    //categoriasIni=fopen("categorias.ini","wb");
    categoriasIni=fopen(INI_CATEGORIAS,"wb");
    bool resultado=true;

    Categoria reg;
    int posDisco=0;

    if(categoriasIni==NULL){
        resultado=false;
    }

    while(reg.leerDeDisco(posDisco++)==1){
        fwrite(&reg, sizeof (Categoria), 1, categoriasIni);
    }

    if (posDisco==0){
        resultado=false;
    }

    fclose(categoriasIni);
    return resultado;
}
bool datosInicioAhorros(){
    FILE *ahorrosIni;
    //ahorrosIni=fopen("ahorros.ini","wb");
    ahorrosIni=fopen(INI_AHORRO,"wb");
    bool resultado=true;

    Ahorro reg;
    int posDisco=0;

    if(ahorrosIni==NULL){
        resultado=false;
    }

    while(reg.leerDeDisco(posDisco++)==1){
        fwrite(&reg, sizeof (Ahorro), 1, ahorrosIni);
    }

    if (posDisco==0){
        resultado=false;
    }

    fclose(ahorrosIni);
    return resultado;
}
bool datosInicioNombreServicios(){
    FILE *nombreServIni;
    nombreServIni=fopen(INI_NOMBRESERVICIOS,"wb");
    bool resultado=true;

    NombreServicio reg;
    int posDisco=0;

    if(nombreServIni==NULL){
        resultado=false;
    }

    while(reg.leerDeDisco(posDisco++)==1){
        fwrite(&reg, sizeof (NombreServicio), 1, nombreServIni);
    }

    if (posDisco==0){
        resultado=false;
    }

    fclose(nombreServIni);
    return resultado;
}
bool generarArchivoDatosInicio(){

    if(datosInicioMovimientos()){
        if(datosInicioCategorias()){
            if(datosInicioAhorros()){
                if(datosInicioNombreServicios()){
                    return true;
                }
            }
        }
    }
    return false;
}

//CARGAR EN SISTEMA LOS ARCHIVOS DE INICIO
bool cargarDatosInicioMovimientos(){
    FILE *restaurarArchivoBkp;
    FILE *eliminarArchivoOrigen;
    Movimiento reg;
    int posDisco=0;
    bool resultado=true;

    //eliminarArchivoOrigen=fopen("movimientos.dat", "wb");
    eliminarArchivoOrigen=fopen(AR_MOVIMIENTOS, "wb");
    fclose(eliminarArchivoOrigen);

    //restaurarArchivoBkp=fopen("movimientos.ini","rb");
    restaurarArchivoBkp=fopen(INI_MOVIMIENTOS,"rb");

    if(restaurarArchivoBkp==NULL){
        resultado=false;
    }

    while(fread(&reg, sizeof reg, 1, restaurarArchivoBkp)==1){
        //reg.grabarEnDisco(posDisco++);
        posDisco=reg.grabarEnDisco();
    }

    if (!cargarDatosInicioMovimientosServicios() || posDisco==0){
        resultado=false;
    }

    fclose(restaurarArchivoBkp);
    return resultado;
}
bool cargarDatosInicioMovimientosServicios(){
    FILE *restaurarArchivoBkp;
    FILE *eliminarArchivoOrigen;
    MovimientoServicio reg;
    int posDisco=0;
    bool resultado=true;

    //eliminarArchivoOrigen=fopen("movimientosServicios.dat", "wb");
    eliminarArchivoOrigen=fopen(AR_MOVIMIENTOSERVICIOS, "wb");
    fclose(eliminarArchivoOrigen);

    //restaurarArchivoBkp=fopen("movimientosServicios.ini","rb");
    restaurarArchivoBkp=fopen(INI_MOVIMIENTOSERVICIOS,"rb");

    if(restaurarArchivoBkp==NULL){
        resultado=false;
    }

    while(fread(&reg, sizeof reg, 1, restaurarArchivoBkp)==1){
        //reg.grabarEnDisco(posDisco++);
        posDisco=reg.grabarEnDisco();
    }

    if (posDisco==0){
        resultado=false;
    }

    fclose(restaurarArchivoBkp);
    return resultado;
}
bool cargarDatosInicioCategorias(){
    FILE *restaurarArchivoBkp;
    FILE *eliminarArchivoOrigen;
    Categoria reg;
    int posDisco=0;
    bool resultado=true;

    //eliminarArchivoOrigen=fopen("categorias.dat", "wb");
    eliminarArchivoOrigen=fopen(AR_CATEGORIAS, "wb");
    fclose(eliminarArchivoOrigen);

    //restaurarArchivoBkp=fopen("categorias.ini","rb");
    restaurarArchivoBkp=fopen(INI_CATEGORIAS,"rb");

    if(restaurarArchivoBkp==NULL){
        resultado=false;
    }

    while(fread(&reg, sizeof reg, 1, restaurarArchivoBkp)==1){
        reg.grabarEnDisco(posDisco++);
    }

    if (posDisco==0){
        resultado=false;
    }

    fclose(restaurarArchivoBkp);
    return resultado;
}
bool cargarDatosInicioAhorros(){
    FILE *restaurarArchivoBkp;
    FILE *eliminarArchivoOrigen;
    Ahorro reg;
    int posDisco=0;
    bool resultado=true;

    //eliminarArchivoOrigen=fopen("ahorros.dat", "wb");
    eliminarArchivoOrigen=fopen(AR_AHORRO, "wb");
    fclose(eliminarArchivoOrigen);

    //restaurarArchivoBkp=fopen("ahorros.ini","rb");
    restaurarArchivoBkp=fopen(INI_AHORRO,"rb");

    if(restaurarArchivoBkp==NULL){
        resultado=false;
    }

    while(fread(&reg, sizeof reg, 1, restaurarArchivoBkp)==1){
        reg.grabarEnDisco(posDisco++);
    }

    if (posDisco==0){
        resultado=false;
    }

    fclose(restaurarArchivoBkp);
    return resultado;
}
bool cargarDatosInicioNombreServicios(){
    FILE *restaurarArchivoBkp;
    FILE *eliminarArchivoOrigen;
    NombreServicio reg;
    int posDisco=0;
    bool resultado=true;

    eliminarArchivoOrigen=fopen(AR_NOMBRESERVICIOS, "wb");
    fclose(eliminarArchivoOrigen);

    restaurarArchivoBkp=fopen(INI_NOMBRESERVICIOS,"rb");

    if(restaurarArchivoBkp==NULL){
        resultado=false;
    }

    while(fread(&reg, sizeof reg, 1, restaurarArchivoBkp)==1){
        reg.grabarEnDisco(posDisco++);
    }

    if (posDisco==0){
        resultado=false;
    }

    fclose(restaurarArchivoBkp);
    return resultado;
}
bool cargarDatosDeInicio(){

    if(cargarDatosInicioMovimientos()){
        if(cargarDatosInicioCategorias()){
            if(cargarDatosInicioAhorros()){
                if(cargarDatosInicioNombreServicios()){
                    return true;
                }
            }
        }
    }

    return false;
}
//FIN FUNCIONES

#endif // FUNCCONFIGURACION_H_INCLUDED
