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

// #define PRINTER [](IT first,IT last)    \
//                   {                                 \
//                       std::cout<<*first<<std::endl;      \
//                       return true;                  \
//                   }


typedef std::string::iterator IT;

bool printer(IT first,IT last)
{
    std::cout<<*first<<std::endl;
    return true;
}

#define PRINTER printer

int main()
{

    _alpha<IT> a1; a1 <= PRINTER;
    _alpha<IT> a2; a2 <= PRINTER;
    _digit<IT> d1; d1 <= PRINTER;
    _digit<IT> d2; d2 <= PRINTER;
    _space<IT> s1; s1 <= PRINTER;
    _space<IT> s2; s2 <= PRINTER;
    std::string ret;

    {
        auto p = "HTTP://" & a1 & d1 & ' ' & a2 & d2 & ' ' & (_alpha<IT>() <= PRINTER);
        p <= _converter(ret);
        std::string str = "HTTP://a3 b4 c";
        IT first = str.begin();
        IT last = str.end();
        if(p(first,last))
        {
            std::cout<<ret<<std::endl;
        }

    }


}

