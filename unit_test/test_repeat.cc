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

#include "../src/compound/and_p.h"
#include "../src/compound/or_p.h"
#include "../src/compound/repeat_p.h"
#include "../src/compound/literal_p.h"
#include "../src/compound/list_p.h"
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

    {
        
        std::size_t sum=0;
        std::string str ="192"; // "192.168.1.1";
        auto it = str.begin();
        auto p = +_digit() <= _converter(sum);

        if(p(it,str.end()))
        {
            std::cout<<sum<<std::endl;
        }
        else
        {
            std::cout<<"fuck"<<std::endl;
        }
    }

    {
        
        std::size_t sum=0;
        std::string str ="192"; // "192.168.1.1";
        auto it = str.begin();
        auto p = *_digit() <= _converter(sum);

        if(p(it,str.end()))
        {
            std::cout<<sum<<std::endl;
        }
        else
        {
            std::cout<<"fuck"<<std::endl;
        }
    }

  
    {
        std::size_t adress1=0;
        std::size_t adress2=0;
        std::size_t adress3=0;
        std::size_t adress4=0; 

        auto ip_parser =  (_digit() & _repeat<0,2>(_digit())) <= _converter(adress1)
                        & '.'
                        & (_digit() & _repeat<0,2>(_digit())) <= _converter(adress2)
                        & '.'
                        & (_digit() & _repeat<0,2>(_digit())) <= _converter(adress3)
                        & '.'
                        & (_digit() & _repeat<0,2>(_digit())) <= _converter(adress4);
                                 

        std::string str ="192.168.1.1"; // "192.168.1.1";
        auto it = str.begin();
        if(ip_parser(it,str.end()))
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

}


