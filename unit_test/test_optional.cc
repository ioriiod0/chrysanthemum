// ======================================================================================
// File         : test_optional.cc
// Author       : Lei Gao 
// Last Change  : 12/06/2011 | 16:23:54 PM | Tuesday,December
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
        std::string ret1;
        std::string ret2;
        auto p = -_literal("abc") <= _emplace_to_string(ret1)
               & "defg" <= _emplace_to_string(ret2);

        std::string str = "abcdefg";
        scanner<IT,line_counter_scanner_policy> scan(str.begin(),str.end());
        if(p(scan))
        {
            std::cout<<"ok"<<std::endl;
            std::cout<<"1:"<<ret1<<std::endl;
            std::cout<<"2:"<<ret2<<std::endl;
        }
        else
        {
            std::cout<<"fuck"<<std::endl;
        }

    }

    {
        std::string ret1;
        std::string ret2;
        auto p = _optional(_literal("abc")) <= _emplace_to_string(ret1) 
               & "defg" <= _emplace_to_string(ret2);
        std::string str = "defg";
        scanner<IT,line_counter_scanner_policy> scan(str.begin(),str.end());
        if(p(scan))
        {
            std::cout<<"ok"<<std::endl;
            std::cout<<"1:"<<ret1<<std::endl;
            std::cout<<"2:"<<ret2<<std::endl;
        }
        else
        {
            std::cout<<"fuck"<<std::endl;
        }

    }



}
