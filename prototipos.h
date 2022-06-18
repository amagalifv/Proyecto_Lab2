#ifndef PROTOTIPOS_H_INCLUDED
#define PROTOTIPOS_H_INCLUDED

#include<iostream>
#include<cstring>

using namespace std;

void mostrarArchivoAhorro();

//ARCHIVOS DAT
//const char *AR_MOVIMIENTOS = "movimientos.dat"; //evaluar cambiar nombre por "DAT_MOVIMIENTOS"
const char *AR_MOVIMIENTOS = "movimientos.dat"; //evaluar cambiar nombre por "DAT_MOVIMIENTOS"
const char *AR_MOVIMIENTOSERVICIOS = "movimientoservicios.dat";
const char *AR_CATEGORIAS = "categorias.dat";
const char *AR_AHORRO = "ahorros.dat";

//ARCHIVOS BKP
const char *BKP_MOVIMIENTOS = "movimientos.bkp";
const char *BKP_MOVIMIENTOSERVICIOS = "movimientosServicios.bkp";
const char *BKP_CATEGORIAS = "categorias.bkp";
const char *BKP_AHORRO = "ahorro.bkp";

//ARCHIVOS INI
const char *INI_MOVIMIENTOS = "movimientos.ini";
const char *INI_MOVIMIENTOSERVICIOS = "movimientosServicios.ini";
const char *INI_CATEGORIAS = "categorias.ini";
const char *INI_AHORRO = "ahorro.ini";


//-------GLOBALES-------
void cargarCadena(char *palabra, int tamano);
void mensajeOperacion(bool resultado);
void mensajesListados(const char *mensaje);

//---MOVIMIENTOS SERVICIOS---
int buscarPorId (int);
void crearRegistroServicio(int);
void bajaLogicaServicio(int);

//--------MOVIMIENTOS---------
void listarMovimientos();
int bajaLogica (int pos);
int modificarRegistro(int id);
void mostrarServicio(int id);

int menuMovimientos();

//--------CATEGORIAS---------
int menuCategorias();
int proximoId();
void agregarCategoria();
bool esMovimientoValido(int);
bool esRepetido(const char *);
int listarCategorias();
int listarCategoriaPorId(int);
bool esGastoFijo(int, int, int);
int calcularCantidadCategorias();

//----------KAKEBO / AHORRO-----------
int menuKakebo();
float calcularIngresos(int, int);
float calcularEgresos(int, int);
float calcularGastoFijo(int, int);
bool validarMontoAhorro(float, int, int);
int existeRegistro(int anio, int mes);
void definirAhorroMes();
bool modificarAhorroMes();
float buscarAhorroPorMesAnio(int, int);
float calcularSaldoDisponibleMesActual();
float calcularSaldoDisponibleMesPuntual(int, int);
float calcularPromedioDiarioSaldo();
void quieroAhorrarPara();
bool logroMetaAhorro(int, int);

//---------INFORMES----------

int menuInformes();

//-------CONFIGURACION-------
int menuConfiguracion();
bool bkpMovimientos();
bool bkpMovimientosServicios();
bool bkpCategorias();
bool bkpAhorro();
bool bkpCompletoSistema();
bool restaurarBkpMovimientos();
bool restaurarBkpMovimientosServicios();
bool restaurarBkpCategorias();
bool restaurarBkpAhorross();
bool restaurarCompletoSistema();
bool datosInicioMovimientos();
bool datosInicioMovimientosServicios();
bool datosInicioCategorias();
bool datosInicioAhorros();
bool generarArchivoDatosInicio();
bool cargarDatosInicioMovimientos();
bool cargarDatosInicioMovimientosServicios();
bool cargarDatosInicioCategorias();
bool cargarDatosInicioAhorros();
bool cargarDatosDeInicio();

//FUNCIONES
//a la funcion cargar cadena la mejore usando toupper
void cargarCadena(char *palabra, int tamano){
    int i=0;
    int j=0;
    fflush(stdin);
    for (i=0; i<tamano; i++){
        palabra[i]=toupper(cin.get());
        if (palabra[i]=='\n'){
            break;
        }
    }

    palabra[i]='\0';
    fflush(stdin);

    while(strlen(palabra)>=tamano){
        j=i-1;

        while(palabra[j]!='\0'){
            cout<<"Nombre muy largo, reescribalo: ";
            fflush(stdin);
            for (j=0; j<tamano; j++){
                palabra[j]=cin.get();
                if (palabra[j]=='\n'){
                    break;
                }
            }
            palabra[j]='\0';
            fflush(stdin);

        }
    }
}
void mensajeOperacion(bool resultado){
    if (resultado){
        cout<<"Operacion exitosa!"<<endl;
    }
    else{
        cout<<"No se pudo realizar la operacion."<<endl;
    }
}
void mensajesListados(const char *mensaje){
    cout<<"******** "<<mensaje<<" ********"<<endl;
}

//FIN FUNCIONES

#endif // PROTOTIPOS_H_INCLUDED