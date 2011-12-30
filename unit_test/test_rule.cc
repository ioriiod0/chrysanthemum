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

#include "../src/compound/and_p.h"
#include "../src/compound/or_p.h"
#include "../src/compound/repeat_p.h"
#include "../src/compound/literal_p.h"
#include "../src/compound/list_p.h"
#include "../src/parsers/basic_parsers.h"
#include "../src/parsers/rule.h"
#include "../src/converter/converters.h"
#include "../src/action/printer.h"
#include "../src/action/back_inserter.h"
#include "../src/action/accumulater.h"
#include "../src/parsers/compposer.h"
#include "../src/action/function_wrapper.h"


using namespace chrysanthemum;


struct list_node;
struct string_node;
struct member_node;


enum NODE_TYPE
{
    STRING_NODE = 0,
    LIST_NODE = 1,
};

struct node 
{
    // node() {}
    // node(NODE_TYPE T):type(t) {}
    virtual ~node() {}
};

struct list_node:public node
{
    // list_node():node(LIST_NODE) {}
    std::vector<member_node*> nodes_;
};

struct string_node:public node
{
    // string_node():node(STRING_NODE) {}
    std::string str;
};

struct member_node:public node
{
    NODE_TYPE type;
    node* p_node;
};


void print_list(list_node* p);
void print_member(member_node* p);
void print_str(string_node* p);

void print_member(member_node* p)
{
    if(p->type == STRING_NODE)
    {
        print_str((string_node*)p->p_node);
        std::cout<<",";
    }
    else
    {
        print_list((list_node*) p->p_node);
        std::cout<<",";
    }
}

void print_list(list_node* p)
{
    std::cout<<"{";
    for_each(p->nodes_.begin(),p->nodes_.end(),print_member);
    std::cout<<"}";
}

void print_str(string_node* p)
{
    std::cout<<p->str;
}


int main()
{

    {
        using namespace std::placeholders;
        typedef std::string::iterator IT;

        struct grammer
        {
            rule<IT,list_node> list;
            rule<IT,string_node> str;
            rule<IT,member_node> member;

            grammer()
            {
                using namespace chrysanthemum::ops;
                
                list %=  '{'
                       &  (member <= [=](IT first,IT last) 
                                    {
                                        member_node* p = new member_node(member.cur_ctx());
                                        list.cur_ctx().nodes_.push_back(p);
                                        member.clear_ctx();
                                        return true;
                                    })  % ','
                       & '}';

                member %=  str <= [=](IT first,IT last)
                                 {
                                    string_node* p = new string_node(str.cur_ctx());
                                    member.cur_ctx().type = STRING_NODE;
                                    member.cur_ctx().p_node = p;
                                    str.clear_ctx();
                                    return true;
                                 }
                          |list <= [=](IT first,IT last)
                                  {
                                      list_node* p = new list_node(list.cur_ctx());
                                      member.cur_ctx().type = LIST_NODE;
                                      member.cur_ctx().p_node = p;
                                      list.clear_ctx();
                                      return true;
                                  }; 

                str %= _repeat<1,INFINITE>(_loalpha())
                            <= [=](IT first,IT last)
                                {
                                    str.cur_ctx().str.assign(first,last);
                                    return true;
                                }; 
                     
            }
            

        };

        
        grammer g; 
        std::string str = "{ aaa \r\n , bbb \t\n, { ccc , ddd } \r\n,{ eee , { fff } } } ";
        std::cout<<str<<std::endl;
        IT it = str.begin();
        if(g.list(it,str.end()))
        {
            std::cout<<"OK"<<std::endl;
            print_list(&g.list.cur_ctx());
            std::cout<<std::endl;
        }
        else
        {
            std::cout<<"FAILED"<<std::endl;
        }

    }
}


