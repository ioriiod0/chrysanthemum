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


#include "../src/core/and_p.h"
#include "../src/core/difference_p.h"
#include "../src/core/repeat_p.h"
#include "../src/core/literal_p.h"
#include "../src/core/scanner.h"
#include "../src/core/compposer.h"
#include "../src/core/list_p.h"
#include "../src/extentions/character_parsers.h"
#include "../src/extentions/scanner_policy.h"
#include "../src/action/printer.h"
#include "../src/action/converters.h"
#include "../src/action/combiner.h"
#include "../src/action/back_inserter.h"

using namespace chrysanthemum;
using namespace chrysanthemum::ops;


int main()
{
    typedef std::string::iterator IT;
    std::vector<std::size_t> vec;

    auto f = _combine(_converter<int>(),_less_equal(255));//_back_inserter(vec));

    auto ip_parser = (
                       (   
                          (_digit()-'0') 
                        & _repeat<0,2>(_digit())
                       ) <=  f
                     )
                     % '.';

    {
        std::string str = "192.168.1.1"; // "192.168.1.1";
        scanner<IT,line_counter_scanner_policy> scan(str.begin(),str.end());
        if(ip_parser(scan))
        {
            std::for_each(vec.begin(),vec.end(),[](std::size_t i){
                          std::cout<<i<<"..."<<std::endl;
                          });
            std::cout<<"................."<<std::endl;
        }
        else
        {
            std::cout<<"fuck..."<<std::endl;
        }
    }

    {
        std::string str = "092.168.1.1"; // "192.168.1.1";
        scanner<IT,line_counter_scanner_policy> scan(str.begin(),str.end());
        if(ip_parser(scan))
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
        typedef std::string::iterator IT;
        std::vector<std::string> vec;
        auto f = _combine(_to_string(),_back_inserter(vec));
        auto parser =( +(_alpha()) <= f ) % ',';
        std::string str = "apple,banana,pear,peach,"; // "192.168.1.1";
        scanner<IT,line_counter_scanner_policy> scan(str.begin(),str.end());
        if(parser(scan))
        {
            std::for_each(vec.begin(),vec.end(),[](std::string i){
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


