// ======================================================================================
// File         : test_variant.h
// Author       : Gao Lei 
// Last Change  : 12/04/2011 | 21:12:11 PM | Sunday,December
// Description  : 
// ======================================================================================


#include <iostream>
#include <string>

#include "mutiple.h"


int main()
{
    typedef mutiple< choice<1,int>,
             choice<3,int>,
             choice<2,char>,
             choice<5,int>,
             choice<10,std::string>,
             choice<18,double> > M;
    M mutiple_;
    mutiple_.set<1>(10);
    std::cout<<mutiple_.which()<<":"<<mutiple_.get<1>()<<std::endl;
    mutiple_.set<3>(19);
    std::cout<<mutiple_.which()<<":"<<mutiple_.get<3>()<<std::endl;
    mutiple_.set<2>('a');
    std::cout<<mutiple_.which()<<":"<<mutiple_.get<2>()<<std::endl;
    // mutiple_.set<3>('c');
    // std::cout<<mutiple_.which()<<":"<<mutiple_.get<3>()<<std::endl;   
    mutiple_.set<5>(123143);
    std::cout<<mutiple_.which()<<":"<<mutiple_.get<5>()<<std::endl;
    //////////////////////
    mutiple_.set<10>("hello world");
    std::cout<<mutiple_.which()<<":"<<mutiple_.get<10>()<<std::endl;

    // mutiple_.set<10>(334435363643);
    // std::cout<<mutiple_.which()<<":"<<mutiple_.get<10>()<<std::endl;
    std::cout<<M::buffer_size<<std::endl;


}

