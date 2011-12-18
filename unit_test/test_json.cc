// ======================================================================================
// File         : test_json.cc
// Author       : Gao Lei 
// Last Change  : 12/18/2011 | 01:24:49 AM | Sunday,December
// Description  : 
// ======================================================================================
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

#include "../src/compound/repeat_p.h"
#include "../src/compound/list_p.h"
#include "../src/compound/optional_p.h"
#include "../src/compound/and_p.h"
#include "../src/compound/or_p.h"
#include "../src/compound/diference_p.h"
#include "../src/action/back_inserter.h"
#include "../src/action/accumulater.h"
#include "../src/action/converters.h"
#include "../src/parsers/parsers.h"
#include "../src/action/comparer.h"
#include "../src/action/condition.h"
#include "../src/utility/rule.h"
#include "../src/action/function_wrapper.h"

template <typename IT>
struct json_grammar
{
    rule<IT> obj,member,string,value,number,array,integer,real;
    json_grammar()
    {
        obj %= '{' & (member % ',') & '}';
        member %= string & ':' & value;
        string %= '"' & _repeat<0,INFINITE>(_char<IT>()) & '"';
        value %= string | number | obj | array | "true" | "false" | "null";
        number %= integer | real;
        array %= '[' & (value % ',') & ']';
        integer %= _optional(_literal<IT>('+') | '-') & _repeat<1,INFINITE>(_digit<IT>());
        real %= integer & '.' & _repeat<0,INFINITE>(_digit<IT>());
    }

    
};

int main()
{

    std::ifstream fs(argv[1]); 
    std::ostringstream ss; 
    ss << fs.rdbuf(); 
    std::string data = ss.str();


}

