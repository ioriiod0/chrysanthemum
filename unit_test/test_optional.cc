// ======================================================================================
// File         : test_optional.cc
// Author       : Lei Gao 
// Last Change  : 12/06/2011 | 16:23:54 PM | Tuesday,December
// Description  : 
// ======================================================================================

#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

#include "../all.h"


int main()
{
    


    {
        auto p = _sequence(_optional(_literal("abc")),
                       _literal("defg"));

        std::string str = "abcdefg";
        auto it = str.begin();
        if(p(it,str.end()))
        {
            if(std::get<0>(p.data()))
                std::cout<<std::get<0>(p.data()).get()<<" ";
            std::cout<<std::get<1>(p.data())<<std::endl;
        }
        else
        {
            std::cout<<"fuck"<<std::endl;
        }

    }

    {
        auto p = _sequence(_optional(_literal("abc")),
                       _literal("defg"));
        std::string str = "defg";
        auto it = str.begin();
        if(p(it,str.end()))
        {
            if(std::get<0>(p.data()))
                std::cout<<std::get<0>(p.data()).get()<<" "<<std::endl;
            std::cout<<std::get<1>(p.data())<<std::endl;
        }
        else
        {
            std::cout<<"fuck"<<std::endl;
        }

    }



}
