#include <iostream>
#include <chrono>
#include <numeric>
#include <array>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>

template<typename TimeT = std::chrono::milliseconds>
struct measure {
    template<typename F, typename ...Args>
    static typename TimeT::rep run(F&& func, Args&&... args) {
        auto start = std::chrono::steady_clock::now();
        std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
        auto duration = std::chrono::duration_cast<TimeT>(std::chrono::steady_clock::now() - start);
        return duration.count();
    }
};

template<size_t N>
struct mean_stddev {
    template<typename F, typename ...Args>
    static auto run(F&& func, Args&&... args){
        std::array<double, N> buffer;
        for(auto& buf:buffer)
            buf = std::forward<decltype(func)>(func)(std::forward<Args>(args)...);
        auto sum = std::accumulate(std::begin(buffer), std::end(buffer), 0.0);
        auto mean = sum/buffer.size();
        std::array<double, N> diff;
        std::transform(std::begin(buffer), std::end(buffer), std::begin(diff), [mean](auto x) { return x - mean; });
        auto sq_sum = std::inner_product(std::begin(diff), std::end(diff), std::begin(diff), 0.0);
        auto stddev = std::sqrt(sq_sum/buffer.size());
        return std::make_pair(mean,stddev);
    }
};

struct A{
  bool active = true;
};

auto test_fn1(){
  
  std::vector<bool> v(10000);
  for(int i=0; i<10000; ++i){
    if(i>20 && i<40)
      v[i] = true;
    else
      v[i] = false;
  }
  
  auto f = [v](){
    int count = 0;
    for(int i=0; i<v.size(); ++i){
      if(!v[i]){
        count++;
      }
    }
  };
  
  return measure<>::run(f);
}

auto test_fn2(){
  
  std::vector<int> v(10000);
  for(int i=0; i<10000; ++i){
    if(i>20 && i<40)
      v[i] = 1;
    else
      v[i] = 0;
  }
  
  auto f = [v](){
    int count = 0;
    for(int i=0; i<v.size(); ++i){
      if(!v[i]){
        count++;
      }
    }
  };
  
  return measure<>::run(f);
}

auto test_fn3(){
  
  std::vector<A> v2(10000);
  for(int i=0; i<10000; ++i){
    if(i>20 && i<40)
      v2[i].active = true;
    else
      v2[i].active = false;
  }
  
  auto f = [v2](){
    int count = 0;
    for(int i=0; i<v2.size(); ++i){
      if(!v2[i].active){
        count++;
      }
    }
  };
  
  return measure<>::run(f);
}

auto main() -> int
{
  const int times = 1000;
  
  std::string name = "test_fn1";
  auto res = mean_stddev<times>::run(test_fn1);
  auto mean = res.first;
  auto std  = res.second;
  std::cout << name << ":" 
            << std::setw(55-name.length()) << mean << "(+-" << std::setprecision(6) 
            << std::setw(8) << std << ") [ms]" 
            << std::endl;  
    
  name = "test_fn2";
  res = mean_stddev<times>::run(test_fn2);
  mean = res.first;
  std  = res.second;
  std::cout << name << ":" 
            << std::setw(55-name.length()) << mean << "(+-" << std::setprecision(6) 
            << std::setw(8) << std << ") [ms]" 
            << std::endl; 
            
  name = "test_fn3";
  res = mean_stddev<times>::run(test_fn3);
  mean = res.first;
  std  = res.second;
  std::cout << name << ":" 
            << std::setw(55-name.length()) << mean << "(+-" << std::setprecision(6) 
            << std::setw(8) << std << ") [ms]" 
            << std::endl;             
  
  return 0;
}