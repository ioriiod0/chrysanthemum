// ======================================================================================
// File         : test_function_wrapper.cc
// Author       : Gao Lei 
// Last Change  : 12/18/2011 | 00:26:23 AM | Sunday,December
// Description  : 
// ======================================================================================
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>


//#include "../all.h"
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
#include "../src/action/function_wrapper.h"

void printer(std::string& str)
{
    std::cout<<str<<std::endl;
}
int main()
{
    typedef std::string::iterator IT;
    {
        auto f = [](const std::string& str) {std::cout<<str<<std::endl;};

        auto fw = _wrapper<void(const std::string&)>(f);
       
        std::string str = "{a{b}{c{d}}}";
        IT it = str.begin();
        if(fw(it,str.end()))
        {
            std::cout<<"OK"<<std::endl;
        }
        else
        {
            std::cout<<"FAILED"<<std::endl;
        }

    }
    {


        auto fw = _wrapper<void(std::string&)>(printer);
       
        std::string str = "{a{b}{c{d}}}";
        IT it = str.begin();
        if(fw(it,str.end()))
        {
            std::cout<<"OK"<<std::endl;
        }
        else
        {
            std::cout<<"FAILED"<<std::endl;
        }

    }

}

