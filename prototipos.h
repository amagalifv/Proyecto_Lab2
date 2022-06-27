#ifndef PROTOTIPOS_H_INCLUDED
#define PROTOTIPOS_H_INCLUDED

#include<iostream>
#include<cstring>
#include<windows.h>
#include "clsFecha.h"

using namespace std;

/* //ARCHIVOS DAT
const char *AR_MOVIMIENTOS = "Achivos/movimientos.dat";
const char *AR_MOVIMIENTOSERVICIOS = "Achivos/movimientoservicios.dat";
const char *AR_NOMBRESERVICIOS = "Achivos/nombreservicios.dat";
const char *AR_CATEGORIAS = "Achivos/categorias.dat";
const char *AR_AHORRO = "Achivos/ahorros.dat";

//ARCHIVOS BKP
const char *BKP_MOVIMIENTOS = "Achivos/movimientos.bkp";
const char *BKP_MOVIMIENTOSERVICIOS = "Achivos/movimientosServicios.bkp";
const char *BKP_NOMBRESERVICIOS = "Achivos/nombreservicios.bkp";
const char *BKP_CATEGORIAS = "Achivos/categorias.bkp";
const char *BKP_AHORRO = "Achivos/ahorro.bkp";

//ARCHIVOS INI
const char *INI_MOVIMIENTOS = "Achivos/movimientos.ini";
const char *INI_MOVIMIENTOSERVICIOS = "Achivos/movimientosServicios.ini";
const char *INI_NOMBRESERVICIOS = "Achivos/nombreservicios.ini";
const char *INI_CATEGORIAS = "Achivos/categorias.ini";
const char *INI_AHORRO = "Achivos/ahorro.ini";
 */
//ARCHIVOS DAT
const char *AR_MOVIMIENTOS = "movimientos.dat"; //evaluar cambiar nombre por "DAT_MOVIMIENTOS"
const char *AR_MOVIMIENTOSERVICIOS = "movimientoservicios.dat";
const char *AR_NOMBRESERVICIOS = "nombreservicios.dat";
const char *AR_CATEGORIAS = "categorias.dat";
const char *AR_AHORRO = "ahorros.dat";

//ARCHIVOS BKP
const char *BKP_MOVIMIENTOS = "movimientos.bkp";
const char *BKP_MOVIMIENTOSERVICIOS = "movimientosServicios.bkp";
const char *BKP_NOMBRESERVICIOS = "nombreservicios.bkp";
const char *BKP_CATEGORIAS = "categorias.bkp";
const char *BKP_AHORRO = "ahorro.bkp";

//ARCHIVOS INI
const char *INI_MOVIMIENTOS = "movimientos.ini";
const char *INI_MOVIMIENTOSERVICIOS = "movimientosServicios.ini";
const char *INI_NOMBRESERVICIOS = "nombreservicios.ini";
const char *INI_CATEGORIAS = "categorias.ini";
const char *INI_AHORRO = "ahorro.ini";


//-------GLOBALES-------
void cargarCadena(char *palabra, int tamano);
void mensajeOperacion(bool resultado);
void mensajesListados(const char *mensaje);
void gotoxy(short x, short y);
HWND WINAPI GetConsoleWindowNT(void);

//---MOVIMIENTOS SERVICIOS---
void crearRegistroServicio(int);
void bajaLogicaServicio(int);
int buscarPorIdServ (int);

//---NOMBRES SERVICIOS---
int buscarNombreServPorCodigo(int codigoNombre);
void listarNombreServicios();
void listarNombreServiciosAcotado();
bool codServicioValido(int cod);
int buscarNombreServicioCodigo(int codNombreServicio);
bool modificarNombreServicio(int codNombreServicio);
bool esRepetidoNombreServicio(const char *pNombre);
void agregarNombreServicio();
int contarRegistrosNombreServicios();

//--------MOVIMIENTOS---------
void listarMovimientos();
int buscarPorIdMov (int &id);
int bajaLogica(int);
int modificarRegistro(int id);
void mostrarServicio(int id);
bool siCategoriaValida(int cate);

int menuMovimientos();

//--------CATEGORIAS---------
int menuCategorias();
int proximoId();
void agregarCategoria();
int buscarCategoriaCodigo(int codCateg);
bool modificarCategoria(int codCateg);
bool esMovimientoValido(int);
bool esRepetido(const char *);
int listarCategorias();
int listarCategoriaPorId(int);
bool esGastoFijo(int, int, int);
int calcularCantidadCategorias();
void listarCategoriasAcotado();
void listarCategoriasEgresoAcotado();
int buscarTipoCategoria(int categoria);

