// ====================================================================================
// Copyright (c) 2013, ioriiod0@gmail.com All rights reserved.
// File         : json.cc
// Author       : ioriiod0@gmail.com
// Last Change  : 02/02/2013 03:20 PM
// Description  : 
// ====================================================================================

#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>
#include <chrono>
#include <cassert>
#include "../chrysanthemum/all.h"

using namespace chrysanthemum; 
using namespace chrysanthemum::ops;


enum json_value_type
{
    JSON_NULL = 0,
    JSON_REAL ,
    JSON_STRING ,
    JSON_BOOLEAN ,
    JSON_ARRAY ,
    JSON_OBJ
};

typedef std::string::iterator IT;

struct json_value {
    int type;
    json_value(int t):type(t) {

    }
    virtual ~json_value() {}
    virtual void print()=0;
};

struct json_string:public json_value {
    json_string():json_value(JSON_STRING) {

    }
    virtual ~json_string() {}
    virtual void print() {
        std::cout<<data;
    }
    std::string data;
};

struct json_null:public json_value {
    json_null():json_value(JSON_NULL) {

    }
    virtual ~json_null() {}
    virtual void print() {
        std::cout<<"null";
    }
};

struct json_real:public json_value {
    json_real():json_value(JSON_REAL) {

    }
    virtual ~json_real() {}
    virtual void print() {
        std::cout<<data;
    }
    double data;
};

struct json_boolean:public json_value {
    json_boolean():json_value(JSON_BOOLEAN) {

    }
    virtual ~json_boolean() {}
    virtual void print() {
        if(data)
            std::cout<<"true";
        else
            std::cout<<"false";
    }
    bool data;
};

struct json_array:public json_value {
    json_array():json_value(JSON_ARRAY) {

    }
    virtual ~json_array() {
        for(auto v:data) {
            delete v;
        }
    }
    virtual void print() {
        std::cout<<"[";
        for(auto v:data) {
            v->print();
            std::cout<<",";
        }
        std::cout<<"]";
    }
    std::vector<json_value*> data;
};

struct json_obj:public json_value {
    json_obj():json_value(JSON_OBJ) {

    }
    virtual ~json_obj() {
        for(const auto& v:data) {
            delete v.second;
        }
    }
    virtual void print() {
        std::cout<<"{";
        for(const auto& v:data) {
            std::cout<<v.first<<":";
            v.second->print();
            std::cout<<",";
        }
        std::cout<<"}";
    }
    std::map<std::string,json_value*> data;
};

////////////////////////////////////////////////////////////////////////////
std::string unescope_string(IT first,IT last);

struct json_grammar
{
    typedef std::string::iterator IT;    
    typedef scanner<IT,line_counter_scanner_policy> scanner_t;
    
    ///////////////////////////////////////////
    rule<scanner_t,json_obj*,_space> obj;
    rule<scanner_t,json_string*,_space> string;
    rule<scanner_t,json_value*,_space> value;
    rule<scanner_t,json_array*,_space> array;
    rule<scanner_t,json_real*,_space> real;
    rule<scanner_t,json_boolean*,_space> boolean;
    rule<scanner_t,json_null*,_space> null;
    //////////////////
    rule<scanner_t,no_context,no_skip> integer;
    rule<scanner_t,no_context,no_skip> character;

