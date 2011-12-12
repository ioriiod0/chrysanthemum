// ======================================================================================
// File         : test2.cc
// Author       : Gao Lei 
// Last Change  : 12/01/2011 | 05:17:53 AM | Thursday,December
// Description  : 
// ======================================================================================

#include <string>
#include <iostream>

//#include "../all.h"
#include "../src/compound/sequence_p.h"
#include "../src/compound/literal_p.h"
#include "../src/parsers/parsers.h"


#define PRINTER [](Iterator first,Iterator last)    \
                  {                                 \
                      std::cout<<*first<<std::endl;      \
                      return true;                  \
                  }

#define PRINTER [](Iterator first,Iterator last)    \
                  {                                 \
                      std::cout<<*first<<std::endl;      \
                      return true;                  \
                  }

int main()
{
    typedef std::string::iterator Iterator;
    _alpha<Iterator> a1;
    _alpha<Iterator> a2;
    _digit<Iterator> d1;
    _digit<Iterator> d2;
    _space<Iterator> s1;
    _space<Iterator> s2;
    //std::string header = "FTP://"; 
    auto p2 = _literal<Iterator>("HTTP://");
    auto p = _sequence<Iterator>(p2, 
                               a1 <= PRINTER,
                               d1 <= PRINTER,
                               s1 <= PRINTER,
                               a2 <= PRINTER,
                               d2 <= PRINTER,
                               s2 <= PRINTER,
                               _alpha<Iterator>() <= PRINTER);
    std::string str = "HTTP://a3 b4 c";
    Iterator first = str.begin();
    Iterator last = str.end();
    
    bool ret = p(first,last);
    std::cout<<ret<<std::endl;

}

