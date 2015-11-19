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

		TEST_METHOD(test_dsgraph_new_edge)
		{
			std::vector<std::string> names = { "a", "b", "c", "d", "e" };
			std::vector<int> phases = { 1,2,3,4,5 };

			DistributionSystemGraph graph(5);
			graph.set_nodes(names, phases);

			graph.new_edge("a", "b", "a-b", "first");
			graph.new_edge("b", "c", "b-c", "second");
			graph.new_edge("c", "d", "c-d", "third");
			graph.new_edge("d", "e", "d-e", "fourth");
			graph.new_edge("e", "a", "e-a", "fifth");
			graph.new_edge("b", "d", "b-d", "sixth");
			graph.new_edge("b", "e", "b-e", "seventh");

			Assert::AreEqual(std::string("a-b"), graph.get_edge("a-b").name);
			Assert::AreEqual(std::string("b-c"), graph.get_edge("b-c").name);
			Assert::AreEqual(std::string("c-d"), graph.get_edge("c-d").name);
			Assert::AreEqual(std::string("d-e"), graph.get_edge("d-e").name);
			Assert::AreEqual(std::string("e-a"), graph.get_edge("e-a").name);
			Assert::AreEqual(std::string("b-d"), graph.get_edge("b-d").name);
			Assert::AreEqual(std::string("b-e"), graph.get_edge("b-e").name);

			Assert::AreEqual(std::string("first"), graph.get_edge("a-b").type);
			Assert::AreEqual(std::string("second"), graph.get_edge("b-c").type);
			Assert::AreEqual(std::string("third"), graph.get_edge("c-d").type);
			Assert::AreEqual(std::string("fourth"), graph.get_edge("d-e").type);
			Assert::AreEqual(std::string("fifth"), graph.get_edge("e-a").type);
			Assert::AreEqual(std::string("sixth"), graph.get_edge("b-d").type);
			Assert::AreEqual(std::string("seventh"), graph.get_edge("b-e").type);

			Assert::AreEqual(std::string("a"), graph.get_edge("a-b").source);
			Assert::AreEqual(std::string("b"), graph.get_edge("b-c").source);
			Assert::AreEqual(std::string("c"), graph.get_edge("c-d").source);
			Assert::AreEqual(std::string("d"), graph.get_edge("d-e").source);
			Assert::AreEqual(std::string("e"), graph.get_edge("e-a").source);
			Assert::AreEqual(std::string("b"), graph.get_edge("b-d").source);
			Assert::AreEqual(std::string("b"), graph.get_edge("b-e").source);

			Assert::AreEqual(std::string("b"), graph.get_edge("a-b").target);
			Assert::AreEqual(std::string("c"), graph.get_edge("b-c").target);
			Assert::AreEqual(std::string("d"), graph.get_edge("c-d").target);
			Assert::AreEqual(std::string("e"), graph.get_edge("d-e").target);
			Assert::AreEqual(std::string("a"), graph.get_edge("e-a").target);
			Assert::AreEqual(std::string("d"), graph.get_edge("b-d").target);
			Assert::AreEqual(std::string("e"), graph.get_edge("b-e").target);
		}
	};
}