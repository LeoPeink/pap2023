#ifndef guard
#define guard

#include <vector>
#include <unordered_map>
#include <queue>

template <typename T>
class Graph {
public:
    
    Graph(); // costruttore
    Graph(std::string name) : name(name) {} // costruttore che salva anche un nome per il grafo

    ~Graph() {name.clear();} // distruttore che cancella anche il nome del grafo

    // funzioni che aggiungono e rimuovono vertici e archi del grafo
    void addVertex(T vertex);    // non sono metodi costanti ne statici in quanto modificano l'oggetto
    void removeVertex(T vertex);
    void addEdge(T src, T dest, int weight);
    void removeEdge(T src, T dest);

    const std::string getName() const { return name;} // metodo costante per ritornare il nome del grafo

    std::unordered_map<T, int> dijkstra(Graph<T>& graph, T src); // dichiarazione degli algoritmi di orienatento
    std::unordered_map<T, int> bellmanFord(Graph<T>& graph, T src);
    
    
    class VertexIterator { // iteratore per i vertici del grafo
    public:
        
        VertexIterator(Graph<T>& graph) : graph(graph), it(graph.vertices.begin()) {} // costruttore che inzia dal primo elemento dell'array di partenza

        // funzioni per la navigazione
        T next() {return *(it++);} // ritona accesso alla zona di memoria del prossimo elemento sfruttando l'iteratore
        bool hasNext() {return it != graph->vertices.end();} // True se elemento puntato dall'iteratore è diverso dall'ultimo
//!! forse la sintasi di hasNext è troppo sofisticata ? cambiare anche i nomi delle funzioni
    private:                                                
        Graph<T>& graph;
        typename std::vector<T>::iterator it; // it è un iteratore della classe vector
    };

    // iteratore per gli archi
    class EdgeIterator {
    public:
        // costruttore
        EdgeIterator(Graph<T>& graph, T vertex) : graph(graph), it(graph.edges[vertex].begin()) {} 

/* starta l'iteratore dal nodo specificato: nella mappa degli edge cerca quello che ha come chiave il vertice selezionato
 graph.edges[vertex] è l'elenco degli archi uscenti dal vertice specificato, rappresentato come una mappa dove la chiave è il vertice di arrivo e il valore è il peso dell'arco.
 graph.edges[vertex].begin() è un iteratore che punta alla prima posizione dell'elenco degli archi uscenti dal vertice specificato.
Immagina di avere un armadietto per ogni studente della scuola, dove ogni armadietto ha un numero univoco. Ogni armadietto contiene una serie di scomparti, dove ogni scomparto è identificato da un numero univoco.
Il numero univoco dell'armadietto è la chiave principale della mappa di mappe, mentre il numero univoco del singolo scomparto è la chiave secondaria. Il contenuto di ogni scomparto è il valore associato alla coppia chiave principale-chiave secondaria.
In questa metafora, per accedere al contenuto di uno specifico scomparto, si utilizzerebbe la chiave dell'armadietto per accedere all'armadietto e poi la chiave del singolo scomparto per accedere al contenuto.*/
//!! anche qua troppo sofisticato

// ultilizza il riferimento "& graph" per essere sicuri che l'oggetto esista

        // funzioni per la navigazione
        std::pair<T, int> next() {return {it->first, it->second};} // first ritona la chiave e dunque l'edge di arrivo mentre second ritorna il peso dell'arco
//!!cambiare sintassi troppo sofisticata
        bool hasNext() {return it != graph->edges[vertex].end();}
    private:
        Graph<T>* graph;
        T vertex;
        typename std::unordered_map<T, int>::iterator it; //it è un iteratore della classe map
    };

private:
    std::vector<T> vertices;
    std::unordered_map<T, std::unordered_map<T, int>> edges; //si usa mappa per questioni di efficienza giustificare !!
// è una mappa di mappe

//!! nell'utilizzo di mappe di mappe risiede la principale vulnerabilita del progetto sarebbe il caso di pensare ad un approccio alternativo anche se il concetto di annidare contenitori è valido, magari provare con gli array anche se meno efficienti

/*Immagina di voler rappresentare un grafo con vertici rappresentati da scatole e archi rappresentati da etichette attaccate alle scatole. Ogni etichetta contiene informazioni su un vertice di destinazione e il peso dell'arco.
La mappa principale rappresenta l'insieme di tutte le scatole del grafo (i vertici), con i nomi delle scatole come chiavi e ogni scatola contiene una mappa secondaria che rappresenta le etichette attaccate alla scatola (gli archi uscenti dal vertice). La mappa secondaria ha come chiave il nome del vertice di destinazione e come valore il peso dell'arco.
In questo modo, per accedere agli archi uscenti da un determinato vertice, si può semplicemente accedere alla mappa secondaria della scatola corrispondente e navigare tra le etichette. Ciò garantisce un accesso rapido e facile agli archi in base al vertice di origine, senza la necessità di scansionare tutti i vertici del grafo.*/

