// ======================================================================================
// File         : test_ip.cc
// Author       : Gao Lei 
// Last Change  : 12/02/2011 | 01:36:05 AM | Friday,December
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



#define ACCUMULATER(SUM) [&](std::vector<std::size_t>& vec) \
                        {                                   \
                            SUM = std::accumulate(vec.begin(),vec.end(),0,[](std::size_t sum,std::size_t x) \
                                                                            {                       \
                                                                                sum *= 10;          \
                                                                                sum += x;           \
                                                                                return sum;         \
                                                                            }                       \
                                                 );                                                      \
                        }
int main()
{

    std::size_t adress1=0;
    std::size_t adress2=0;
    std::size_t adress3=0;
    std::size_t adress4=0;

    // std::string str2 = "192";
    // // auto p = _repeat<1,3>(_digit())
    // //             <= [](std::vector<std::size_t>& vec)
    // //                  { std::for_each(vec.begin(),vec.end(),[](std::size_t i){std::cout<<i<<std::endl;}); } ;
    // auto p = _repeat<1,3>(_digit()) <= ACCUMULATER(adress1);
    // auto it = str2.begin();
    // if(p(it,str2.end()))
    // {
    //     std::cout<<adress1<<std::endl;
    // }
    // else
    // {
    //     std::cout<<"err2..."<<std::endl;
    // }
    // 

    auto lit = _literal(".");

    auto ip_parser = _sequence( _repeat<1,3>(_digit()) <= ACCUMULATER(adress1),
                                lit,
                                _repeat<1,3>(_digit()) <= ACCUMULATER(adress2),
                                lit,
                                _repeat<1,3>(_digit()) <= ACCUMULATER(adress3),
                                lit,
                                _repeat<1,3>(_digit()) <= ACCUMULATER(adress4)
                              );

    std::string str ="192.168.1.1"; // "192.168.1.1";
    auto it = str.begin();
    if(ip_parser(it,str.end()))
    //if(lit(it,str.end()))
    {
        std::cout<<adress1<<std::endl;
        std::cout<<adress2<<std::endl;
        std::cout<<adress3<<std::endl;
        std::cout<<adress4<<std::endl;
    }
    else
    {
        std::cout<<"err..."<<std::endl;
    }   

}


