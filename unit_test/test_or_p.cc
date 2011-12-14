// ======================================================================================
// File         : test_alternative.cc
// Author       : Gao Lei 
// Last Change  : 12/05/2011 | 02:15:42 AM | Monday,December
// Description  : 
// ======================================================================================

#include <string>
#include <iostream>
//#include "../all.h"
#include "../src/action/action.h"
#include "../src/compound/or_p.h"
#include "../src/compound/and_p.h"
#include "../src/parsers/parsers.h"



int main()
{

    std::string str;
    typedef std::string::iterator Iterator;
    auto p1 = _literal<Iterator>("FTP") <= to_string<Iterator>(str);
    auto p2 = _literal<Iterator>("HTTP") <= to_string<Iterator>(str);
    auto p3 = _literal<Iterator>("TCP") <= to_string<Iterator>(str);


    {
        auto p = _or<Iterator>( p1,
                                p2,
                                p3,
                                _literal<Iterator>("IP") <= to_string<Iterator>(str)
                              );
        std::string str = "HTTP";
        std::string::iterator it = str.begin();
        if(p(it,str.end()) )
        {
            std::cout<<str<<std::endl;
        }

    }



    {
        auto p = _or<Iterator>( p1,
                                p2,
                                p3,
                                _literal<Iterator>("IP") <= to_string<Iterator>(str)
                              );
        std::string str = "TCP";
        std::string::iterator it = str.begin();
        if(p(it,str.end()) )
        {
            std::cout<<str<<std::endl;
        }

    }



    {
        auto p = _or<Iterator>( p1,
                                p2,
                                p3,
                                "IP" <= to_string<Iterator>(str)
                              );
        std::string str = "IP";
        std::string::iterator it = str.begin();
        if(p(it,str.end()) )
        {
            std::cout<<str<<std::endl;
        }

    }


    {
        auto p =   "UDP"  <= to_string<Iterator>(str)
                 | "TCP" <= to_string<Iterator>(str)
                 | "HTTP" <= to_string<Iterator>(str) 
                 | "IP" <= to_string<Iterator>(str);
        std::string str = "IP";
        std::string::iterator it = str.begin();
        if(p(it,str.end()) )
        {
            std::cout<<str<<std::endl;
        }

    }

    {
        auto p =   "UDP"  <= to_string<Iterator>(str)
                 | "TCP" <= to_string<Iterator>(str)
                 | 'b' <= to_string<Iterator>(str) 
                 | 'c' <= to_string<Iterator>(str);
        std::string str = "b";
        std::string::iterator it = str.begin();
        if(p(it,str.end()) )
        {
            std::cout<<str<<std::endl;
        }

    }


    {
        auto p =   "UDP"  <= to_string<Iterator>(str)
                 | "TCP" <= to_string<Iterator>(str)
                 | 'b' <= to_string<Iterator>(str) 
                 | 'c' <= to_string<Iterator>(str);
        std::string str = "UDP";
        std::string::iterator it = str.begin();
        if(p(it,str.end()) )
        {
            std::cout<<str<<std::endl;
        }

    }

    ////////////////////////////////////////////////////////


}


