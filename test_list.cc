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

#include "data_holder.h"
#include "parsers.h"
#include "sequential.h"
#include "tuple_serialization.h"
#include "literal.h"
#include "repeat.h"
#include "list.h"

#define ACCUMULATER [](std::vector<std::size_t>& vec) \
                        {                                   \
                            std::size_t ret = 0;            \
                            ret = std::accumulate(vec.begin(),vec.end(),0,[](std::size_t sum,std::size_t x) \
                                                                            {                       \
                                                                                sum *= 10;          \
                                                                                sum += x;           \
                                                                                return sum;         \
                                                                            });                     \
                            std::cout<<ret<<std::endl;                                              \
                        }
int main()
{


    // auto ip_parser = _sequence( _repeat<1,3>(_digit()) <= ACCUMULATER(adress1),
    //                             lit,
    //                             _repeat<1,3>(_digit()) <= ACCUMULATER(adress2),
    //                             lit,
    //                             _repeat<1,3>(_digit()) <= ACCUMULATER(adress3),
    //                             lit,
    //                             _repeat<1,3>(_digit()) <= ACCUMULATER(adress4)
    //                           );

    auto lit = _literal(".");
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
                      [](std::vector<std::size_t>& vec)
                      {
                        std::for_each(vec.begin(),vec.end(),
                                      [](std::size_t i)
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


