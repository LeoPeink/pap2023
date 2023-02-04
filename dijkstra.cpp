template <typename T>
std::unordered_map<T, int> dijkstra(Graph<T> g, T src)
{
    // implementazione dell'algoritmo di Dijkstra
    std::unordered_map<T, int> dist;        //mappa di distanze A : 6, C : 9
    std::unordered_map<T, T> prev;            //precedente: C:A -> C precede A, per estrarre il PRECEDENTE si chiama FIRST
    std::vector<T> queue;                    //coda di vertici

    // Inizializzazione
    for (auto it = g.v_begin(); it != g.v_end(); ++it)        //itero i vertici con vertex_iterator
    {
        dist[it] = INT_MAX;                                //la distanza da src va a infinito
        prev[it] = -1;                                        //il precedente è -1, = null
        queue.push_back(it);                                //aggiungo il vertice alla coda
    }
    dist.at(src) = 0;    //la distanza da src a src è 0 ovviamente

    //iterate through all vertices
        for (int i = 0; i < g.getVertices().size() - 1; i++)
        {
            for (auto it = g.v_begin(); it != g.v_end(); ++it)        //vrtx corrente =it
            {
                auto nears = g.getEdges().at(it);    //nears contiene i vicini del vertice corrente

                //per ogniuno dei vicini,
                //se la distanza è 

                for (auto e_it = nears.begin(); e_it != nears.end(); ++it)
                {
                    auto v = e_it->first;
                    int weight = e_it->second;
                    if (dist.at(it) != INT_MAX && dist.at(v) + weight < dist.at(v))
                    {
                        dist.at(v) = dist.at(it) + weight;
                        prev.at(v) =it;
                    }

                }
            }
        }

    return dist;
}
