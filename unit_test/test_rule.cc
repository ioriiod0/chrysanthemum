// ======================================================================================
// File         : test_rule.cc
// Author       : Gao Lei
// Last Change  : 12/17/2011 | 20:22:39 PM | Saturday,December
// Description  : 
// ======================================================================================

#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

#include "../src/core/and_p.h"
#include "../src/core/difference_p.h"
#include "../src/core/repeat_p.h"
#include "../src/core/literal_p.h"
#include "../src/core/scanner.h"
#include "../src/core/compposer.h"
#include "../src/core/list_p.h"
#include "../src/core/not_p.h"
#include "../src/core/or_p.h"
#include "../src/core/optional_p.h"
#include "../src/core/rule.h"
#include "../src/extentions/character_parsers.h"
#include "../src/extentions/scanner_policy.h"
#include "../src/action/printer.h"
#include "../src/action/converters.h"
#include "../src/action/combiner.h"
#include "../src/action/back_inserter.h"
#include "../src/action/accumulater.h"


using namespace chrysanthemum;
using namespace chrysanthemum::ops;
using namespace std::placeholders;


struct list_node;
struct string_node;
struct member_node;


enum NODE_TYPE
{
    STRING_NODE = 0,
    OBJ_NODE = 1,
};

struct node 
{
    NODE_TYPE type;
    node() {}
    node(NODE_TYPE t):type(t) {}
    virtual ~node() {}
};

struct obj_node:public node
{
    obj_node():node(OBJ_NODE) {}
    std::vector<node*> nodes_;

    void add_child(node* p)
    {
        nodes_.push_back(p);
    }

    virtual ~obj_node() 
    {
        std::for_each(nodes_.begin(),nodes_.end(),[](node* p){delete p;} );
    }
};

struct string_node:public node
{
    string_node():node(STRING_NODE) {}

    template <typename IT>
    void assign(IT first,IT last) 
    {
        str.assign(first,last);
    }

    std::string str;
    virtual ~string_node() {}
};


void print_obj(obj_node* p)
{
    std::cout<<"{";
    for_each(p->nodes_.begin(),p->nodes_.end(),[](node* q){
                switch(q->type)
                {
                    case OBJ_NODE:
                        print_obj(static_cast<obj_node*>(q));
                        break;
                    case STRING_NODE:
                        std::cout<< static_cast<string_node*>(q)->str<<',';
                        break;
                    default: break;
                }
             });
    std::cout<<"},";
}


int main()
{

    {

        typedef std::string::iterator IT;
        typedef scanner<IT,line_counter_scanner_policy> scanner_t;

        struct grammer
        {
            rule<scanner_t,obj_node*,_space> obj;
            rule<scanner_t,string_node*,_space> str;

            grammer()
            {
                
                obj %=  '{' <= [=](IT first,IT last){ obj.cur_ctx() = new obj_node(); return true;}
                       & (   
                             str <= [=](IT first,IT last)
                                       {
                                            obj.cur_ctx()->add_child(str.pop_ctx());
                                            return true;
                                       }
                           | obj <= [=](IT first,IT last)
                                       {    
                                            auto tmp = obj.pop_ctx();
                                            obj.cur_ctx()->add_child(tmp);
                                            return true;
                                       } 
                         )  % ','
                       & '}';

                str %= +_lower() <= [=](IT first,IT last)
                                       {
                                            str.cur_ctx() = new string_node();
                                            str.cur_ctx()->assign(first,last);
                                            return true;
                                       }; 
                     
            }
            

        };

        
        grammer g; 
        std::string str = "{ aaa  , bbb , { ccc , ddd } ,{ eee , { fff } } } ";
        std::cout<<str<<std::endl;
        scanner_t scan(str.begin(),str.end());
        if(g.obj(scan))
        {
            std::cout<<"OK"<<std::endl;
            print_obj(g.obj.pop_ctx());
            std::cout<<std::endl;
        }
        else
        {
            std::cout<<"FAILED"<<std::endl;
        }

    }
}


