#include <cstdio>
#include <vector>
#include <iostream>
#include <cstring>

// template variable C++14
// constexpr evaluates the value at compile time.
template <typename T>
constexpr T pi = T(3.1415926535897932385);

// Template alias
// usage: vec_t<std::string>   vs;
template <typename T> 
using vec_t = std::vector<T>;


template<typename T, size_t S>
class Array {
private:
  T* data = nullptr;
public:
  Array(const T init_val){
    data = new T[S];
  }
  ~Array(){
    delete[] data;
  }
  
  // since S is known at compile time, it is good to expose size() at compile time too!
  constexpr size_t size() const { return S; }
  
  const T& operator[](const size_t index) const {
    //assert()
    return data[index];
  }
  
  T& operator[](const size_t index){
    //assert()
    return data[index];
  }  
  // and so on...
};

// template template parameter
template <typename T, template <typename, typename> class Cont >
void print_container(Cont<T, std::allocator<T> > container) 
{
    for (const T& v : container)
        std::cout << v << ' ';
    std::cout << '\n';
}


/*
  Factorial at compile time!
*/
// we can compute math at compile time!
// usage: static_assert(fact<2>::value == 2);
template<size_t T> struct fact;

template<> // Explicit specialization
struct fact<0>
{
    constexpr static auto value = 1;
};

template<size_t T>
struct fact
{
    constexpr static auto value = T * fact<T - 1>::value;   
};


auto main() -> int {
  std::cout << pi<int> << std::endl;
  std::cout << pi<double> << std::endl;
  std::cout << fact<3>::value << std::endl;
  
  Array<int, 10> a(2);
  a[0] = 1;
  a[1] = 2;
  std::cout << a.size() << std::endl;
  std::cout << a[0] << std::endl;
  std::cout << a[1] << std::endl;
  
  std::vector<float> v(3);
  print_container(v);
}

