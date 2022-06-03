#ifndef FUNCIONESGLOBALES_H_INCLUDED
#define FUNCIONESGLOBALES_H_INCLUDED

#include <string.h>

using namespace std;

//PROTOTIPOS

void cargarCadena(char *palabra, int tamano);
void backupYRestore(bool resultado);

//FIN PROTOTIPOS


//FUNCIONES GLOBALES
void cargarCadena(char *palabra, int tamano){
    int i=0;
    int j=0;
    fflush(stdin);
    for (i=0; i<tamano; i++){
        palabra[i]=cin.get();
        palabra[i]=toupper(palabra[i]);
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

void backupYRestore(bool resultado){
    if (resultado){
        cout<<"Operacion exitosa!"<<endl;
    }
    else{
        cout<<"No se pudo realizar la operacion."<<endl;
    }
}

//FIN FUNCIONES GLOBALES


#endif // FUNCIONESGLOBALES_H_INCLUDED
