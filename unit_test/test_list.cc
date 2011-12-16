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
#include "../src/action/back_inserter.h"
#include "../src/action/converters.h"
#include "../src/parsers/parsers.h"


int main()
{

    typedef std::string::iterator IT;
    std::vector<std::size_t> vec;
    auto ip_parser = (_repeat<1,3>(_digit<IT>()) 
                        <= make_back_inserter<IT,str_to_numeric<IT,std::size_t>>(vec)) % '.';
    std::string str = "192.168.1.1"; // "192.168.1.1";
    auto it = str.begin();
    if(ip_parser(it,str.end()))
    {
        std::for_each(vec.begin(),vec.end(),[](std::size_t i){
                      std::cout<<i<<std::endl;
                      });
        std::cout<<"................."<<std::endl;
    }
    else
    {
        std::cout<<"err..."<<std::endl;
    }   

}


