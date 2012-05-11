// ======================================================================================
// File         : test_not_p.cc
// Author       : Lei Gao , Qianhong Wang
// Last Change  : 12/17/2011 | 14:20:31 PM | Saturday,December
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
   {
       std::string str = "fs*&^%%\r\nFDSFjjffh2351sdfFF";
       typedef std::string::iterator IT;
       auto f = _combine(_to_string(),_line_printer(std::cout));
       auto p = *(!_digit()) <= f;
       scanner<IT,line_counter_scanner_policy> scan(str.begin(),str.end()); 
       if(p(scan))
       {
           std::cout<<"ok"<<std::endl;
           std::cout<<scan.consumed<<std::endl;
           std::cout<<scan.line_no<<std::endl;
           std::cout<<scan.col_no<<std::endl;
       }
       else
       {
           std::cout<<"FUCK"<<std::endl;
       }
   }
}
