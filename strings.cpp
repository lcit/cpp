#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

auto main() -> int {
    
  std::string s1 = "abc";
  std::string s{"abc"};
  std::cout << s << " len=" << s.length() << std::endl; // abc len=3
  
  std::string s2;
  s2 += "ab";
  s2 += 'c';
  s2 += 100;
  s2 += 0144;
  s2 += 0x64;
  std::cout << s2 << " len=" << s2.length() << std::endl; // abcddd len=6
  
  std::string s3 = "ac";
  s3.insert(1, "b"); // add string
  std::cout << s3 << std::endl; // abc
  s3.insert(1, "xyz", 2); // add substring with len
  std::cout << s3 << std::endl; // axybc
  s3.insert(1, ".-<", 1,1); // add substring with start and len
  std::cout << s3 << std::endl; // a-xybc   
  
  s3.erase(1,3);
  std::cout << s3 << std::endl; // abc 
  
  s3.erase(s3.begin(),s3.begin()+2);
  std::cout << s3 << std::endl; // c 
  
  s3.clear();
  std::cout << s3 << std::endl; // 
  
  s3 = "abc";
  s3.replace(0,3, "ABC");
  std::cout << s3 << std::endl; // ABC
  
  // --- Find ---
  
  s3 = "abcabc";
  std::size_t found = s3.find("abc");
  if(found!=std::string::npos){
    std::cout << found << std::endl; // 0
  }
  
  found = s3.find("abc", 1);
  if(found!=std::string::npos){
    std::cout << found << std::endl; // 3
  }  
  
  found = s3.find("abc", 2);
  if(found!=std::string::npos){
    std::cout << found << std::endl; // 3
  }  

  // --- Streams ---

  std::ostringstream oss;
  oss << 1 << ", ";
  oss << 2 << ", ";
  oss << 3 << ", ";
  std::string out = oss.str();
  std::cout << out << std::endl; // 1, 2, 3, 
  
  std::istringstream iss(out);
  std::string ele;
  while(iss >> ele){
    std::cout << ele << std::endl; // 1, 
                                   // 2, 
                                   // 3, 
  }
  
  std::vector<int> v{1,2,3,4,5};
  std::ostringstream oss2;
  std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(oss2, ","));
  std::cout << oss2.str() << std::endl;
  
  return 0;
}