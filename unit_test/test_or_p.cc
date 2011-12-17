// ======================================================================================
// File         : test_alternative.cc
// Author       : Gao Lei 
// Last Change  : 12/05/2011 | 02:15:42 AM | Monday,December
// Description  : 
// ======================================================================================

#include <string>
#include <iostream>
//#include "../all.h"
#include "../src/action/converters.h"
#include "../src/compound/or_p.h"
#include "../src/compound/and_p.h"
#include "../src/parsers/parsers.h"



int main()
{


    std::string ret;
    typedef std::string::iterator IT;
    auto p1 = _literal<IT>("FTP") <= _converter(ret);
    auto p2 = _literal<IT>("HTTP") <= _converter(ret);
    auto p3 = _literal<IT>("TCP") <= _converter(ret);


    {
        auto p = _or( p1,
                      p2,
                      p3,
                      _literal<IT>("IP") <= _converter(ret)
                    );
        std::string str = "HTTP";
        std::string::iterator it = str.begin();
        if(p(it,str.end()) )
        {
            std::cout<<ret<<std::endl;
        }

    }



    {
        auto p =  p1
                | p2
                | p3
                | (_literal<IT>("IP") <= _converter(ret));
        std::string str = "TCP";
        std::string::iterator it = str.begin();
        if(p(it,str.end()) )
        {
            std::cout<<ret<<std::endl;
        }

    }


    ////////////////////////////////////////////////////////


}


