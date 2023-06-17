"""
MODELO FINAL 

1)v o f
    -F
    -F (que sea criptografica no tiene nada que ver con la distribucion de las colisiones)
    -a veces (ejemplo de funcion de hashing de input string, que devuelve un numero)
    -V si a!=0 (cumple las 3 condiciones de hashing(deterministica, pocas colisones y eficiente))

2)
    pos Flag clave   
    0       Amarillo
    1       Blanco
    2  /B/  /Azul/  Naranja
    3       Verde

    #rojo falla
    Encontrar bkanco en 4 pasos
    Violeta en 4 pasos

3)
    Dijkstra
        dis ant
    1   0       #tacho    
    2   9    3  #tacho    
    3   7    4  #tacho
    4   3    1  #tacho

    1-4-3-2

4)
#hacer un bfs 
    def path_exists(a,b,max_dist):
        d=0
        nodes=[]
        nodes.append((a,d))
        visitados= set()
        visitados.add(a)
        while len(nodes)>0:
            d+=1
            n,d2=nodes.pop(0)
            if d2==max_dist return False
            vecinos=n.neighbots()
            for v,d2 in vecinos:
                if v==b and d2<=max_dist-1:
                    return True
                else:
                    if v not in visitados:
                        visitados.add(v)
                        nodes.append(v,d+1)
        return False
5)
    memo={}
    def robotways(dist):
        if dist<0:
            return 0
        if dist==1 or dist==0:
            return 1
        if dist in memo:
            return memo[dist]
        memo[dist]=robotways(dist-1)+robotways(dist-2)+robotways(dist-3)
        return memo[dist]


    print(robotways(3))

    #hay alternativa con table

    def robot2(dist):
        

6)

7)
8)
9)
10)

"""