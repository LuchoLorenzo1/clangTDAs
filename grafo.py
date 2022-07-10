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


def dijkstra(grafo: GrafoHH, origen):
    if not grafo or not origen:
        return

    visitados = {origen}
    no_visitados = set(grafo.vertices.keys())

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
# DFS(grafo, "A", print)
# print("BFS")
# BFS(grafo, "A", print)

# print(dijkstra(grafo, "A"))

print(grafo)
print("-----")


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
                if adyacente not in visitados:
                    d = grafo.devuelve_distancia(visitado, adyacente)
                    if d < min[0]:
                        min = (d, visitado, adyacente)

        no_visitados.remove(min[2])
        visitados.add(min[2])
        arbol_minimo.insertar_arista_no_dirigida(min[1], min[2], min[0])

    return arbol_minimo

def kruskal(graph: GrafoHH) -> GrafoHH:
    """
    returns minimum spanning tree of the graph
    """
    visitados = set()
    spanning_tree = GrafoHH()


    while no_visitados:

        min = (inf, None, None)

        for visitado in visitados:
            adyacencias = grafo.obtener_adyacencias(visitado)
            for adyacente in adyacencias:
                if adyacente not in visitados:
                    d = grafo.devuelve_distancia(visitado, adyacente)
                    if d < min[0]:
                        min = (d, visitado, adyacente)

        no_visitados.remove(min[2])
        visitados.add(min[2])
        arbol_minimo.insertar_arista_no_dirigida(min[1], min[2], min[0])

    return arbol_minimo

grafo2 = GrafoHH()
grafo2.insertar_arista_no_dirigida("1", "2", 1)
grafo2.insertar_arista_no_dirigida("1", "5", 7)
grafo2.insertar_arista_no_dirigida("2", "3", 6)
grafo2.insertar_arista_no_dirigida("2", "7", 8)
grafo2.insertar_arista_no_dirigida("3", "4", 21)
grafo2.insertar_arista_no_dirigida("3", "7", 2)
grafo2.insertar_arista_no_dirigida("3", "8", 3)
grafo2.insertar_arista_no_dirigida("3", "9", 9)
grafo2.insertar_arista_no_dirigida("4", "5", 4)
grafo2.insertar_arista_no_dirigida("4", "9", 3)
grafo2.insertar_arista_no_dirigida("5", "6", 15)
grafo2.insertar_arista_no_dirigida("5", "10", 3)
grafo2.insertar_arista_no_dirigida("6", "10", 10)
grafo2.insertar_arista_no_dirigida("6", "13", 7)
grafo2.insertar_arista_no_dirigida("7", "11", 21)
grafo2.insertar_arista_no_dirigida("7", "8", 3)
grafo2.insertar_arista_no_dirigida("8", "11", 18)
grafo2.insertar_arista_no_dirigida("8", "12", 4)
grafo2.insertar_arista_no_dirigida("8", "9", 9)
grafo2.insertar_arista_no_dirigida("9", "10", 1)
grafo2.insertar_arista_no_dirigida("9", "12", 12)
grafo2.insertar_arista_no_dirigida("9", "13", 14)
grafo2.insertar_arista_no_dirigida("10", "13", 5)
grafo2.insertar_arista_no_dirigida("11", "12", 11)
grafo2.insertar_arista_no_dirigida("12", "13", 19)

spanning_tree = prim(grafo2, "4")
print(spanning_tree)
