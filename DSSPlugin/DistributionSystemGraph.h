#pragma once
#include <boost/graph/adjacency_list.hpp>

struct DistributionSystemNode {
	std::string name;
	int phase;
	int index;
};

struct DistributionSystemEdge {
	std::string name;
	std::string type;
	std::string bus1;
	std::string bus2;
	int bus1_phase;
	int bus2_phase;
};

class DistributionSystemGraph
{
	
	//==========================
	// Custom Vertex Properties
	//==========================
	struct vertex_phase_t { typedef boost::vertex_property_tag kind; };

	typedef boost::property<vertex_phase_t, int> VertexPhase;
	typedef boost::property<boost::vertex_name_t, std::string, VertexPhase> VertexName;

	//==========================
	// Custom Edge Properties
	//==========================
	struct edge_phase_t { typedef boost::edge_property_tag kind; };
	struct edge_type_t { typedef boost::edge_property_tag kind; };

	typedef boost::property<edge_type_t, std::string> EdgeType;
	typedef boost::property<edge_phase_t, int, EdgeType> EdgePhase;
	typedef boost::property<boost::edge_name_t, std::string, EdgePhase> EdgeName;

	//==========================
	// typedef Graph and Edge
	//==========================
	typedef boost::adjacency_list < boost::vecS, boost::vecS, boost::bidirectionalS, VertexName, EdgeName > Graph;
	typedef std::pair<int, int> Edge;

	public:

		DistributionSystemGraph(int num_nodes);
		~DistributionSystemGraph();

		DistributionSystemNode get_node(const char * name);
		int num_nodes();

		void set_nodes(std::vector<std::string> &names, std::vector<int> &phases);

		std::vector<std::string> list_nodes();

	private:

		Graph _graph;
		std::map<std::string, int> _vertex_map;
		std::map<std::string, int> _edge_map;

};

