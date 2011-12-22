// ======================================================================================
// File         : test2.cc
// Author       : Gao Lei 
// Last Change  : 12/01/2011 | 05:17:53 AM | Thursday,December
// Description  : 
// ======================================================================================



//#include "../all.h"
#include "../src/compound/and_p.h"
#include "../src/compound/literal_p.h"
#include "../src/parsers/basic_parsers.h"
#include "../src/parsers/rule.h"
#include "../src/converter/converters.h"
#include "../src/action/printer.h"
#include "../src/action/back_inserter.h"
#include "../src/action/accumulater.h"
#include "../src/parsers/compposer.h"


#include <string>
#include <iostream>




int main()
{

    typedef std::string::iterator IT;
    _alpha a1; char ch1;
    _alpha a2; char ch2;
    _digit d1; char ch3;
    _digit d2; char ch4;
    _space s1; char ch5;
    _space s2; char ch6;

    {
        //////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////
        std::string ret;
        char ch;
        rule<IT,std::string,no_skip> p;
        p %= ( "HTTP://" <= _converter(ret) <= _line_printer(std::cout)
            & a1 <= _converter(ch1) <= _line_printer(std::cout)
            & d1 <= _converter(ch2) <= _line_printer(std::cout)
            & ' ' 
            & a2 
            & d2 
            & ' ' 
            & _alpha()
            ) <= _converter(p.ctx()) <= _line_printer(std::cout);
        // p %= "HTTP://" <= _converter(p.ctx()) <= _line_printer(std::cout)
        //     & a1 <= _converter(ch1) <= _line_printer(std::cout);
        std::string str = "HTTP://a3 b4 c";
        IT first = str.begin();
        if(p(first,str.end()))
        {
            std::cout<<p.ctx()<<"   lala"<<std::endl;
        }
        else
        {
            printf("err\r\n");
        }
        /////////////////////////////////////////////////////////////////
    }


}

