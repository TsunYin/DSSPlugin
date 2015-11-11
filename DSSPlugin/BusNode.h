#pragma once
#include <vector>
#include <string>
class BusNode
{
public:
	std::vector<BusNode> m_connections;
	std::string m_name;
	int m_phase;

	BusNode(std::string name, int phase);
	~BusNode();

	std::string full_name();
};