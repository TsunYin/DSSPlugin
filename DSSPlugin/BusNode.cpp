#include "stdafx.h"
#include "BusNode.h"

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

BusNode::BusNode(std::string name, int phase) : m_name(name),m_phase(phase)
{
	
}


BusNode::~BusNode()
{
}

std::string BusNode::full_name() {
	return m_name + '.' + std::to_string(m_phase);
}