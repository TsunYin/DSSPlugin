#include "stdafx.h"
#include "CppUnitTest.h"

#include <utility>                   // for std::pair
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace DSSPluginUnitTests
{
	TEST_CLASS(TestBoostGraphCreate)
	{
	public:

		TEST_METHOD(test_adjacency_list_basic)
		{
			using namespace boost;
			typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;

			//==================================
			//	Graph Instantiation
			//==================================

			// Make convenient labels for the vertices
			enum { A, B, C, D, E, N };
			const int num_vertices = N;
			const char* name = "ABCDE";

			// writing out the edges in the graph
			typedef std::pair<int, int> Edge;
			Edge edge_array[] =
			{ Edge(A,B), Edge(A,D), Edge(C,A), Edge(D,C), Edge(C,E), Edge(B,D), Edge(D,E) };
			const int num_edges = sizeof(edge_array) / sizeof(edge_array[0]);

			// declare graph object
			// add the edges to the graph 
			Graph g(edge_array, edge_array + sizeof(edge_array) / sizeof(Edge), num_vertices);

			Assert::AreEqual(g.m_edges.size(), std::size_t(7));


			//==================================
			//	Accessing the Vertex Set
			//==================================
			typedef graph_traits<Graph>::vertex_descriptor Vertex;

			// get the property map for vertex indices
			typedef property_map<Graph, vertex_index_t>::type IndexMap;
			IndexMap index = get(vertex_index, g);

			typedef graph_traits<Graph>::vertex_iterator vertex_iter;

			std::pair<vertex_iter, vertex_iter> vp;
			for (vp = vertices(g); vp.first != vp.second; ++vp.first) {
				Vertex v = *vp.first;
				//Logger::WriteMessage(std::to_string(index[*vp.first]).data());
			}

			//==================================
			//	Accessing the Edge Set
			//==================================
			graph_traits<Graph>::edge_iterator ei, ei_end;
			for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
				//Logger::WriteMessage(std::to_string(index[source(*ei, g)]).data());
				//Logger::WriteMessage(std::to_string(index[target(*ei, g)]).data());
			}

			Assert::AreEqual(boost::num_vertices(g), size_t(5));
			Assert::AreEqual(boost::num_edges(g), size_t(7));
		}

		TEST_METHOD(test_adjacency_list_properties)
		{
			using namespace boost;

			// Define custom properties
			struct CustomVertex {
				std::string name;
				int age;
			};

			typedef adjacency_list<vecS, vecS, bidirectionalS, CustomVertex> Graph;
			typedef std::pair<int, int> Edge;
			Edge edge_array[] = { Edge(0,1), Edge(0,3), Edge(2,0), Edge(3,2), Edge(2,5), Edge(1,3), Edge(5,4) };
			Graph g(edge_array, edge_array + sizeof(edge_array) / sizeof(Edge), 6);

			auto v = get(vertex_bundle, g);
			v[0].name = "Reimu";
			v[1].name = "Marisa";
			v[2].name = "Youmu";
			v[3].name = "Sakuya";
			v[4].name = "Sanae";
			v[5].name = "Reisen";
			v[0].age = 17;
			v[1].age = 19;
			v[2].age = 22;
			v[3].age = 21;
			v[4].age = 20;
			v[5].age = 25;

			Assert::AreEqual(num_vertices(g), size_t(6));

			int i = 0;
			std::string expected_name[] = { "Reimu", "Marisa", "Youmu", "Sakuya", "Sanae", "Reisen" };
			int expected_age[] = { 17, 19, 22, 21, 20, 25 };

			auto name = get(&CustomVertex::name, g);
			auto age = get(&CustomVertex::age, g);
			for (int i = 0; i < 5; i++) {
				Assert::AreEqual(name[i], expected_name[i]);
				Assert::AreEqual(age[i], expected_age[i]);
				i++;
			}
		}
	};
}