// ======================================================================================
// File         : test_variant.h
// Author       : Gao Lei 
// Last Change  : 12/04/2011 | 21:12:11 PM | Sunday,December
// Description  : 
// ======================================================================================


#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "mutiple.h"

struct tester
{
    char buffer_[100];
    tester()
    {
        std::cout<<"construct tester"<<std::endl;
    }
    ~tester()
    {
        std::cout<<"desconstruct tester"<<std::endl;
    }
};

int main()
{
    typedef mutiple<int, //0
             int, //1
             int, //2
             int, //3
             std::string, //4
             std::vector<char>, //5
             double, //6
             tester> M; //7
    M mutiple_;
    mutiple_.set<0>(10);
    std::cout<<mutiple_.which()<<":"<<mutiple_.get<0>()<<std::endl;
    ////////////////////////////////////////////////////
    mutiple_.set<1>(19);
    std::cout<<mutiple_.which()<<":"<<mutiple_.get<1>()<<std::endl;
    ///////////////////////////////////
    mutiple_.set<4>("lalala");
    std::cout<<mutiple_.which()<<":"<<mutiple_.get<4>()<<std::endl;
  
    mutiple_.set<5>({'a','b','c','d'});
    std::cout<<mutiple_.which()<<":";/*<<mutiple_.get<5>()*/
    std::for_each(mutiple_.get<5>().begin(),mutiple_.get<5>().end(),[](char ch){std::cout<<ch<<",";});
    std::cout<<std::endl;
    /////////////////////
    mutiple_.set<7>(tester());
    std::cout<<mutiple_.which()<<":"<<std::endl;
    //////////////////////
    mutiple_.set<6>(345346246373);
    std::cout<<mutiple_.which()<<":"<<mutiple_.get<6>()<<std::endl;
    //////////////////////

    std::cout<<M::buffer_size<<std::endl;


}

