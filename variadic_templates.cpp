// Variadic template C++11
// usage: f(1.5, 23, "Amar") this does recursion
template<typename T, typename... Tail>
void f(T head, Tail... tail)
{
    g(head);   //do someting to head
    f(tail...);      //try again with tail
}

// Variadic function template
// usage: multiply(1,2,3,4) gives 1*2*3*4
template<typename T, typename... ARGS> // Function parameter pack
T multiply(const T& arg, const ARGS&... args)
{
  return arg * multiply(args...); // Unpacking the parameter
}

// Variadic calss template
template <typename... T_values> // called parameter pack
class Base
{
public
    virtual void f(T_values... values) = 0;
};

class Derived1 : public Base<int, short, double>
{
public:
    void f(int a, short b, double c) override;
};