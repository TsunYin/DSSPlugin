// DSSPlugin.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>

#include "StringUtils.h"
#include "BusNode.h"
#include "BusElement.h"
#include "NodeConnector.h"
#include "DistributionSystemGraph.h"

#define WORKSPACE "C:/Users/TsunYin/Dropbox/Nurhachi/Engineering/opendss/8500-node"
//#define WORKSPACE "E:/Dropbox/Nurhachi/Engineering/opendss/8500-node"

#define NODES_FILE "IEEE8500_EXP_NodeNames.CSV"
#define NODE_ORDER "IEEE8500_EXP_NodeOrder.CSV"
#define ELEMENTS_FILE "IEEE8500_Elements.Txt"

struct Node {
	std::string fullname;
	std::string name;
	int phase;
};

struct Element {
	std::string fullname;
	std::string name;
	std::string type;
	std::string bus1;
	std::string bus2;
	std::string bus3;
	int n_buses;
};

std::vector<Node> get_nodes(std::string filename) {
	std::vector<Node> nodes;
	std::regex regex_obj("(\\S+)\\.(\\d)");
	std::smatch match;

	std::ifstream fs(filename);
	if (fs.is_open())  {
		std::string line;
		while (std::getline(fs, line)) {
			if (std::regex_search(line, match, regex_obj)) {
				std::string name = match[1];
				int phase = stoi(match[2]);
				Node n;
				n.name = match[1];
				n.phase = stoi(match[2]);
				n.fullname = lower_case(n.name + '.' + std::to_string(n.phase));
				nodes.push_back(n);
			}
		}
	}
	fs.close();

	return nodes;
}

std::map<std::string, Element> get_elements(std::string filename) {
	std::map<std::string, Element> elements;
	std::regex regex_1bus("\"(\\S+)\\.(\\S+)\"\\s+(\\S+)\\s*$");
	std::regex regex_2bus("\"(\\S+)\\.(\\S+)\"\\s+(\\S+)\\s+(\\S+)\\s*$");
	std::regex regex_3bus("\"(\\S+)\\.(\\S+)\"\\s+(\\S+)\\s+(\\S+)\\s+(\\S+)\\s*$");
	std::smatch match;

	std::ifstream fs(filename);
	if (fs.is_open()) {
		std::string line;
		while (std::getline(fs, line)) {
			Element e;
			if (std::regex_search(line, match, regex_1bus)) {
				e.type = match[1];
				e.name = match[2];
				e.fullname = lower_case(e.type + '.' + e.name);
				e.bus1 = match[3];
				e.n_buses = 1;
				elements[e.fullname] = e;
			}
			else if (std::regex_search(line, match, regex_2bus)) {
				e.type = match[1];
				e.name = match[2];
				e.fullname = lower_case(e.type + '.' + e.name);
				e.bus1 = match[3];
				e.bus2 = match[4];
				e.n_buses = 2;
				elements[e.fullname] = e;
			}
			else if (std::regex_search(line, match, regex_3bus)) {
				e.type = match[1];
				e.name = match[2];
				e.fullname = lower_case(e.type + '.' + e.name);
				e.bus1 = match[3];
				e.bus2 = match[4];
				e.bus3 = match[5];
				e.n_buses = 3;
				elements[e.fullname] = e;
			}
		}
	}
	fs.close();

	return elements;
}

DistributionSystemGraph add_edges(std::string filename, std::map<std::string, Element> elements, DistributionSystemGraph g) {
	std::vector<NodeConnector*> edges;
	

	
	return g;
}

int main() {
	SetCurrentDirectory(_T(WORKSPACE));
	
	std::cout << "Reading " << NODES_FILE << "... ";
	std::vector<Node> nodes = get_nodes(NODES_FILE);
	std::cout << std::to_string(nodes.size()) << " found." << std::endl;

	std::vector<std::string> names(nodes.size());
	std::vector<int> phases(nodes.size());
	for (int i = 0; i < nodes.size(); i++) {
		names[i] = nodes[i].fullname;
		phases[i] = nodes[i].phase;
	}

	DistributionSystemGraph g(nodes.size());
	g.set_nodes(names, phases);

	std::cout << "Reading " << ELEMENTS_FILE << "... ";
	std::map<std::string, Element> elements = get_elements(ELEMENTS_FILE);
	std::cout << std::to_string(elements.size()) << " found." << std::endl;

	std::cout << "Reading " << NODE_ORDER << "..." << std::endl;

	std::ifstream fs(NODE_ORDER);
	std::regex regex_name("\"(\\S+\\.\\S+)\"");
	std::smatch match;
	std::string line;
	while (std::getline(fs, line)) {
		std::vector<std::string> lsplit = split_and_trim(line, ',');
		if (!std::regex_search(lsplit[0], match, regex_name)) {
			continue;
		}
		std::string fullname = lower_case(match[1]);

		int n_phases = (lsplit.size() - 3) / 2;
		Element e = elements[fullname];

		if (e.n_buses == 2) {
			for (int i = 0; i < n_phases; i++) {
				std::string source_phase = lsplit[3 + i];
				std::string target_phase = lsplit[3 + i + n_phases];

				if (source_phase == "0" || target_phase == "0") {
					std::cout << "ASDFASDFASDF" << std::endl;
				}

				std::string source = e.bus1 + "." + source_phase;
				std::string target = e.bus2 + "." + target_phase;
				std::string name = e.name + "." + std::to_string(i+1);
				g.new_edge(source, target, name, e.type);
			}
		}
	}

	fs.close();

	g.print_summary("../output.txt");
	g.print_log("../logs.txt");

	return 0;
}