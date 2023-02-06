# pap2023
Progetto di Programmazione Avanzata e Parallela, UniTS, AIDA, 2023
 
# DOCUMENTATION
Per l'utilizzo della classe Graph sono necessarie le seguenti librerie:

-iostream

-vector

-algorithm

## Graph

Graph è una classe template che accetta qualsiasi tipo primitivo come T.

### Attributi

 (private) std::vector<T> vertices
 
 (private) std::string name

 (private) std::unordered_map<T, std::unordered_map<T, int>> edges;

### Metodi
 
void addVertex(T v): aggiunge un vertex a vertices, bisogna specificare un identificatore (di tipo T).
 
void removeVertex(T v): rimuove v da vertices

 void addEdge(T src, T dst, int weight): aggiunge un arco da srt a dst di peso weight a edges.

 void removeEdge(T src, T dst):  rimuove il vertice da src a dst

 vertex_iterator v_begin(): ritorna un iteratore al primo elemento del vettore

 vertex_iterator v_end(): ritorna un iteratore all'ultimo elemento del vettore
 
 ### Metodi di classe
 
 std::unordered_map<T, int>> dijkstra(Graph<T> g, T src): esegue l'algoritmo di Dijkstra sul grafo g specificato, a partire dal nodo src. Ritorna la lista delle distanze come mappa di coppie "nodo di arrivo" : costo di arrivo.
 
std::unordered_map<T, int>> bellmanFord(Graph<T> g, T src): esegue l'algoritmo di Bellman-Ford sul grafo g specificato, a partire dal nodo src. Ritorna la lista delle distanze come mappa di coppie "nodo di arrivo" : costo di arrivo.
 
 
