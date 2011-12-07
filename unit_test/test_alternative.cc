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

#include "../all.h"

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
    typedef alternative<int, //0
             int, //1
             int, //2
             int, //3
             std::string, //4
             std::vector<char>, //5
             double, //6
             tester> my_type; //7
    my_type alternative_;
    alternative_.set<0>(10);
    std::cout<<alternative_.which()<<":"<<alternative_.get<0>()<<std::endl;
    ////////////////////////////////////////////////////
    alternative_.set<1>(19);
    std::cout<<alternative_.which()<<":"<<alternative_.get<1>()<<std::endl;
    ///////////////////////////////////
    alternative_.set<4>("lalala");
    std::cout<<alternative_.which()<<":"<<alternative_.get<4>()<<std::endl;
  
    alternative_.set<5>({'a','b','c','d'});
    std::cout<<alternative_.which()<<":";/*<<alternative_.get<5>()*/
    std::for_each(alternative_.get<5>().begin(),alternative_.get<5>().end(),[](char ch){std::cout<<ch<<",";});
    std::cout<<std::endl;
    /////////////////////
    alternative_.set<7>(tester());
    std::cout<<alternative_.which()<<":"<<std::endl;
    //////////////////////
    alternative_.set<6>(345346246373);
    std::cout<<alternative_.which()<<":"<<alternative_.get<6>()<<std::endl;
    //////////////////////

    std::cout<<my_type::buffer_size<<std::endl;



}