//----------KAKEBO / AHORRO-----------
int menuKakebo();
//float calcularIngresos(int, int);
//float calcularEgresos(int, int);
float calcularEgresos(Fecha fecha);
//float calcularGastoFijo(int, int);
float calcularGastoFijo(Fecha Fecha);
//bool validarMontoAhorro(float, int, int);
bool validarMontoAhorro(float montoAhorro, Fecha fecha);
int existeRegistro(int anio, int mes);
void definirAhorroMes();
bool modificarAhorroMes();
float consultarAhorroDefinido();
void mostrarArchivoAhorro();
float buscarAhorroPorMesAnio(int, int);
float calcularSaldoDisponibleMesActual();
float calcularSaldoDisponibleMesPuntual(int, int);
float calcularPromedioDiarioSaldo();
void quieroAhorrarPara();
//bool logroMetaAhorro(int, int);
bool logroMetaAhorro(Fecha fecha);

//---------INFORMES----------
void totalIngresosPorMes(int anio);
void totalEgresosPorMes(int anio);
void totalIngresosPorAnio(int anio);
void totalEgresosPorAnio(int anio);
int calcularCantidadMovimientosAnio(int anio);
void ponerMatrizEnCero(int **matrizCategMensual, int filas, int columnas);
void ponerVectorEnCero(float *arrayAnual, int cant);
void cargarMatrizCategMensual(int **matrizCategMensual);
void mostrarMatriz(int **matrizCategMensual, int filas, int columnas);
void mostrarMatrizPartida(int **matrizCategMensual, int filas, int columnas);
void totalGastoCategMatriz();
void cargarImportesEnVector(float *arrayAnual, int anio);
void totalGastoCategoriaAnual(int anio);
float sumarAcumuladoCategoriaPeriodo(int codCateg,int opc, Fecha fecha);
float calcularConsumosCategorias(int codCateg, int opc, Fecha fechaActual, Fecha fecha2);
void compararAhorroCategoriaPeriodos();
void totalAhorroMensual();
void totalAhorroAnual();

int menuInformes();

//-------CONFIGURACION-------
int menuConfiguracion();
bool bkpMovimientos();
bool bkpMovimientosServicios();
bool bkpCategorias();
bool bkpAhorro();
bool bkpNombresServicios();
bool bkpCompletoSistema();
bool restaurarBkpMovimientos();
bool restaurarBkpMovimientosServicios();
bool restaurarBkpCategorias();
bool restaurarBkpAhorros();
bool restaurarBkpNombreServicios();
bool restaurarCompletoSistema();
bool datosInicioMovimientos();
bool datosInicioMovimientosServicios();
bool datosInicioCategorias();
bool datosInicioAhorros();
bool datosInicioNombreServicios();
bool generarArchivoDatosInicio();
bool cargarDatosInicioMovimientos();
bool cargarDatosInicioMovimientosServicios();
bool cargarDatosInicioCategorias();
bool cargarDatosInicioAhorros();
bool cargarDatosInicioNombreServicios();
bool cargarDatosDeInicio();

//FUNCIONES
//a la funcion cargar cadena la mejore usando toUpper(case)
void cargarCadena(char *palabra, int tamano){
    int i=0;
    fflush(stdin);
    for (i=0; i<tamano; i++){
        palabra[i]=toupper(cin.get());
        if (palabra[i]=='\n'){
            break;
        }
    }

    palabra[i]='\0';
    fflush(stdin);
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

// COLOCA CURSOR EN DET. LUGAR
void gotoxy(short x, short y){
    COORD a;
    a.X = x;
    a.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),a);
}

HWND WINAPI GetConsoleWindowNT(void){
  typedef HWND WINAPI(*GetConsoleWindowT)(void);
  GetConsoleWindowT GetConsoleWindow;
  HMODULE hk32Lib = GetModuleHandle(TEXT("KERNEL32.DLL"));
  GetConsoleWindow = (GetConsoleWindowT)GetProcAddress(hk32Lib,TEXT("GetConsoleWindow"));

  if(GetConsoleWindow == NULL){
      return NULL;
  }

  return GetConsoleWindow();
}

//FIN FUNCIONES

#endif // PROTOTIPOS_H_INCLUDED
