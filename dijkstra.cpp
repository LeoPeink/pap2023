
template <typename T>
std::unordered_map<T, int> Graph<T>::dijkstra(Graph<T>& graph, T src) {
    // implementazione dell'algoritmo di Dijkstra
            std::unordered_map<T, int> dist;
            std::unordered_map<T, T> prev;
            std::unordered_map<T, int> INT_MAX;
    
            // Inizializzazione
            for (auto it = g.v_begin(); it != g.v_end(); ++it) {
                dist[it] = INT_MAX;
                prev[it] = -1;
            }
            dist[src] = 0;

            // Relaxazione degli archi |V|-1 volte
            for (int i = 0; i < vertices.size() - 1; i++)            
                for (auto u = g.v_begin(); it != g.v_end(); ++it) {
                    for (auto e = g.e_begin(); it != g.e_end(); ++it)) {
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
