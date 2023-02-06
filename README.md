# pap2023
Progetto di Programmazione Avanzata e Parallela, UniTS, AIDA, 2023
 
## DOCUMENTATION
Per l'utilizzo della classe Graph sono necessarie le seguenti librerie std:
-iostream
-vector
-algorithm

### Graph

Graph è una classe template che accetta qualsiasi tipo primitivo come T.

#### Attributi
 (private) std::vector<T> vertices
 
 (private) std::string name

 (private) std::unordered_map<T, std::unordered_map<T, int>> edges;

#### Metodi
void addVertex(T v): aggiunge un vertex a vertices, bisogna specificare un identificatore (di tipo T).
 
void removeVertex(T v): rimuove v da this.vertices

 void addEdge(T src, T dst, int weight): aggiunge un arco da srt a dst di peso weight.

 void removeEdge(T src, T dst):  rimuove il vertice da src a dst

 vertex_iterator v_begin(): ritorna un iteratore al primo elemento del vettore

 vertex_iterator v_end(): ritorna un iteratore all'ultimo elemento del vettore
