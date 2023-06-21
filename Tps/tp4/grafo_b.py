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

    return []

def punto2():
    # actor1 = "nm0000138"  # Tom Hanks
    # actor2 = "nm0000102" # Kevin Bacon
    actor1 = "nm0000158"  # Robert De Niro
    actor2 = "nm0004730" # Michael Fassbender 
    
    distancia = grado_de_separacion(graph, actor1, actor2)
    print(distancia)
    print("Distancia entre", actor1, "y", actor2, ":", len(distancia))


def mayor_grado_separacion_componente_conexa(grafo, kevin_bacon):
    if not grafo.vertex_exists(kevin_bacon):
        return None  
    
    visitados = set()
    cola = deque([(kevin_bacon, 0)])  # Cola de tuplas (actor, distancia)
    mayor_grado_separacion = 0
    while cola:
        actual, distancia = cola.popleft()
        
        if distancia >= mayor_grado_separacion:
                mayor_grado_separacion = int(distancia/2) #Divido por 2 porque la distancia es entre actores y no peliculas
                actor_mayor_separacion=grafo.get_neighbors(actual)


        if actual not in visitados:
            visitados.add(actual)
            adyacentes = grafo.get_neighbors(actual)
            for adyacente in adyacentes:
                cola.append((adyacente, distancia+1))
    
    return actor_mayor_separacion,mayor_grado_separacion

def punto3():
    actor="nm0000102" # Kevin Bacon
    lista,mayor_grado_separacion = mayor_grado_separacion_componente_conexa(graph, actor)
    print("Mayor grado de separación de la componente conexa de", actor, ":", mayor_grado_separacion)
    print("Actor con mayor grado de separación de la componente conexa de", actor, ":", lista)

#REVISAR
def random_walk_centrality(graph, num_walks, num_steps):
    actor_counts = {}
    movie_counts = {}

    for _ in tqdm(range(num_walks)):
        current_vertex = random.choice(list(graph._graph.keys()))

        for _ in range(num_steps):
            neighbors = graph.get_neighbors(current_vertex)
            if neighbors:
                current_vertex = random.choice(neighbors)
            else:
                break

            if graph.vertex_exists(current_vertex):
                pal=str(current_vertex)
                if pal[0]=='n':
                    actor_counts[current_vertex] = actor_counts.get(current_vertex, 0) + 1
                elif pal[0]=='t':
                    movie_counts[current_vertex] = movie_counts.get(current_vertex, 0) + 1

    actor_centrality = {actor: count / (num_walks * num_steps) for actor, count in actor_counts.items()}
    movie_centrality = {movie: count / (num_walks * num_steps) for movie, count in movie_counts.items()}

    top_actors = sorted(actor_centrality, key=actor_centrality.get, reverse=True)[:5]
    top_movies = sorted(movie_centrality, key=movie_centrality.get, reverse=True)[:5]

    return top_actors, top_movies

def punto8():
    num_walks = 500
    walk_length = 10

    top_actors, top_movies = random_walk_centrality(graph, num_walks, walk_length)

    print("Actores con mayor centralidad:", top_actors)
    print("Películas con mayor centralidad:", top_movies)


def main():
    # graph.print_graph()
    punto2()
    # punto3()
    # punto8()

main()