#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Vertex
{
  float x, y, z, w;
  
  Vertex(float x=-1, float y=-1, float z=-1, float w=-1) 
    : x(x), y(y), z(z), w(w) {}
  
  friend std::ostream& operator<<(std::ostream& os, const Vertex& x)
  {
      os << "x=" << x.x << " y=" << x.y << " z=" << x.z << " w=" << x.w;
      return os;
  }
};

struct TexCoord
{
  float u, v, w;
  
  TexCoord(float u=0, float v=0, float w=0) 
    : u(u), v(v), w(w) {}  
    
  friend std::ostream& operator<<(std::ostream& os, const TexCoord& x)
  {
      os << "u=" << x.u << " v=" << x.v << " w=" << x.w;
      return os;
  }    
};

struct VertexNormal 
{
  float x, y, z;
  
  VertexNormal(float x=0, float y=0, float z=0) 
    : x(x), y(y), z(z) {}   

  friend std::ostream& operator<<(std::ostream& os, const VertexNormal& x)
  {
      os << "x=" << x.x << " y=" << x.y << " z=" << x.z;
      return os;
  }   
};

auto main(int argc, char* argv[]) -> int 
{
  
  std::vector<Vertex> vertexes;
  std::vector<TexCoord> texture_coords;
  std::vector<VertexNormal> vertex_normals;
  
  std::ifstream file;
  file.exceptions(std::ifstream::badbit);
  try
  {
    file.open("capsule.obj");
    std::string line, sub;
    float x, y, z, w, u, v;
    while(std::getline(file, line))
    {
      std::stringstream ss(line);
      std::getline(ss, sub, ' ');
      if(sub=="v")
      {
        std::getline(ss, sub, ' '); x = std::stof(sub);
        std::getline(ss, sub, ' '); y = std::stof(sub);
        std::getline(ss, sub, ' '); z = std::stof(sub);
        std::getline(ss, sub, ' '); w = sub.empty() ? 1.0 : std::stof(sub);  
        vertexes.emplace_back(x, y, z, w);
      }
      else if(sub=="vt")
      {
        std::getline(ss, sub, ' '); u = std::stof(sub);
        std::getline(ss, sub, ' '); v = sub.empty() ? 0.0 : std::stof(sub);
        std::getline(ss, sub, ' '); w = sub.empty() ? 0.0 : std::stof(sub);      
        texture_coords.emplace_back(u, v, w);
      }
      else if(sub=="vn")
      {
        std::getline(ss, sub, ' '); x = std::stof(sub);
        std::getline(ss, sub, ' '); y = std::stof(sub);
        std::getline(ss, sub, ' '); z = std::stof(sub);  
        vertex_normals.emplace_back(x, y, z);        
      }
    }      
  }
  catch (const std::ifstream::failure& e) 
  {
    std::cout << "\nException opening/reading file";
  }

  file.close();
  
  std::cout << vertexes.size() << " " << texture_coords.size() << " " << vertex_normals.size() << '\n' << std::endl;
  
  std::cout << "veritices \n";
  for(int i=0; i<5; ++i)
  {
    std::cout << vertexes[i] << '\n';
  }
  std::cout << std::endl;
  
  std::cout << "Texture coordinates \n";
  for(int i=0; i<5; ++i)
  {
    std::cout << texture_coords[i] << '\n';
  }
  std::cout << std::endl;
  
    std::cout << "Vertex normals \n";
  for(int i=0; i<5; ++i)
  {
    std::cout << vertex_normals[i] << '\n';
  }
  std::cout << std::endl;

  return 0;
}