// ======================================================================================
// File         : test1.cc
// Author       : Gao Lei
// Last Change  : 12/01/2011 | 02:25:43 AM | Thursday,December
// Description  : 
// ======================================================================================

#include <cstdlib>
#include <string>
#include <tuple>
#include <iostream>
#include <functional>
#include <type_traits>
#include <map>



//#include "../all.h"


template <typename Derived>
struct base
{
    Derived& derived()
    {
        return *(static_cast<Derived*>(this));
    }

    const Derived& derived() const
    {
        return *(static_cast<const Derived*>(this));
    }
};

struct tester:public base<tester>
{
    template <typename T>
    bool operator() (T p,T q)
    {

    }
};


namespace xxx{
struct BASE
{
    
};


struct Derived1:public BASE
{
    int a;
};

struct Derived2:public BASE
{
    int b;
};

template <typename T,typename U>
struct decuce_policy
{
    typedef typename std::remove_reference<T>::type T1;
    typedef typename std::remove_reference<U>::type U1;
    const static bool value = std::is_base_of<BASE,T1>::value || std::is_base_of<BASE,U1>::value;
    typedef std::integral_constant<bool,value> type;
};


template <typename T,typename U>
void do_add(T&& t,U&& u,const std::true_type&)
{
    std::cout<<"lalala"<<std::endl;
    return T();
}

template <typename T,typename U>
typename std::remove_reference<T>::type do_add(T&& t,U&& u,const std::false_type&)
{
    return std::forward<T>(t)+std::forward<U>(u);
}



template <typename T,typename U>
T operator+ (T&& t,U&& u)
{
    return do_add(std::forward<T>(t),std::forward<U>(u),typename decuce_policy<T,U>::type());    
}

} //end namespace xxx
void fuck1(tester&& t)
{
    std::cout<<"right"<<std::endl;
}

void fuck1(const tester& t)
{
    std::cout<<"left"<<std::endl;
}

template <typename T>
void fuck(const base<T>& t)
{
    fuck1(t.derived());
}

template <typename T>
void fuck(base<T>&& t)
{
    fuck1(std::move(t.derived()));
}


template <typename T>
struct B
{
public:
    const T& operator=(int i)
    {
        p->set (10);
        return *p;
    }
};


struct A:public B<A>
{
    int i;
    void set(int j)
    {
        i = j;
    }
};

using namespace xxx;
int main()
{

    A a;
    a=10;
    std::cout<<a.i<<std::endl;
    // typename sequence_traits<data_holder<int> ,data_holder<char> ,data_holder<float> >::data_type t;
   //  t = std::make_tuple(3,'a',0.2f); 


   // typename sequence_traits<alpha_parser,digit_parser>::data_type t2;
   // t2 = std::make_tuple('c','8');


   // std::cout<<std::get<0>(t2)<<" "<<std::get<1>(t2)<<std::endl;
    // std::function<void(char*,char*)> f = tester();//[](char* p,char* q){ std::cout<<std::string(p,q)<<std::endl; };
    // f(NULL,NULL);
    //test1();
    // std::map<std::string,std::string> m;
    // m["a"] = "a";
    // m["b"] = "b";
    // typedef std::map<std::string,std::string>::value_type value_type;
    // for(const value_type& v:m)
    // {
    //     std::cout<<v.first<<":"<<v.second<<std::endl;
    // }
    // tester t;
    // fuck(tester());
    // fuck(t);

    // Derived1 d1;
    // Derived2 d2;

    // d1+d2;

    // int a = 3+4;
    // std::cout<<a<<std::endl;

    // std::string bb = "aaa";
    // std::string ddd = bb + "ddddd";

    
}

