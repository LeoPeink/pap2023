#include <iostream>
#include <unordered_map>
#include <vector>
#include "errorMessages.h"

//todo dividere in files

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

	//getter
	std::vector<T> getVertices() { return vertices;}
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
		vertex_iterator& operator++()		{ ++ptr; return *this; }						//operatore di incremento prefisso
		vertex_iterator operator++(int)	{ vertex_iterator tmp{*this}; ++ptr; return tmp; }	//operatore di incemento postfisso
		inline reference operator*() { return *ptr; }										//operatore di dereferenziazione
		inline pointer operator->() { return ptr; }											//operatore puntatore			
		inline bool operator==(const vertex_iterator& it) { return ptr==it.ptr; }			//operatore uguaglianza
		inline bool operator!=(const vertex_iterator& it) { return ptr !=it.ptr; }			//operatore disuguaglianza
		//NB:inline per efficienza, non serve chiamare la funzione, basta far copiare il codice al compilatore al momento della chiamata
		


		//iterator(typename std::vector<T>::iterator it) : it{ it } {}; 

	private:
		vertex_iterator(pointer ptr) : ptr{ ptr } {};		//costruttore privato per creare un iteratore a partire da un puntatore: privato per evitare mismatch di tipi tra il container e l'iteratore
		
		pointer ptr; //puntatore all'elemento associato all'iteratore

		friend class Graph<T>;	//permette a Graph di accedere ai membri privati di iterator
	};

	inline vertex_iterator v_begin() { return vertex_iterator{ &vertices[0] }; }	//ritorna un iteratore al primo elemento del vettore, TODO CHECK SE FUNZIONA
	inline vertex_iterator v_end() { return vertex_iterator{ &vertices[vertices.size() - 1] + 1 }; }	//ritorna un iteratore all'ultimo elemento del vettore,	TODO CHECK SE FUNZIONA

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

	inline edge_iterator e_begin() {return  edge_iterator{ edges.begin()}; }	//ritorna un iteratore al primo elemento della mappa, TODO CHECK SE FUNZIONA
	inline edge_iterator e_end() { return edge_iterator{ edges.end()}; }	//ritorna un iteratore all'ultimo elemento del vettore,	TODO CHECK SE FUNZIONA

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
void djikstra(Graph<T> g, std::string start)
{
	/*
	for (T& val : g.getVertices())		//ITERATORE PER I VERTICI: FUNZIONA!!!!
	{
		std::cout << val << std::endl;
	}
	*/
	//std::unordered_map<T, int> dist;
	// .at() per gettare l'elemento dalla key, ma qua non serve (iteratore?)
	/*
	for each vertex V in G
		dist[V] < -infinite
		prev[V] < -NULL
		If V != S, add V to Priority Queue Q
		dist[S] < -0

		while Q IS NOT EMPTY
			U < -Extract MIN from Q
			for each unvisited neighbour V of U
				temperoryDist < -dist[U] + edgeWeight(U, V)
				if temperoryDist < dist[V]
					dist[V] < -temperoryDist
					prev[V] < -U
					return dist[], prev[]
					*/
}


int main()
{
	//instance a new graph named "graph"
	Graph<std::string> g("graph");
	//add vertex
	g.addVertex("A");
	g.addVertex("B");
	g.addVertex("C");
	g.addVertex("D");
	g.addVertex("E");
	//add edges
	g.addEdge("A", "B", 1);
	g.addEdge("A", "C", 1);
	g.addEdge("B", "D", 1);
	g.addEdge("C", "D", 1);
	djikstra(g, "a");

	//TEST iteratore per i vertici
	for (auto it = g.v_begin(); it != g.v_end(); ++it)
	{
		std::cout << *it << std::endl;
	}

	for (auto& lista : g.getEdges())
	{
		std::cout << lista.first << std::endl;
		for (auto& arco : lista.second)
		{
			std::cout << arco.first << " " << arco.second << std::endl;
		}
			
	}

	/*
	//print all existing edges
	for (auto it = g.e_begin(); it != g.e_end(); ++it)
	{
		it->first;
		
		//std::cout << it->first << " " << it->second << std::endl;
	}
	*/
}
