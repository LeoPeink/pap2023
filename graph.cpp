
#include "graph.h"

template <typename T>
class Graph
{
public:
	//costruttori
	Graph() {};
	Graph(std::string name) : name{ name } {};

	//funzioni
	void addVertex(T vertex);    // non sono metodi costanti ne statici in quanto modificano l'oggetto
	void removeVertex(T vertex);
	void addEdge(T src, T dest, int weight);
	void removeEdge(T src, T dest);

	//metodi statici
	static const std::unordered_map<T, int> dijkstra(Graph<T> g, T src);		//TODO min heap per la coda, ora è v2
	static const std::unordered_map<T, int> bellmanFord(Graph<T> g, T src);
	//statici perchè metodi di classe, const perchè non devono modificare il grafo ma solo generare la tabella di distanze: per lo stesso motivo, passiamo il grafo per valore.

	//getter
	std::vector<T> getVertices() { return vertices; }
	std::unordered_map<T, std::unordered_map<T, int>> getEdges() { return edges; }

	//iteratori
	class vertex_iterator
	{
	public:
		using iterator_category = std::forward_iterator_tag;	//perchè proprio un iteratore forward?
		using difference_type = std::ptrdiff_t;					//la differenza tra puntatori è un ptrdiff_type 
		using value = T;										//il tipo di dato che contiene l'iteratore
		using pointer = value*;									//il tipo di dato puntato dall'iteratore
		using reference = value&;								//il tipo riferimento puntato dall'iteratore

		vertex_iterator() : ptr{ nullptr } {};							//costruttore di default
		//iterator(const iterator& it) : it{ it.it } {};									//costruttore di copia: inutile perchè già implicitamente implementato TODO capire(?)
		//iterator& operator=(const iterator& it) { this->it = it.it; return *this; }		//operatore di copia  : inutile perchè già implicitamente implementato TODO capire(?)
		vertex_iterator& operator++() { ++ptr; return *this; }						//operatore di incremento prefisso
		vertex_iterator operator++(int) { vertex_iterator tmp{ *this }; ++ptr; return tmp; }	//operatore di incemento postfisso
		inline reference operator*() { return *ptr; }										//operatore di dereferenziazione
		inline pointer operator->() { return ptr; }											//operatore puntatore			
		inline bool operator==(const vertex_iterator& it) { return ptr == it.ptr; }			//operatore uguaglianza
		inline bool operator!=(const vertex_iterator& it) { return ptr != it.ptr; }			//operatore disuguaglianza
		//NB:inline per efficienza, non serve chiamare la funzione, basta far copiare il codice al compilatore al momento della chiamata

		//iterator(typename std::vector<T>::iterator it) : it{ it } {}; 

	private:
		vertex_iterator(pointer ptr) : ptr{ ptr } {};		//costruttore privato per creare un iteratore a partire da un puntatore: privato per evitare mismatch di tipi tra il container e l'iteratore

		pointer ptr; //puntatore all'elemento associato all'iteratore

		friend class Graph<T>;	//permette a Graph di accedere ai membri privati di iterator
	};

	inline vertex_iterator v_begin() { return vertex_iterator{ &vertices[0] }; }	//ritorna un iteratore al primo elemento del vettore,
	inline vertex_iterator v_end() { return vertex_iterator{ &vertices[vertices.size() - 1] + 1 }; }	//ritorna un iteratore all'ultimo elemento del vettore,

	class edge_iterator
	{
	public:

		using iterator_category = std::forward_iterator_tag;	//perchè proprio un iteratore forward?
		using difference_type = std::ptrdiff_t;					//la differenza tra puntatori è un ptrdiff_type 
		using value = T;										//il tipo di dato che contiene l'iteratore
		using pointer = value*;									//il tipo di dato puntato dall'iteratore
		using reference = value&;								//il tipo riferimento puntato dall'iteratore

		edge_iterator() : ptr{ nullptr } {};							//costruttore di default
		//iterator(const iterator& it) : it{ it.it } {};									//costruttore di copia: inutile perchè già implicitamente implementato TODO capire(?)
		//iterator& operator=(const iterator& it) { this->it = it.it; return *this; }		//operatore di copia  : inutile perchè già implicitamente implementato TODO capire(?)
		edge_iterator& operator++() { ++ptr; return *this; }								//operatore di incremento prefisso
		edge_iterator operator++(int) { edge_iterator tmp{ *this }; ++ptr; return tmp; }	//operatore di incemento postfisso
		inline reference operator*() { return *ptr; }										//operatore di dereferenziazione
		inline pointer operator->() { return ptr; }											//operatore puntatore			
		inline bool operator==(const edge_iterator& it) { return ptr == it.ptr; }					//operatore uguaglianza
		inline bool operator!=(const edge_iterator& it) { return ptr != it.ptr; }					//operatore disuguaglianza
		//NB:inline per efficienza, non serve chiamare la funzione, basta far copiare il codice al compilatore al momento della chiamata

	private:

		edge_iterator(pointer ptr) : ptr{ ptr } {};		//costruttore privato per creare un iteratore a partire da un puntatore: privato per evitare mismatch di tipi tra il container e l'iteratore
		pointer ptr;									//puntatore all'elemento associato all'iteratore
		friend class Graph<T>;
	};

	inline edge_iterator e_begin() { return  edge_iterator{ edges.begin() }; }	//ritorna un iteratore al primo elemento della mappa, TODO CHECK SE FUNZIONA
	inline edge_iterator e_end() { return edge_iterator{ edges.end() }; }	//ritorna un iteratore all'ultimo elemento del vettore,	TODO CHECK SE FUNZIONA

private:
	std::string name;
	std::vector<T> vertices;
	std::unordered_map<T, std::unordered_map<T, int>> edges;

};


