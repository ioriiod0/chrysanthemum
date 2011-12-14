// ======================================================================================
// File         : test_ip.cc
// Author       : Gao Lei 
// Last Change  : 12/02/2011 | 01:36:05 AM | Friday,December
// Description  : 
// ======================================================================================


#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

//#include "../all.h"
#include "literal_p.h"
#include "and_p.h"
#include "or_p.h"
#include "../action/action.h"
#include "../parsers/parsers.h"




int main()
{

    {
        std::size_t sum=0;
        std::string str ="192"; // "192.168.1.1";
        auto it = str.begin();
        auto p = _repeat<1,4>(_digit()) <= ACCUMULATER(sum);
        if(p(it,str.end()))
        {
            std::cout<<sum<<std::endl;
        }
        else
        {
            std::cout<<"fuck"<<std::endl;
        }
    }

    {
        auto lit = _literal('.');
        std::string str ="."; // "192.168.1.1";
        auto it = str.begin();
        if(lit(it,str.end()))
        {
            std::cout<<lit.data()<<std::endl;
        }
        else
        {
            std::cout<<"fuck"<<std::endl;
        }

    }

    {
        std::size_t adress1=0;
        std::size_t adress2=0;
        std::size_t adress3=0;
        std::size_t adress4=0;

        auto lit = _literal('.');

        auto ip_parser = _sequence( _repeat<1,3>(_digit()) <= ACCUMULATER(adress1),
                                    lit,
                                     _repeat<1,3>(_digit()) <= ACCUMULATER(adress2),
                                    lit,
                                    _repeat<1,3>(_digit()) <= ACCUMULATER(adress3),
                                    lit,
                                    _repeat<1,3>(_digit()) <= ACCUMULATER(adress4)
                                  );

        std::string str ="192.168.1.1"; // "192.168.1.1";
        auto it = str.begin();
        if(ip_parser(it,str.end()))
        {
            std::cout<<adress1<<std::endl;
            std::cout<<adress2<<std::endl;
            std::cout<<adress3<<std::endl;
            std::cout<<adress4<<std::endl;
        }
        else
        {
            std::cout<<"err..."<<std::endl;
        }   
    }

}


