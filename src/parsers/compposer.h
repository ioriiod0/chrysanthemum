// ======================================================================================
// File         : compposer.h
// Author       : Lei Gao 
// Last Change  : 12/22/2011 | 17:02:42 PM | Thursday,December
// Description  : 
// ======================================================================================

#ifndef __COMPPOSER_H__
#define __COMPPOSER_H__
#include <type_traits>
#include <string>

#include "basic_parsers.h"
#include "action_parser.h"
#include "../compound/literal_p.h"

template <typename Parser,typename Action>
inline auto operator<= (Parser&& p,Action&& ac)
    -> decltype(_action_parser(std::forward<Parser>(p),
                           std::forward<Action>(ac)) )
{
    return _action_parser(std::forward<Parser>(p),std::forward<Action>(ac));
}

template <typename Action>
inline auto operator<= (const char* str,Action&& c)
    -> action_parser<literal_str_p,Action>
{
    return _action_parser(_literal(str),std::forward<Action>(c));
}

template <typename Action>
inline auto operator<= (const std::string& str,Action&& c)
    -> action_parser<literal_str_p,Action>
{
    return _action_parser(_literal(str),std::forward<Action>(c));
}

template <typename Action>
inline auto operator<= (std::string&& str,Action&& c)
    -> action_parser<literal_str_p,Action>
{
    return _action_parser(_literal(std::move(str)),std::forward<Action>(c));
}

template <typename Action>
inline auto operator<= (char ch,Action&& c)
    -> action_parser<literal_ch_p<char>,Action>
{
    return _action_parser(_literal(ch),std::forward<Action>(c));
}
#endif
