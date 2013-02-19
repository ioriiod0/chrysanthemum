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

#include "../chrysanthemum/all.h"

using namespace chrysanthemum;
using namespace chrysanthemum::ops;
using namespace std::placeholders;

enum NODE_TYPE
{
    STRING_NODE = 0,
    LIST_NODE = 1,
};

struct node 
{
    NODE_TYPE type;
    node() {}
    node(NODE_TYPE t):type(t) {}
    virtual ~node() {}
};

struct list_node:public node
{
    list_node():node(LIST_NODE) {}
    std::vector<node*> nodes_;

    void add_child(node* p)

    {
        nodes_.push_back(p);
    }

    virtual ~list_node() 
    {
        std::for_each(nodes_.begin(),nodes_.end(),[](node* p){delete p;} );
    }
};

struct string_node:public node
{
    string_node():node(STRING_NODE) {}
    virtual ~string_node() {}

    template <typename IT>
    void assign(IT first,IT last) 
    {
        str.assign(first,last);
    }

    std::string str;
};


void print_obj(list_node* p)
{
    std::cout<<"{";
    for_each(p->nodes_.begin(),p->nodes_.end(),[](node* q){
                switch(q->type) {
                    case LIST_NODE:
                        print_obj(static_cast<list_node*>(q));
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
            rule<scanner_t,list_node*,_space> obj;
            rule<scanner_t,string_node*,_space> str;

            grammer()
            {
                obj.on_init([](list_node*& p){p=new list_node();});
                obj.on_error([](list_node*& p){delete p;});
                obj %=  '{'
                       & (   
                             str <= [=](IT first,IT last) {
                                        obj.cur_ctx()->add_child(str.pop_ctx());
                                        return true;
                                    }
                           | obj <= [=](IT first,IT last) {    
                                        auto p = obj.pop_ctx();
                                        obj.cur_ctx()->add_child(p);
                                        return true;
                                    } 
                         )  % ','
                       & '}';

                str.on_init([](string_node*& p){p=new string_node();});
                str.on_error([](string_node*& p){delete p;});
                str %= +_lower() <= [=](IT first,IT last) {
                                            str.cur_ctx()->assign(first,last);
                                            return true;
                                    };
                     
            }
            

        };

        
        grammer g;
        std::string str = "{ aaa  , bbb ,{ccc}, {{ddd},eee} } ";
        std::cout<<str<<std::endl;
        scanner_t scan(str.begin(),str.end());
        if(g.obj(scan))
        {
            std::cout<<"OK"<<std::endl;
            auto p = g.obj.pop_ctx();
            print_obj(p);
            delete p;
            std::cout<<std::endl;
        }
        else
        {
            std::cout<<"FAILED"<<std::endl;
        }

    }
}


