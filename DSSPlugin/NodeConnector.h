#pragma once
#include "BusNode.h"
class NodeConnector
{
public:
	BusNode* m_node1;
	BusNode* m_node2;

	NodeConnector(BusNode* node1, BusNode* node2);
	~NodeConnector();
};

