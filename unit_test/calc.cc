// ======================================================================================
// File         : calc.cc
// Author       : ioriiod0@gmail.com
// Last Change  : 09/20/2012
// Description  : 
// ======================================================================================


#include <string>
#include <iostream>
#include <algorithm>
#include "../all.h"

using namespace chrysanthemum;
using namespace chrysanthemum::ops;

struct grammer
{

    typedef std::string::iterator IT;
    typedef scanner<IT,line_counter_scanner_policy> scanner_t;

    rule<scanner_t,int,_space> integer;
    rule<scanner_t,int,_space> term;
    rule<scanner_t,int,_space> expression;

    grammer()
    {
        
        integer %= (+_digit()) <= [&](IT first,IT last){ integer.cur_ctx() = converter<int>::do_convert(first,last); return true;};

        term %=   integer <= [&](IT first,IT last){ term.cur_ctx() = integer.pop_ctx(); return true;}
                & *(
                                ('*' & integer ) <= [&](IT first,IT last){  term.cur_ctx() *= integer.pop_ctx(); return true; } 
                              | ('/' & integer ) <= [&](IT first,IT last){  term.cur_ctx() /= integer.pop_ctx(); return true; }                       
                    );

        expression %=   term <= [&](IT first,IT last){ expression.cur_ctx() = term.pop_ctx(); return true; }
                      & *(
                                ('+' & term ) <= [&](IT first,IT last){ expression.cur_ctx() += term.pop_ctx(); return true; } 
                              | ('-' & term ) <= [&](IT first,IT last){  expression.cur_ctx() -= term.pop_ctx(); return true; }
                         ) ;
    }

    int excute(std::string& str)
    {
        scanner_t scan(str.begin(),str.end());
        if(expression(scan) && scan.at_end())
        {
            std::cout<<"result:"<<expression.pop_ctx()<<std::endl;
        }
        else
        {
            std::cout<<"syntax error:("<<scan.line_no<<","<<scan.col_no<<")"<<std::endl;
        }
    }
    
};

int main()
{
    grammer g;
    std::string str = " 20+ 2 * 3 + 6/2/3 +1000 ";
    g.excute(str);

    str = " 20 +2 +3";
    g.excute(str);

    str = " 20*2*3 ";
    g.excute(str);

    str = " 20+ 2 * 3a + 6/2/3 +1000 ";
    g.excute(str);
         
}




