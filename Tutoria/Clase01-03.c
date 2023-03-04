#include <stdio.h>

/*
Programacion en C:

    -Estructurado
    -Compilado de bajo nivel
    -Tipado estatico

    En vez de Objetos se usan Structs

    COMPILADO
        Como es estructurado en tiempo de compilacion se verifica que los tipos tengan sentido. 
        Haciendolo mucho mas robusto.
        Al estar a mas bajo nivel, C resulta mucho mas rapido.

    BAJO NIVEL
        Siempre que hablemos de binario o relacionado, es decir que estamos hablando mas cerca del hardware.

*/

int sumImpar(int n){
    int m=0;
    for(size_t i=1;i<n;i+=2){
        m+=i;
    }
    return m;
}

int main(){
    printf("%d\n",sumImpar(4));
    return 0;
}