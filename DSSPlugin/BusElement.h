#pragma once
#include "BusNode.h"
class BusElement
{
public:
	std::string m_type;
	std::string m_name;
	std::string m_bus1;
	std::string m_bus2;
	std::string m_bus3;

	BusElement(std::string type, std::string name, std::string bus1);
	BusElement(std::string type, std::string name, std::string bus1, std::string bus2);
	BusElement(std::string type, std::string name, std::string bus1, std::string bus2, std::string bus3);
	~BusElement();
	std::string full_name();
};

