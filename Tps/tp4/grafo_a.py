from graph import Graph
import csv
from itertools import combinations

from collections import deque
import heapq

import time
from tqdm import tqdm


MOVIE_TITLE_TYPE = "movie"
MOVIE_COLUMNS = ["tconst", "titleType", "primaryTitle"]
PRINCIPALS_COLUMNS = ["nconst", "category"]
MOVIES_DATA_PATH = "./datasets/title-basics-f.tsv"
ACTORS_DATA_PATH = "./datasets/title-principals-f.tsv"
ACTORS_NAMES_PATH = "./datasets/name-basics-f.tsv"


def read_data(movies_file, actors_file, actors_name_file):
    print("Reading data")
    movies_by_id = {}
    with open(movies_file, "r", newline="", encoding="utf-8") as file1:
        reader = csv.DictReader(file1, delimiter="\t")
        for row in reader:
            if row["titleType"] == MOVIE_TITLE_TYPE:
                movies_by_id[row['tconst']] = row

    actors_ids = set()
    actors_by_movie = {m: set() for m in movies_by_id.keys()}
    with open(actors_file, "r", newline="", encoding="utf-8") as file2:
        reader = csv.DictReader(file2, delimiter="\t")
        for row in reader:
            if row["tconst"] in actors_by_movie:
                actors_by_movie[row["tconst"]].update([row["nconst"]])
                actors_ids.update([row["nconst"]])

    actor_names_by_id = {}
    with open(actors_name_file, "r", newline="", encoding="utf-8") as file2:
        reader = csv.DictReader(file2, delimiter="\t")
        for row in reader:
            if row["nconst"] in actors_ids:
                actor_names_by_id[row["nconst"]] = row["primaryName"]

    return movies_by_id, actors_by_movie, actor_names_by_id


def load_graph(movies_by_id, actors_by_movie, actor_names_by_id) -> Graph:
    """
    Loads the graph
    :param movies_by_id: the movies data by id as dict
    :param actors_by_movie: the actors data by movie
    :param actor_names_by_id: the actors names by their ids
    :return: a Graph
    """
    graph = Graph()
    print("Loading graph")

    for movie_id in movies_by_id.keys():
        movie_title = movies_by_id[movie_id]['primaryTitle']
        for actor1, actor2 in combinations(actors_by_movie[movie_id], 2):
            if not graph.vertex_exists(actor1):
                graph.add_vertex(actor1, actor_names_by_id.get(actor1, "ERROR"))
            if not graph.vertex_exists(actor2):
                graph.add_vertex(actor2, actor_names_by_id.get(actor2, "ERROR"))
            existing_data = set()
            if graph.edge_exists(actor1, actor2):
                existing_data = graph.get_edge_data(actor1, actor2)
            graph.add_edge(vertex1=actor1, vertex2=actor2,data={movie_title} | existing_data)
    return graph



# Define the paths to the datasets

movies_by_id, actors_by_movie, actor_names_by_id = read_data(MOVIES_DATA_PATH, ACTORS_DATA_PATH, ACTORS_NAMES_PATH)
graph = load_graph(movies_by_id, actors_by_movie, actor_names_by_id)
# graph.print_graph()

def bfs_componentes_conexas(grafo):
    visitados = set()
    componentes_conexas = []

    #iterar en todos los vertices
    for vertice, data in grafo._graph.items():
        if vertice not in visitados:
            componente = []
            cola = deque([vertice])

            while cola:
                actual = cola.popleft()

                if actual not in visitados:
                    visitados.add(actual)
                    componente.append(actual)
                    cola.extend(grafo.get_neighbors(actual))
            componentes_conexas.append(componente)
    return componentes_conexas

def punto1():
    componentes_conexas=bfs_componentes_conexas(graph)
    cantidad_componentes_conexas=len(componentes_conexas)
    print("Cantidad de componentes conexas: ",cantidad_componentes_conexas)

    # Ordenar componentes de mayor a menor tamaño
    componentes_ordenadas = sorted(componentes_conexas, key=len, reverse=True)

    # Segunda componente conexa más grande
    segunda_componente_grande = componentes_ordenadas[1] if len(componentes_ordenadas) >= 2 else []
    print("Segunda componente conexa más grande:", len(segunda_componente_grande))

    # Componente más pequeña
    componente_mas_pequena = min(componentes_conexas, key=len) if componentes_conexas else []
    print("Componente más pequeña:", len(componente_mas_pequena))

# punto1()

def dijkstra(grafo, artista_inicial):
    if not grafo.vertex_exists(artista_inicial):
        return None, None  # El artista inicial no existe en el grafo
    
    distancias = {artista: float('inf') for artista, data in grafo._graph.items()}
    distancias[artista_inicial] = 0
    
    padres = {}
    
    visitados = set()
    
    cola_prioridad = [(0, artista_inicial)]
    heapq.heapify(cola_prioridad)
    
    while cola_prioridad:
        distancia_actual, artista_actual = heapq.heappop(cola_prioridad)
        
        if artista_actual in visitados:
            continue
        
        visitados.add(artista_actual)
        
        adyacentes = grafo.get_neighbors(artista_actual)
        
        for artista_adyacente in adyacentes:
            t = grafo.edge_exists(artista_actual, artista_adyacente)
            distancia_adyacente = 0
            if t:
                distancia_adyacente = 1
            distancia_total = distancia_actual + distancia_adyacente
            
            if distancia_total < distancias[artista_adyacente]:
                distancias[artista_adyacente] = distancia_total
                padres[artista_adyacente] = artista_actual
                heapq.heappush(cola_prioridad, (distancia_total, artista_adyacente))
    
    return distancias, padres

