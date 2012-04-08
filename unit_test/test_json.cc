// ======================================================================================
// File         : test_json.cc
// Author       : Gao Lei 
// Last Change  : 12/18/2011 | 01:24:49 AM | Sunday,December
// Description  : 
// ======================================================================================
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>
#include <ext/pool_allocator.h>
#include <chrono>

#include "../all.h"
// #include "../src/core/and_p.h"
// #include "../src/core/difference_p.h"
// #include "../src/core/repeat_p.h"
// #include "../src/core/literal_p.h"
// #include "../src/core/scanner.h"
// #include "../src/core/compposer.h"
// #include "../src/core/list_p.h"
// #include "../src/core/not_p.h"
// #include "../src/core/or_p.h"
// #include "../src/core/optional_p.h"
// #include "../src/core/rule.h"
// #include "../src/extentions/character_parsers.h"
// #include "../src/extentions/scanner_policy.h"
// #include "../src/action/printer.h"
// #include "../src/action/converters.h"
// #include "../src/action/combiner.h"
// #include "../src/action/back_inserter.h"
// #include "../src/action/accumulater.h"
// #include "../src/utility/alternative.h"


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

typedef std::string json_string;
typedef double json_real;
typedef bool json_boolean;
struct json_null {};
struct json_array;
struct json_obj;


typedef chrysanthemum::alternative<
                    json_null, //JSON_NULL
                    json_real, //JSON_REAL
                    json_string, //JSON_STRING
                    json_boolean, //JSON_BOOLEAN
                    json_array, //JSON_BOOLEAN
                    json_obj /*JSON_OBJ*/ > json_value;

typedef std::pair<json_string,json_value> json_member;

struct json_obj
{
    std::map<json_string,
             json_value,
             std::less<json_string>,
             __gnu_cxx::__pool_alloc<std::pair<const json_string,json_value>>
            > map_;
};

struct json_array
{
    std::vector<json_value,__gnu_cxx::__pool_alloc<json_value> > array_;
};


struct json_grammar
{
    typedef std::string::iterator IT;    
    typedef scanner<IT,line_counter_scanner_policy> scanner_t;
    rule<scanner_t,json_obj,_space> obj;
    rule<scanner_t,json_member,_space> member;
    rule<scanner_t,json_string,_space> string;
    rule<scanner_t,json_value,_space> value;
    rule<scanner_t,json_array,_space> array;
    rule<scanner_t,json_real,_space> real;
    ////////////helpers///////////////
    rule<scanner_t,no_context,no_skip> integer;
    rule<scanner_t,char,no_skip> character;

