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

//#define WORKSPACE "C:/Users/TsunYin/Dropbox/Nurhachi/Engineering/opendss/8500-node"
#define WORKSPACE "E:/Dropbox/Nurhachi/Engineering/opendss/8500-node"

#define NODES_FILE "IEEE8500_EXP_NodeNames.CSV"
#define NODE_ORDER "IEEE8500_EXP_NodeOrder.CSV"
#define ELEMENTS_FILE "IEEE8500_Elements.Txt"

std::map<std::string, BusNode*> get_nodes(std::string filename) {
	std::map<std::string, BusNode*> nodes;
	std::regex regex_obj("(\\S+)\\.(\\d)");
	std::smatch match;

	std::ifstream fs(filename);
	if (fs.is_open())  {
		std::string line;
		while (std::getline(fs, line)) {
			if (std::regex_search(line, match, regex_obj)) {
				std::string name = match[1];
				int phase = stoi(match[2]);
				BusNode* n = new BusNode(name, phase);
				nodes[n->full_name()] = n;
			}
		}
	}
	fs.close();

	return nodes;
}

std::map<std::string, BusElement*> get_elements(std::string filename) {
	std::map<std::string, BusElement*> elements;
	std::regex regex_1bus("\"(\\S+)\\.(\\S+)\"\\s+(\\S+)\\s*$");
	std::regex regex_2bus("\"(\\S+)\\.(\\S+)\"\\s+(\\S+)\\s+(\\S+)\\s*$");
	std::regex regex_3bus("\"(\\S+)\\.(\\S+)\"\\s+(\\S+)\\s+(\\S+)\\s+(\\S+)\\s*$");
	std::smatch match;

	std::ifstream fs(filename);
	if (fs.is_open()) {
		std::string line;
		while (std::getline(fs, line)) {
			BusElement* e;
			if (std::regex_search(line, match, regex_1bus)) {
				e = new BusElement(match[1], match[2], match[3]);
				elements[e->full_name()] = e;
			}
			else if (std::regex_search(line, match, regex_2bus)) {
				e = new BusElement(match[1], match[2], match[3], match[4]);
				elements[e->full_name()] = e;
			}
			else if (std::regex_search(line, match, regex_3bus)) {
				e = new BusElement(match[1], match[2], match[3], match[4], match[5]);
				elements[e->full_name()] = e;
			}
		}
	}
	fs.close();

	return elements;
}

std::vector<NodeConnector*> parse_node_order(std::string filename, std::map<std::string, BusNode*> nodes, std::map<std::string, BusElement*> elements) {
	std::vector<NodeConnector*> edges;
	std::regex regex_name("\"(\\S+\\.\\S+)\"");
	std::smatch match;

	std::ifstream fs(filename);
	if (fs.is_open()) {
		std::string line;
		while (std::getline(fs, line)) {
			std::vector<std::string> lsplit = split(line, ',');
			if (!std::regex_search(lsplit[0], match, regex_name)) {
				continue;
			}

			std::string fullname = match[1];
			int n_conn = (lsplit.size() - 3) / 2;
			if (elements.find(fullname) != elements.end()) {
				std::cout << elements[fullname]->full_name() << std::endl;
			}

			for (int i = 0; i < n_conn; i++) {
				BusNode* node1;
				BusNode* node2;
			}
		}
	}
	fs.close();

	return edges;
}

int main() {
	SetCurrentDirectory(_T(WORKSPACE));

	std::cout << "Reading " << NODES_FILE << "..." << std::endl;
	std::map<std::string, BusNode*> nodes;
	//nodes = get_nodes(NODES_FILE);

	std::cout << "Reading " << ELEMENTS_FILE << "..." << std::endl;
	std::map<std::string, BusElement*> elements;
	elements = get_elements(ELEMENTS_FILE);

	std::cout << "Reading " << NODE_ORDER << "..." << std::endl;
	std::vector<NodeConnector*> edges = parse_node_order(NODE_ORDER, nodes, elements);

	return 0;
}