    json_grammar()
    {
        ///////////////////helpers//////////////////////
        integer %=  -(_literal('+') | '-') & +_digit() ;
        character %=  (_any() - _cntrl() - '"' - '\\')
                    | "\\\"" | "\\\\" | "\\/" | "\\b"
                    | "\\f" | "\\n" | "\\r" | "\\t"
                    | ( "\\u" & (_N<4>(_digit())));
        /////////////////////////////////////////
        obj.on_init([](json_obj*& p){p = new json_obj();});
        obj.on_error([](json_obj*& p){delete p;});
        obj %=  '{'
                &((string & ':' & value)
                    <=  [=](IT first,IT last) {
                            obj.cur_ctx()->data[string.pop_ctx()->data] = value.pop_ctx();
                            return true;
                        }) % ','
                &'}';
        ///////////////////////////////////////
        string.on_init([](json_string*& p){p=new json_string();});
        string.on_error([](json_string*& p){delete p;});
        string %=   '"'
                    &(+(character)) <=  [=](IT first,IT last) {
                                            //std::cout<<std::string(first,last);
                                            string.cur_ctx()->data = unescope_string(first,last);
                                            return true;
                                        }
                    &'"';
        ///////////////////////////////////////
        null.on_init([](json_null*& p){p=new json_null();});
        null.on_error([](json_null*& p){delete p;});
        null %= _literal("null");
        /////////////////////////////////
        boolean.on_init([](json_boolean*& p){p=new json_boolean();});
        boolean.on_error([](json_boolean*& p){delete p;});
        boolean %= "true" <=    [=](IT first,IT last) {
                                    boolean.cur_ctx()->data = true;
                                    return true;
                                }
                | "false" <=    [=](IT first,IT last) {
                                    boolean.cur_ctx()->data = false;
                                    return true;
                                };
        /////////////////////////////////////////
        value %=  string <= [=](IT first,IT last) {
                                value.cur_ctx() = string.pop_ctx();
                                return true;
                            }
                |real  <=   [=](IT first,IT last) {
                                value.cur_ctx() = real.pop_ctx();
                                return true;
                            }
                |obj   <=   [=](IT first,IT last) {
                                value.cur_ctx() = obj.pop_ctx();
                                return true; 
                            }
                |array <=   [=](IT first,IT last) {
                                value.cur_ctx() = array.pop_ctx();
                                return true;
                            }
                |boolean<=  [=](IT first,IT last) {
                                value.cur_ctx() = boolean.pop_ctx();
                                return true;
                            }
                |null <=    [=](IT first,IT last) {
                                value.cur_ctx() = null.pop_ctx();
                                return true; 
                            };
        /////////////////////////////////////////
        array.on_init([](json_array*& p){p=new json_array();});
        array.on_error([](json_array*& p){delete p;});
        array %= '['
                & (value <= [=](IT first,IT last) {
                                array.cur_ctx()->data.push_back(value.pop_ctx());
                                return true; 
                            }) % ','
                & ']';
        ////////////////////////////////////////////
        real.on_init([](json_real*& p){p=new json_real();});
        real.on_error([](json_real*& p){delete p;});
        real %= (integer & -( '.'  & +_digit()) & -( ( _literal('e') | 'E' ) & integer))
                    <= [=](IT first,IT last) {
                        real.cur_ctx()->data = converter<double>::do_convert(first,last);
                        return true;
                    };
    }
    
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string unescope_string(IT first,IT last) {
    std::string ret;
    ret.reserve(32);
    for(;first!=last;++first) {
        if(*first == '\\') {
            switch(*++first) {
                case '\\':
                    ret+='\\';
                    break;
                case 'b':
                    ret+='\b';
                    break;
                case 'f':
                    ret+='\f';
                    break;
                case 't':
                    ret+='\t';
                    break;
                case 'r':
                    ret+='\r';
                    break;
                case 'n':
                    ret+='\n';
                    break;
                case 'u':
                    ret+=(char) converter<int,16>::do_convert(first+1,first+5);
                    first+=4;
                    break;
                default:
                    assert(false);
                    break;         
            }
        } else {
            ret += *first;
        }
    }
    return ret;
}



int main(int argc,const char* argv[])
{
    typedef std::string::iterator IT;
    typedef scanner<IT,line_counter_scanner_policy> scanner_t;
    std::ifstream fs(argv[1]); 
    std::ostringstream ss; 
    ss << fs.rdbuf(); 
    std::string data = ss.str();
    scanner_t scan(data.begin(),data.end());
    json_grammar g;

    if(g.obj(scan))
    {
        std::cout<<"OK"<<std::endl;
        auto p = g.obj.pop_ctx();
        p->print();
        delete p;
        std::cout<<std::endl;
    }
    else
    {
        std::cout<<"FAILED"<<std::endl;
    }

    return 0;
}

