// ======================================================================================
// File         : test_alternative.cc
// Author       : Gao Lei 
// Last Change  : 12/05/2011 | 02:15:42 AM | Monday,December
// Description  : 
// ======================================================================================

#include <string>
#include <iostream>
//#include "../all.h"
#include "../src/core/and_p.h"
#include "../src/core/or_p.h"
#include "../src/core/literal_p.h"
#include "../src/core/compposer.h"
#include "../src/built_in_parsers/character_parsers.h"
#include ""


using namespace chrysanthemum;
using namespace chrysanthemum::ops;


int main()
{

    typedef std::string::iterator IT;
    auto f = _wrapper(_converter(std::string()),_line_printer(std::cout));
    auto tcp = _literal("TCP") <= f;
    std::string HTTP = "HTTP";

    {

         auto p =  tcp <= f
                 | HTTP <= f
                 | "UDP" <= f
                 | std::string("FTP") <= f ;
        std::string str = "TCP";
        std::string::iterator it = str.begin();
        if(p(it,str.end()) )
        {
            std::cout<<"OK"<<std::endl;
        }
        std::string str = "UDP";
        std::string::iterator it = str.begin();
        if(p(it,str.end()) )
        {
            std::cout<<"OK"<<std::endl;
        }        
        std::string str = "FTP";
        std::string::iterator it = str.begin();
        if(p(it,str.end()) )
        {
            std::cout<<"OK"<<std::endl;
        }
        std::string str = "HTTP";
        std::string::iterator it = str.begin();
        if(p(it,str.end()) )
        {
            std::cout<<"OK"<<std::endl;
        }
    }


    ////////////////////////////////////////////////////////


}


