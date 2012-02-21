// ======================================================================================
// File         : json_script.cc
// Author       : Lei Gao 
// Last Change  : 02/21/2012 | 13:29:32 PM | Tuesday,February
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

/////////forward declaration/////////
struct value_t;

struct logical_OR_expression_t;
struct logical_AND_expression_t;
struct inclusive_OR_expression_t;
struct exclusive_OR_expression_t;
struct AND_expression_t;
struct equality_expression_t;
struct relational_expression_t;
struct shift_expression_t;
struct additive_expresssion_t;
struct mutiplicative_expression_t;
struct unary_expression_t;
struct postfix_expression_t;
struct expressions_t;
struct expression_t;
struct assignment_expression_t;
struct conditional_expression_t;
struct constant_expression_t;
struct symbol;
struct closure_t; //for block
struct declaration_t;
struct declarator_t;
struct init_declarator_t;
struct initializer_t;
struct function_t;
struct translation_unit_t;
////////////////////
struct symbol
{
    std::string name;
    std::size_t id;
};
/////////////values///////////////

struct value_t
{
    enum json_value_type
    {
        JSON_NULL = 0,
        JSON_REAL ,
        JSON_STRING ,
        JSON_BOOLEAN ,
        JSON_ARRAY ,
        JSON_OBJ
    };
    json_value_type type;
    value_t(json_value_type t):type(t) {}
};

struct json_string_t :public value_t
{
    std::string str;
    json_string_t():value_t(JSON_STRING) 
    {
        str.reverse(32);
    }

    struct hasher
    {
        std::size_t operator()(const json_string& t) const
        {
            return std::hasher<std::string>(t.str);
        }
    };

    struct equal_to
    {
        bool operator()(const json_string& l,const json_string& r) const
        {
            return l.str == r.str;
        }
    };

};

struct json_real_t:public value_t
{
    double n;
    json_real_t():value_t(JSON_REAL) {}
};

struct json_boolean_t :public value_t
{
    bool b;
    json_boolean_t():value_t(JSON_BOOLEAN) {}
};

struct json_null_t:public value_t
{
    json_null_t():value_t(JSON_NULL) {}
};

struct json_array_t:public value_t
{
    std::vector<value_t*> v;
    json_array_t():value_t(JSON_ARRAY) {}
};

struct json_obj_t:public value_t
{
    std::unordered_map<json_string,value_t*,json_string::hasher,json_string::equal_to> m;
    json_obj_t():value_t(JSON_OBJ) {}
};

//////////////statement//////////////


struct statement_t
{
    enum statement_type
    {
        IF_S = 0,
        IF_ELSE_S ,
        WHILE_S ,
        DO_WHILE_S ,
        FOR_S ,
        CONTINUE_S,
        BREAK_S,
        RETURN_S,
    };
    statement_type type;
    statement_t(statement_type t):type(t) {}
};

struct statement_wrapper
{
    statement_t* s;
};

struct if_statement_t:public statement_t
{
    if_statement_t():statement_t(IF_S),e(NULL),s(NULL){}
};

struct if_else_statement_t:public statement_t
{
    expression_t* e;
    statement_t* s;
    if_else_statement_t():statement_t(IF_ELSE_S),e(NULL),s(NULL){}
};

struct while_statement_t:public statement_t
{
    expression_t* e;
    statement* s
    while_statement_t():statement_t(WHILE_S),e(NULL),s(NULL){}
};

struct do_while_statement_t:public statement_t
{
    expression_t* e;
    statement* s;
    do_while_statement_t():statement_t(DO_WHILE_S),e(NULL),s(NULL) {}
};

struct for_statement_t:public statement_t
{
    expression_t* e1;
    expression_t* e2;
    expression_t* e3;
    statement* s;
    for_statement_t():statement_t(FOR_S),e1(NULL),e2(NULL),e3(NULL),s(NULL) {}
};

struct continue_statement_t:public statement_t
{
    continue_statement_t():statement_t(CONTINUE_S) {}
};

