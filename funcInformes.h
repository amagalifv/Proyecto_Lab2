#ifndef FUNCINFORMES_H_INCLUDED
#define FUNCINFORMES_H_INCLUDED

#include <string.h>
#include <iostream>

#include "prototipos.h"
#include "clsMovimiento.h"
#include "clsCategoria.h"

using namespace std;

//PROTOTIPOS
void cargarArchivoCategoriasEnVector(Categoria *arrayCateg, int cant);
void mostrarArray(Categoria *arrayCateg, float *arrayAnual, int cant);
//FIN PROTOTIPOS

//FUNCIONES
int menuInformes(){
    int opc=0;
    int auxInt;
    int anio=0;

    while(true){
        cout<<"*************************************"<<endl;
        cout<<"            MENU INFORMES            "<<endl;
        cout<<"*************************************"<<endl;
        cout<<"      1) TOTAL DE INGRESOS POR MES"<<endl;
        cout<<"      2) TOTAL DE EGRESOS POR MES"<<endl;
        cout<<"      3) TOTAL INGRESOS ANUALES"<<endl;
        cout<<"      4) TOTAL EGRESOS ANUALES"<<endl;
        cout<<"      5) TOTAL GASTO POR CATEGORIA MENSUAL"<<endl;
        cout<<"      6) TOTAL GASTO POR CATEGORIA ANUAL"<<endl;
        cout<<"      7) COMPARACION DE AHORRO DE 2 PERIODOS POR CATEGORIA"<<endl;
        cout<<"      8) TOTAL AHORRO MENSUAL"<<endl;
        cout<<"      9) TOTAL AHORRO ANUAL"<<endl;
        cout<<"*************************************"<<endl;
        cout<<"      0) VOLVER AL MENU PRINCIPAL"<<endl;
        cout<<"*************************************"<<endl;
        cout<<"SELECCIONE UNA DE LAS OPCIONES: ";
        cin>>opc;
        system("cls");

        switch (opc){
            //1. TOTAL DE INGRESOS POR MES
            case 1: mensajesListados("TOTAL DE INGRESOS POR MES");
                cout<<"INGRESE EL AÑO A LISTAR: ";
                cin>>anio;
                totalIngresosPorMes(anio);
                break;

            //2. TOTAL DE EGRESOS POR MES
            case 2: mensajesListados("TOTAL DE EGRESOS POR MES");
                cout<<"INGRESE EL AÑO A LISTAR: ";
                cin>>anio;
                totalEgresosPorMes(anio);
                break;

            //3. TOTAL INGRESOS ANUALES
            case 3: mensajesListados("TOTAL DE INGRESOS ANUALES");
                cout<<"INGRESE EL AÑO A LISTAR: ";
                cin>>anio;
                totalIngresosPorAnio(anio);
                break;

            //4. TOTAL EGRESOS ANUALES
            case 4: mensajesListados("TOTAL DE EGRESOS ANUALES");
                cout<<"INGRESE EL AÑO A LISTAR: ";
                cin>>anio;
                totalEgresosPorAnio(anio);
                break;

            //5. TOTAL GASTO POR CATEGORIA MENSUAL
            case 5: totalGastoCategMatriz();
                break;

            //6. TOTAL GASTO POR CATEGORIA ANUAL
            case 6: cout<<"Escriba el aÃ±o a consultar: ";
                    cin>>auxInt;
                    cout<<endl;
                    totalGastoCategoriaAnual(auxInt);
                break;

            //7. COMPARACION DE AHORRO DE 2 PERIODOS POR CATEGORIA
            case 7: compararAhorroCategoriaPeriodos();
                break;

            //8. TOTAL AHORRO MENSUAL
            case 8: totalAhorroMensual();
                break;

            //9. TOTAL AHORRO ANUAL
             case 9: totalAhorroAnual();
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
void totalIngresosPorMes(int anio){
    Movimiento mov;
    float v[12]={0};
    string  meses[12]={"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Sepiembre","Octubre","Noviembre","Diciembre"};
    int j=0, tipoCategoria;

    while(mov.leerDeDisco(j)==1) {

        tipoCategoria=buscarTipoCategoria(mov.getCategoria());

        if (mov.getFecha().getAnio()==anio && tipoCategoria==1) {
            v[mov.getFecha().getMes()-1]+=mov.getImporte();
        }
        j++;
    }

    cout<<"\n*********LISTA DE INGRESOS POR MES*********\n";
    for (int k=0; k<12; k++) {
        cout<<meses[k]<<" - Total $ "<<v[k]<<endl;
    }
}

void totalEgresosPorMes(int anio){
    Movimiento mov;
    float v[12]={0};
    string  meses[12]={"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Sepiembre","Octubre","Noviembre","Diciembre"};
    int j=0, tipoCategoria;

    while(mov.leerDeDisco(j)==1) {
        tipoCategoria=buscarTipoCategoria(mov.getCategoria());
        if (mov.getFecha().getAnio()==anio && tipoCategoria==2) {
            v[mov.getFecha().getMes()-1]+=mov.getImporte();
        }
        j++;
    }

    cout<<"\n*********LISTA DE EGRESOS POR MES*********\n";
    for (int k=0; k<12; k++) {
        cout<<meses[k]<<" - Total $ "<<v[k]<<endl;
    }
}

void totalIngresosPorAnio(int anio){
    Categoria cate;
    Movimiento mov;
    float acu=0;
    int i=0, j=0;

    while (cate.leerDeDisco(i)==1) {

        if (cate.getTipoMov()==1) { // si es igual a ingreso
            cout<<"CATEGORIA: "<<cate.getId()<<" - "<<cate.getNombre();

            while(mov.leerDeDisco(j)==1) {
                if (mov.getFecha().getAnio()==anio && mov.getCategoria()==cate.getId()) {
                    acu+=mov.getImporte();
                }
                j++;
            }

            cout<<": $"<<acu<<endl;
            acu=0;
            j=0;
        }

        i++;
    }
}

void totalEgresosPorAnio(int anio){
    Categoria cate;
    Movimiento mov;
    float cont=0;
    int i=0, j=0;

    while (cate.leerDeDisco(i)==1) {

        if (cate.getTipoMov()==2) { // si es igual a egreso
            cout<<"CATEGORIA: "<<cate.getId()<<" - "<<cate.getNombre();

            while(mov.leerDeDisco(j)==1) {
                if (mov.getFecha().getAnio()==anio && mov.getCategoria()==cate.getId()) {
                    cont+=mov.getImporte();
                }
                j++;
            }

            cout<<": $"<<cont<<endl;
            cont=0;
            j=0;
        }

        i++;
    }
}
int calcularCantidadMovimientosAnio(int anio){
    Movimiento reg;
    int posDisco=0;

    while(reg.leerDeDisco(posDisco)==1){
        if(reg.getFecha().getAnio()==anio){
            posDisco++;
        }
    }
    return posDisco;
}
void ponerMatrizEnCero(float **matrizCategMensual, int filas, int columnas){
    for(int i=0; i<filas; i++){
        for (int j=0; j<columnas; j++){
            *(*(matrizCategMensual+i)+j)=0;
        }
    }
}
void ponerVectorEnCero(float *arrayAnual, int cant){
    for(int i=0; i<cant; i++){
        arrayAnual[i]=0;
    }
}
void cargarMatrizCategMensual(float **matrizCategMensual){
    Movimiento reg;
    int posDisco=0;
    int posMatriz=-1;

    while(reg.leerDeDisco(posDisco++)==1){
        //matrizCategMensual[reg.getIdCategoria()-1][reg.getFecha().getMes()-1]+=reg.getImporte();
        posMatriz=buscarCategoriaCodigo(reg.getCategoria());
        *(*(matrizCategMensual+(posMatriz))+(reg.getFecha().getMes()-1))+=reg.getImporte();
    }
}
void mostrarMatriz(float **matrizCategMensual, int filas, int columnas){

    Categoria reg;

    mensajesListados("TOTAL GASTOS MENSUALES POR CATEGORIA");
    cout<<"   "<<"CATEGORIA"<<"\t\t\t";
    for (int i=1; i<=12; i++){
        cout<<"MES "<<i<<"\t";
    }
    cout<<endl;

    for(int i=0; i<filas; i++){
        reg.leerDeDisco(i);
        if(strlen(reg.getNombre())<9){
            printf(" %s\t\t\t\t", reg.getNombre());
        }
        else{
            if(strlen(reg.getNombre())>8 && strlen(reg.getNombre())<15){
                printf(" %s\t\t\t", reg.getNombre());
            }
            else{
                printf(" %s\t\t", reg.getNombre());
            }
        }
        for (int j=0; j<columnas; j++){
            printf("$%.2f\t", *(*(matrizCategMensual+i)+j));
            //cout<<"$"<<*(*(matrizCategMensual+i)+j)<<"\t";
        }
        cout<<endl;
    }
}
void mostrarMatrizPartida(float **matrizCategMensual, int filas, int columnas){

    Categoria reg;

    mensajesListados("TOTAL GASTOS MENSUALES POR CATEGORIA");
    
    /// MUESTRO MATRIZ DEL MES 1 AL 6
    cout<<"   "<<"CATEGORIA"<<"\t\t\t";
    for (int i=1; i<=6; i++){
        cout<<"MES "<<i<<"\t\t";
    }
    cout<<endl;

    for(int i=0; i<filas; i++){
        reg.leerDeDisco(i);
        if(strlen(reg.getNombre())<9){
            printf(" %s\t\t\t\t", reg.getNombre());
        }
        else{
            if(strlen(reg.getNombre())>8 && strlen(reg.getNombre())<15){
                printf(" %s\t\t\t", reg.getNombre());
            }
            else{
                printf(" %s\t\t", reg.getNombre());
            }
        }
        for (int j=0; j<6; j++){
            printf("$%.2f\t\t", *(*(matrizCategMensual+i)+j));
            //cout<<"$"<<*(*(matrizCategMensual+i)+j)<<"\t";
        }
        cout<<endl;
    }

    /// MUESTRO MATRIZ DEL MES 7 AL 12
    cout<<"\n   "<<"CATEGORIA"<<"\t\t\t";
    for (int i=7; i<=12; i++){
        cout<<"MES "<<i<<"\t\t";
    }
    cout<<endl;

    for(int i=0; i<filas; i++){
        reg.leerDeDisco(i);
        if(strlen(reg.getNombre())<9){
            printf(" %s\t\t", reg.getNombre());
        }
        else{
            if(strlen(reg.getNombre())>8 && strlen(reg.getNombre())<15){
                printf(" %s\t", reg.getNombre());
            }
            else{
                printf(" %s", reg.getNombre());
            }
        }
        for (int j=6; j<12; j++){
            printf("\t\t$%.2f", *(*(matrizCategMensual+i)+j));
            //cout<<"$"<<*(*(matrizCategMensual+i)+j)<<"\t";
        }
        cout<<endl;
    }

}
void totalGastoCategMatriz(){
    int filas=calcularCantidadCategorias();
    const int columnas=12;
    float **matrizCategMensual;

    //PEDIR MEMORIA
    matrizCategMensual= new float *[filas];
    for(int i=0; i<filas; i++){
        matrizCategMensual[i]=new float [columnas];
    }

    ponerMatrizEnCero(matrizCategMensual, filas, columnas);

    cargarMatrizCategMensual(matrizCategMensual);

    //mostrarMatriz(matrizCategMensual, filas, columnas);
    //cout<<"\nMATRIZ PARTIDA"<<endl;
    mostrarMatrizPartida(matrizCategMensual, filas, columnas);

    //LIBERAR MEMORIA
    for(int i=0; i<filas; i++){
        delete matrizCategMensual[i];
    }

    delete matrizCategMensual;
}
void cargarArchivoCategoriasEnVector(Categoria *arrayCateg, int cant){
    Categoria reg;
    int pos=0;
    for(int i=0;i<cant;i++){
        reg.leerDeDisco(i);
        pos=reg.getId()-1;
        arrayCateg[pos]=reg;
    }
}
void cargarImportesEnVector(float *arrayAnual, int anio){
    Movimiento reg;
    int posDisco=0;
    int posMatriz=-1;

    while(reg.leerDeDisco(posDisco++)==1){
        if(reg.getFecha().getAnio()==anio){
            posMatriz=buscarCategoriaCodigo(reg.getCategoria());
            arrayAnual[posMatriz]+=reg.getImporte();
        }
    }
}
void mostrarArray(Categoria *arrayCateg, float *arrayAnual, int cant){
    for(int i=0; i<cant; i++){
        //cout<<arrayCateg[i].getNombre()<<"\t"<<arrayAnual[i]<<"\t";
        if(strlen(arrayCateg[i].getNombre())<9){
            printf("  %s\t\t\t $%.2f\n",arrayCateg[i].getNombre(),arrayAnual[i]);
        }
        else{
            if(strlen(arrayCateg[i].getNombre())>8 && strlen(arrayCateg[i].getNombre())<14){
                printf("  %s\t\t $%.2f\n",arrayCateg[i].getNombre(),arrayAnual[i]);
            }
            else{
                printf("  %s\t $%.2f\n",arrayCateg[i].getNombre(),arrayAnual[i]);
            }
        }
        //printf("  %s\t $%.2f\n",arrayCateg[i].getNombre(),arrayAnual[i]);
    }
}
void totalGastoCategoriaAnual(int anio){
    Movimiento reg;
    int cant=0;

    cant=calcularCantidadCategorias();
    Categoria *arrayCateg;
    arrayCateg=new Categoria[cant];
    cargarArchivoCategoriasEnVector(arrayCateg, cant);

    float *arrayAnual;
    arrayAnual=new float[cant]; //es del mismo largo que categorias
    ponerVectorEnCero(arrayAnual, cant);
    cargarImportesEnVector(arrayAnual, anio);

    mensajesListados("GASTOS ANUALES POR CATEGORIA");
    mostrarArray(arrayCateg, arrayAnual,cant);

    delete arrayCateg;
    delete arrayAnual;
}
float sumarAcumuladoCategoriaPeriodo(int codCateg,int codNombreServ, Fecha fecha){
    Movimiento reg;
    MovimientoServicio regServ;
    int posDisco=0;
    int posDiscoServ=0;
    float acumulador=0;

    while(reg.leerDeDisco(posDisco)==1){
        if(reg.getEstado()){
            if(reg.getCategoria()==codCateg){
                if(reg.getFecha().getAnio()==fecha.getAnio() && reg.getFecha().getMes()== fecha.getMes()){
                    if(codCateg==7){
                        while(regServ.leerDeDisco(posDiscoServ)==1){
                            if(regServ.getCodNombre()==codNombreServ){
                                acumulador+=reg.getImporte();
                            }
                            posDiscoServ++;
                        }
                    }
                    else{
                        acumulador+=reg.getImporte();
                    }
                }
            }
        }
        posDisco++;
    }
    return acumulador;
}
float calcularConsumosCategorias(int codCateg, int codNombreServ, Fecha fechaActual, Fecha fecha2){
    float totalGastoActual=0;
    float totalGasto2=0;
    float porcentaje=0;

    totalGastoActual=sumarAcumuladoCategoriaPeriodo(codCateg, codNombreServ, fechaActual);
    totalGasto2=sumarAcumuladoCategoriaPeriodo(codCateg, codNombreServ, fecha2);

    if(totalGasto2==0){
        porcentaje=-2;
    }
    else{
        if(totalGastoActual==0){
            porcentaje=-3;
        }
        else{
            porcentaje=totalGastoActual*100/totalGasto2;
        }
    }

    if(totalGasto2==0 && totalGastoActual==0){
        porcentaje=-1;
    }

    return porcentaje;
}
void compararAhorroCategoriaPeriodos(){
    Fecha fechaActual;
    Fecha fecha2;
    int codNombreServ=0;
    int mes=0;
    int anio=0;
    int codCateg;
    int posCateg=-1;
    float porcentaje=0;

    devuelveFechaActualSistema(&fechaActual);

    mensajesListados("PORCENTAJE DE AHORRO CON RELACION A GASTO ANTERIOR");
    
    cout<<"Ingrese el codigo de la categoria a comparar (0 para salir): \n";
    listarCategoriasAcotado();
    cout<<"\nCategoria elegida: ";    
    cin>>codCateg;

    if(codCateg==0){
        cout<<"Proceso cancelado!"<<endl;
        return;
    }

    if(codCateg==7){
        cout<<"Listado de servicios disponibles para consultar: "<<endl;
        listarNombreServiciosAcotado();
        cout<<"Ingrese el código del servicio: ";
        cout<<"Código elegido: ";
        cin>>codNombreServ;
        while(codNombreServ<=0 && codNombreServ>contarRegistrosNombreServicios()){
            cout<<"Opcion ingresada inválida, escríbala nuevamente: ";
            cin>>codNombreServ;
        }
    }

    posCateg=buscarCategoriaCodigo(codCateg);

    while(posCateg==-1){
        cout<<"El codigo elegido no corresponde a una categoria del listado, escriba nuevamente: ";
        cin>>codCateg;
        posCateg=buscarCategoriaCodigo(codCateg);
    }

    cout<<"Ingrese el periodo a comparar (se comparará el periodo actual con otro mes/año a elección): "<<endl;
    cout<<"Mes: ";
    cin>>mes;
    cout<<"Año: ";
    cin>>anio;
    fecha2.setMes(mes);
    fecha2.setAnio(anio);

    porcentaje=calcularConsumosCategorias(codCateg, codNombreServ, fechaActual, fecha2);

    //**********************
    //Agregar que debe comparar movServ si es categ 7!!!

    if(porcentaje==-1){
        cout<<"No tuviste gastos de ese servicio en ninguno de los periodos!"<<endl;
        return;
    }
    if(porcentaje==-2){
        cout<<"No tuviste gastos de ese servicio en el periodo anterior. No se puede comparar."<<endl;
        return;
    }
    if(porcentaje==-3){
        cout<<"No tuviste gastos de ese servicio en el periodo actual. No se puede comparar."<<endl;
    }
    if(porcentaje==0){
        cout<<"Comparando ambos periodos gastaste lo mismo."<<endl;
    }
    else{
        if(porcentaje>=1 && porcentaje<=100){
            printf("Comparando ambos periodos tuviste un ahorro del %.2f%\n",porcentaje);
        }
        else{
            if(porcentaje>100){
                cout<<"Comparando ambos periodos gastaste un "<<porcentaje-100<<"% más que el periodo anterior."<<endl;
            }
        }
    }
}
void totalAhorroMensual(){
    int anio=0;
    float montoAhorro;

    mensajesListados("TOTAL DE AHORROS POR MES");
    cout<<"\nIndique el año a informar: ";
    cin>>anio;
    
    for(int i=0; i<12; i++){
        montoAhorro=buscarAhorroPorMesAnio(anio, i+1);
        if(montoAhorro==-1){montoAhorro=0;}
        cout<<"Mes "<<i+1<<"\t$"<<montoAhorro+calcularSaldoDisponibleMesPuntual(anio, i+1)<<endl;
    }    
}
void totalAhorroAnual(){
    float acumulador;
    int anio=0;
    float montoAhorro;

    mensajesListados("TOTAL DE AHORROS POR AÑO");
    cout<<"\nIndique el año a informar: ";
    cin>>anio;
    
    for(int i=0; i<12; i++){
        montoAhorro=buscarAhorroPorMesAnio(anio, i+1);
        acumulador=montoAhorro+calcularSaldoDisponibleMesPuntual(anio, i+1);
    }

    cout<<"El total de dinero ahorrado durante el año "<<anio<<" fue de $"<<acumulador<<endl;
}
//FIN FUNCIONES

#endif // FUNCINFORMES_H_INCLUDED
