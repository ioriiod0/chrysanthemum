// ======================================================================================
// File         : action_parser.h
// Author       : Lei Gao 
// Last Change  : 12/22/2011 | 16:41:01 PM | Thursday,December
// Description  : 
// ======================================================================================

#ifndef __ACTION_PARSER_H__
#define __ACTION_PARSER_H__

#include <type_traits>
#include <string> 
#include "type_tags.h"



template <typename Parser,typename Action>
class action_parser
{
public:
    action_parser(Parser&& p,Action&& a):
                    p_(std::forward<Parser>(p)),
                    a_(std::forward<Action>(a)) {}
public:
    template <typename Iterator>
    bool operator() (Iterator& first,Iterator last)
    {
        Iterator it = first;
        if(p_(first,last))
            return a_(p_.ctx());
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

template <typename Parser,typename Action>
inline auto do_compose (Parser&& p,Action&& c,const context_parser_tag&)
    -> action_parser<Parser,Action>
{
    return action_parser<Parser,Action>(std::forward<Parser>(p),std::forward<Action>(c));
}

// template <typename Action>
// inline auto do_compose (const char* str,Action&& c,const context_parser_tag&)
//     -> action_parser<literal_str_p,Action>
// {
//     return _action_parser(_literal(str),std::forward<Action>(c));
// }


// template <typename Action>
// inline auto do_compose (const std::string& str,Action&& c,const context_parser_tag&)
//     -> action_parser<literal_str_p,Action>
// {
//     return _action_parser(_literal(str),std::forward<Action>(c));
// }

// template <typename Action>
// inline auto do_compose (char ch,Action&& c)
//     -> decltype(_action_parser(_literal(ch),std::forward<Action>(c)),const )
// {
//     return _action_parser(_literal(ch),std::forward<Action>(c));
// }


#endif

