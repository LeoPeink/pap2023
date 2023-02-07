#include "graph.h"

template <typename T>
void Graph<T>::addVertex(T vertex)
{

	if (std::find(vertices.begin(), vertices.end(), vertex) == vertices.end())	//se il vertice non esiste già
	{
		vertices.push_back(vertex);												//aggiungilo
	}
	else																		//altrimenti
	{
		std::cout << E_VERTEX_ALREADY_EXISTING;									//stampa messaggio di errore
	}
	//else ignore, potential TODO: error message abo
}

template <typename T>
void Graph<T>::addEdge(T src, T dest, int weight) {
	
	if (std::find(vertices.begin(), vertices.end(), src) != vertices.end() &&	// controllo che i vertici esistano
		std::find(vertices.begin(), vertices.end(), dest) != vertices.end())
	{
	
		edges[src][dest] = weight;												// aggiungo l'arco
	}
	else																		//altrimenti
	{
		std::cout << E_MISSING_VERTEX;											//stampa un errore
	}
}

template <typename T>
void Graph<T>::removeVertex(T vertex)
{
	auto it = std::find(v_begin(), v_end(), vertex);				// controllo se il vertice esiste con std::find
	if (it != v_end())
	{
		vertices.erase(it);											// se esiste, lo rimuovo dal vettore dei vertici
		edges.erase(vertex);
		for (auto& e : edges)										// rimuovo anche tutti gli archi che includono il vertice
		{
			e.second.erase(vertex);
		}
	}
	else															//se non esiste,
	{
		std::cout << E_MISSING_VERTEX << std::endl;					//stampa un errore
	}
}

template <typename T>
void Graph<T>::removeEdge(T src, T dest) {
	// controllo che l'arco esista
	if (edges.count(src) && edges[src].count(dest)) {
		// rimuovo l'arco
		edges[src].erase(dest);
	}
	else
	{
		std::cout << E_MISSING_EDGE << std::endl;
	}
}

template <typename T>
const std::unordered_map<T, int> Graph<T>::dijkstra(Graph<T> g, T src)
{
	// implementazione dell'algoritmo di Dijkstra
	std::unordered_map<T, int> dist;		//mappa di distanze A : 6, C : 9. E' la soluzione del problema, che verrà returnata.
	std::unordered_map<T, T> prev;			//lista dei precedenti: C:A significa C precede A
	std::vector<T> queue;					//tiene traccia dei vertici già visitati

	if (g.getVertices().empty())
	{
		std::cout << E_EMPTY_GRAPH << std::endl;
		return dist;
	}

	// Inizializzazione
	for (auto it = g.v_begin(); it != g.v_end(); ++it)		//itero i vertici con vertex_iterator
	{
		dist[*it] = INT_MAX;								//la distanza da src va a infinito
		prev[*it] = "";										//il precedente è vuoto
		queue.push_back(*it);								//aggiungo il vertice alla coda
	}
	try
	{
		dist.at(src) = 0;	//la distanza da src a src è 0 ovviamente. Nel caso il vertice non sia nel grafo, gestiamo l'eccezione.
	}
	catch (const std::out_of_range e)
	{
		std::cout << E_MISSING_VERTEX << std::endl;
		return dist;
	}
	
	while (queue.size() > 0)
	{
		int min = INT_MAX;
		T min_key;
		for (auto it = queue.begin(); it != queue.end(); ++it)	//trova il vertice minore cercando all'interno della coda
		{
			if (dist.at(*it) <= min)							
			{
				min = dist.at(*it);								//e salva la distanza minima (serve a confrontare le distanze)
				min_key = *it;									//e salva la chiave (serve ad accedere direttamente grazie alla unordered_map)
			}
		}
		queue.erase(find(queue.begin(), queue.end(), min_key)); //togli dalla coda il nodo con la distanza minima
		try														//prova ad estrarre i vicini
		{
			auto nears = g.getEdges().at(min_key);				//nears contiene i vicini del vertice corrente (identificato dereferenziando l'iteratore *it)
			for (auto e_it = nears.begin(); e_it != nears.end(); ++e_it) //per ogniuno dei vicini (gli adiacenti al vrtx corrente)
			{
				auto v = e_it->first;									//"v" contiene il nome del vicino, es. "A"
				int weight = e_it->second;								//weight contiene il peso dell'arco, es. 5. Da *it a v c'è un arco pesante weight.
				if (weight < 0)
				{
					std::cout << E_NEGATIVE_GRAPH << std::endl;
				}
				if (dist.at(min_key) != INT_MAX && (dist.at(min_key) + weight) < dist.at(v)) //se la distanza non è INF ed il percorso trovato è migliore,
				{
					dist.at(v) = dist.at(min_key) + weight;									//aggiorna la tabella di distanze
					prev.at(v) = min_key;
				}
			}
		}
		catch (const std::out_of_range e) {}// l'eccezione si presenta quando un vertice non ha vicini, la riga 98 lancia out_of_range exception.
	}
	return dist; //ritorno la mappa delle distanze. Per risolvere il problema di shortest-path tra due vertici bisognerebbe apportare lievi modifiche al codice e ritornare anche prev, magari sotto forma di dizionario insieme a dist.
}

template <typename T>
const std::unordered_map<T, int> Graph<T>::bellmanFord(Graph<T> g, T src)
{
	std::unordered_map<T, int> dist;		//mappa di distanze A : 6, C : 9

	if (g.getVertices().empty())
	{
		std::cout << E_EMPTY_GRAPH << std::endl;
		return dist;
	}

	for (auto it = g.v_begin(); it != g.v_end(); ++it)		//itero i vertici con vertex_iterator
	{
		dist[*it] = INT_MAX;								//la distanza da src va a infinito
	}

	try
	{
		dist.at(src) = 0;	//la distanza da src a src è 0 ovviamente. Nel caso il vertice non sia nel grafo, gestiamo l'eccezione.
	}
	catch (const std::out_of_range e)
	{
		std::cout << E_MISSING_VERTEX << std::endl;
		return dist;
	}

	for (int i = 0; i < g.getVertices().size(); ++i)	//processo gli archi ripetutamente: per tutti i vertici
	{
		for (auto& lista : g.getEdges())				//per tutti gli archi
		{
			auto u = lista.first;						//vertice in analisi
			for (auto& arco : lista.second)				//per tutti gli archi (cont'd)
			{
				auto v = arco.first;					//è il nodo destinazione
				auto w = arco.second;					//è il peso dell'arco src -> v
				if (dist.at(u) != INT_MAX && dist.at(u) + w < dist.at(v))	//se il percorso in analisi conviene rispetto al precedente,
				{
					dist.at(v) = dist.at(u) + w;							//aggiorna la tabella delle distanze
				}
			}
		}
	}

	for (auto& lista : g.getEdges())		//controllo la presenza di cicli negativi: per tutti gli archi
	{
		auto u = lista.first;				//vertice in analisi
		for (auto& arco : lista.second)				//per tutti gli archi (cont'd)
		{
			auto v = arco.first;	//è il nodo destinazione 
			auto w = arco.second;	//è il peso dell'arco src -> v
			if (dist.at(u) != INT_MAX && dist.at(u) + w < dist.at(v))	//se è ancora possibile ottimizzare
			{
				std::cout << E_NEGATIVE_WEIGHT_CYCLE << std::endl;		//allora siamo in presenza di un ciclo negativo.
				return dist;											//ritorno mappa di distanze e stampo l'errore.
			}
		}
	}
	return dist;
}
