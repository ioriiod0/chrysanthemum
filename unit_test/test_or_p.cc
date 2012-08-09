// ======================================================================================
// File         : test_alternative.cc
// Author       : Gao Lei
// Last Change  : 12/05/2011 | 02:15:42 AM | Monday,December
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
#include "../src/core/not_p.h"
#include "../src/core/or_p.h"
#include "../src/core/optional_p.h"
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
    {
        auto f = _combine(_to_string(),_line_printer(std::cout));
        auto tcp = _literal("TCP") <= f;
        std::string HTTP = "HTTP";
        auto p =  tcp <= f
                 | HTTP <= f
                 | "UDP" <= f
                 | std::string("FTP") <= f ;

        {
            std::string str = "TCP";
            scanner<IT,line_counter_scanner_policy> scan(str.begin(),str.end());
            if(p(scan) )
            {
                std::cout<<"OK"<<std::endl;
            }
        }

        {
            std::string str = "UDP";
            scanner<IT,line_counter_scanner_policy> scan(str.begin(),str.end());
            if(p(scan) )
            {
                std::cout<<"OK"<<std::endl;
            }
        }
        {
            std::string str = "FTP";
            scanner<IT,line_counter_scanner_policy> scan(str.begin(),str.end());
            if(p(scan) )
            {
                std::cout<<"OK"<<std::endl;
            }
        }
        {
            std::string str = "HTTP";
            scanner<IT,line_counter_scanner_policy> scan(str.begin(),str.end());
            if(p(scan) )
            {
                std::cout<<"OK"<<std::endl;
            }
        }
    }
    {
        auto f = _combine(_to_string(),_line_printer(std::cout));
        auto alpha_num = *(_alpha() | _digit()) <= f;
        std::string str = "abcd1234";
        scanner<IT,line_counter_scanner_policy> scan(str.begin(),str.end());
        if(alpha_num(scan))
        {
            std::cout<<"ok"<<std::endl;
        }
        else
        {
            std::cout<<"fuck"<<std::endl;
        }
    }

    ////////////////////////////////////////////////////////


}


