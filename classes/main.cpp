#include <iostream>

class Abstract {
  // if not specified, all members are private
private: 
  // members cannot be accessed (or viewed) from outside the class
protected:
  // members cannot be accessed from outside the class, however, they can be accessed in inherited classes.
public:
  // members are accessible from outside the class
  
  /* This is a pure virtual function. 
     A class that has a pure virtual function is an abstract class.
     When an object inherit from Abstract, it has to proved an implementation for the pure virtual functions.
  */
  virtual void e() = 0;
  
  void f(int a) {
    std::cout << "f() Abstract: hello " << a << std::endl;
    
  }
  
  // this virtual function does nothave to be overridden.
  virtual void g(int a) {
    std::cout << "g() Abstract: hello " << a << std::endl;
  }
};

class A : public Abstract {
public:
  int a;
  double b;
  int c;
  int d;

  A(int a_, double b_=1) : a(a_),   // a is initialized first becase int a; comes before double b; and int c; and so on
                           b(b_+a), // this is therefore valid
                           c(d),    // compiles but c is initialized to some random value
                           d(a_)
  {
    std::cout << "a=" << a << " b=" << b << " c=" << c << " d=" << d << std::endl;
  }
  
  // This function overrides Abstract::e().
  // The override specificer will check that the signarue of A::e() is the same of Abstarct::e().
  void e() override 
  {
  }

  void f(int a) {
      std::cout << "f() hello " << a << std::endl;
  }
  
  void g(int a) override {
    std::cout << "g() hello " << a << std::endl;
  }

  inline    // the call to e() is replaced with the implementation if e() 
  // static // a static object is created only once and shared.
  void aa() const    // members of the class cannot be modified.
            noexcept // this function does not throw exceptions
  {

  }

};

auto main() -> int {
    
  A a(10);
  a.f(20);    // prints f() hello 20
  a.g(20);    // prints g() hello 20
  std::cout << std::endl;
  
  //Abstract b; // cannot create an Abstract class

  Abstract& b = a;
  b.f(1);   // prints f() Abstract: hello 1 because f() is not virtual
  b.g(2);   // prints g() Abstract: hello 2 because g() is virtual
  std::cout << std::endl;
  
  Abstract* c = &a;
  c->f(3);  // same as above
  c->g(4);
 
  return 0;
}