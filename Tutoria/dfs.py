
#la uso para ver si el nodo ya fue visitado. veo cual de los nodos no se visito y analiso esos con bfs devuelta
def bfs(origen):
    visited = set()
    # visitados = [False]*n
    q = deque()
    q.enqueue(origen)
    visited.add(origen)
    while not q.empty():
        actual = q.dequeue()
        for v in actual.neighbors():
            if not visited[v]:
                visited.add(v)
                q.enqueue(v)

#sudoku
def dfs(origen):
    visited = set()
    # visitados = [False]*n
    q = stack()
    q.push(origen)
    visited.add(origen)
    while not q.empty():
        actual = q.pop()
        for v in actual.neighbors():
            if not visited[v]:
                visited.add(v)
                q.push(v)

def dijkstra(graph,origen):
    visited = set()
    dist={v:maxint for v in graph}
    prev={}
    heap=Heap()
    dist[origen]=0
    for v in graph:
        heap.insert(v, dist[v])
    while not heap.empty():
        actual=heap.pop()[0]
        visited.add(actual)
        for n in actual.neighbors():
            if n in heap:
                new_dist=dist[actual]+actual.get_edge_data(n)
                if new_dist<dist[n]:
                    dist[n]=new_dist
                    prev[n]=actual
                    heap.add(n, new_dist)

# tqdm con NO USAR floywarshall para caminos minimos
