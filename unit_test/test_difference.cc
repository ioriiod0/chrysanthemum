// ======================================================================================
// File         : test_difference.cc
// Author       : Lei Gao 
// Last Change  : 12/08/2011 | 15:22:17 PM | Thursday,December
// Description  : 
// ======================================================================================

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

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
#include "../src/compound/not_p.h"
#include "../src/compound/diference_p.h"


using namespace chrysanthemum;
using namespace chrysanthemum::ops;

int main()
{
 
    typedef std::string::iterator IT;
    std::string ret;
    auto p = '{' & _repeat<0,INFINITE>(_oct()-'{'-'}') <= _converter(ret); //& '}';
    std::string str = "{sdfs123214}fdsfsdf}";
    auto it = str.begin();
    if(p(it,str.end()))
    { 
        std::cout<<ret<<std::endl;
    }
    else
    {
        std::cout<<"fuck"<<std::endl;
    }
}
