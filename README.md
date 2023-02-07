# Programmazione Avanzata e Parallela 2023
 
Progetto di Programmazione Avanzata e Parallela, UniTS, AIDA, 2023 : realizzazione di una classe template per la creazione di grafi ed implementazione degli algoritmi di ottimizzazione per la ricerca del percorso di costo minimo "Dijkstra" e "Bellman-Ford".

Autori: Leo Peinkhofer, Lorenzo Di Bernardo
 
# Documentazione Graph
Includendo Graph.cpp si includono automaticamente le librerie:
"iostream", "unordered_map", "vector", "limits.h" e "algorithm"

## Graph
Graph è una classe template che accetta qualsiasi tipo primitivo come T.

### Attributi
 Graph non espone attributi pubblici.
 
 (private) std::vector<T> vertices
 
 (private) std::string name

 (private) std::unordered_map<T, std::unordered_map<T, int>> edges;

### Metodi pubblici
 
std::string getName(): restituisce il nome del grafo
 
void addVertex(T v): aggiunge un vertex a vertices, bisogna specificare un identificatore (di tipo T).
 
void removeVertex(T v): rimuove v da vertices

 void addEdge(T src, T dst, int weight): aggiunge un arco da srt a dst di peso weight a edges.

 void removeEdge(T src, T dst):  rimuove il vertice da src a dst

 vertex_iterator v_begin(): ritorna un iteratore al primo elemento del vettore

 vertex_iterator v_end(): ritorna un iteratore all'ultimo elemento del vettore
 
 (private) std::vector<T> getVertices() : restituisce il vector di vertici
 
 (private) std::unordered_map<T, std::unordered_map<T, int>> getEdges(): restituisce la mappa di mappe contenente archi e pesi
 
 ### Metodi della classe
 
 std::unordered_map<T, int>> dijkstra(Graph<T> g, T src): esegue l'algoritmo di Dijkstra sul grafo g specificato, a partire dal nodo src. Ritorna la lista delle distanze come mappa di coppie "nodo di arrivo" : costo di arrivo.
 
std::unordered_map<T, int>> bellmanFord(Graph<T> g, T src): esegue l'algoritmo di Bellman-Ford sul grafo g specificato, a partire dal nodo src. Ritorna la lista delle distanze come mappa di coppie "nodo di arrivo" : costo di arrivo.
 
# Varie
 
 ## errorMessages.h
 
 Questo file contiene vari messaggi di errore che vengono usati per gestire a livello di interfaccia utente alcune eccezioni o casi limite.
 
 ## main.cpp
 
 Questo file sorgente contiene un metodo main() con un menu pre-configurato, al fine di verificare facilmente il funzionamento della libreria tramite CLI.
 
 ## Demo images
 
La cartella contiene la rappresentazione grafica dei grafi pre-impostati nel menu per facilitare il test della libreria.
