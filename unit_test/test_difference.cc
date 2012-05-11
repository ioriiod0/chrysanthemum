// ======================================================================================
// File         : test_difference.cc
// Author       : Lei Gao , Qianhong Wang
// Last Change  : 12/08/2011 | 15:22:17 PM | Thursday,December
// Description  : 
// ======================================================================================

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "../src/core/and_p.h"
#include "../src/core/difference_p.h"
#include "../src/core/repeat_p.h"
#include "../src/core/literal_p.h"
#include "../src/core/scanner.h"
#include "../src/core/compposer.h"
#include "../src/extentions/character_parsers.h"
#include "../src/extentions/scanner_policy.h"
#include "../src/action/printer.h"
#include "../src/action/converters.h"
#include "../src/action/combiner.h"

using namespace chrysanthemum;
using namespace chrysanthemum::ops;

int main()
{
    { 
        typedef std::string::iterator IT;
        auto f = _combine(_to_string(),_line_printer(std::cout)); 
        auto p = '{' 
                & *(_any()-'{'-'}')  <=  f 
                & '}';
        std::string str = "{hello world! 12345!} .......";
        scanner<IT,line_counter_scanner_policy> scan(str.begin(),str.end());
        if(p(scan))
        { 
            std::cout<<"OK"<<std::endl;
        }
        else
        {
            std::cout<<"fuck"<<std::endl;
        }
    }

    { 
        typedef std::string::iterator IT;
        auto f = _combine(_converter<int,10>(),_line_printer(std::cout)); 
        auto p = *(_digit()-'0')  <=  f;
        std::string str = "123406789 .......";
        scanner<IT,line_counter_scanner_policy> scan(str.begin(),str.end());
        if(p(scan))
        { 
            std::cout<<"OK"<<std::endl;
        }
        else
        {
            std::cout<<"fuck"<<std::endl;
        }
    }
}
