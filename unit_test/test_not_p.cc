// ======================================================================================
// File         : test_not_p.cc
// Author       : Lei Gao 
// Last Change  : 12/17/2011 | 14:20:31 PM | Saturday,December
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
#include "../src/compound/not_p.h"

using namespace chrysanthemum;
using namespace chrysanthemum::ops;


int main()
{
   typedef std::string::iterator IT;
   {
       std::string ret;
       std::string str = "*&^%%\r\nFDSFjjffh2351";
       auto n = _not(_digit());
       auto p = _repeat<0,INFINITE>(n) <= _converter(ret);
       IT it = str.begin();
       if(p(it,str.end()))
       {
           std::cout<<ret<<std::endl;
       }
   }
}
