#ifndef FUNCAHORRO_H_INCLUDED
#define FUNCAHORRO_H_INCLUDED

#include "prototipos.h"
#include "clsAhorro.h"
#include "clsMovimiento.h"
#include "clsCategoria.h"
#include "funcCategoria.h"

using namespace std;

//VER COMO IMPLEMENTAR DIA 1 DE CADA MES SE RESETAN LOS ACUMULADORES

//PROTOTIPOS
int calcularMeses(Fecha fechaHoy, Fecha fechaFutura);
bool opcionEgresoValida(Categoria *arrayCateg, int cantidad, int opc);
//FIN PROTOTIPOS

//FUNCIONES
int menuKakebo(){
    int opc=0;
    int mes=0;
    int anio=0;
    float montoAhorro=0;
    float auxFloat=0;
    Fecha fechaActual;

    while(true){
        cout<<"*********************************************"<<endl;
        cout<<"                 MENU KAKEBO                 "<<endl;
        cout<<"*********************************************"<<endl;
        cout<<"      1) DEFINIR AHORRO DEL MES"<<endl;
        cout<<"      2) MODIFICAR AHORRO DEL MES"<<endl;
        cout<<"      3) CONSULTAR AHORRO DEFINIDO"<<endl;
        cout<<"      4) VER SALDO DISPONIBLE"<<endl;
        cout<<"      5) VER PROMEDIO DIARIO DISPONIBLE"<<endl;
        cout<<"      6) SIMULACION: QUIERO AHORRAR PARA..."<<endl;
        cout<<"      7) VER SI LOGRE LA META DE AHORRO"<<endl;
        cout<<"*********************************************"<<endl;
        cout<<"      0) VOLVER AL MENU PRINCIPAL"<<endl;
        cout<<"*********************************************"<<endl;
        cout<<"SELECCIONE UNA DE LAS OPCIONES: ";
        cin>>opc;
        system("cls");

        switch (opc){
            //1. DEFINIR AHORRO DEL MES
            case 1: definirAhorroMes();
                break;

            //2. MODIFICAR AHORRO DEL MES
            case 2: cout<<"IMPORTANTE: SOLO SE PODRA MODIFICAR EL AHORRO DE ESTE PERIODO!"<<endl;
                mensajeOperacion(modificarAhorroMes());
                break;

            //3. VER SALDO DISPONIBLE
            case 3:
                cout<<"Ahorro del mes definido:  $"<<consultarAhorroDefinido();
                break;

            //4. VER SALDO DISPONIBLE
            case 4:
                cout<<"El total de dinero disponible que tenes para gastar a lo largo del mes es $"<<calcularSaldoDisponibleMesActual();
                break;

            //5. VER PROMEDIO DIARIO DISPONIBLE
            case 5: auxFloat=calcularPromedioDiarioSaldo();
                cout<<"El promedio diario de dinero disponible que tenes para gastar a lo largo del mes es $"<<auxFloat<<endl;
                break;

            //6. SIMULACION: QUIERO AHORRAR PARA...
            case 6: quieroAhorrarPara();
                break;

            //7. VER SI LOGRE LA META DE AHORRO
            case 7: devuelveFechaActualSistema(&fechaActual);
                mes=fechaActual.getMes();
                anio=fechaActual.getAnio();

                mensajesListados("VER RESULTADO META DE AHORRO");
                cout<<"Mes: "<<mes<<endl;
                cout<<"Anio: "<<anio<<endl;

                if(logroMetaAhorro(fechaActual)){
                    montoAhorro=buscarAhorroPorMesAnio(anio, mes);
                    cout<<"Felicitaciones, has logrado ahorrar lo que te propusiste!"<<endl;
                    cout<<"Ahorro propuesto: $"<<montoAhorro<<endl;
                    cout<<"Ahorro conseguido: $"<<montoAhorro+calcularSaldoDisponibleMesPuntual(anio, mes);
                }
                else{
                    cout<<"No te desanimes! Empieza con menos e intenta proponerte un ahorro menor el prÃ³ximo mes."<<endl;
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
//float calcularIngresos(int anio, int mes){
float calcularIngresos(Fecha fecha){
    Categoria *arrayCategorias;
    int cantidad=0;
    Movimiento reg;
    int posDisco=0;
    int categoria=0;
    float totalIngresos=0;
    int mes=fecha.getMes();
    int anio=fecha.getAnio();

    cantidad=calcularCantidadCategorias();
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

    //cantRegCateg=generarVectorDinamicoCategorias(arrayCategorias);

    while(reg.leerDeDisco(posDisco++)==1){
        if (reg.getEstado()){
            if(reg.getFecha().getAnio()==anio && reg.getFecha().getMes()==mes){
                categoria=reg.getCategoria();
                if(!esEgreso(arrayCategorias,categoria)){
                    totalIngresos+=reg.getImporte();
                }
            }
        }
    }

    delete arrayCategorias;

    return totalIngresos;
}
//float calcularEgresos(int anio, int mes){
float calcularEgresos(Fecha fecha){
    Categoria *arrayCategorias;
    int cantidad=0;
    Movimiento reg;
    int posDisco=0;
    int categoria=0;
    float totalEgresos=0;
    int anio=fecha.getAnio();
    int mes=fecha.getMes();

    cantidad=calcularCantidadCategorias();
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

    //cantRegCateg=generarVectorDinamicoCategorias(arrayCategorias);

    while(reg.leerDeDisco(posDisco++)==1){
        if (reg.getEstado()){
            if(reg.getFecha().getAnio()==anio && reg.getFecha().getMes()==mes){
                categoria=reg.getCategoria();
                if(esEgreso(arrayCategorias,categoria)){
                    totalEgresos+=reg.getImporte();
                }
            }
        }
    }

    delete arrayCategorias;

    return totalEgresos;
}
//float calcularGastoFijo(int anio, int mes){
float calcularGastoFijo(Fecha Fecha){
    Categoria *arrayCategorias;
    int cantidad=0;
    Movimiento reg;
    int posDisco=0;
    int categoria=0;
    float totalGastoFijo=0;
    int anio=Fecha.getAnio();
    int mes=Fecha.getMes();

    cantidad=calcularCantidadCategorias();
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

    //cantRegCateg=generarVectorDinamicoCategorias(arrayCategorias);

    while(reg.leerDeDisco(posDisco++)==1){
        if (reg.getEstado()){
            if(reg.getFecha().getAnio()==anio && reg.getFecha().getMes()==mes){
                categoria=reg.getCategoria();
                if(esGastoFijo(anio, mes,categoria)){
                    totalGastoFijo+=reg.getImporte();
                }
            }
        }
    }

    delete arrayCategorias;

    return totalGastoFijo;
}
//bool validarMontoAhorro(float montoAhorro, int anio, int mes){
bool validarMontoAhorro(float montoAhorro, Fecha fecha){

    cout<<endl;

    //VER QUE PASA SI LOS GASTOS CARGADOS SON MAYORES QUE LOS INGRESOS
    //int totalIngresos=calcularIngresos(anio, mes);
    int totalIngresos=calcularIngresos(fecha);
    //int totalEgresos=calcularEgresos(anio, mes);
    int totalEgresos=calcularEgresos(fecha);
    //int totalGastoFijo=calcularGastoFijo(anio, mes);

    if(totalIngresos==0 || totalEgresos==0){
        cout<<"Para cargar el ahorro primero debe cargar los ingresos y gastos del mes."<<endl;
        return false;
    }

    if(montoAhorro>0 && montoAhorro<=(totalIngresos-totalEgresos)){
        return true;
    }

    if(montoAhorro<0){
        cout<<"El ahorro no puede ser negativo."<<endl;
    }

    if(montoAhorro>=(totalIngresos-totalEgresos)){
        cout<<"El ahorro no puede ser mayor al dinero que ingresa por mes."<<endl;
        cout<<"Ingreso del mes en curso : $"<<totalIngresos<<endl<<endl;
    }
    return false;
}
int existeRegistro(int anio, int mes){
    Ahorro reg;
    int posDisco=0;

    while(reg.leerDeDisco(posDisco)==1){
        if(reg.getFecha().getAnio()==anio){
            if(reg.getFecha().getMes()==mes){
                return posDisco;
            }
        }
        posDisco++;
    }

    posDisco=-1;
    return posDisco;
}
void definirAhorroMes(){
    Ahorro reg;
    Fecha fechaAhorro;
    int posDisco=0;
    float auxFloat=0;

    mensajesListados("DEFINIR AHORRO DEL MES");
    
    devuelveFechaActualSistema(&fechaAhorro);

    posDisco=existeRegistro(fechaAhorro.getAnio(), fechaAhorro.getMes());

    if(posDisco==-1){
        cout<<"Monto que quiere ahorrar: $";
        cin>>auxFloat;

        if(validarMontoAhorro(auxFloat, fechaAhorro)){

            if(reg.Cargar(fechaAhorro,auxFloat)){
                reg.grabarEnDisco();
                cout<<"Ahorro configurado!"<<endl;
            }
        }
        else{
            cout<<"No se pudo cargar el ahorro. "<<endl;
        }
    }
    else{
        cout<<"El registro ya existe. No se puede agregar, ejecute Modificar ahorro."<<endl;
    }
}
bool modificarAhorroMes(){
    Ahorro reg;
    float ahorroMes=0;
    bool resultado=false;

    reg.leerDeDisco(-8);   //fuerzo a que sÃ³lo se pueda modificar el Ãºltimo registro generado.

    cout<<"\nEl monto actualmente configurado es: $"<<reg.getMontoAhorro()<<endl;

    cout<<"Ingrese el nuevo monto a ahorrar (-1 para cancelar): $";
    cin>>ahorroMes;

    if(ahorroMes==-1){
        return 0;
    }

    if(validarMontoAhorro(ahorroMes, reg.getFecha())){
        reg.setMonto(ahorroMes);
        reg.grabarEnDisco(existeRegistro(reg.getFecha().getAnio(), reg.getFecha().getMes()));
        resultado=true;
    }

    return resultado;
}
float consultarAhorroDefinido(){
    Ahorro reg;

    reg.leerDeDisco(-8);

    return reg.getMontoAhorro();
}
void mostrarArchivoAhorro(){
    Ahorro reg;
    int posDisco=0;
    while(reg.leerDeDisco(posDisco++)==1){
        reg.Mostrar();
    }

    system("pause");
}
float buscarAhorroPorMesAnio(int anio, int mes){
    Ahorro reg;
    int posDisco=0;

    while(reg.leerDeDisco(posDisco)==1){
        if(reg.getFecha().getAnio()==anio && reg.getFecha().getMes()==mes){
            return reg.getMontoAhorro();
        }
        posDisco++;   
    }
    return -1;
}
float calcularSaldoDisponibleMesActual(){
    Ahorro reg;
    reg.leerDeDisco(-8);
    Fecha fecha=reg.getFecha();
    int anio= fecha.getAnio();
    int mes= fecha.getMes();

    //float totalIngresos=calcularIngresos(anio, mes);
    float totalIngresos=calcularIngresos(fecha);
    //float totalEgresos=calcularEgresos(anio, mes);
    float totalEgresos=calcularEgresos(fecha);
    float montoAhorro=buscarAhorroPorMesAnio(anio, mes);
    

    if(montoAhorro==-1){
        montoAhorro=0;
    }

    return totalIngresos-totalEgresos-montoAhorro;
}
float calcularSaldoDisponibleMesPuntual(int anio, int mes){
    Ahorro reg;

    Fecha fecha;
    fecha.setAnio(anio);
    fecha.setMes(mes);

    //float totalIngresos=calcularIngresos(anio, mes);
    //float totalEgresos=calcularEgresos(anio, mes);
    float totalIngresos=calcularIngresos(fecha);
    float totalEgresos=calcularEgresos(fecha);
    float montoAhorro=buscarAhorroPorMesAnio(anio, mes);


    if(montoAhorro==-1){
        montoAhorro=0;
    }

    return totalIngresos-totalEgresos-montoAhorro;
}
float calcularPromedioDiarioSaldo(){
    Ahorro reg;
    int diasDelMes=0;
    float promedioDiarioRestante=0;
    Fecha fecha;

    reg.leerDeDisco(-8);

    //int anio=reg.getFecha().getAnio();  //migrar a objeto fecha
    int mes=reg.getFecha().getMes();
    int dia;
    devuelveFechaActualSistema(&fecha);

    // cout<<"Ingrese el dia de hoy: ";    //ver posib de usar fecha sistema.
    // cin>>dia;
    dia=fecha.getDia();

    float saldoDisponible=calcularSaldoDisponibleMesActual();

    if(mes==11 || mes==4 || mes==6 || mes==9){
        diasDelMes=30;
    }
    else{
        if(mes==2){
            diasDelMes=28;
        }
        else{
            if(mes==0){
                diasDelMes=0;
            }
            else{
                diasDelMes=31;
            }
        }
    }

    promedioDiarioRestante=saldoDisponible/(diasDelMes-dia);

    return promedioDiarioRestante;
}
int calcularMeses(Fecha fechaHoy, Fecha fechaFutura){
    int mesesDisponibles=0;
    int aniosDisponibles=0;
    /*06- 2022  fecha futura 04-2024
        cantidadAnios=anioFuturo-anioActual
        meses=12-mesActual
        cantidadAnios-1;
        meses+=12*cantAnios;
        meses+=mesesFuturos;

    */
    aniosDisponibles=fechaFutura.getAnio()-fechaHoy.getAnio();  //2
    mesesDisponibles=12-fechaHoy.getMes();
    aniosDisponibles--;
    mesesDisponibles+=12*aniosDisponibles;
    mesesDisponibles+=fechaFutura.getMes();
    return mesesDisponibles;
}
bool opcionEgresoValida(Categoria *arrayCateg, int cantidad, int opc){
    for(int i=0; i<cantidad; i++){
        if(arrayCateg[i].getTipoMov()==2){
            if(arrayCateg[i].getId()==opc){
                return true;
            }
        }
    }
    return false;
}
void quieroAhorrarPara(){

    Fecha fechaHoy;  //devuelveFechaActualSistema(&fechaHoy);
    devuelveFechaActualSistema(&fechaHoy);

    Fecha fechaFutura;
    int opcion=0;
    float necesitoAhorrar=0;
    int mesesDisponibles=0;
    //int aniosDisponibles=0;

    Categoria *arrayCategorias;
    //int cantidad=generarVectorDinamicoCategorias(arrayCategorias);

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

    // cout<<"Ingrese la fecha de hoy: ";  //migrar a obtener fecha del sistema
    // fechaHoy.Cargar();

    cout<<endl;
    mensajesListados("CATEGORIAS");
    cout<<"A continuación se listarán las categorías disponibles para simular el plan de ahorro:"<<endl;
    system("pause");
    cout<<endl;
    mostrarEgresosArrayCategoriasAcotado(arrayCategorias, cantidad);
    cout<<"Indique el codigo de categoria del rubro a simular: "<<endl;;
    cout<<"Categoria elegida: ";
    cin>>opcion;

    while(!opcionEgresoValida(arrayCategorias, cantidad, opcion)){
        cout<<"El codigo elegido no corresponde a una categoria del listado, escriba nuevamente: ";
        cin>>opcion;
    }

    cout<<"Ingrese cuanto cuesta lo que desea comprar (0 para salir): $";
    cin>>necesitoAhorrar;

    if(necesitoAhorrar==0){
        exit(0);
    }

    while(necesitoAhorrar<0){
        if(necesitoAhorrar<=0){
            cout<<"El monto a simular no puede ser un numero negativo, ingreselo nuevamente: ";
            cin>>necesitoAhorrar;
        }
    }

    cout<<"Ingrese la fecha en la que desea concretar dicha compra: "<<endl;
    fechaFutura.Cargar(true);

    while(fechaFutura.fConsolidada()<fechaHoy.fConsolidada()){
        cout<<"El ahorro debe ser a futuro. Escriba nuevamente la fecha: "<<endl;
        fechaFutura.Cargar(true);
    }

    mesesDisponibles=calcularMeses(fechaHoy, fechaFutura);

    cout<<endl;
    mensajesListados("QUIERO AHORRAR PARA...");

    //ver por que no funciona array categorias para mostrar directo.
    cout<<"\t Categoria: "<<arrayCategorias[opcion-1].getNombre()<<endl;
    printf("\t Dinero a ahorrar $%.2f\n",necesitoAhorrar);
    cout<<"\t Meses para lograrlo: "<<mesesDisponibles<<endl;
    if(mesesDisponibles==0){
        //cout<<"\t Dinero a ahorrar por mes $"<<necesitoAhorrar<<endl;
        printf("\t Dinero a ahorrar por mes $%.2f\n",necesitoAhorrar);
    }
    else{
        //cout<<"\t Dinero a ahorrar por mes $"<<necesitoAhorrar/mesesDisponibles<<endl;
        printf("\t Dinero a ahorrar por mes $%.2f\n",necesitoAhorrar/mesesDisponibles);
    }

    delete arrayCategorias;
}
//bool logroMetaAhorro(int anio, int mes){
bool logroMetaAhorro(Fecha fecha){
    int anio=fecha.getAnio();
    int mes=fecha.getMes();
    
    float ahorrado= calcularSaldoDisponibleMesPuntual(anio, mes);
    
    if(ahorrado >=0){
        return true;
    }

    return false;

}
//FIN FUNCIONES
#endif // FUNCAHORRO_H_INCLUDED
