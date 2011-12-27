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
            return a_(it,first);
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


#endif

