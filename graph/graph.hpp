#pragma once

#include <iostream>
#include <sstream>
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <limits>
#include <limits>

uint64_t pair_indexes(uint32_t a, uint32_t b)
{
  return a >= b ? a * a + a + b : a + b * b;
}

struct Vertex
{
  bool enabled = true;
};

struct Edge
{
  uint32_t u, v;
  float weight;
  bool enabled = true;
  Edge(uint32_t u, uint32_t v, float weight=1) 
    : u(u), v(v), weight(weight) {}
  Edge() = default; // for unordered_map[]
};

class Graph
{
public:
  std::vector<Vertex> vertices;
  std::unordered_map<uint64_t, Edge> edges;
  std::vector<std::vector<uint32_t>> adjacency_list;
  size_t _n_vertices=0, _n_edges=0;
  
  Graph(const size_t n=0)
  {
    _n_vertices = n;
    adjacency_list.resize(_n_vertices);
    vertices.resize(_n_vertices);
  }
  
  Graph() = default;
  
  void disable_vertex(const uint32_t idx)
  {
    vertices[idx].enabled = false;
    _n_vertices--;    
  }
  
  void disable_edge(const uint64_t key)
  {
    edges[key].enabled = false;
    _n_edges--;
  }  
  
  void add_vertex()
  {
    _n_vertices++;
    adjacency_list.resize(_n_vertices);
    vertices.resize(_n_vertices);
  }
  
  void remove_vertex(const uint32_t idx)
  {
    disable_vertex(idx);
    
    auto keys_adj_edges = find_adjacent_edges(idx);
    for(auto key : keys_adj_edges)
    {
      disable_edge(key);
    }
  }
  
  void remove_edge(const uint32_t u, const uint32_t v)
  {
    auto key = pair_indexes(u,v);
    if(edges.find(key)!=edges.end())
    {
      disable_edge(key);
      
      // remove isolated vertices
      if(find_adjacent_edges(u).size()==0)
        disable_vertex(u);
      if(find_adjacent_edges(v).size()==0)
        disable_vertex(v);
    }
  }
  
  std::pair<bool, uint64_t> find_edge(const uint32_t u, const uint32_t v, bool directed=false)
  {
    uint64_t key = pair_indexes(u, v);
    if(edges.find(key)!=edges.end())
    {
      return std::make_pair(true, key);
    }
    else
    {
      if(!directed)
      {
        key = pair_indexes(v, u);
        if(edges.find(key)!=edges.end())
        {
          return std::make_pair(true, key);
        }       
      }
    }
    return std::make_pair(false, 0);
  }
  
  std::vector<uint64_t> find_adjacent_edges(const uint32_t u, bool directed=false)
  { 
    std::vector<uint64_t> keys;
    uint64_t key;
    for(const uint32_t v : adjacency_list[u])
    {
      key = pair_indexes(u,v);
      if(edges.find(key) != edges.end())
      {
        if(edges[key].enabled)       
          keys.push_back(key);
      }
      else
      {
        if(!directed)
        {
          key = pair_indexes(v,u);
          if(edges.find(key) != edges.end() && edges[key].enabled)
            keys.push_back(key);  
        }
      }
    }   
    return keys;
  }
  
  std::vector<uint32_t> find_adjacent_vertices(const uint32_t u, bool directed=false)
  { 
    return adjacency_list[u];
  }  
  
  void add_edge(const uint32_t u, const uint32_t v, const float weight=1)
  {
    if(u>=_n_vertices || v>=_n_vertices)
    {
      std::stringstream ss;
      ss << "Vertex " << u << " or " << v << " does not exist!";
      throw std::invalid_argument(ss.str());
    }
    _n_edges++;
    edges[pair_indexes(u,v)] = Edge(u,v,weight);
    
    adjacency_list[u].push_back(v);
    adjacency_list[v].push_back(u);
  }
  
  uint32_t n_vertices() const
  {
    return _n_vertices;
  }
  
  uint32_t n_edges() const
  {
    return _n_edges;
  }
  
  uint32_t _min_vertex_shortest_path(std::unordered_map<uint32_t, float> dist,
                                     std::vector<int> visited)
  {
    float min_dist = std::numeric_limits<float>::max();
    uint32_t min_vertex;
 
    for(const auto& p : dist)
    {
        if(visited[p.first]==0 && dist[p.first] <= min_dist)
        {
          min_dist = dist[p.first];
          min_vertex = p.first;
        }
    }
    return min_vertex;
  }
  
  //Dijkstra
  std::unordered_map<uint32_t, std::vector<uint32_t>> 
  all_pairs_shortest_path(const uint32_t source)
  {
    std::unordered_map<uint32_t, std::vector<uint32_t>> shortest_path_tree;
    std::unordered_map<uint32_t, float> dist;
    std::vector<int> visited(vertices.size(), 0);
    
    for(uint32_t u=0; u<vertices.size(); ++u)
    {
      if(vertices[u].enabled)
      {
        dist[u] = std::numeric_limits<float>::max();
      }
    }
    dist[source] = 0;
    shortest_path_tree[source].push_back(source);
    
    uint32_t curr;
    for(size_t i=0; i<_n_vertices-1; ++i)
    {
      curr = _min_vertex_shortest_path(dist, visited);
      visited[curr] = 1;
      
      auto adj_vertices = find_adjacent_vertices(curr);
      for(const uint32_t dest : adj_vertices)
      {
        if(visited[dest]==0)
        {
          auto key_s = find_edge(curr, dest);
          if(key_s.first)
          {
            float next_dist = dist[curr] + edges[key_s.second].weight;
            if(next_dist < dist[dest])
            {
              dist[dest] = next_dist;
              
              auto path = shortest_path_tree[curr];
              path.push_back(dest);
              shortest_path_tree[dest] = path;
            }
          }
        }
      }
    }
    return shortest_path_tree;
  }
  
};