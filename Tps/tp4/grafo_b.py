from graph import Graph
import csv
from itertools import combinations

from collections import deque
from tqdm import tqdm
import random

MOVIE_TITLE_TYPE = "movie"
MOVIE_COLUMNS = ["tconst", "titleType", "primaryTitle"]
PRINCIPALS_COLUMNS = ["nconst", "category"]
MOVIES_DATA_PATH = "./datasets/title-basics-f.tsv"
ACTORS_DATA_PATH = "./datasets/title-principals-f.tsv"
ACTORS_NAMES_PATH = "./datasets/name-basics-f.tsv"

PELI="pelicula"
ACTOR="actor"

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
        graph.add_vertex(movie_id, [movie_title, PELI])
        for actor in actors_by_movie[movie_id]:
            if not graph.vertex_exists(actor):
                graph.add_vertex(actor, [actor_names_by_id.get(actor, "ERROR"),ACTOR])
            graph.add_edge(vertex1=actor, vertex2=movie_id, data=movie_title)
    return graph



movies_by_id, actors_by_movie, actor_names_by_id = read_data(MOVIES_DATA_PATH, ACTORS_DATA_PATH, ACTORS_NAMES_PATH)
graph = load_graph(movies_by_id, actors_by_movie, actor_names_by_id)
# graph.print_graph()



def grado_de_separacion(graph, actor1, actor2):
    if not graph.vertex_exists(actor1) or not graph.vertex_exists(actor2):
        return []

    if actor1 == actor2:
        return []

    visited = set()
    queue = deque()
    queue.append((actor1, set()))

    while queue:
        actor, movies = queue.popleft()
        visited.add(actor)

        if actor == actor2:
            return list(movies)

        neighbors = graph.get_neighbors(actor)
        for neighbor in neighbors:
            if neighbor not in visited:
                movie = graph.get_edge_data(actor, neighbor)
                movies_with_neighbor = movies.copy()
                movies_with_neighbor.add(movie)
                queue.append((neighbor, movies_with_neighbor))

    # Actors are not connected
    return []

def punto2():
    # actor1 = "nm0000138"  # Tom Hanks
    # actor2 = "nm0000158"  # Robert De Niro
    actor1 = "nm0000102" # Kevin Bacon
    actor2 = "nm0004730" # Michael Fassbender 
    
    distancia = grado_de_separacion(graph, actor1, actor2)
    print("Distancia entre", actor1, "y", actor2, ":", len(distancia))

# punto2()

def mayor_grado_separacion_componente_conexa(grafo, kevin_bacon):
    if not grafo.vertex_exists(kevin_bacon):
        return None  # Kevin Bacon no existe en el grafo
    
    visitados = set()
    cola = deque([(kevin_bacon, 0)])  # Cola de tuplas (actor, distancia)
    mayor_grado_separacion = 0
    
    while cola:
        actual, distancia = cola.popleft()
        
        if distancia > mayor_grado_separacion:
            mayor_grado_separacion = distancia
        
        if actual not in visitados:
            visitados.add(actual)
            adyacentes = grafo.get_neighbors(actual)
            
            for adyacente in adyacentes:
                cola.append((adyacente, distancia + 1))
    
    return mayor_grado_separacion

def punto3():
    actor="nm0000102" # Kevin Bacon
    mayor_grado_separacion = mayor_grado_separacion_componente_conexa(graph, actor)
    print("Mayor grado de separación de la componente conexa de", actor, ":", mayor_grado_separacion)

# punto3()

#REVISAR
def random_walks(graph, num_walks, walk_length):
    vertex_counts = {vertex: 0 for vertex, data in graph._graph.items()}

    for _ in tqdm(range(num_walks)):
        current_vertex = random.choice(list(graph._graph.keys()))

        for _ in range(walk_length):
            neighbors = graph.get_neighbors(current_vertex)
            if not neighbors:
                break
            current_vertex = random.choice(neighbors)
            vertex_counts[current_vertex] += 1

    return vertex_counts

def punto8():
    num_walks = 500
    walk_length = 10

    vertex_counts = random_walks(graph, num_walks, walk_length)

    # Ordenar los vértices por su centralidad en orden descendente
    sorted_vertices = sorted(vertex_counts.items(), key=lambda x: x[1], reverse=True)

    # Imprimir los vértices con mayor centralidad
    for vertex, count in sorted_vertices:
        print("Vértice:", vertex, "Centralidad:", count)

# punto8()