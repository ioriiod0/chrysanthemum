// ======================================================================================
// File         : test2.cc
// Author       : Gao Lei 
// Last Change  : 12/01/2011 | 05:17:53 AM | Thursday,December
// Description  : 
// ======================================================================================

#include <string>
#include <iostream>

#include "data_holder.h"
#include "parsers.h"
#include "sequential.h"
#include "tuple_serialization.h"
#include "literal.h"


int main()
{
    alpha_parser a1;
    alpha_parser a2;
    digit_parser d1;
    digit_parser d2;
    space_parser s1;
    space_parser s2;
    std::string header = "FTP://"; 
    auto p2 = _literal("HTTP://") <= [&header](std::string& str){ str = header; };
    auto p = _sequence(p2,
                           a1,
                           d1,
                           s1,
                           a2,
                           d2,
                           s2,
                           alpha_parser() <= [](char& ch){std::cout<<"char "<<ch<<" changed to i"<<std::endl;ch = 'i';} );
    std::string str = "HTTP://a3 b4 c";
    std::string::iterator it = str.begin();
    bool ret = p(it,str.end());
    std::cout<<ret<<std::endl;
    std::cout<<p.data()<<std::endl;
    std::cout<<d1.data()<<std::endl;
    ////////////////////////////////////////////////////////
    std::cout<<"------------------------------------------"<<std::endl;
   
    std::string str2 = "HTTP://";
    it = str2.begin();
    ret = p2(it,str2.end());
    std::cout<<ret<<std::endl;

}

