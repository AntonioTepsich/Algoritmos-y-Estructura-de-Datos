from graph import Graph
import csv
from itertools import combinations

from collections import deque
import heapq

import time
from tqdm import tqdm
import random


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

    segunda_componente_grande = componentes_ordenadas[1] if len(componentes_ordenadas) >= 2 else []
    print("Segunda componente conexa más grande:", len(segunda_componente_grande))

    componente_mas_pequena = min(componentes_conexas, key=len) if componentes_conexas else []
    print("Componente más pequeña:", len(componente_mas_pequena))


def dijkstra(grafo, artista_inicial):
    if not grafo.vertex_exists(artista_inicial):
        return None, None  # Si el artista inicial no existe en el grafo
    
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


def punto4():
    distancias, padres = dijkstra(graph, "nm0000138") # Kevin Bacon
    print("Distancia de Kevin Bacon a Kevin Bacon:", distancias["nm0000138"]) # Kevin Bacon
    print("Distancia de Kevin Bacon a Tom Cruise:", distancias["nm0000129"]) # Tom Cruise
    print("Distancia de Kevin Bacon a Meryl Streep:", distancias["nm0000658"]) # Meryl Streep
    print("Distancia de Kevin Bacon a Robert De Niro:", distancias["nm0000134"]) # Robert De Niro
    print("Distancia de Kevin Bacon a Leonardo DiCaprio:", distancias["nm0000138"]) # Leonardo DiCaprio
    print("Distancia de Kevin Bacon a Johnny Depp:", distancias["nm0000136"]) # Johnny Depp


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


    for vertex in tqdm(graph.get_vertices()):
        shortest_paths = shortest_path(graph, vertex)
        all_shortest_paths[vertex] = shortest_paths


    return all_shortest_paths

# REVISAR
def punto5():
    all_shortest_paths,time = calculate_shortest_paths(graph)
# # Si anduviera, debería mostrar el tiempo de ejecución y un ejemplo de llamado
    # print("Tiempo de ejecución:", time)
    # actor1 = "nm0000138" # Kevin Bacon
    # actor2 = "nm0000129" # Tom Cruise
    # print("Camino mínimo entre Kevin Bacon y Tom Cruise:", all_shortest_paths[actor1][actor2])


# REVISAR
def estimate_diameter(graph, time_limit):
    diameter = 0

    # Realiza un BFS desde cada vertice para encontrar la distancia maxima
    for vertex in tqdm(graph._graph.keys()): 
        visited = set()
        distance = 0
        queue = deque([(vertex, distance)])

        start_time = time.time() 

        while queue and time.time() - start_time < time_limit:
            curr_vertex, curr_distance = queue.popleft()

            if curr_vertex not in visited:
                visited.add(curr_vertex)
                distance = curr_distance

                # Agrega los vecinos no visitados a la cola
                neighbors = graph.get_neighbors(curr_vertex)
                for neighbor in neighbors:
                    if neighbor not in visited:
                        queue.append((neighbor, curr_distance + 1))

        diameter = max(diameter, distance)

    return diameter

def punto6():
    diameter = estimate_diameter(graph, 900)
    print("Diámetro estimado del grafo:", diameter)


def get_connected_component(graph):
    visited = set()
    component = []

    queue = deque()

    # Encuentra un vertice inicial para comenzar el recorrido BFS
    initial_vertex = next(iter(graph._graph.keys()))

    queue.append(initial_vertex)
    visited.add(initial_vertex)

    while queue:
        vertex = queue.popleft()
        component.append(vertex)

        neighbors = graph.get_neighbors(vertex)
        for neighbor in neighbors:
            if neighbor not in visited:
                queue.append(neighbor)
                visited.add(neighbor)

    return component


def bfs(graph, start):
    distances = {vertex: float('inf') for vertex in graph._graph.keys()}
    distances[start] = 0

    queue = deque()
    queue.append(start)

    while queue:
        current_vertex = queue.popleft()

        for neighbor in graph.get_neighbors(current_vertex):
            if distances[neighbor] == float('inf'):
                distances[neighbor] = distances[current_vertex] + 1
                queue.append(neighbor)

    return distances

