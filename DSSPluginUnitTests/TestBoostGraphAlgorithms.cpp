#include "stdafx.h"
#include "CppUnitTest.h"

#include <utility>                   // for std::pair
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/floyd_warshall_shortest.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace DSSPluginUnitTests
{
	TEST_CLASS(TestBoostGraphAlgorithms)
	{
	public:

		TEST_METHOD(test_boost_dijkstra)
		{
			using namespace boost;
			typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int> > Graph;
			typedef graph_traits<Graph>::vertex_descriptor Vertex;
			typedef std::pair<int, int> E;

			E edges[] = { E(0,2), E(1,1), E(1,3), E(1,4), E(2,1), E(2,3), E(3,4), E(4,0), E(4,1) };
			int weights[] = { 1, 2, 1, 2, 7, 3, 1, 1, 1 };
			Graph g(edges, edges + sizeof(edges) / sizeof(E), weights, 5);

			Assert::AreEqual(num_vertices(g), size_t(5));
			Assert::AreEqual(num_edges(g), size_t(9));

			// vector for storing distance property
			std::vector<int> d(num_vertices(g));

			// get the first vertex (vertex 0)
			Vertex s = *(vertices(g).first);
			// invoke variant 2 of Dijkstra's algorithm
			dijkstra_shortest_paths(g, s, distance_map(&d[0]));

			int expected_distances[] = { 0, 6, 1, 4, 5 };
			
			int i = 0;
			graph_traits<Graph>::vertex_iterator vi;
			for (vi = vertices(g).first; vi != vertices(g).second; ++vi) {
				Assert::AreEqual(d[*vi], expected_distances[i]);
				i++;
			}
		}

		TEST_METHOD(test_boost_apsp)
		{
			using namespace boost;
			typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int> > Graph;
			typedef graph_traits<Graph>::vertex_descriptor Vertex;
			typedef std::pair<int, int> E;

			E edges[] = {
				E(0, 1),
				E(1, 2), E(1, 3),
				E(2, 0), E(2, 3),
				E(3, 0), E(3, 1),
			};
			int weights[] = {
				3,
				12, 5,
				4, -1,
				2, -4,
			};

			Graph g(edges, edges + sizeof(edges) / sizeof(E), weights, 4);
			int d[4][4];
			floyd_warshall_all_pairs_shortest_paths(g, d);

			int expected_answer[][4] = { 
				{0, 3, 15, 8},
				{7, 0, 12, 5},
				{1, -5, 0, -1},
				{2, -4, 8, 0}
			};

			for (int r = 0; r < 4; r++) {
				for (int c = 0; c < 4; c++) {
					Assert::AreEqual(d[r][c], expected_answer[r][c]);
				}
			}
		}

		TEST_METHOD(test_boost_multiple_graphs) {
			using namespace boost;
			typedef adjacency_list<vecS, vecS, bidirectionalS, no_property, property<edge_weight_t, int> > Graph;
			typedef graph_traits<Graph>::vertex_descriptor Vertex;
			typedef std::pair<int, int> E;

			E edges[] = {
				E(0, 1), E(1, 2), E(2, 0),
				E(3, 4), E(4, 5), E(5, 0)
			};
			int weights[] = { 1, 2, 3, 4, 5, 6 };

			Graph g(edges, edges + sizeof(edges) / sizeof(E), weights, 6);
			int d[6][6];
			floyd_warshall_all_pairs_shortest_paths(g, d);

			/*
			int expected_answer[][4] = {
			{ 0, 3, 15, 8 },
			{ 7, 0, 12, 5 },
			{ 1, -5, 0, -1 },
			{ 2, -4, 8, 0 }
			};
			*/

			for (int r = 0; r < 6; r++) {
				for (int c = 0; c < 6; c++) {
					//Assert::AreEqual(d[r][c], expected_answer[r][c]);
					Logger::WriteMessage(std::to_string(d[r][c]).data());
				}
			}
		}
	};
}