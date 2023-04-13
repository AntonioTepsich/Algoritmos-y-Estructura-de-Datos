/*
COLAS DE PRIORIDAD
    bool insert(elem,pri)   O(log(n))
    elem get_max()          O(1)
    elem remove_max()       O(log(n))
    bool build(elem[],n)    O(n)


    ARBOLES BINARIOS
        Padre(i)=[(i-1)/2]
        Hijo1(i)=i+3
        Hijo2(i)=i+4
        Cantidad max de nodos para altura h = 2^(h+1)-1
        Cantidad min de nodos para altura h = 2^(h)

    HEAPS
        Es un arbol binario completo a izquierda que cumple la propiedad de heap.
        Y la propiedad de heap el padre siempre es mayor que su hijo.

    TOURNAMENT TREES
        Es un arbol binario completo
        Los elementos estan en las hojas
        los nodos no-hoja replican elementos
        cumple la propiedad de heap
        la cantidad de elementos es potencia de 2

        OBS: es muy facil hacer el meld de 2 TTs con igual cantidad de elementos

    TOURNAMENT HEAP
        Es un conjunto de Tournament Trees
        No puede haber mas de un TT de igual altura

        bool insert(elem,pri)   O(log(n))
        elem get_max()          O(log(n))
        elem remove_max()       O(log(n))
        meld(pq1,pq2)           O(log(n))

    TEOREMA
        En una cola de prioridad => insert o remove_max tiene que ser al menos O(log(n))
        No puedo mejorar insert Y remove_max
        Pero puedo intentar mejorar uno de ellos

        Mejoramos Insert
            LAZY TOURNAMENT HEAPS
                insert:         O(1)
                get_max()       O(n)
                remove_max()    O(n)
                meld(pq1,pq2)   O(log(n))

                Idea: Al insertar, no hacer nada

                En REMOVE_MAX: luego de sacar el max hecemos los "melds" necesarios.

    Abdication Heaps
        mejor manera de decrementar el max.



*/