Antonio Tepsich

# SOLUCIONES
Todos los ejercicios se pueden ejecutar al final de cada archivo, donde en la funcion main van a poder encontrar cada punto.

## Punto 1
Para resolver este problema utilice el algoritmo BFS.
- El grafo tiene 34634 componentes conexas
- La segunda componente conexa más grande es de 69 elementos
- Y la mas chica de todas es de 2 elementos

## Punto 2
Para resolver este problema utilice el algoritmo BFS.
- En el ejemplo de prueba tome a dos actores como "nm0000158" que es Robert De Niro y "nm0004730" es Michael Fassbender, nos da una distancia de 2 peliculas ['Philadelphia', 'The Equalizer 2'].

## Punto 3
- El mayor grado de separacion con Kevin Bacon es de 14 y son los actores con el codigo ['nm8311374', 'nm8094369', 'nm8311372', 'nm1961230', 'nm8311375', 'nm8311370', 'nm8179203', 'nm8311371', 'nm8311373']

## Punto 4
Para resolver este problema utilice el algoritmo Dijkstra.
Ejemplos de distancias con Kevin Bacon
- Distancia de Kevin Bacon a Kevin Bacon: 0
- Distancia de Kevin Bacon a Tom Cruise: 2
- Distancia de Kevin Bacon a Meryl Streep: 1
- Distancia de Kevin Bacon a Robert De Niro: 1
- Distancia de Kevin Bacon a Leonardo DiCaprio: 0
- Distancia de Kevin Bacon a Johnny Depp: 1

## Punto 5
- Para este caso utilizamos tqmd para calcular el tiempo aproximado en terminar, el cual me dio de 784 horas y 35 minutos, aproximadamente son 32 dias en terminar. Otra alternativa puede ser calcular el numero de vertices * data_size/velocidad de procesamiento.

## Punto 6
Para resolver este problema utilice el algoritmo BFS.
- No logre conseguir un resultado menor a los 41 dias aproximadamente para encontrar una solucion.
- Como bien pasa en el ejercicio siguiente para estimar el diametro del grafo, el resultado me diara infinito. La razon puede ser que tome un subgrafo del componente conexo principal y este puede ser no conexo, dando como resultado infinito.

## Punto 7
- Lo que hice al saber que no voy a poder terminar de ejecutar el codigo por cuestiones de tiempo, selecciono 100 elementos al azar y del cual voy a sacar el promedio general de separacion. El resultado me dio infinito. La razon puede ser que tome un subgrafo del componente conexo principal y este puede ser no conexo, dando como resultado infinito.

## Punto 8
- Actores con mayor centralidad: ['nm0456577', 'nm0335663', 'nm5442085', 'nm8895975', 'nm8629008']
- Películas con mayor centralidad: ['tt4958596', 'tt2749114', 'tt25994570', 'tt26629864', 'tt2070749']


## Punto 9
- No pude conseguir un resultado en un tiempo razonable que no sea superior a los 20 dias.

## Punto 10
Resultado de los 9 actores con menor coeficiente de clustering.
- Actor: nm0021201, Clustering Coefficient: 0.0
- Actor: nm0408925, Clustering Coefficient: 0.0
- Actor: nm7648264, Clustering Coefficient: 0.0
- Actor: nm6758812, Clustering Coefficient: 0.0
- Actor: nm11804552, Clustering Coefficient: 0.0
- Actor: nm11542788, Clustering Coefficient: 0.0
- Actor: nm8987658, Clustering Coefficient: 0.0
- Actor: nm0000616, Clustering Coefficient: 0.01395963268181244
- Actor: nm0001424, Clustering Coefficient: 0.023670903375700422
- Actor: nm0261724, Clustering Coefficient: 0.024018958107402497