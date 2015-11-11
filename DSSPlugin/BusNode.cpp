#include "stdafx.h"
#include "BusNode.h"

BusNode::BusNode(std::string name, int phase) : m_name(name),m_phase(phase)
{

}


BusNode::~BusNode()
{
}

std::string BusNode::full_name() {
	return m_name + '.' + std::to_string(m_phase);
}