struct break_statement_t:public statement_t
{
    break_statement_t():statement_t(BREAK_S) {}
};

struct return_statement_t:public statement_t
{
    expression_t* e;
    return_statement_t():statement_t(RETURN_S),e(NULL) {}
};

//////////////////expression_t////////////////////

struct expression_t 
{
    enum expression_type
    {
        ASSIGNMENT_E=0,
        CONDITIONAL_E,
        CONSTANT_E,
        LOGICAL_OR_E,
        LOGICAL_AND_E,
        INCLUSIVE_OR_E,
        EXCLUSIVE_OR_E,
        AND_E,
        EQUALITY_E,
        RELATIONAL_E,
        SHIFT_E,
        ADDITIVE_E,
        MUTIPLICATIVE_E,
        UNARY_E,
        POSTFIX_E,

    };
    expression_type type;
    expression_t(expression_type t):type(t) {}
};

struct expressions_t ////for expression
{
    std::list<expression_t*> l;
};



struct assignment_expression_t
{
    enum assignment_type
    {
        ASSIGNMENT = 0;
        MUTIPLE_ASSIGNMENT,
        DEVIVED_ASSIGNMENT,
        MODULO_ASSIGNMENT,
        ADD_ASSIGNMENT,
        MINUS_ASSIGNMENT,
        LEFT_SHIFT_ASSIGNMENT,
        RIGHT_SHIFT_ASSIGNMENT,
        AND_ASSIGNMENT,
        EXCLUSIVE_OR_ASSIGNMENT,
        INCLUSIVE_OR_ASSIGNMENT
    };
    struct obj_t { unary_expression_t* e; assignment_type type;};
    std::list<obj_t> l;
    conditional_expression_t* e;
    assignment_expression_t():expression_t(ASSIGNMENT_E),l(NULL),e(NULL) {}
};

struct conditional_expression_t
{
    logical_OR_expression_t* e;
    conditional_expression_t():expression_t(LOGICAL_OR_E),e(NULL) {}
};

struct constant_expression_t
{
    conditional_expression_t* e;
    constant_expression_t():expression_t(CONSTANT_E),e(NULL) {}
};

struct logical_OR_expression_t
{
    logical_AND_expression_t* e;
    std::list<logical_AND_expression_t*> l;
    logical_OR_expression_t():expression_t(LOGICAL_OR_E),e(NULL) {}
};

struct logical_AND_expression_t
{
    inclusive_OR_expression_t *e;
    std::list<inclusive_OR_expression_t*> l;
    logical_AND_expression_t():expression_t(LOGICAL_AND_E),e(NULL) {}
};

struct inclusive_OR_expression_t
{
    exclusive_OR_expression_t* e;
    std::list<exclusive_OR_expression_t*> l;
    inclusive_OR_expression_t():expression_t(INCLUSIVE_OR_E),e(NULL) {}
};

struct exclusive_OR_expression_t
{
    AND_expression_t* e;
    std::list<AND_expression_t*> l;
    exclusive_OR_expression_t():expression_t(EXCLUSIVE_OR_E),e(NULL) {}
};

struct AND_expression_t
{
    equality_expression_t* e;
    std::list<equality_expression_t*> l;
    AND_expression_t():expression_t(AND_E),e(NULL) {}
};

struct equality_expression_t
{
    enum equality_type
    {
        EQUAL = 0;
        NOT_EQUAL;
    };
    struct obj_t { relational_expression_t* e;equality_type type; };
    relational_expression_t* e;
    std::list<obj_t> l;
    equality_expression_t():expression_t(EQUALITY_E),e(NULL) {}
};


struct relational_expression_t
{
    enum relational_type
    {
        LESS = 0,
        NOT_GREATER,
        GREATER,
        NOT LESS,
    }
    struct obj_t { shift_expression_t* e; relational_type type; };
    shift_expression_t* e;
    std::list<obj_t> l;
    relational_expression_t():expression_t(RELATIONAL_E),e(NULL) {}
};



