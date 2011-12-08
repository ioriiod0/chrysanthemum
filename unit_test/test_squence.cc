// ======================================================================================
// File         : test2.cc
// Author       : Gao Lei 
// Last Change  : 12/01/2011 | 05:17:53 AM | Thursday,December
// Description  : 
// ======================================================================================

#include <string>
#include <iostream>

#include "../all.h"



int main()
{
    alpha_parser a1;
    alpha_parser a2;
    digit_parser d1;
    digit_parser d2;
    space_parser s1;
    space_parser s2;
    std::string header = "FTP://"; 
    auto p2 = _literal("HTTP://") <= [&header](std::string& str) -> bool { str = header; return true;};
    auto p = _sequence(p2,
                       a1,
                       d1,
                       s1,
                       a2,
                       d2,
                       s2,
                       alpha_parser() <= [](char& ch) -> bool {std::cout<<"char "<<ch<<" changed to i"<<std::endl;ch = 'i';return true;} );
    std::string str = "HTTP://a3 b4 c";
    std::string::iterator it = str.begin();
    bool ret = p(it,str.end());
    std::cout<<ret<<std::endl;
    std::cout<<p.data()<<std::endl;
    std::cout<<d1.data()<<std::endl;
;

}

