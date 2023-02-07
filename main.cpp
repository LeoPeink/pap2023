#include "graph.CPP"

int main()
{
	int selection = 0;
	Graph<std::string> g;
	do
	{
		std::cout << std::endl << "---GRAPH DEMO:---" << std::endl << std::endl;
		std::cout << "0) Generate a demo graph as for graph_demo_0.png. This graph contains a negative cycle." << std::endl;
		std::cout << "1) Generate a demo graph as for graph_demo_1.png. This graph has only positive edges." << std::endl;
		std::cout << "2) Generate a demo graph as for graph_demo_2.png.This graph has positive and negative edges." << std::endl;
		std::cout << "3) Generate an empty graph and add custom Vertices and Edges" << std::endl;
		std::cout << "4) Execute and print results of Dijkstra Algorithm on the graph" << std::endl;
		std::cout << "5) Execute and print results of Bellman-Ford Algorithm on the graph" << std::endl;
		std::cout << "6) Exit demo" << std::endl << std::endl;
		std::cin >> selection;
		switch (selection)
		{
		case 0:
		{
			//GRAPH for BELLMAN-FORD testing, as for graph_demo_0.png 
			//add vertices
			g = Graph<std::string>("demo_graph_2");
			g.addVertex("S");
			g.addVertex("A");
			g.addVertex("B");
			g.addVertex("C");
			g.addVertex("D");
			g.addVertex("E");
			//add edges
			g.addEdge("S", "A", 10);
			g.addEdge("S", "E", 8);
			g.addEdge("A", "C", -2);
			g.addEdge("B", "A", 1);
			g.addEdge("C", "B", -2);
			g.addEdge("E", "D", 1);
			g.addEdge("C", "D", -1);
			g.addEdge("D", "A", -4);
			std::cout << "graph_demo_0 has been loaded and is ready." << std::endl;
			break;
		}		
		case 1:
		{
			//GRAPH for DIJKSTRA testing, as for graph_demo_1.png 
			//add vertices
			g = Graph<std::string>("demo_graph_1");
			g.addVertex("A");
			g.addVertex("B");
			g.addVertex("C");
			g.addVertex("D");
			g.addVertex("E");
			//add edges
			g.addEdge("A", "B", 4);
			g.addEdge("A", "C", 2);
			g.addEdge("B", "C", 3);
			g.addEdge("B", "D", 2);
			g.addEdge("B", "E", 3);
			g.addEdge("C", "B", 1);
			g.addEdge("C", "D", 4);
			g.addEdge("C", "E", 5);
			g.addEdge("E", "D", 1);
			std::cout << "graph_demo_1 has been loaded and is ready." << std::endl;
			break;
		}
		case 2:
		{
			//GRAPH for BELLMAN-FORD testing, as for graph_demo_1.png 
			//add vertices
			g = Graph<std::string>("demo_graph_2");
			g.addVertex("S");
			g.addVertex("A");
			g.addVertex("B");
			g.addVertex("C");
			g.addVertex("D");
			g.addVertex("E");
			//add edges
			g.addEdge("S", "A", 10);
			g.addEdge("S", "E", 8);
			g.addEdge("A", "C", 2);
			g.addEdge("B", "A", 1);
			g.addEdge("C", "B", -2);
			g.addEdge("E", "D", 1);
			g.addEdge("D", "C", -1);
			g.addEdge("D", "A", -4);
			std::cout << "graph_demo_2 has been loaded and is ready." << std::endl;
			break;
		}
		case 3:
		{
			int numVer;
			int numEdges;

			g = Graph<std::string>("custom_demo_graph");

			std::cout << "How many vertices?" << std::endl;
			std::cin >> numVer;
			std::string v = "";
			for (int i = 0; i < numVer; i++)
			{
				std::cout << "Lets create vertex n." << i + 1 << ":" << std::endl;
				std::cout << "Insert vertex name: " << std::endl;
				std::cin >> v;
				g.addVertex(v);
			}

			std::cout << "How many edges?" << std::endl;
			std::cin >> numEdges;
			std::string s = "";
			std::string d = "";
			int w;
			for (int i = 0; i < numEdges; i++)
			{
				std::cout << "Lets create edge n." << i+1 << ":" << std::endl;
				std::cout << "Insert source vertex: " << std::endl;
				std::cin >> s;
				std::cout << "Insert destination vertex: " << std::endl;
				std::cin >> d;
				std::cout << "Insert weigth of edge from " << s << " to " << d << std::endl;
				std::cin >> w;
				g.addEdge(s, d, w);
			}
			break;
		}
		case 4:
		{
			std::string src = "";
			std::cout << "Source vertex: " << std::endl;
			std::cin >> src;
			auto res = Graph<std::string>::dijkstra(g, src);
			for (auto it = res.begin(); it != res.end(); ++it)
			{
				std::cout << it->first << " " << it->second << std::endl;
			}
			break;
		}
		case 5:
		{
			std::string src = "";
			std::cout << "Source vertex: " << std::endl;
			std::cin >> src;
			auto res = Graph<std::string>::bellmanFord(g, src);
			for (auto it = res.begin(); it != res.end(); ++it)
			{
				std::cout << it->first << " " << it->second << std::endl;
			}
			break;
		}
		case 6:
		{
			std::cout << "exiting demo..." << std::endl;
		}

		}
	} while (selection != 6);
}