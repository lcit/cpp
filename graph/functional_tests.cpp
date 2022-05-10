#include <iostream>
#include <stdexcept>
#include <sstream>

#include "graph.hpp"

void _test(const bool& pred, const char *file, int line)
{ 
  if(!pred)
  {
    std::stringstream ss;
    ss << "Test failed! " << file << " line " << line;
    throw std::runtime_error(ss.str()); 
  }
}
#define test(arg) _test(arg, __FILE__, __LINE__)

void create_manipulate_graph()
{
  Graph g(6);
  g.add_edge(0,1,1);
  g.add_edge(0,2,1);
  g.add_edge(2,1,2);
  g.add_edge(1,3,3);
  g.add_edge(1,4,4);
  g.add_edge(3,5,5);
  g.add_edge(4,5,2);
  
  test(g.n_vertices()==6);
  test(g.n_edges()==7);
  
  g.remove_vertex(3);
  
  test(g.n_vertices()==5);
  test(g.n_edges()==5);
  
  g.remove_edge(4,5);
  
  test(g.n_vertices()==4);
  test(g.n_edges()==4);  
}

void shortest_path_graph()
{
  Graph g(6);
  g.add_edge(0,1,1);
  g.add_edge(0,2,1.1);
  g.add_edge(2,1,2);
  g.add_edge(1,3,3);
  g.add_edge(1,4,4);
  g.add_edge(3,5,5);
  g.add_edge(4,5,2);
  g.add_edge(2,3,0);
 
  std::unordered_map<uint32_t, std::vector<uint32_t>> shortest_path_tree = g.all_pairs_shortest_path(1);
  
  std::unordered_map<uint32_t, std::vector<uint32_t>> shortest_path_tree_truth;
  shortest_path_tree_truth[0].push_back(1);
  shortest_path_tree_truth[0].push_back(0);
  
  shortest_path_tree_truth[1].push_back(1);
  
  shortest_path_tree_truth[2].push_back(1);
  shortest_path_tree_truth[2].push_back(2);
  
  shortest_path_tree_truth[3].push_back(1);
  shortest_path_tree_truth[3].push_back(2);
  shortest_path_tree_truth[3].push_back(3);
  
  shortest_path_tree_truth[4].push_back(1);
  shortest_path_tree_truth[4].push_back(4);
  
  shortest_path_tree_truth[5].push_back(1);
  shortest_path_tree_truth[5].push_back(4); 
  shortest_path_tree_truth[5].push_back(5);
  /*
  for(const auto& p : shortest_path_tree_truth)
  {
    std::cout << "Destination " << p.first << "\n";
    for(const auto& ele : p.second)
    {
      std::cout << "\t " << ele << ", ";
    }
    std::cout << std::endl;
  }
  
  std::cout << "----" << std::endl;
  for(const auto& p : shortest_path_tree)
  {
    std::cout << "Destination " << p.first << "\n";
    for(const auto& ele : p.second)
    {
      std::cout << "\t " << ele << ", ";
    }
    std::cout << std::endl;
  }  
  */
  test(shortest_path_tree_truth.size()==shortest_path_tree.size());
  for(int i=0; i<5; ++i)
  {
    test(std::equal(shortest_path_tree_truth[i].begin(), 
                    shortest_path_tree_truth[i].end(),
                    shortest_path_tree[i].begin()));
  }
}

auto main() -> int
{
  
  create_manipulate_graph();
  shortest_path_graph();
  
  std::cout << "All good!" << std::endl;

  return 0;
}