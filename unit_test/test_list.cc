// ======================================================================================
// File         : test_list.cc
// Author       : Gao Lei 
// Last Change  : 12/03/2011 | 00:36:11 AM | Saturday,December
// Description  : 
// ======================================================================================



#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

#include "../all.h"


#define ACCUMULATER [](std::vector<char>& vec) \
                        {                                   \
                            std::for_each(vec.begin(),vec.end(),[](char ch){std::cout<<ch<<std::endl;}); \
                        }
int main()
{

    auto lit = _literal('.');
    auto ip_parser = _list(_repeat<1,3>(_digit()) <= ACCUMULATER ,
                           lit);
    std::string str ="192.168.1.1"; // "192.168.1.1";
    auto it = str.begin();
    if(ip_parser(it,str.end()))
    {
        typedef decltype(ip_parser) ip_parser_type;
        ip_parser_type::data_type& data = ip_parser.data();
        std::for_each(data.begin(),
                      data.end(),
                      [](std::vector<char>& vec)
                      {
                        std::for_each(vec.begin(),vec.end(),
                                      [](char i)
                                      {
                                        std::cout<<i;
                                      }); 
                        std::cout<<"|";
                      });
        std::cout<<std::endl;
    }
    else
    {
        std::cout<<"err..."<<std::endl;
    }   

}


