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

#include "../src/compound/repeat_p.h"
#include "../src/compound/list_p.h"
#include "../src/compound/and_p.h"
#include "../src/compound/or_p.h"
#include "../src/compound/diference_p.h"
#include "../src/action/back_inserter.h"
#include "../src/action/converters.h"
#include "../src/parsers/parsers.h"
#include "../src/compound/optional_p.h"

int main()
{
    

    typedef std::string::iterator IT;
    {
        std::string ret1;
        std::string ret2;
        auto p = _optional(_literal<IT>("abc")) <= _converter(ret1)
               & _literal<IT>("defg") <= _converter(ret2);

        std::string str = "abcdefg";
        auto it = str.begin();
        if(p(it,str.end()))
        {
            std::cout<<"1:"<<ret1<<std::endl;
            std::cout<<"2:"<<ret2<<std::endl;
        }
        else
        {
            std::cout<<"fuck"<<std::endl;
        }

    }

    {
        std::string ret1;
        std::string ret2;
        auto p = _optional(_literal<IT>("abc")) <= _converter(ret1) 
               & _literal<IT>("defg") <= _converter(ret2);
        std::string str = "defg";
        auto it = str.begin();
        if(p(it,str.end()))
        {
            std::cout<<"1:"<<ret1<<std::endl;
            std::cout<<"2:"<<ret2<<std::endl;
        }
        else
        {
            std::cout<<"fuck"<<std::endl;
        }

    }



}
