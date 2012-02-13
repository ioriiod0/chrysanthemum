// ======================================================================================
// File         : action_parser.h
// Author       : Lei Gao 
// Last Change  : 12/22/2011 | 16:41:01 PM | Thursday,December
// Description  : 
// ======================================================================================

#ifndef __ACTION_PARSER_H__
#define __ACTION_PARSER_H__

#include <type_traits>

#include "parser_base.h"



namespace chrysanthemum{

template <typename Parser,typename Action>
class action_parser:public parser_base<action_parser<Parser,Action>>
{
public:
    action_parser(Parser&& p,Action&& a):
                    p_(std::forward<Parser>(p)),
                    a_(std::forward<Action>(a)) {}
public:
    template <typename Scanner>
    bool operator() (Scanner& scan)
    {
        auto it = scan.cur;
        if(p_(scan))
            return a_(it,scan.cur);
        return false;
    }
private:
    Parser p_;
    Action a_;
};


template <typename Parser,typename Action>
inline auto _action_parser (Parser&& p,Action&& c)
    -> action_parser<Parser,Action>
{
    return action_parser<Parser,Action>(std::forward<Parser>(p),std::forward<Action>(c));
}


} //end namespace

#endif

