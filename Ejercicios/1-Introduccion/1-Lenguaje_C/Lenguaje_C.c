#include <stdio.h>
#include <stdbool.h>


/*
Ejercicio 1.1 
    Escribir la función que dado n P N devuelve si es primo. Recuerden que un
    número es primo si los únicos divisores que tiene son 1 y el mismo.
*/
bool is_prime(int x){
    for(size_t i=2;i<x;i++){
        if(x%i==0){
            return false;
        }
    }
    return true;
}

/*
Ejercicio 1.2 
    Escribir la función que dado n P N devuelve la suma de todos los números
    impares menores que n
*/
int odds_sum(int x){
    int sum=0;
    for(size_t i=1;i<x;i+=2){
        sum+=i;
    }
    return sum;
}



int main(){
    is_prime(4); //1.1
    odds_sum(7); //1.2



    return 0;
}