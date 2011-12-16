// ======================================================================================
// File         : test2.cc
// Author       : Gao Lei 
// Last Change  : 12/01/2011 | 05:17:53 AM | Thursday,December
// Description  : 
// ======================================================================================

#include <string>
#include <iostream>

//#include "../all.h"
#include "../src/compound/and_p.h"
#include "../src/compound/literal_p.h"
#include "../src/parsers/parsers.h"
#include "../src/action/converters.h"

#define PRINTER [](Iterator first,Iterator last)    \
                  {                                 \
                      std::cout<<*first<<std::endl;      \
                      return true;                  \
                  }


int main()
{
    typedef std::string::iterator Iterator;
    _alpha<Iterator> a1; a1 <= PRINTER;
    _alpha<Iterator> a2; a2 <= PRINTER;
    _digit<Iterator> d1; d1 <= PRINTER;
    _digit<Iterator> d2; d2 <= PRINTER;
    _space<Iterator> s1; s1 <= PRINTER;
    _space<Iterator> s2; s2 <= PRINTER;
    std::string ret;

    {
        auto p = "HTTP://" & a1 & d1 & ' ' & a2 & d2 & ' ' & (_alpha<Iterator>() <= PRINTER);
        p <= to_string<Iterator>(ret);
        std::string str = "HTTP://a3 b4 c";
        Iterator first = str.begin();
        Iterator last = str.end();
        if(p(first,last))
        {
            std::cout<<ret<<std::endl;
        }

    }


}

