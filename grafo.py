# from typing import Dict, List
from math import inf


class Grafo:
    """
    Grafo estatico de tamanio n
    Implementado con matriz de adyacencias
    """

    def __init__(self, n: int):
        """
        n es el numero de aristas
        """
        self.matriz = [[inf for _ in range(n)] for _ in range(n)]
        for i in range(n):
            self.matriz[i][i] = 0

    def insertar_arista(self, origen, destino, peso):
        self.matriz[origen][destino] = peso

    def insertar_arista_no_dirigida(self, v1, v2, peso):
        self.insertar_arista(v1, v2, peso)
        self.insertar_arista(v2, v1, peso)

    def borrar_arista(self, origen, destino):
        self.insertar_arista(origen, destino, inf)

    def devuelve_distancia(self, origen, destino):
        return self.matriz[origen][destino]

    def obtener_adyacencias(self, o):
        return [i for i in range(len(self.matriz)) if self.matriz[o][i] != inf]

    def copy(self):
        m = []
        for fila in self.matriz:
            m.append(fila.copy())
        return m

    def __str__(self):
        cadena = ""
        for origen in range(len(self.matriz)):
            cadena += "[|"
            for destino in range(len(self.matriz)):
                cadena += str(self.matriz[origen][destino]) + "|"
            cadena += "]\n"
        return cadena


def floyd_warshall(grafo: Grafo):
    """
    Devuelve la matriz de distancias de un Grafo
    """
    if not grafo:
        return

    dist = grafo.copy()
    for x in range(len(dist)):
        for i in range(len(dist)):
            if x == i:
                continue
            for j in range(len(dist)):
                if j == i or j == x:
                    continue
                dist[i][j] = min(dist[i][j], dist[i][x] + dist[x][j])

    return dist


grafo = Grafo(4)
grafo.insertar_arista(0, 1, 2)
grafo.insertar_arista(0, 3, 2)
grafo.insertar_arista(1, 0, 7)
grafo.insertar_arista(1, 2, 9)
grafo.insertar_arista(1, 3, 2)
grafo.insertar_arista(2, 1, 1)
grafo.insertar_arista(3, 0, 8)
grafo.insertar_arista(3, 2, 3)
print(grafo)
print(floyd_warshall(grafo))


class GrafoHH:
    """
    Grafo implementado con diccionarios de vertices.
    diccionario de adyacencias.
    """

    def __init__(self, nombresVertices=[]):
        self.vertices = dict()
        for nombre in nombresVertices:
            self.vertices[nombre] = {}

    def insertar_arista(self, origen, destino, peso):
        self.vertices[origen] = self.vertices.get(origen, {})
        self.vertices[origen][destino] = peso

    def insertar_arista_no_dirigida(self, v1, v2, peso):
        self.vertices[v1] = self.vertices.get(v1, {})
        self.vertices[v2] = self.vertices.get(v2, {})
        self.vertices[v1][v2] = peso
        self.vertices[v2][v1] = peso

    def borrar_arista(self, origen, destino):
        self.insertar_arista(origen, destino, inf)

    def devuelve_distancia(self, origen: str, destino: str):
        vertice = self.vertices.get(origen, {})
        if destino in vertice:
            return vertice[destino]
        return inf

    def obtener_adyacencias(self, origen: str) -> list:
        vertice = self.vertices.get(origen, {})
        return list(vertice)

    def obtener_vertices(self) -> list:
        return list(self.vertices.keys())

    def __str__(self):
        return str(self.vertices)


def DFS(grafo: GrafoHH, origen, f):
    pila = [origen]
    visitados = {origen}

    while pila:
        vertice = pila.pop()
        f(vertice)
        for v in grafo.obtener_adyacencias(vertice):
            if v not in visitados:
                pila.append(v)
                visitados.add(v)


def BFS(grafo: GrafoHH, origen, f):
    cola = [origen]
    visitados = {origen}

    while cola:
        vertice = cola.pop(0)
        f(vertice)
        for v in grafo.obtener_adyacencias(vertice):
            if v not in visitados:
                cola.append(v)
                visitados.add(v)