template <typename T>
void Graph<T>::addVertex(T vertex)
{
	if (std::find(vertices.begin(), vertices.end(), vertex) == vertices.end())	//if the vertex is not already existing in the vector
	{
		vertices.push_back(vertex);												//add it to the vector of vertices
	}
	else
	{
		std::cout << E_VERTEX_ALREADY_EXISTING;
	}
	//else ignore, potential TODO: error message abo
}

template <typename T>
void Graph<T>::addEdge(T src, T dest, int weight) {
	// controllo che i vertici esistano
	if (std::find(vertices.begin(), vertices.end(), src) != vertices.end() &&
		std::find(vertices.begin(), vertices.end(), dest) != vertices.end()) {
		// aggiungo l'arco
		edges[src][dest] = weight;
	}
	else
	{
		std::cout << E_MISSING_VERTEX;
	}
}

template <typename T>
void Graph<T>::removeVertex(T vertex)
{
	// controllo se il vertice esiste con un iteratore? TODO errori
	auto it = std::find(vertices.begin(), vertices.end(), vertex);
	if (it != vertices.end())
	{
		// se esiste, lo rimuovo dal vettore dei vertici
		vertices.erase(it);
		// rimuovo anche tutti gli archi che includono il vertice
		edges.erase(vertex);
		for (auto& e : edges)
		{
			e.second.erase(vertex);
		}
	}
}

template <typename T>
void Graph<T>::removeEdge(T src, T dest) {
	// controllo che l'arco esista come?? TODO errori
	if (edges.count(src) && edges[src].count(dest)) {
		// rimuovo l'arco
		edges[src].erase(dest);
	}
}

template <typename T>
const std::unordered_map<T, int> Graph<T>::bellmanFord(Graph<T> g, T src)
{
	std::unordered_map<T, int> dist;		//mappa di distanze A : 6, C : 9

	// Step 1: fill the distance array and predecessor array
	for (auto it = g.v_begin(); it != g.v_end(); ++it)		//itero i vertici con vertex_iterator
	{
		dist[*it] = INT_MAX;								//la distanza da src va a infinito
	}

	// Mark the source vertex
	dist.at(src) = 0;	//la distanza da src a src è 0 ovviamente


	for (int i = 0; i < g.getVertices().size(); ++i)	//for tutti i vertici
	{
		for (auto& lista : g.getEdges())				//per tutti gli archi
		{
			auto u = lista.first;			//src, T
			for (auto& arco : lista.second)				//per tutti gli archi (cont'd)
			{
				auto v = arco.first;	//dst, T
				auto w = arco.second;	//peso, int
				if (dist.at(u) != INT_MAX && dist.at(u) + w < dist.at(v))
				{
					dist.at(v) = dist.at(u) + w;
				}
			}
		}
	}

	//step 3: 
	for (auto& lista : g.getEdges())		//per tutti gli archi
	{
		auto u = lista.first;				//src, T
		for (auto& arco : lista.second)				//per tutti gli archi (cont'd)
		{
			auto v = arco.first;	//dst, T
			auto w = arco.second;	//peso, int
			if (dist.at(u) != INT_MAX && dist.at(u) + w < dist.at(v))
			{
				std::cout << E_NEGATIVE_WEIGHT_CYCLE << std::endl;
				return dist;
			}
		}
	}

	return dist;
}

template <typename T>
const std::unordered_map<T, int> Graph<T>::dijkstra(Graph<T> g, T src)
{
	std::unordered_map<T, int> dist;		//mappa di distanze A : 6, C : 9
	std::unordered_map<T, T> prev;			//precedente: C:A -> C precede A, per estrarre il PRECEDENTE si chiama FIRST
	std::vector<T> queue;	//tiene traccia dei vertici già visitati
	
	// Inizializzazione
	for (auto it = g.v_begin(); it != g.v_end(); ++it)		//itero i vertici con vertex_iterator
	{
		//TODO capire *it
		dist[*it] = INT_MAX;								//la distanza da src va a infinito
		prev[*it] = "";										//il precedente è -1, = null
		queue.push_back(*it);								//aggiungo il vertice alla coda
	}
	dist.at(src) = 0;	//la distanza da src a src è 0 ovviamente



	//finchè la coda non è vuota
	while(queue.size()>0)
	{
		//trova il vertice minore NELLA CODA
		int min = INT_MAX;
		T min_key;
		for (auto it = queue.begin(); it != queue.end(); ++it)
		{
			if (dist.at(*it) <= min)
			{
				min = dist.at(*it);
				min_key = *it;
			}
		}
	
		//toglilo dalla coda
		queue.erase(find(queue.begin(), queue.end(), min_key));
		
			try
			{
				auto nears = g.getEdges().at(min_key);	//nears contiene i vicini del vertice corrente
				for (auto e_it = nears.begin(); e_it != nears.end(); ++e_it) //per ogniuno dei vicini (gli adiacenti al vrtx corrente)
				{
					auto v = e_it->first;									//"v" contiene il nome del vicino, es. "A"
					int weight = e_it->second;								//weight contiene il peso dell'arco, es. 5. Significato: da *it a v c'è un arco pesante weight.

					//std::cout << "ARCO:" << *it << " -> " << v << ", PESO: " << weight << std::endl;

					if (dist.at(min_key) != INT_MAX && (dist.at(min_key) + weight) < dist.at(v)) //se la distanza non è INF e  
					{
						dist.at(v) = dist.at(min_key) + weight;
						prev.at(v) = min_key;
					}
				}
				//std::cout << std::endl;
			}
			catch (const std::out_of_range e)
			{
				//TODO gestire l'eccezione, viene quando un vertice non ha vicini
			}
	}
	
	return dist;
}