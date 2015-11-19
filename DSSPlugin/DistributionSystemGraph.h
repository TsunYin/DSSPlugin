#pragma once
#include <boost/graph/adjacency_list.hpp>

struct DistributionSystemNode {
	int index;

	std::string name;
	int phase;
};

struct DistributionSystemEdge {
	std::string name;
	std::string type;
	std::string source;
	std::string target;
};

class DistributionSystemGraph
{
	typedef boost::adjacency_list < boost::vecS, boost::vecS, boost::bidirectionalS, DistributionSystemNode, DistributionSystemEdge > Graph;
	typedef std::pair<int, int> Edge;

	public:
			
		DistributionSystemGraph(int num_nodes);
		~DistributionSystemGraph();

		DistributionSystemNode get_node(const char * name);
		DistributionSystemEdge get_edge(const char * name);

		int num_nodes();
		int num_edges();

		void set_nodes(std::vector<std::string> &names, std::vector<int> &phases);
		void new_edge(std::string source, std::string target, std::string name, std::string type);

		void print_summary(std::string filename);
		void print_log(std::string filename);

	private:

		Graph _graph;
		std::map<std::string, Graph::vertex_descriptor> _vertex_map;
		std::map<std::string, Graph::edge_descriptor> _edge_map;
		std::vector<std::string> _logs;
};