def dijkstra(grafo: GrafoHH, origen) -> dict:
    if not grafo or not origen:
        return {}

    visitados = {origen}
    no_visitados = set(grafo.obtener_vertices())

    matriz = {vertice: [inf, None] for vertice in no_visitados}
    matriz[origen][0] = 0

    while no_visitados:
        actual = min(no_visitados, key=lambda k: matriz[k][0])
        d_actual = matriz[actual][0]
        for v in grafo.obtener_adyacencias(actual):
            d = grafo.devuelve_distancia(actual, v)
            if d + d_actual < matriz[v][0]:
                matriz[v][0] = d + d_actual
                matriz[v][1] = actual

        visitados.add(actual)
        no_visitados.remove(actual)

    return matriz


# graph = GrafoHH(["A", "B", "C", "D", "E", "F"])

# graph.insertar_arista_no_dirigida("A", "B", 5)
# graph.insertar_arista_no_dirigida("A", "D", 6)
# graph.insertar_arista_no_dirigida("B", "C", 9)
# graph.insertar_arista_no_dirigida("B", "D", 4)
# graph.insertar_arista_no_dirigida("C", "E", 1)
# graph.insertar_arista_no_dirigida("C", "F", 7)
# graph.insertar_arista_no_dirigida("D", "F", 2)
# graph.insertar_arista_no_dirigida("D", "E", 6)
# graph.insertar_arista_no_dirigida("F", "E", 3)

# print("DFS")
# DFS(grafo, "A", print)
# print("BFS")
# BFS(grafo, "A", print)


def prim(grafo: GrafoHH, origen) -> GrafoHH:
    """
    Devuelve spanning tree de grafo
    """
    visitados = {origen}
    no_visitados = set(grafo.vertices.keys())
    no_visitados.remove(origen)

    arbol_minimo = GrafoHH()

    while no_visitados:

        min = (inf, None, None)

        for visitado in visitados:
            adyacencias = grafo.obtener_adyacencias(visitado)
            for adyacente in adyacencias:
                d = grafo.devuelve_distancia(visitado, adyacente)
                if adyacente not in visitados:
                    if d < min[0]:
                        min = (d, visitado, adyacente)

        no_visitados.remove(min[2])
        visitados.add(min[2])
        arbol_minimo.insertar_arista_no_dirigida(min[1], min[2], min[0])

    return arbol_minimo


# def kruskal(graph: GrafoHH) -> GrafoHH:
#     """
#     returns minimum spanning tree of the graph
#     """
#     spanning_tree = GrafoHH()
#     lista = []
#     adyacencias  = graph.vertices.items()


# grafo_numeros = GrafoHH()
# grafo_numeros.insertar_arista_no_dirigida("1", "2", 1)
# grafo_numeros.insertar_arista_no_dirigida("1", "5", 7)
# grafo_numeros.insertar_arista_no_dirigida("2", "3", 6)
# grafo_numeros.insertar_arista_no_dirigida("2", "7", 8)
# grafo_numeros.insertar_arista_no_dirigida("3", "4", 21)
# grafo_numeros.insertar_arista_no_dirigida("3", "7", 2)
# grafo_numeros.insertar_arista_no_dirigida("3", "8", 3)
# grafo_numeros.insertar_arista_no_dirigida("3", "9", 9)
# grafo_numeros.insertar_arista_no_dirigida("4", "5", 4)
# grafo_numeros.insertar_arista_no_dirigida("4", "9", 3)
# grafo_numeros.insertar_arista_no_dirigida("5", "6", 15)
# grafo_numeros.insertar_arista_no_dirigida("5", "10", 3)
# grafo_numeros.insertar_arista_no_dirigida("6", "10", 10)
# grafo_numeros.insertar_arista_no_dirigida("6", "13", 7)
# grafo_numeros.insertar_arista_no_dirigida("7", "11", 21)
# grafo_numeros.insertar_arista_no_dirigida("7", "8", 3)
# grafo_numeros.insertar_arista_no_dirigida("8", "11", 18)
# grafo_numeros.insertar_arista_no_dirigida("8", "12", 4)
# grafo_numeros.insertar_arista_no_dirigida("8", "9", 9)
# grafo_numeros.insertar_arista_no_dirigida("9", "10", 1)
# grafo_numeros.insertar_arista_no_dirigida("9", "12", 12)
# grafo_numeros.insertar_arista_no_dirigida("9", "13", 14)
# grafo_numeros.insertar_arista_no_dirigida("10", "13", 5)
# grafo_numeros.insertar_arista_no_dirigida("11", "12", 11)
# grafo_numeros.insertar_arista_no_dirigida("12", "13", 19)
