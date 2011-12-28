// ======================================================================================
// File         : test_alternative.cc
// Author       : Gao Lei 
// Last Change  : 12/05/2011 | 02:15:42 AM | Monday,December
// Description  : 
// ======================================================================================

#include <string>
#include <iostream>
//#include "../all.h"
#include "../src/compound/and_p.h"
#include "../src/compound/or_p.h"
#include "../src/compound/literal_p.h"
#include "../src/parsers/basic_parsers.h"
#include "../src/parsers/rule.h"
#include "../src/converter/converters.h"
#include "../src/action/printer.h"
#include "../src/action/back_inserter.h"
#include "../src/action/accumulater.h"
#include "../src/parsers/compposer.h"
#include "../src/action/function_wrapper.h"



int main()
{

    typedef std::string::iterator IT;
    auto p1 = _literal("FTP") <= _wrapper(_converter(std::string()),_line_printer(std::cout));
    auto p2 = _literal("HTTP") <= _wrapper(_converter(std::string()),_line_printer(std::cout));
    auto p3 = _literal("TCP") <= _wrapper(_converter(std::string()),_line_printer(std::cout));


    {
        auto p = _or( p1,
                      p2,
                      p3,
                      _literal("IP") 
                        <= _wrapper(_converter(std::string()),_line_printer(std::cout))
                    );
        std::string str = "HTTP";
        IT it = str.begin();
        if(p(it,str.end()) )
        {
            std::cout<<"OK"<<std::endl;
        }

    }



    {
        auto p =  p1
                | p2
                | p3
                | "IP"
                   <= _wrapper(_converter(std::string()),_line_printer(std::cout));
        std::string str = "TCP";
        std::string::iterator it = str.begin();
        if(p(it,str.end()) )
        {
            std::cout<<"OK"<<std::endl;
        }

    }


    ////////////////////////////////////////////////////////


}


