template <typename T>
std::unordered_map<T, int> dijkstra(Graph<T> g, T src)        //TODO min heap per la coda, ora è v2
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
        //queue.push_back(it);                                //aggiungo il vertice alla coda
    }
    dist.at(src) = 0;    //la distanza da src a src è 0 ovviamente

    //iterate through all vertices
    while (!queue.empty()) {
        auto u = std::min_element(queue.begin(), queue.end())

                queue.erase(u);
        }

            //std::cout << "VERTICE IN ANALISI: " <<it << std::endl;

            try
            {
                auto nears = g.getEdges().at(it);    //nears contiene i vicini del vertice corrente
                for (auto e_it = nears.begin(); e_it != nears.end(); ++e_it) //per ogniuno dei vicini (gli adiacenti al vrtx corrente)
                {
                    auto v = e_it->first;                                    //"v" contiene il nome del vicino, es. "A"
                    int weight = e_it->second;                                //weight contiene il peso dell'arco, es. 5. Significato: dait a v c'è un arco pesante weight.

                    //std::cout << "ARCO:" << it << " -> " << v << ", PESO: " << weight << std::endl;

                    if (dist.at(it) != INT_MAX && (dist.at(it) + weight) < dist.at(v)) //se la distanza non è INF e
                    {
                        dist.at(v) = dist.at(it) + weight;
                        prev.at(v) = *it;
                    }
                }
                //std::cout << std::endl;
            }
            catch(const std::out_of_range e)
            {
                //
            }
        }
    }

    return dist;
}
