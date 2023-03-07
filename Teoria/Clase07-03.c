#include <stdio.h>

/*
Vectores - Arrays - Arreglos
    Operaciones (Vector Estatico)                          #Estatico=no puede cambiar tamano
        * build(n) 
        * get_at_i(i)
        * set_at_i(i,x)
        * destroy()
        
        2 Implementaciones:

            1-Vectores usando vectores                        
                Metadatos:  Tamano del vector (n)
                            Tamano de cada elemento (l)
                            Punto al vector
                          0   1   2
                        |   |   |   |
                          l   l    l

                Algoritmos:
                    * build(n) => O(n)
                        malloc(n*l)  

                    * get_at_i(i) => O(1)
                        ptr+=i*(l)  

                    * set_at_i(i,x) => O(1)

            2-Vectores usando punteros(Listas)
                Metadatos:  Head
                        head => |   | => |   | => |NULL|

                Algoritmos:
                    * build(n) => O(n)

                    * get_at_i(i) => O(n)

                    * set_at_i(i,x) => O(n)


    Operaciones (Vector Dinamico)
        * build(n) 
        * get_at_i(i)
        * set_at_i(i,x)
        * destroy()
        * Insert_at_i(i,x)
        * Delete_at_i(i)
        * Insert_first()
        * Insert_last()
        * Delete_first(i)
        * Delete_last(i)
        
        
        2 Implementaciones:

            1-Vectores dinamicos usando vectores estaticos                        
                Metadatos:  Tamano del vector (n)
                            Tamano de cada elemento (l)
                            Punto al vector
                          0   1   2
                        |   |   |   |
                          l   l    l

                Algoritmos:
                    * build(n) => O(n)
                    * get_at_i(i) => O(1)
                    * set_at_i(i,x) => O(1)
                    * Insert_at_i(i,x) => O(n)
                    * Delete_at_i(i) => O(n)
                    * Insert_first() => O(n)
                    * Insert_last() => O(n)
                    * Delete_first(i) => O(n)
                    * Delete_last(i) => O(n)

            2-Vectores dinamicos usando punteros(Listas)
                Metadatos:  Head
                        head => |   | => |   | => |NULL|

                Algoritmos:
                    * build(n) => O(n)
                    * get_at_i(i) => O(n)
                    * set_at_i(i,x) => O(n)
                    * Insert_at_i(i,x) => O(n)
                    * Delete_at_i(i) => O(n)
                    * Insert_first() => O(1)
                    * Insert_last() => O(n)
                    * Delete_first(i) => O(1)
                    * Delete_last(i) => O(n)

            Otra vez Vectores dinamicos usando vectores estaticos...                        
            Insert_last() 
                0               1
                0 4             2
                0 4 18          3
                0 4 18 21       4
                                n

            costo de "n" operaciones Insert_last() => sum(i)=(n-1)n/2=O(n^2)
            el costo de todo es O(n^2)
            el costo de una es O(n^2/n) = O(n)

            IDEA
            En lugar de extender el vector de a 1 elemento
            dupliquemos su tamano cuando no podemos insertar
                0                       1
                0 4                     2
                0 4 18 -                4
                0 4 18 21               
                0 4 18 21 25 - - -      8
                                        n

            costo de "n" operaciones Insert_last() => sum(2^i)=2(n-1)=O(n)
            el costo de todo es O(n)
            el costo de una es O(n/n) = O(1)


            BACK TO PYTHON

                Listas: a=[3,4,"hola",18]
                    Las listas de python son vectores dinamicos de punteros a objetos
                    usa mas o menos la estrategia que dimos antes

*/