// ======================================================================================
// File         : test_alternative.cc
// Author       : Lei Gao , Qianhong Wang
// Last Change  : 02/15/2012 | 14:37:23 PM | Wednesday,February
// Description  : 
// ======================================================================================


#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>

#include "../src/utility/alternative.h"
using namespace chrysanthemum;

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

    {
        typedef std::map<std::string,std::string> map_type;
        typedef alternative<int, //0
                 std::string, //1
                 std::vector<char>, //2
                 map_type //3
                 > my_type; 
        my_type alternative_,tmp;
        alternative_.set<0>(100000);
        std::cout<<alternative_.which()<<":"<<alternative_.get<0>()<<std::endl;
        tmp = alternative_;
        std::cout<<"copy:"<<tmp.which()<<":"<<tmp.get<0>()<<std::endl;
        tmp = std::move(alternative_);
        std::cout<<"move:"<<tmp.which()<<":"<<tmp.get<0>()<<std::endl;
        ////////////////////////////////////////////////////
        alternative_.set<1>("fuck ~~~~~~");
        std::cout<<alternative_.which()<<":"<<alternative_.get<1>()<<std::endl;
        tmp = alternative_;
        std::cout<<"copy:"<<tmp.which()<<":"<<tmp.get<1>()<<std::endl;
        tmp = std::move(alternative_);
        std::cout<<"move:"<<tmp.which()<<":"<<tmp.get<1>()<<std::endl;
        ///////////////////////////////////
        alternative_.set<2>({'a','b','c','d'});
        std::cout<<alternative_.which()<<":";/*<<alternative_.get<5>()*/
        std::for_each(alternative_.get<2>().begin(),alternative_.get<2>().end(),[](char ch){std::cout<<ch<<",";});
        std::cout<<std::endl;
        tmp = alternative_;
        std::cout<<"copy:"<<tmp.which()<<":";/*<<alternative_.get<5>()*/
        std::for_each(tmp.get<2>().begin(),tmp.get<2>().end(),[](char ch){std::cout<<ch<<",";});
        std::cout<<std::endl;
        tmp = std::move(alternative_);
        std::cout<<"move:"<<tmp.which()<<":";/*<<alternative_.get<5>()*/
        std::for_each(tmp.get<2>().begin(),tmp.get<2>().end(),[](char ch){std::cout<<ch<<",";});
        std::cout<<std::endl;
        /////////////////////
        map_type m = { {"1","one"},{"2","two"} };
        alternative_.set<3>(m);
        std::cout<<alternative_.which()<<":"<<std::endl;
        std::for_each(alternative_.get<3>().begin(),alternative_.get<3>().end(),
                       [](const map_type::value_type& t)
                       {
                            std::cout<<t.first<<":"<<t.second<<",";
                       });
        std::cout<<std::endl;
        tmp = alternative_;
        std::cout<<"copy:"<<tmp.which()<<":";/*<<alternative_.get<5>()*/
        std::for_each(tmp.get<3>().begin(),tmp.get<3>().end(),
                       [](const map_type::value_type& t)
                       {
                            std::cout<<t.first<<":"<<t.second<<",";
                       });
        std::cout<<std::endl;
        tmp = std::move(alternative_);
        std::cout<<"move"<<tmp.which()<<":";/*<<alternative_.get<5>()*/
        std::for_each(tmp.get<3>().begin(),tmp.get<3>().end(),
                       [](const map_type::value_type& t)
                       {
                            std::cout<<t.first<<":"<<t.second<<",";
                       });
        std::cout<<std::endl;
        //////////////////////



    }

}

