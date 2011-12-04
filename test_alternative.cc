// ======================================================================================
// File         : test_alternative.cc
// Author       : Gao Lei 
// Last Change  : 12/05/2011 | 02:15:42 AM | Monday,December
// Description  : 
// ======================================================================================

#include <string>
#include <iostream>

#include "data_holder.h"
#include "parsers.h"
#include "sequential.h"
#include "tuple_serialization.h"
#include "literal.h"
#include "alternative.h"


int main()
{
    
    auto p1 = _literal("FTP");
    auto p2 = _literal("HTTP");
    auto p3 = _literal("TCP");
    auto p = _alternative( _choice<1>(p1),
                           _choice<2>(p2),
                           _choice<3>(p3),
                           _choice<4>(_literal("IP")) );
    {

        std::string str = "HTTP";
        std::string::iterator it = str.begin();
        if(p(it,str.end()) )
        {
            std::cout<<p.data().which()<<":"<<p.data().get<2>()<<std::endl;
        }

    }
    // {
    //     std::string str = "TCP";
    //     std::string::iterator it = str.begin();
    //     bool ret = p(it,str.end());
    //     std::cout<<ret<<std::endl;
    //     std::cout<<p.data().which()<<std::endl;
    // }
    // {
    //     std::string str = "IP";
    //     std::string::iterator it = str.begin();
    //     bool ret = p(it,str.end());
    //     std::cout<<ret<<std::endl;
    //     std::cout<<p.data().which()<<" "<<p.data().get<4>()<<std::endl;
    // }
    ////////////////////////////////////////////////////////


}


