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


grafo = GrafoHH(["hospital", "colegio", "iglesia"])
