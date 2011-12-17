// ======================================================================================
// File         : test_list.cc
// Author       : Gao Lei 
// Last Change  : 12/03/2011 | 00:36:11 AM | Saturday,December
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


int main()
{

    typedef std::string::iterator IT;
    std::vector<std::size_t> vec;
    auto ip_parser = (((_digit<IT>()-'0') & _repeat<0,2>(_digit<IT>())) <= _back_inserter(vec)) % '.';

    {
        std::string str = "192.168.1.1"; // "192.168.1.1";
        auto it = str.begin();
        if(ip_parser(it,str.end()))
        {
            std::for_each(vec.begin(),vec.end(),[](std::size_t i){
                          std::cout<<i<<"..."<<std::endl;
                          });
            std::cout<<"................."<<std::endl;
        }
        else
        {
            std::cout<<"err..."<<std::endl;
        }
    }

    {
        std::string str = "092.168.1.1"; // "192.168.1.1";
        auto it = str.begin();
        if(ip_parser(it,str.end()))
        {
            std::for_each(vec.begin(),vec.end(),[](std::size_t i){
                          std::cout<<i<<"..."<<std::endl;
                          });
            std::cout<<"................."<<std::endl;
        }
        else
        {
            std::cout<<"err..."<<std::endl;
        }
    }




    {
        std::string ret;
        auto ip_parser = (((_digit<IT>()-'0') & _repeat<0,2>(_digit<IT>())) <= _accumulater(ret)) % '.';
        std::string str = "192.168.1.1"; // "192.168.1.1";
        auto it = str.begin();
        if(ip_parser(it,str.end()))
        {
            std::cout<<ret<<std::endl;
        }
        else
        {
            std::cout<<"err..."<<std::endl;
        }
    }


    {
        auto ip_parser = (((_digit<IT>()-'0') & _repeat<0,2>(_digit<IT>())) <= _less_equal(255)) % '.';
        std::string str = "192.168.1.1"; // "192.168.1.1";
        auto it = str.begin();
        if(ip_parser(it,str.end()))
        {
            std::cout<<"yes.."<<std::endl;
        }
        else
        {
            std::cout<<"err..."<<std::endl;
        }
    }
    {
        auto ip_parser = (((_digit<IT>()-'0') & _repeat<0,2>(_digit<IT>())) <= _less_equal(255)) % '.';
        std::string str = "256.168.1.1"; // "192.168.1.1";
        auto it = str.begin();
        if(ip_parser(it,str.end()))
        {
            std::cout<<"yes.."<<std::endl;
        }
        else
        {
            std::cout<<"err..."<<std::endl;
        }
    }
}


