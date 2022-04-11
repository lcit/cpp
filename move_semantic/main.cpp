#include <cstring>
#include <iostream>

/*
For the copy and move constructors, the compiler provide implicit ones if no copy or move ctors or assignement
operators are defined by the user. 
If you define a copy constructor then there will be no implicit move ctors or move operators.
*/

class String{
	
public:

  // we explicitely provide a default constructor that do not initiate the member variables
  // the compiler otherwise would provide one that initilizes the members with some default values like 0 (I think)
  String() = default;

  // constructor
  String(const char* string){
    std::cout << "String constructor" << std::endl;
    size = strlen(string);
    data = new char[size];
    memcpy(data, string, size);
  }	

  // copy constructor
  String(const String& string){
    std::cout << "String copy constructor";
    size = string.size;
    if(data){
      std::cout << " + delete data";
      delete data;
    }
    data = new char[size];
    memcpy(data, string.data, size);		
    std::cout << std::endl;
  }

  // copy assignement operator
  // a string "leo" is a const char*. If we assign string = "leo"
  // we call the String constructor first then the this copy operator!!!
  String& operator=(const String& string){
    std::cout << "String copy assignement operator";
    size = string.size;
    if(data){
      std::cout << " + delete data";
      delete data;
    }
    data = new char[size];
    memcpy(data, string.data, size);		
    std::cout << std::endl;
  }

  // copy assignement operator 2
  String& operator=(const char* string){
    std::cout << "String copy assignement operator";
    size = strlen(string);
    if(data){
      std::cout << " + delete data";
      delete data;
    }
    data = new char[size];
    memcpy(data, string, size);		
    std::cout << std::endl;
  }

  String& operator=(String&& string){
    std::cout << "String move assignement operator";
    size = string.size;
    if(data){
      std::cout << " + delete data";
      delete data;
    }
    data = string.data;

    string.data = nullptr;
    string.size = 0;

    std::cout << std::endl;
  }	
	
  String(String&& string){
    std::cout << "String move constructor";
    size = string.size;
    if(data){
      std::cout << " + delete data";
      delete data;
    }
    data = string.data;

    string.data = nullptr;
    string.size = 0;

    std::cout << std::endl;
  }	
	
	//String(String&& string) = default;
	//String(String&& string) = delete;
	
  void print(){
    for(int i=0; i<size; ++i){
      std::cout << data[i];
    }
    std::cout << std::endl;
  }
	
private:
  char* data = nullptr;
  std::size_t size = 0;
};

class Entity{
	
public:
  String m_string;

  Entity() = default;

  /*
  We use Entity as:

  String s("leo"); // this calls String constructor
  Entity e(s); // more explanation here below...
  */

  /*
  // (1)
  Entity(String string)  // makes a copy
    : m_string(string){ // makes another copy
    std::puts(__PRETTY_FUNCTION__);		
  }
  */
  /*
  // (2)
  Entity(String& string) // nothing
    : m_string(string){ // makes a copy
    std::puts(__PRETTY_FUNCTION__);
  }
  */
  /*
  // (3)
  Entity(String& string) // nothing
    : m_string(std::move(string)){ // makes a move
    std::puts(__PRETTY_FUNCTION__);
  }
  */
  /*
  // (4)
  Entity(const String& string) // nothing
    : m_string(string){ // makes a copy
    std::puts(__PRETTY_FUNCTION__);
  }
  */
  /*
  // (5)
  Entity(const String& string) // nothing
    : m_string(std::move(string)){ // makes a copy!!!
    std::puts(__PRETTY_FUNCTION__);		
  }
  */
  /*
  // (6)
  Entity(String&& string) // this does not work unless Entity e(std::move(s));
    : m_string(string){ // makes a copy
    std::puts(__PRETTY_FUNCTION__);
  }	
  */
  /*
  // (7)
  Entity(String&& string) // this does not work unless Entity e(std::move(s));
    : m_string(std::move(string)){ // makes a move
    std::puts(__PRETTY_FUNCTION__);
  }
  */
  /*
  // (7)
  Entity(const String&& string) // same as above
    : m_string(string){
    std::puts(__PRETTY_FUNCTION__);			
  }
  */


  // We want to copy the passed object when std::move is not used and moved otherwise. Thsi is how we decide when to move owenership of the data.

  // Perfect forwarding replaces exactly the behaviour of overloaded ctors (4) (7) but using only one function.

  template<typename T>
  Entity(T&& string)
    : m_string(std::forward<T>(string)){ // makes a copy if Entity e(s);
                                         // makes move if Entity e(std::move(s));
    std::puts(__PRETTY_FUNCTION__);
  }	
	
  void print(){
    std::cout << "Entity print: " << std::endl; 
    m_string.print();
    std::cout << std::endl;
  }	
};

int main(){
	
  String s("leo"); // calls constructor
  //Entity e(s);
  Entity e(std::move(s));
  e.print();





  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;


  
  // the following is with perfect forwarding implementation
  
  Entity e2("e2"); // String ctor
  e2.print();
  
  Entity e3(String("e3")); // String ctor + move ctor
  e3.print();
  
  Entity e4; 
  e4 = "e4"; // String ctor + move assignement
  e4.print();
  
  Entity e5;
  e5 = String("e5"); // String ctor + move ctor + move assignement
  e5.print();  
  
  Entity e6;
  String s2("e6"); // String ctor
  e6 = s2; // copy ctor + move assignement
  e6.print(); 

  Entity e7;
  String s3("e7"); // String ctor
  e7 = std::move(s3); // move ctor + move assignement
  e7.print(); 
	
  return 0;
}