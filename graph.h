#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <limits.h>

#include "errorMessages.h"

template <typename T>
class Graph
{
public:
	//costruttori
	Graph() { name = ""; };							//costruttore di default, vuoto ma inizializza un nome a "".
	Graph(std::string name) : name{ name } {};		//costruttore che specifica un nome, preso come parametro dal costruttore.

	//metodi di instanza
	void addVertex(T vertex);    // non sono metodi costanti in quanto modificano l'oggetto direttamente, non sono statici perchè ogniuno modifica l'instanza da cui viene chiamato.
	void removeVertex(T vertex);
	void addEdge(T src, T dest, int weight);
	void removeEdge(T src, T dest);

	//metodi statici
	static const std::unordered_map<T, int> dijkstra(Graph<T> g, T src);
	static const std::unordered_map<T, int> bellmanFord(Graph<T> g, T src);
	//statici perchè metodi di classe, const perchè non devono modificare il grafo ma solo generare la tabella di distanze, infatti passiamo il grafo per valore.

	//getter
	std::string getName() { return name; }
	std::vector<T> getVertices() { return vertices; }
	std::unordered_map<T, std::unordered_map<T, int>> getEdges() { return edges; }

	//iteratori
	class vertex_iterator
	{
	public:
		using iterator_category = std::forward_iterator_tag;	//TODO comment
		using difference_type = std::ptrdiff_t;					//la differenza tra puntatori è un ptrdiff_type 
		using value = T;										//il tipo di dato che contiene l'iteratore
		using pointer = value*;									//il tipo di dato puntato dall'iteratore
		using reference = value&;								//il tipo riferimento puntato dall'iteratore

		vertex_iterator() : ptr{ nullptr } {};					//costruttore di default
		//iterator(const iterator& it) : it{ it.it } {};									//costruttore di copia: inutile perchè già implicitamente implementato 
		//iterator& operator=(const iterator& it) { this->it = it.it; return *this; }		//operatore di copia  : inutile perchè già implicitamente implementato
		vertex_iterator& operator++() { ++ptr; return *this; }								//operatore di incremento prefisso
		vertex_iterator operator++(int) { vertex_iterator tmp{ *this }; ++ptr; return tmp; }//operatore di incemento postfisso
		inline reference operator*() { return *ptr; }										//operatore di dereferenziazione
		inline pointer operator->() { return ptr; }											//operatore puntatore			
		inline bool operator==(const vertex_iterator& it) { return ptr == it.ptr; }			//operatore uguaglianza
		inline bool operator!=(const vertex_iterator& it) { return ptr != it.ptr; }			//operatore disuguaglianza

	private:
		vertex_iterator(pointer ptr) : ptr{ ptr } {};		//costruttore privato per creare un iteratore a partire da un puntatore: privato per evitare mismatch di tipi tra il container e l'iteratore

		pointer ptr; //puntatore all'elemento associato all'iteratore

		friend class Graph<T>;	//permette a Graph di accedere ai membri privati di iterator
	};

	/*
	//tentativo di implementazione di un iteratore per scorrere gli archi.
	class edge_iterator
	{
	public:

		using iterator_category = std::forward_iterator_tag;	
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

	inline edge_iterator e_begin() { return  edge_iterator{ edges.begin() }; }	//ritorna un iteratore
	inline edge_iterator e_end() { return edge_iterator{ edges.end() }; }	//ritorna un iteratore
	
	*/


	inline vertex_iterator v_begin() { return vertex_iterator{ &vertices[0] }; }	//ritorna un iteratore al primo elemento del vettore di vertici
	inline vertex_iterator v_end() { return vertex_iterator{ &vertices[vertices.size() - 1] + 1 }; }	//ritorna un iteratore all'ultimo elemento del vettore di vertici

private:
	std::string name;
	std::vector<T> vertices;
	std::unordered_map<T, std::unordered_map<T, int>> edges;

};
