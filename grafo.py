from math import inf


class Grafo:
    """
    Grafo estatico de tamanio n
    Implementado con matriz de adyacencias
    """

    def __init__(self, n: int):
        self.matriz = [[inf for _ in range(n)] for _ in range(n)]

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
        # adyacencias = []
        # for destino in range(len(self.matriz)):
        #     if self.matriz[origen][destino] != inf:
        #         adyacencias.append(destino)
        return [i for i in range(len(self.matriz)) if self.matriz[o][i] != inf]

    def __str__(self):
        cadena = ""
        for origen in range(len(self.matriz)):
            cadena += "[|"
            for destino in range(len(self.matriz)):
                cadena += str(self.matriz[origen][destino]) + "|"
            cadena += "]\n"
        return cadena


class GrafoHH:
    """
    Grafo implementado con diccionarios de diccionarios
    """

    def __init__(self, nombresVertices):
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


def DFS(grafo: GrafoHH, origen, f):
    pila = [origen]
    visitados = [origen]

    while pila:
        vertice = pila.pop()
        f(vertice)
        for v in grafo.obtener_adyacencias(vertice):
            if v not in visitados:
                pila.append(v)
                visitados.append(vertice)


def BFS(grafo: GrafoHH, origen, f):
    cola = [origen]
    visitados = [origen]

    while cola:
        vertice = cola.pop(0)
        f(vertice)
        for v in grafo.obtener_adyacencias(vertice):
            if v not in visitados:
                cola.append(v)
                visitados.append(v)


def dijkstra(grafo: GrafoHH, origen):
    if not grafo or not origen:
        return

    visitados = [origen]
    no_visitados = list(grafo.vertices.keys())

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

        visitados.append(actual)
        no_visitados.remove(actual)

    return matriz


grafo = GrafoHH(["A", "B", "C", "D", "E", "F"])


grafo.insertar_arista_no_dirigida("A", "B", 5)
grafo.insertar_arista_no_dirigida("A", "D", 6)
grafo.insertar_arista_no_dirigida("B", "C", 9)
grafo.insertar_arista_no_dirigida("B", "D", 4)
grafo.insertar_arista_no_dirigida("C", "E", 1)
grafo.insertar_arista_no_dirigida("C", "F", 7)
grafo.insertar_arista_no_dirigida("D", "F", 2)
grafo.insertar_arista_no_dirigida("D", "E", 6)
grafo.insertar_arista_no_dirigida("F", "E", 3)

# print("DFS")
# DFS(grafo, "1", print)
# print("BFS")
# BFS(grafo, "1", print)


# print(grafo.obtener_adyacencias("E"))
print(dijkstra(grafo, "E"))