    std::string name; //nome del grafo idealmente usato in costruttori
};

//!! da rifare completamente ma dato che sono noti basta copiare una diversa implementazione

template <typename T>
std::unordered_map<T, int> Graph<T>::dijkstra(Graph<T>& graph, T src) {
    // implementazione dell'algoritmo di Dijkstra
            std::unordered_map<T, int> dist;
            std::unordered_map<T, T> prev;
            std::unordered_map<T, int> INT_MAX;
    
            // Inizializzazione
            for (auto v : vertices) {
                dist[v] = INT_MAX;
                prev[v] = -1;
            }
            dist[src] = 0;

            // Relaxazione degli archi |V|-1 volte
            for (int i = 0; i < vertices.size() - 1; i++) {
                for (auto u : vertices) {
                    for (auto e : edges[u]) {
                        T v = e.first;
                        int weight = e.second;
                        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                            dist[v] = dist[u] + weight;
                            prev[v] = u;
                        }
                    }
                }
            }
        };

template <typename T>
std::unordered_map<T, int> Graph<T>::bellmanFord(Graph<T>& graph, T src) {
    // implementazione dell'algoritmo di Bellman-Ford
    std::unordered_map<T, int> dist;
            std::unordered_map<T, T> prev;
            std::priority_queue<std::pair<int, T>, std::vector<std::pair<int, T>>, std::greater<>> pq;
            std::unordered_map<T, int> INT_MAX; //capire come funzionano le mappe
    
            // Inizializzazione
            for (auto v : vertices) {
                dist[v] = INT_MAX;
                prev[v] = -1;
            }
            dist[src] = 0;
            pq.push({0, src});

            // Relaxazione degli archi
            while (!pq.empty()) {
                T u = pq.top().second;
                pq.pop();

                for (auto e : edges[u]) {
                    T v = e.first;
                    int weight = e.second;
                    if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        prev[v] = u;
                        pq.push({dist[v], v});
                    }
                }
            }
        };


//!! riscrivere i commenti e riformulare le funzioni cambiando anche ordine in cui compaiono o parentesi/identatura

template <typename T> //questa è semplice probabilmente basta riformulare in altri termini
void Graph<T>::addVertex(T vertex) {
    // controllo se il vertice esiste già
    auto it = std::find(vertices.begin(), vertices.end(), vertex); // cerca tra i vertici quello che vogliamo aggiungere
    if (it == vertices.end()) { // se non dovesse esistere lo aggiunge al vettore dei vertici        
        vertices.push_back(vertex);
    }
}

template <typename T>
void Graph<T>::removeVertex(T vertex) {
    // controllo se il vertice esiste
    auto it = std::find(vertices.begin(), vertices.end(), vertex);
    if (it != vertices.end()) {
        // se esiste, lo rimuovo dal vettore dei vertici
        vertices.erase(it);
        // rimuovo anche tutti gli archi che includono il vertice
        edges.erase(vertex);
        for (auto& e : edges) {
            e.second.erase(vertex);
        }
    }
}

template <typename T>
void Graph<T>::addEdge(T src, T dest, int weight) {
    // controllo che i vertici esistano
    if (std::find(vertices.begin(), vertices.end(), src) != vertices.end() &&
        std::find(vertices.begin(), vertices.end(), dest) != vertices.end()) {
        // aggiungo l'arco
        edges[src][dest] = weight;
    }
}

template <typename T>
void Graph<T>::removeEdge(T src, T dest) {
    // controllo che l'arco esista
    if (edges.count(src) && edges[src].count(dest)) {
        // rimuovo l'arco
        edges[src].erase(dest);
    }
}

#endif