struct shift_expression_t
{
    enum shift_type
    {
        LEFT_SHIFT = 0;
        RIGHT_SHIFT;
    };
    struct obj_t {additive_expresssion_t* e;shift_type type;};
    additive_expresssion_t* e;
    std::list<obj_t> l;
    shift_expression_t():expression_t(SHIFT_E),e(NULL) {}
};



struct additive_expresssion_t
{
    enum additive_type
    {
        ADD = 0,
        MINUS ,
    };
    struct subject {mutiplicative_expression_t* e;additive_type type;};
    mutiplicative_expression_t* e;
    std::list<subject> l;
    additive_expresssion_t():expression_t(ADDITIVE_E),e(NULL) {}
};


struct mutiplicative_expression_t
{
    enum mutiplicative_type
    {
        MUTIPLICATE = 0,
        DEVIVE ,
    };
    struct subject {unary_expression_t* e;mutiplicative_type type;};
    unary_expression_t* e;
    std::list<subject> l;
    mutiplicative_expression_t():expression_t(MUTIPLICATIVE_E),e(NULL) {}
};


struct unary_expression_t
{
    enum unary_type_1
    {
        INCREASEMENT = 0;
        DECREASEMENT,
    }
    enum unary_type_2
    {
        POSITIVE = 0,
        NEGATIVE,
        NOT,
        BITWISE,
    };

    std::vector<unary_type_1> inc_or_dec;
    expression_t* e; // unary_expression_t or postfix_expression_t
    unary_type_2 type; //only for unary_expression_t;
    unary_expression_t():expression_t(UNARY_E),e(NULL) {}
};


struct postfix_expression_t
{
    enum obj_type
    {
        ID = 0,
        VALUE,
        EXPRESSION,
    };

    struct obj_t
    {
        obj_type type;
        obj_t(obj_type t):type(t) {}
    }

    struct id_obj_t:public obj_t
    {
        symbol s;
        id_obj_t():obj_t(ID) {}
    };

    struct value_obj_t:public obj_t
    {
        value_t* v;
        value_obj_t():obj_t(VALUE),v(NULL) {}
    };

    struct expression_obj_t:public obj_t
    {
        expression_t* e;
        expression_obj_t():obj_t(EXPRESSION),e(NULL) {}
    };
    

    enum op_type
    {
        PARENTHESE = 0,
        SQUARE_BRACKETS,
        DOT,
        INC,
        DEC,
    };

    struct op_t
    {
        op_type type;
        op_t(op_type t):type(t) {}
    }
    
    struct square_bracket_op_t:public op_t
    {
        square_bracket_op():op_t(SQUARE_BRACKETS),e(NULL) {}
        expression_t* e;
    };

    struct parenthese_op_t:public op_t
    {
        assignment_expression_t* e;
        parenthese_op_t():op_t(PARENTHESE),e(NULL) {}
    };

    struct dot_op_t:public op_t
    {
        symbol s;
        dot_op_t():op_t(DOT) {}
    };

    struct increasement_op_t:public op_t
    {
        increasement_op_t():op_t(INC) {}
    };

    struct decreasement_op_t:public op_t
    {
        decreasement_op_t():op_t(DEC) {}
    };

    //////////////////////
    obj_t* o;
    op_t* op;
 
};

struct closure_t //for block
{
    std::size_t idx;

};

struct declaration_t
{
    std::list<init_declarator_t*> l;
};

struct declarator_t
{   
    enum obj_type
    {   
        ID = 0,
        DECLARATOR,
    };
    enum op_type
    {
        PARENTHESE = 0,
        SQUARE_BRACKETS,
    };

    struct obj_t
    {
        obj_type type;
        obj_t(obj_type t):type(t) {}
    };

    struct obj_id_t:public obj_t
    {
        symbol s;
        obj_id_t():obj_t(ID) {}
    };

    struct obj_declarator_t:public obj_t
    {
        declarator_t* d;
        obj_declarator_t():obj_t(DECLARATOR),d(NULL) {}
    };

    struct op_t
    {
        op_type type;
        op_t(op_type t):type(t) {}
    };