def calculate_average_separations(graph, sample_size=100):
    component = get_connected_component(graph)
    actors = random.sample(component, sample_size)
    total_separations = 0

    for actor in tqdm(actors):
        shortest_paths = shortest_path(graph, actor)
        separations = sum(shortest_paths.values())
        total_separations += separations

    average_separations = total_separations / sample_size
    estimated_average_separations = average_separations * (len(component) / sample_size)

    return estimated_average_separations

def punto7():
    average_separations = calculate_average_separations(graph,100)
    print("Promedio general de separaciones:")
    print(average_separations)


def calculate_betweenness_centrality(graph):
    betweenness = {actor: 0 for actor in graph.get_vertices()}

    for actor in tqdm(graph.get_vertices()):
        visited = set()
        stack = deque()
        distance = {v: -1 for v in graph.get_vertices()}
        paths = {v: [] for v in graph.get_vertices()}
        sigma = {v: 0 for v in graph.get_vertices()}
        sigma[actor] = 1
        distance[actor] = 0
        queue = deque([actor])

        while queue:
            v = queue.popleft()
            stack.append(v)
            visited.add(v)

            for neighbor in graph.get_neighbors(v):
                if distance[neighbor] == -1:
                    queue.append(neighbor)
                    distance[neighbor] = distance[v] + 1

                if distance[neighbor] == distance[v] + 1:
                    sigma[neighbor] += sigma[v]
                    paths[neighbor].append(v)

        delta = {v: 0 for v in graph.get_vertices()}
        while stack:
            v = stack.pop()
            for neighbor in paths[v]:
                delta[neighbor] += (sigma[neighbor] / sigma[v]) * (1 + delta[v])
            if v != actor:
                betweenness[v] += delta[v]

    sorted_centrality = sorted(betweenness.items(), key=lambda x: x[1], reverse=True)
    return sorted_centrality

def punto9():
    betweenness = calculate_betweenness_centrality(graph)

    top_actors = betweenness[:10]  # los 10 actores principales
    for actor, centrality in top_actors:
        print(f"Actor: {actor}, Betweenness Centrality: {centrality}")


def calculate_clustering_coefficient(graph, actor):
    neighbors = graph.get_neighbors(actor)
    num_neighbors = len(neighbors)

    if num_neighbors < 2:
        return 0.0

    num_triangles = 0
    num_possible_triangles = (num_neighbors * (num_neighbors - 1)) / 2

    for i in range(num_neighbors - 1):
        for j in range(i + 1, num_neighbors):
            neighbor1 = neighbors[i]
            neighbor2 = neighbors[j]

            if graph.edge_exists(neighbor1, neighbor2):
                num_triangles += 1

    clustering_coefficient = (2 * num_triangles) / num_possible_triangles
    return clustering_coefficient

def find_actors_with_low_clustering_coefficient(graph, min_movies, max_clustering_coefficient):
    actors = [actor for actor in graph.get_vertices() if len(graph.get_neighbors(actor)) >= min_movies]
    low_clustering_actors = []

    for actor in tqdm(actors):
        clustering_coefficient = calculate_clustering_coefficient(graph, actor)
        if clustering_coefficient < max_clustering_coefficient:
            low_clustering_actors.append((actor, clustering_coefficient))

    low_clustering_actors = sorted(low_clustering_actors, key=lambda x: x[1], reverse=False)
    return low_clustering_actors

def punto10():
    actors_with_low_clustering = find_actors_with_low_clustering_coefficient(graph, min_movies=3, max_clustering_coefficient=0.5)

    # Imprimo los 50 actores con mayor numero de pelis y menor coeficiente de clustering
    c=0
    for actor, clustering_coefficient in actors_with_low_clustering:
        print(f"Actor: {actor}, Clustering Coefficient: {clustering_coefficient}")
        c+=1
        if c==50:
            break

def main():
    # graph.print_graph()
    punto1()
    # punto4()
    # punto5()
    # punto6()
    # punto7()
    # punto9()
    # punto10()

main()
