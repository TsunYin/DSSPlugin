#include "stdafx.h"
#include "DistributionSystemGraph.h"
#include "StringUtils.h"
#include <iostream> // For logging purposes
#include <fstream>  // For logging purposes

using namespace boost;

DistributionSystemGraph::DistributionSystemGraph(int num_nodes) {
	_graph = Graph(num_nodes);
}

DistributionSystemGraph::~DistributionSystemGraph() {
}

DistributionSystemNode DistributionSystemGraph::get_node(const char * name) {
	DistributionSystemNode node;
	if (_vertex_map.find(name) != _vertex_map.end()) {
		auto vertices_map = get(vertex_bundle, _graph);
		node = vertices_map[_vertex_map[name]];
	}
	return node;
}

DistributionSystemEdge DistributionSystemGraph::get_edge(const char * name) {
	DistributionSystemEdge edge;
	if (_edge_map.find(name) != _edge_map.end()) {
		auto edges_map = get(edge_bundle, _graph);
		edge = edges_map[_edge_map[name]];
	}
	return edge;
}

void DistributionSystemGraph::set_nodes(std::vector<std::string> &names, std::vector<int> &phases) {
	if (names.size() != phases.size()) {
		_logs.push_back("ERROR: name and phase vectors must be the same length!");
		throw std::invalid_argument("name and phases vectors must be same length!");
	}

	auto vertices_map = get(vertex_bundle, _graph);
	for (size_t i = 0; i < names.size(); i++) {
		std::string name_lc = lower_case(names[i]);
		_vertex_map[name_lc] = i;

		vertices_map[i].index = i;
		vertices_map[i].name = name_lc;
		vertices_map[i].phase = phases[i];
		_logs.push_back("UPDATE: added vertex #" + std::to_string(i) + " " + name_lc);
	}
}

void DistributionSystemGraph::new_edge(std::string source, std::string target, std::string name, std::string type) {
	std::string source_lc = lower_case(source);
	std::string target_lc = lower_case(target);
	std::string name_lc = lower_case(name);

	if (_edge_map.find(name_lc) != _edge_map.end()) {
		_logs.push_back("ERROR: cannot add edge " + name_lc + ": graph already contains an edge with the same name");
		throw std::invalid_argument("graph already contains an edge named " + name_lc);
	}

	if (_vertex_map.find(source_lc) == _vertex_map.end()) {
		_logs.push_back("WARNING: edge " + name_lc + ": could not find source node " + source_lc);
	}
	if (_vertex_map.find(target_lc) == _vertex_map.end()) {
		_logs.push_back("WARNING: edge " + name_lc + ": could not find target node " + target_lc);
	}

	DistributionSystemEdge new_edge;
	new_edge.name = name_lc;
	new_edge.type = lower_case(type);
	new_edge.source = source_lc;
	new_edge.target = target_lc;
	add_edge(_vertex_map[source_lc], _vertex_map[target_lc], new_edge, _graph);

	_edge_map[name_lc] = edge(_vertex_map[source_lc], _vertex_map[target_lc], _graph).first;
	_logs.push_back("UPDATE: added edge " + name_lc + " from " + source_lc + " to " + target_lc);

}

int DistributionSystemGraph::num_nodes() {
	return num_vertices(_graph);
}

int DistributionSystemGraph::num_edges() {
	return boost::num_edges(_graph);
}

void DistributionSystemGraph::print_summary(std::string filename) {
	auto vertices_map = get(vertex_bundle, _graph);
	auto edges_map = get(edge_bundle, _graph);

	std::ofstream outfile;
	outfile.open(filename);

	outfile << "Vertices: ( " << num_nodes() << " )" << std::endl;
	for (auto i = _vertex_map.begin(); i != _vertex_map.end(); i++) {
		DistributionSystemNode n = vertices_map[i->second];
		outfile << "\t" << n.name << std::endl;
	}
	outfile << std::endl;

	outfile << "Edges: ( " << num_edges() << " )" << std::endl;
	for (auto i = _edge_map.begin(); i != _edge_map.end(); i++) {
		DistributionSystemEdge e = edges_map[i->second];
		outfile << "\t" << e.type << "." << e.name << "   " << e.source << " - " << e.target << std::endl;
	}

	outfile.close();
}

void DistributionSystemGraph::print_log(std::string filename) {
	std::ofstream out;
	out.open(filename);
	if (!out.is_open()) { return; }
	for (size_t i = 0; i < _logs.size(); i++) {
		out << _logs[i] << std::endl;
	}
	out.close();
}