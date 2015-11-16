#include "stdafx.h"
#include "DistributionSystemGraph.h"

using namespace boost;

DistributionSystemGraph::DistributionSystemGraph(int num_nodes) {
	_graph = Graph(num_nodes);
		
}

DistributionSystemGraph::~DistributionSystemGraph() {
}

void DistributionSystemGraph::set_nodes(std::vector<std::string> &names, std::vector<int> &phases) {
	property_map<Graph, vertex_name_t>::type name_map = get(vertex_name_t(), _graph);
	property_map<Graph, vertex_phase_t>::type phase_map = get(vertex_phase_t(), _graph);
	
	if (names.size() != phases.size()) {
		throw std::invalid_argument("name and phases vectors must be same length!");
	}

	for (size_t i = 0; i < names.size(); i++) {
		_vertex_map[names[i]] = i;

		name_map[i] = names[i];
		phase_map[i] = phases[i];
	}
}

DistributionSystemNode DistributionSystemGraph::get_node(const char * name) {
	DistributionSystemNode node;
	if (_vertex_map.find(name) != _vertex_map.end()) {
		property_map<Graph, vertex_phase_t>::type phase_map = get(vertex_phase_t(), _graph);

		node.name = name;
		node.index = _vertex_map[name];
		node.phase = phase_map[node.index];
	}
	return node;
}

int DistributionSystemGraph::num_nodes() {
	return num_vertices(_graph);
}

std::vector<std::string> DistributionSystemGraph::list_nodes() {
	int num_nodes = num_vertices(_graph);
	property_map<Graph, vertex_name_t>::type name_map = get(vertex_name_t(), _graph);

	std::vector<std::string> nodes(num_nodes);
	for (int i = 0; i < num_nodes; i++) {
		nodes[i] = name_map[i];
	}

	return nodes;
}