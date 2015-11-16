#include "stdafx.h"
#include "CppUnitTest.h"

#include "../DSSPlugin/DistributionSystemGraph.cpp"
#include <string>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DSSPluginUnitTests
{
	TEST_CLASS(TestDistributionSystemGraph)
	{
	public:

		TEST_METHOD(test_dsgraph_get_set_nodes)
		{
			std::vector<std::string> names = { "a", "b", "c", "d", "e" };
			std::vector<int> phases = { 9,8,7,6,5 };

			DistributionSystemGraph graph(5);

			graph.set_nodes(names, phases);
			
			Assert::AreEqual(5, graph.num_nodes());

			Assert::AreEqual(std::string("a"), graph.get_node("a").name);
			Assert::AreEqual(std::string("b"), graph.get_node("b").name);
			Assert::AreEqual(std::string("c"), graph.get_node("c").name);
			Assert::AreEqual(std::string("d"), graph.get_node("d").name);
			Assert::AreEqual(std::string("e"), graph.get_node("e").name);

			Assert::AreEqual(0, graph.get_node("a").index);
			Assert::AreEqual(1, graph.get_node("b").index);
			Assert::AreEqual(2, graph.get_node("c").index);
			Assert::AreEqual(3, graph.get_node("d").index);
			Assert::AreEqual(4, graph.get_node("e").index);
			
			Assert::AreEqual(9, graph.get_node("a").phase);
			Assert::AreEqual(8, graph.get_node("b").phase);
			Assert::AreEqual(7, graph.get_node("c").phase);
			Assert::AreEqual(6, graph.get_node("d").phase);
			Assert::AreEqual(5, graph.get_node("e").phase);
		}
	};
}