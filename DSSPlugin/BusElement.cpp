#include "stdafx.h"
#include "BusElement.h"


BusElement::BusElement(std::string type, std::string name, std::string bus1) : m_type(type), m_name(name), m_bus1(bus1)
{
}

BusElement::BusElement(std::string type, std::string name, std::string bus1, std::string bus2) : m_type(type), m_name(name), m_bus1(bus1), m_bus2(bus2)
{
}

BusElement::BusElement(std::string type, std::string name, std::string bus1, std::string bus2, std::string bus3) : m_type(type), m_name(name), m_bus1(bus1), m_bus2(bus2), m_bus3(bus3)
{
}

std::string BusElement::full_name() {
	return m_type + '.' + m_name;
}

BusElement::~BusElement()
{
}