#include <stdio.h>
#include <stdlib.h>
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
/*
Ejercicio 1.3 
    ¿Cuál es el valor de a y b luego de ejecutar el programa?
*/
void myFunc(int* a, int b){
    (*a)++;
    b++;
}

void main3(){
    int a = 10;
    int b = 10;
    myFunc(&a, b); 

    //printf("%d - %d\n",a,b);
}

/*
Ejercicio 1.4 
    ¿Que valor se imprime por consola luego de cada llamado a printf?
*/
void main4(){
    int x = 10;
    int* px = &x;
    printf("%d \n", px);  
    printf("%d \n", (*px));  //10
    (*px)++;
    printf("%d \n", px);
    printf("%d \n", (*px)); //11
}

/*
Ejercicio 1.5 
    Implementar las siguientes funciones en C
*/
void crearArreglo(int v){
    int array[8];
    for (size_t i = 0; i < 8; i++){
        array[i]=v;
        printf("%d - ",array[i]);
    }
}

int* crearArregloDin(int n, int v){
    int *array=(int *)malloc(sizeof(int)*n);
    for (size_t i = 0; i < n; i++){
        array[i]=v;
    }
    return array;
}
void mostrarMemoria(int* arr, int size){
    for(int i=0; i<size; i++){
        printf("Elemento: %d, Direccion: %d\n", i, &arr[i]);
    }
}

void main5(){
    crearArreglo(5);
    int* ar=crearArregloDin(5,4);
    mostrarMemoria(ar,5);
    free(ar);
}

/*
Ejercicio 1.6 
    Cuál es la diferencia entre malloc y calloc? Cuando utilizamos la
    función free?

    malloc inicializa con cualquier numero, calloc con cero.
    free se utiliza cada vez que pedimos memoria, para liberarla
*/

/*
Ejercicio 1.7 
    Dado el siguiente struct que representa una Persona
*/
typedef struct Persona{
    int edad;
    char* nombre;
} Persona;

Persona* inicializarPersonas1(int n){
    Persona* as= (Persona*)malloc(sizeof(Persona)*n);
    return as;
}
Persona* inicializarPersonas2(int n){
    Persona* as= (Persona*)calloc(n,sizeof(Persona));
    return as;
}

void main7(){
    Persona* as1=inicializarPersonas1(5);
    Persona* as2=inicializarPersonas2(5);
    free(as1);
    free(as2);
}

/*
Ejercicio 1.8 
    Programar las siguientes funciones en C
*/
int maximo(int* arr, int size){
    int max=arr[0];
    for (size_t i = 1; i < size; i++){
        if(max<arr[i]){
            max=arr[i];
        }
    }
    return max;
}

void sumador(int* arr, int size, int c){
    for (size_t i = 0; i < size; i++){
        arr[i]+=c;
    }
}

int* reverso(int* arr, int size){
    int temp;
    for (size_t i = 0; i < size/2; i++){
        temp=arr[i];
        arr[i]=arr[size-i-1];
        arr[size-i-1]=temp;
    }
}

bool estaOrdenado(int* arr, int size){
    int s=0;
    if(arr[0]<arr[1]){
        s=1;
    } else{
        s=2;
    }
    switch (s){
        case 1:
            for (size_t i = 1; i < size; i++){
                if(arr[i-1]>arr[i]){
                    return false;
                }
            }
            break;

        default:
            for (size_t i = 1; i < size; i++){
                if(arr[i-1]<arr[i]){
                    return false;
                }
            }
            break;
    }
    return true;
}

 bool esPalindromo(char* s){
    for (size_t i = 0; i < sizeof(s)/2; i++){
        if(s[i]!=s[sizeof(s)-i-1]){
            return false;
        }
    }
    return true;
 }

void main8(){

}

/*
Ejercicio 1.9
    Programar las siguientes funciones en C

    Ordenar2 tarda menos.
*/
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
  
void ordenar1(int* arr, int size){
    int i, j, min_idx;
  
    for (i = 0; i < size-1; i++){
        min_idx = i;
        for (j = i+1; j < size; j++){
            if (arr[j] < arr[min_idx]){
                min_idx = j;
                if(min_idx != i){
                    swap(&arr[min_idx], &arr[i]);
                }
            }
        }
    }
}

void ordenar2(int *arr, int size){
    if(arr==NULL){return;}
    int i, j;
    for (i = 0; i+1 <size; i++){
        for (j = 0; j+i+1<size; j++){
            if (arr[j] > arr[j + 1]){
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
    return;
}

void main9(){
    //ordenar1(a,b);
    //ordenar2(a,b);
}

/*
Ejercicio 1.10 
    Programar las siguientes funciones en C
*/


/*
Ejercicio 1.11
    Que hace este programa?

    int i = 0;
    while( i < n-1 ){                    funciona hasta llegar al anteultimo
        int j = 0;                       
        while( j < n-1 ){                funciona hasta llegar al anteultimo
            if( a[j] > a[j+1] ){         cheque que sea menor el numero posterior
                swap(a, j, j+1);         cambia de lugar
                j++;
            }
        }
        i++;
    }

    peor caso (n-1)^2
*/

/*
Ejercicio 1.12
    Programar las siguientes funciones en C
*/
bool twoSum1(int* arr, int size, int target){
    for (size_t i = 0; i < size; i++){
        for (size_t j = i+1; j < size; j++){
            if(arr[j]+arr[i]==target){
                return true;
            }
        }
    }
    return false;
}
bool twoSum2(int* arr, int size, int target){
    for (size_t i = 0; i < size; i++){
        for (size_t j = i+1; j < size; j++){
            if(arr[j]+arr[i]==target){
                return true;
            }
        }
    }
    return false;
}



int main(){
    // is_prime(4); //1.1
    // odds_sum(7); //1.2
    // main3(); //1.3
    // main4(); //1.4
    // main5(); //1.5

    // main7(); //1.7
    // main8(); //1.8
    // main9(); //1.9
    



    return 0;
}