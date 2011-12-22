// ======================================================================================
// File         : test_rule.cc
// Author       : Gao Lei 
// Last Change  : 12/17/2011 | 20:22:39 PM | Saturday,December
// Description  : 
// ======================================================================================

#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

#include "../src/compound/repeat_p.h"
#include "../src/compound/list_p.h"
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


int main()
{
    typedef std::string::iterator IT;
    {
        auto f = [](const std::string& str) {std::cout<<str<<std::endl;};
        auto wrapper = _wrapper<void(const std::string& str)>(f);
        //decltype(fw) fw2(fw);
        //{a{b{c{d}}}}
        rule<IT> rule_;
        rule_ %= (   '{' 
                   & _repeat<0,INFINITE>(_char<IT>()-'{'-'}') 
                   & _repeat<0,INFINITE>(rule_) 
                   & '}') <= wrapper;

        std::string str = "{a{b}{c{d}}}";
        IT it = str.begin();
        if(rule_(it,str.end()))
        {
            std::cout<<"OK"<<std::endl;
        }
        else
        {
            std::cout<<"FAILED"<<std::endl;
        }

    }
}