    json_grammar()
    {


        obj %= '{' 
                &   (member <= [=](IT first,IT last)
                               {
                                    obj.cur_ctx().map_.insert(std::move(member.cur_ctx()));
                                    member.clear_ctx();
                                    return true; 
                               }
                    ) % ','
                & '}';
        ////////////////////////////////////
        member %= string <= [=](IT first,IT last) 
                             {
                                member.cur_ctx().first = std::move(string.cur_ctx());
                                string.clear_ctx();
                                return true; 
                             }
                & ':' 
                & value <= [=](IT first,IT last) 
                            {
                                member.cur_ctx().second = std::move(value.cur_ctx());
                                value.clear_ctx();
                                return true;
                            };
        /////////////////////////////////////
        string %= '"' 
                & +(character  <= [=](IT first,IT last)
                                   {
                                        string.cur_ctx() += character.cur_ctx();
                                        character.clear_ctx();
                                        return true;
                                   }
                   )
                & '"';
        ///////////////////////////////////////
        value %= string <= [=](IT first,IT last)
                            {
                                value.cur_ctx().set<JSON_STRING>(std::move(string.cur_ctx()));
                                string.clear_ctx();
                                return true;
                            }
                | real <= [=](IT first,IT last)
                            {
                                value.cur_ctx().set<JSON_REAL>(std::move(real.cur_ctx()));
                                real.clear_ctx();
                                return true;
                            }
                | obj <= [=](IT first,IT last)
                          {
                                value.cur_ctx().set<JSON_OBJ>(std::move(obj.cur_ctx()));
                                obj.clear_ctx();
                                return true;
                          }
                | array <= [=](IT first,IT last)
                            {
                                value.cur_ctx().set<JSON_ARRAY>(std::move(array.cur_ctx()));
                                array.clear_ctx();
                                return true;
                            }
                | "true" <= [=](IT first,IT last)
                            {
                                value.cur_ctx().set<JSON_BOOLEAN>(true);
                                return true; 
                            }
                | "false" <= [=](IT first,IT last)
                             {
                                value.cur_ctx().set<JSON_BOOLEAN>(false); 
                                return true;
                             }                
                | "null" <= [=](IT first,IT last)
                            {
                                value.cur_ctx().set<JSON_NULL>(json_null());
                                return true;
                            };
        /////////////////////////////////////////
        array %= '[' 
                & (value <= [=](IT first,IT last)
                             {
                                array.cur_ctx().array_.push_back(std::move(value.cur_ctx()));
                                value.clear_ctx();
                                return true;
                             }
                  ) % ','
                & ']';
        ////////////////////////////////////////////
        real %= (   integer 
                  & -(  
                        '.' 
                       & +_digit()
                       & -(   
                            ( _literal('e') | 'E' ) 
                            & integer 
                          )
                      )
                ) <= [=](IT first,IT last) 
                      {
                            real.cur_ctx() = strtod(&(*first),NULL);
                            return true;
                      };

        ////////////////////////////////////////////
        integer %=  -(_literal('+') | '-') 
                   & +_digit() ;

        character %=  (_any() - _cntrl() - '"' - '\\') 
                            <= [=](IT first,IT last)
                                {
                                    character.cur_ctx() = *first;
                                    return true;
                                }
                    | "\\\"" <= [=](IT first,IT last) {character.cur_ctx() = '"';return true;}
                    | "\\\\" <= [=](IT first,IT last) {character.cur_ctx() = '\\';return true;}
                    | "\\/" <= [=](IT first,IT last) {character.cur_ctx() = '/';return true;}
                    | "\\b" <= [=](IT first,IT last) {character.cur_ctx() = '\b';return true;}
                    | "\\f" <= [=](IT first,IT last) {character.cur_ctx() = '\f';return true;}
                    | "\\n" <= [=](IT first,IT last) {character.cur_ctx() = '\n';return true;}
                    | "\\r" <= [=](IT first,IT last) {character.cur_ctx() = '\r';return true;}
                    | "\\t" <= [=](IT first,IT last) {character.cur_ctx() = '\t';return true;}
                    | (
                       "\\u"
                       & (_digit()&_digit()) 
                                <= [=](IT first,IT last) {
                                    int i = *first++ - '0';
                                    i = i*10 + (*first-'0');
                                    character.cur_ctx() = (char)i;
                                    return true;}
                      );



    }

    
};



void print_json_obj(const json_obj& t);
void print_json_array(const json_array& t);

void print_json_string(const json_string& t)
{
    std::cout<<t;
}

void print_json_boolean(const json_boolean& t)
{
    if(t)
        std::cout<<"true";
    else
        std::cout<<"false";
}

void print_json_real(const json_real& t)
{
    std::cout<<t;
}
void print_json_null(const json_null& t)
{
    std::cout<<"null";
}


void print_json_value(const json_value& t)
{
    switch(t.which())
    {
        case JSON_STRING: 
            print_json_string(t.get<JSON_STRING>());
            break;
        case JSON_BOOLEAN:
            print_json_boolean(t.get<JSON_BOOLEAN>());  
            break;         
        case JSON_ARRAY:
            print_json_array(t.get<JSON_ARRAY>());   
            break;
        case JSON_OBJ:
            print_json_obj(t.get<JSON_OBJ>());  
            break;
        case JSON_REAL:
            print_json_real(t.get<JSON_REAL>());  
            break;
        case JSON_NULL:
            print_json_null(t.get<JSON_NULL>()); 
            break;
        default:
            break;
    }
   
}

void print_json_obj(const json_obj& t)
{
    std::cout<<"{";
    typedef typename std::map<json_string,json_value>::value_type value_type;
    std::for_each(t.map_.begin(),t.map_.end(),[](const value_type& v){
                  std::cout<<v.first<<":";
                  print_json_value(v.second);
                  std::cout<<",";
                  });
    std::cout<<"}";
}
void print_json_array(const json_array& t)
{
  std::cout<<"[";
    std::for_each(t.array_.begin(),t.array_.end(),[](const json_value& v){
                  print_json_value(v);
                  std::cout<<",";
                  });
    std::cout<<"]";

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
        print_json_obj(g.obj.cur_ctx()); 
        g.obj.clear_ctx();
        std::cout<<std::endl;
    }
    else
    {
        std::cout<<"FAILED"<<std::endl;
    }

    auto t1 = std::chrono::system_clock::now();
    for(std::size_t i=0;i<100000;++i)
    {
        scanner_t scan(data.begin(),data.end());
        g.obj(scan);
        g.obj.clear_ctx();
    }
    auto t2 = std::chrono::system_clock::now();
    auto delta = t2 - t1;
    std::cout<<delta.count()<<std::endl;


}

