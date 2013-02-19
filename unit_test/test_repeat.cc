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

#include "../chrysanthemum/all.h"


using namespace chrysanthemum;
using namespace chrysanthemum::ops;

int main()
{

    typedef std::string::iterator IT;

    {
        std::size_t sum=0;
        auto p = +_digit() <= _emplace_converter<std::size_t>(sum);
        std::string str ="192132"; // "192.168.1.1";
        scanner<IT,line_counter_scanner_policy> scan(str.begin(),str.end());
        if(p(scan))
        {
            std::cout<<sum<<std::endl;
        }
        else
        {
            std::cout<<"fuck"<<std::endl;
        }
    }

    {
        auto f = _converter<int>();
        auto p = *_digit() <= f;
        std::string str ="1932422"; // "192.168.1.1";
        scanner<IT,line_counter_scanner_policy> scan(str.begin(),str.end());
        if(p(scan))
        {
            std::cout<<f.ctx()<<std::endl;
        }
        else
        {
            std::cout<<"fuck"<<std::endl;
        }
    }

  
    {
        std::vector<std::size_t> vec;
        auto f = _combine(_converter<std::size_t>(),_back_inserter(vec));
        auto num = (
                      (_digit()-'0') 
                    & _repeat<0,2>(_digit())
                   ) <= f;

        auto ip_parser =  num
                        & _N<3>( '.' & num);

                                 

        std::string str ="192.168.1.1"; // "192.168.1.1";
        scanner<IT,line_counter_scanner_policy> scan(str.begin(),str.end());
        if(ip_parser(scan))
        {
            std::cout<<"ok"<<std::endl;
            std::for_each(vec.begin(),vec.end(),_line_printer(std::cout));
        }
        else
        {
            std::cout<<"fuck..."<<std::endl;
        }   
    }

}