    struct parenthese_op_t:public op_t
    {
        std::list<declaration_t*> l;
        parenthese_op_t():op_t(PARENTHESE) {}
    };

    struct square_bracket_op_t:public op_t
    {
        constant_expression_t* e;
        square_bracket_op_t():op_t(SQUARE_BRACKETS),e(NULL) {}
    };


};

struct init_declarator_t
{
    declarator_t* d;
    initializer_t* i;
};

struct initializer_t
{
    assignment_expression_t* e;
};

struct function_t
{
    
};

struct translation_unit_t
{
    
};
struct json_script_grammar
{
    typedef std::string::iterator IT;    
    typedef scanner<IT,line_counter_scanner_policy> scanner_t;
    //////////////////////////declaration/////////////////////////////
    rule<scanner_t,translation_unit_t,_space> translation_unit;
    rule<scanner_t,function_t,_space> function_definition;
    rule<scanner_t,declaration_t,_space> declaration;
    rule<scanner_t,init_declarator_t,_space> init_declarator;
    rule<scanner_t,declarator_t,_space> declarator;
    rule<scanner_t,initializer_t,_space> initializer;
    rule<scanner_t,statement_wrapper,_space> statement;
    rule<scanner_t,closure_t,_space> block;
    rule<scanner_t,expressions_t,_space> expression;
    rule<scanner_t,assignment_expression_t,_space> assignment_expression;
    rule<scanner_t,conditional_expression_t,_space> conditional_expression;
    rule<scanner_t,constant_expression_t,_space> constant_expression;
    rule<scanner_t,logical_OR_expression_t,_space> logical_OR_expression;
    rule<scanner_t,logical_AND_expression_t,_space> logical_AND_expression;
    rule<scanner_t,exclusive_OR_expression_t,_space> exclusive_OR_expression;
    rule<scanner_t,inclusive_OR_expression_t,_space> inclusive_OR_expression;
    rule<scanner_t,AND_expression_t,_space> AND_expression;
    rule<scanner_t,equality_expression_t,_space> equality_expression;
    rule<scanner_t,relational_expression_t,_space> relational_expression;
    rule<scanner_t,shift_expression_t,_space> shift_expression;
    rule<scanner_t,additive_expresssion_t,_space> additive_expresssion;
    rule<scanner_t,mutiplicative_expression_t,_space> mutiplicative_expression;
    rule<scanner_t,unary_expression_t,_space> unary_expression;
    rule<scanner_t,postfix_expression_t,_space> postfix_expression;
    rule<scanner_t,json_value,_space> value;
    rule<scanner_t,json_obj,_space> obj;
    rule<scanner_t,json_member,_space> member;
    rule<scanner_t,json_string,_space> string;
    rule<scanner_t,json_array,_space> array;
    rule<scanner_t,json_real,_space> real;
    ////////////helpers//////////////////////////
    rule<scanner_t,no_context,no_skip> integer;
    rule<scanner_t,char,no_skip> character;
    //////////////////////////defination/////////////////////////
    json_script_grammar()
    {
        translation_unit %= +(function_definition | declaration);

        function_definition %= "function" & declarator & *(declarator % ',') & block;

        declaration %= *(init_declarator % ',');

        init_declarator %= declarator & -( '=' & initializer );

        declarator %=  ( identifier | ('(' & declarator & ')'))
                      & *(   
                             ( '[' & -(constant_expression) & ']' )
                           //| ( '(' & parameter_list & ')' )
                           | ( '(' & (declarator % ',') & ')')
                         );

        initializer %= assignment_expression;

        statement %= (*identifier & -expression) 
                    | block
                    |( "if" & *_space() & '(' & expression & ')' & statement )
                    |("if" & *_space() & '(' & expression & ')' & statement & "else" & statement)
                    |("while" & *_space() & '(' & expression & ')' & statement)
                    |("do" & statement & "while" & *_space() & '(' & expression & ")")
                    |("for" & *_space() & '(' & -expression & ';' -expression & ';' & -expression & ')' statement )
                    | "continue"
                    | "break"
                    | ("return" & -expression);

        block %= '{' &  *declaration & *statement & '}';

        expression %=  assignment_expression % ',';

        assignment_expression %= *(  unary_expression 
                                   & (literal_p("=") | "*=" | "/=" | "%=" | "+=" | "-=" | "<<=" | ">>=" | "&=" | "^=" | "|=" )
                                  ) 
                                   & conditional_expression;

        conditional_expression %= logical_OR_expression;  

        constant_expression %= conditional_expression;

        logical_OR_expression %= logical_AND_expression & *( "||" & logical_AND_expression );

        logical_AND_expression %= inclusive_OR_expression & *( "&&" & inclusive_OR_expression );

        inclusive_OR_expression %= exclusive_OR_expression & *('|' & exclusive_OR_expression );

        exclusive_OR_expression %= AND_expression & *('^' & AND_expression);

        AND_expression %= equality_expression & *('&' & equality_expression);

        equality_expression %= relational_expression & *((literal_p("==") | "!=") & relational_expression);

        relational_expression %= shift_expression & *((literal_p('<') | '>' | "<=" | ">=") & shift_expression );

        shift_expression %= additive_expresssion & *((literal_p("<<") | ">>") & additive_expresssion);

        additive_expresssion %= mutiplicative_expression & *((literal_p('+') | '-') & mutiplicative_expression);

        mutiplicative_expression %= unary_expression & *((literal_p('*') | '/' | '%') & unary_expression);

        unary_expression %=  *(literal_p("++") | "--" ) 
                            & (  
                                  ((literal_p('+') | '-' | '!' | '~' ) & unary_expression)
                                | postfix_expression
                              )
        postfix_expression %=  (identifier | value | ('(' & expression & ')'))
                             & *(
                                   ('[' & expression & ']')
                                 | ('(' & assignment_expression & ')')
                                 | ('.' & identifier)
                                 | "++"
                                 | "--"
                                );

        identifier %= _alpha() & *(_alnum() | '_');

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

//json_obj = load(string)
//json_obj.key 
//


struct command_t {};
struct var_t {}; //for identifier
typedef alternative<var_t,std::string,int> value_t;
typedef std::vector<value_t> value_list_t;
struct access_exp_t //for access_expression
{
    var_t subject;
    var_t attr;
}; 
struct assignment_t
{
    var_t left;
    value_t right;
};

struct command_exp_t 
{
    command_t command;
    value_list_t args;
};


typedef alternative<access_exp_t,command_exp_t> postfix_exp_t;





struct

struct promt_grammar
{
    typedef std::string::iterator IT;    
    typedef scanner<IT,line_counter_scanner_policy> scanner_t;
    rule<scanner_t,command_t,_space> command;
    rule<scanner_t,var_t,_space> identifier;
    rule<scanner_t,,_space> 


    rule<scanner_t,json_string,_space> string;
    ////////////helpers///////////////
    rule<scanner_t,no_context,no_skip> integer;
    rule<scanner_t,char,no_skip> character;

    promt_grammar()
    {
        ////////////////////////////////////
        command %= literal_p("load") | "print";
        identifier %= _alpha() & *(_alnum() | '_');
        value %= identifier | string | constant;
        value_list %= value % ',';
        access_expression %=     identifier
                                & * (    
                                          ('[' & identifier &']')
                                        | ('.' & identifier )
                                    );
        command_expression %=  command & ('(' & value_list &')' );
        postfix_expression %= access_expression
                            | command_expression;
                            
        assignment_expression %= postfix_expression & '=' & postfix_expression;
        constant %=    integer_constant
                    |  character_constant;

        string %= '"' 
                & +(character  <= [=](IT first,IT last)
                                   {
                                        string.cur_ctx() += character.cur_ctx();
                                        character.clear_ctx();
                                        return true;
                                   }
                   )
                & '"';
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
        integer_constant %=  -(_literal('+') | '-') 
                   & +_digit() ;
        character_constant %= '\'' & alnum_p() &'\'';
 

        







    }

    
};
// a[i] f() a.  load(), a.key

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

