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


//#include "../all.h"
#include "../src/compound/and_p.h"
#include "../src/compound/list_p.h"
#include "../src/compound/or_p.h"
#include "../src/compound/diference_p.h"
#include "../src/compound/repeat_p.h"
#include "../src/compound/literal_p.h"
#include "../src/parsers/basic_parsers.h"
#include "../src/parsers/rule.h"
#include "../src/converter/converters.h"
#include "../src/action/printer.h"
#include "../src/action/back_inserter.h"
#include "../src/action/accumulater.h"
#include "../src/parsers/compposer.h"
#include "../src/action/function_wrapper.h"

using namespace chrysanthemum;
using namespace chrysanthemum::ops;


int main()
{

    typedef std::string::iterator IT;
    std::vector<std::size_t> vec;
    auto ip_parser = (((_digit()-'0') & _repeat<0,2>(_digit())) 
                      <= _wrapper(_converter(std::size_t()),_back_inserter(vec)))
                     % '.';

    {
        std::string str = "192.168.1.1"; // "192.168.1.1";
        auto it = str.begin();
        if(ip_parser(it,str.end()))
        {
            std::for_each(vec.begin(),vec.end(),[](std::size_t i){
                          std::cout<<i<<"..."<<std::endl;
                          });
            std::cout<<"................."<<std::endl;
        }
        else
        {
            std::cout<<"err..."<<std::endl;
        }
    }

    {
        std::string str = "092.168.1.1"; // "192.168.1.1";
        auto it = str.begin();
        if(ip_parser(it,str.end()))
        {
            std::for_each(vec.begin(),vec.end(),[](std::size_t i){
                          std::cout<<i<<"..."<<std::endl;
                          });
            std::cout<<"................."<<std::endl;
        }
        else
        {
            std::cout<<"err..."<<std::endl;
        }
    }




    // {
    //     std::size_t sum = 0;
    //     auto ip_parser = (((_digit<IT>()-'0') & _repeat<0,2>(_digit<IT>())) <= _accumulater(sum)) % '.';
    //     std::string str = "192.168.1.1"; // "192.168.1.1";
    //     auto it = str.begin();
    //     if(ip_parser(it,str.end()))
    //     {
    //         std::cout<<sum<<std::endl;
    //     }
    //     else
    //     {
    //         std::cout<<"err..."<<std::endl;
    //     }
    // }


    // {
    //     auto condition = _less_equal(255);
    //     auto ip_parser = ( 
    //                         ((_digit<IT>()-'0') & _repeat<0,2>(_digit<IT>()))
    //                             <= _if_then(condition,[&condition](){ std::cout<<condition.data()<<std::endl;})
    //                      ) % '.';
    //     std::string str = "192.168.1.1"; // "192.168.1.1";
    //     auto it = str.begin();
    //     if(ip_parser(it,str.end()))
    //     {
    //         std::cout<<"yes.."<<std::endl;
    //     }
    //     else
    //     {
    //         std::cout<<"err..."<<std::endl;
    //     }
    // }
    // {
    //     auto condition = _less_equal(255);
    //     auto ip_parser = ( 
    //                         ((_digit<IT>()-'0') & _repeat<0,2>(_digit<IT>()))
    //                             <= _if_else(condition,
    //                                         [&condition](){ std::cout<<condition.data()<<std::endl;},
    //                                         [&condition](){ std::cout<<"wrong num:"<<condition.data()<<std::endl;}
    //                                        )
    //                      ) % '.';
    //     std::string str = "256.168.1.1"; // "192.168.1.1";
    //     auto it = str.begin();
    //     if(ip_parser(it,str.end()))
    //     {
    //         std::cout<<"yes.."<<std::endl;
    //     }
    //     else
    //     {
    //         std::cout<<"err..."<<std::endl;
    //     }
    // }
}


