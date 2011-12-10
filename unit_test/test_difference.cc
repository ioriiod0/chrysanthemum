// ======================================================================================
// File         : test_difference.cc
// Author       : Lei Gao 
// Last Change  : 12/08/2011 | 15:22:17 PM | Thursday,December
// Description  : 
// ======================================================================================

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "../all.h"

int main()
{
    auto p_start = _literal('{');
    auto p_end = _literal('}');
    auto p1 = _repeat<0,INFINITE>(_oct()-p_end) <= [](std::vector<char>& vec){
        std::for_each(vec.begin(),vec.end(),[](char c){
                      std::cout<<c;
                      });
        return true;
    };
  


    auto p = _sequence(p_start,p1,p_end);
    std::string str = "{sdfs123214fdsfsdf}";
    auto it = str.begin();
    if(p(it,str.end()))
    { 
        std::cout<<"YEAH!"<<std::endl;
    }
    else
    {
        std::cout<<"fuck"<<std::endl;
    }
}