def calcular_camino_minimo(graph, actor1, actor2):
    if not graph.vertex_exists(actor1) or not graph.vertex_exists(actor2):
        return None

    if actor1 == actor2:
        return []

    visited = set()
    distances = {vertex: float('inf') for vertex in graph.get_vertices()}
    distances[actor1] = 0
    previous = {vertex: None for vertex in graph.get_vertices()}

    queue = [(0, actor1)]

    while queue:
        current_distance, current_vertex = heapq.heappop(queue)

        if current_vertex == actor2:
            # Reconstruir el camino mínimo
            path = []
            while current_vertex is not None:
                path.append(current_vertex)
                current_vertex = previous[current_vertex]
            return list(reversed(path))

        if current_vertex in visited:
            continue

        visited.add(current_vertex)

        neighbors = graph.get_neighbors(current_vertex)
        for neighbor in neighbors:
            edge_data = graph.get_edge_data(current_vertex, neighbor)
            weight = len(edge_data)
            distance = current_distance + weight

            if distance < distances[neighbor]:
                distances[neighbor] = distance
                previous[neighbor] = current_vertex
                heapq.heappush(queue, (distance, neighbor))

    # No se encontró un camino entre los artistas
    return None

#Puede estar mal
def punto4():
    distancias, padres = dijkstra(graph, "nm0000138") # Kevin Bacon
    print("Distancia de Kevin Bacon a Kevin Bacon:", distancias["nm0000138"]) # Kevin Bacon
    print("Distancia de Kevin Bacon a Tom Cruise:", distancias["nm0000129"]) # Tom Cruise
    print("Distancia de Kevin Bacon a Meryl Streep:", distancias["nm0000658"]) # Meryl Streep
    print("Distancia de Kevin Bacon a Robert De Niro:", distancias["nm0000134"]) # Robert De Niro
    print("Distancia de Kevin Bacon a Leonardo DiCaprio:", distancias["nm0000138"]) # Leonardo DiCaprio
    print("Distancia de Kevin Bacon a Johnny Depp:", distancias["nm0000136"]) # Johnny Depp

# punto4() 

def punto4Aux():
    resultado=calcular_camino_minimo(graph, "nm0000138", "nm0000129") # Kevin Bacon y Tom Cruise
    
    print("Camino mínimo entre Kevin Bacon y Tom Cruise:", resultado)
# punto4Aux() 

def shortest_path(graph, start):
    distances = {vertex: float('inf') for vertex in graph.get_vertices()}
    distances[start] = 0

    queue = [(0, start)]

    while queue:
        current_distance, current_vertex = heapq.heappop(queue)

        if current_distance > distances[current_vertex]:
            continue

        neighbors = graph.get_neighbors(current_vertex)
        for neighbor in neighbors:
            weight = len(graph.get_edge_data(current_vertex, neighbor))
            distance = current_distance + weight

            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(queue, (distance, neighbor))

    return distances


def calculate_shortest_paths(graph):
    all_shortest_paths = {}

    start_time = time.time()

    # Inicializar el tqdm
    progress_bar = tqdm(total=len(graph.get_vertices()))

    for vertex in graph.get_vertices():
        shortest_paths = shortest_path(graph, vertex)
        all_shortest_paths[vertex] = shortest_paths

        # Actualizar el progreso
        progress_bar.update()

    # Cerrar el tqdm
    progress_bar.close()

    end_time = time.time()

    return all_shortest_paths, end_time - start_time

# REVISAR
def punto5():
    all_shortest_paths,time = calculate_shortest_paths(graph)
    print("Tiempo de ejecución:", time)
    actor1 = "nm0000138" # Kevin Bacon
    actor2 = "nm0000129" # Tom Cruise
    # print("Camino mínimo entre Kevin Bacon y Tom Cruise:", all_shortest_paths[actor1][actor2])
punto5()

# REVISAR
def estimate_diameter(graph, time_limit):
    diameter = 0

    # Realizar un BFS desde cada vértice para encontrar la distancia máxima
    # Utilizar un tiempo límite para interrumpir el proceso si se excede el límite
    for vertex in tqdm(graph._graph.keys()):  # Recorrer los vértices del grafo
        visited = set()
        distance = 0
        queue = deque([(vertex, distance)])

        start_time = time.time()  # Guardar el tiempo de inicio

        while queue and time.time() - start_time < time_limit:
            curr_vertex, curr_distance = queue.popleft()

            if curr_vertex not in visited:
                visited.add(curr_vertex)
                distance = curr_distance

                # Agregar los vecinos no visitados a la cola
                neighbors = graph.get_neighbors(curr_vertex)
                for neighbor in neighbors:
                    if neighbor not in visited:
                        queue.append((neighbor, curr_distance + 1))

        diameter = max(diameter, distance)

    return diameter

def punto6():
    diameter = estimate_diameter(graph, 900)
    print("Diámetro estimado del grafo:", diameter)

# punto6()