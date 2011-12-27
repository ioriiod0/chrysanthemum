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
#include "../src/utility/analysis_stack.h"

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



int main()
{

    {
        using namespace std::placeholders;
        typedef std::string::iterator IT;

        struct grammer
        {
            rule<IT,no_skip> list,str,member;
            std::stack<node*> stack_;

            grammer()
            {
                list %= _void() <= std::bind(&grammer::push_list,this,_1,_2)
                       & '{' 
                       & (member <= std::bind(&grammer::on_member,this,_1,_2)) % ','
                       & '}';
                member %= _void() <= std::bind(&grammer::push_member,this,_1,_2) &
                         (str <= std::bind(&grammer::on_string,this,_1,_2)
                         | list <= std::bind(&grammer::on_list,this,_1,_2));
                str %= _void() <= std::bind(&grammer::push_string,this,_1,_2)
                         & _repeat<0,INFINITE>(_loalpha()) <= std::bind(&grammer::on_string2,this,_1,_2); 
            }
            
            bool push_list(IT first,IT last)
            {
                std::cout<<"push list"<<std::endl;
                list_node* p = new list_node;
                stack_.push(p);
                return true;
            }

            bool push_string(IT first,IT last)
            {
                std::cout<<"push string"<<std::endl;
                string_node* p = new string_node;
                stack_.push(p);
                return true;
            }

            bool push_member(IT first,IT last)
            {
                std::cout<<"push member"<<std::endl;
                member_node* p = new member_node;
                stack_.push(p);
                return true;
            }

            bool on_member(IT first,IT last)
            {
                std::cout<<"on member"<<std::endl;
                member_node* p = (member_node*)stack_.top();
                stack_.pop();
                list_node* q = (list_node*)stack_.top();
                q->nodes_.push_back(p);
                return true;
            }

            bool on_list(IT first,IT last)
            {
                std::cout<<"on list"<<std::endl;
                list_node* p = (list_node*)stack_.top();
                stack_.pop();
                member_node* q = (member_node*)stack_.top();
                q->type = LIST_NODE;
                q->p_node = p;
                return true;
            }

            bool on_string(IT first,IT last)
            {
                std::cout<<"on string"<<std::endl;
                string_node* p = (string_node*)stack_.top();
                stack_.pop();
                member_node* q = (member_node*)stack_.top();
                q->type = STRING_NODE;
                q->p_node = p;
                return true;
            }

            bool on_string2(IT first,IT last)
            {
                std::cout<<"on string2"<<std::endl;
                string_node* p =(string_node*) stack_.top();
                p->str.assign(first,last);
                return true;
            }

            list_node* ctx()
            {
                return (list_node*)stack_.top();
            }

        };

        
        grammer g; 
        //std::string str = "{aaa,bbb,{ccc,ddd},{eee,{fff}}}";
        std::string str = "{aaa,{bbb}}";
        IT it = str.begin();
        if(g.list(it,str.end()))
        {
            std::cout<<"OK"<<std::endl;
        }
        else
        {
            std::cout<<"FAILED"<<std::endl;
        }

    }
}
