// ======================================================================================
// File         : compposer.h
// Author       : Lei Gao , Qianhong Wang
// Last Change  : 12/22/2011 | 17:02:42 PM | Thursday,December
// Description  : 
// ======================================================================================

#ifndef __COMPPOSER_H__
#define __COMPPOSER_H__
#include <type_traits>
#include <string>

#include "action_parser.h"
#include "literal_p.h"


namespace chrysanthemum {

namespace ops {

template <typename Parser,typename Action>
inline auto operator<= (parser_base<Parser>&& p,Action&& ac)
    -> action_parser<Parser,Action>
{
    return _action_parser(std::move(p.derived()),std::forward<Action>(ac));
}

template <typename Parser,typename Action>
inline auto operator<= (parser_base<Parser>& p,Action&& ac)
    -> action_parser<Parser&,Action>
{
    return _action_parser(p.derived(),std::forward<Action>(ac));
}


/////////////////////////////////char////////////////////////////
template <typename Action>
inline auto operator<= (const char* str,Action&& c)
    -> action_parser<literal_str_p<char>,Action>
{
    return _action_parser(_literal(str),std::forward<Action>(c));
}

template <typename Action>
inline auto operator<= (const std::string& str,Action&& c)
    -> action_parser<literal_str_p<char>,Action>
{
    return _action_parser(_literal(str),std::forward<Action>(c));
}

template <typename Action>
inline auto operator<= (std::string&& str,Action&& c)
    -> action_parser<literal_str_p<char>,Action>
{
    return _action_parser(_literal(std::move(str)),std::forward<Action>(c));
}

template <typename Action>
inline auto operator<= (char ch,Action&& c)
    -> action_parser<literal_ch_p<char>,Action>
{
    return _action_parser(_literal(ch),std::forward<Action>(c));
}
////////////////////////////////////wchar_t//////////////////////////////
template <typename Action>
inline auto operator<= (const wchar_t* str,Action&& c)
    -> action_parser<literal_str_p<wchar_t>,Action>
{
    return _action_parser(_literal(str),std::forward<Action>(c));
}

template <typename Action>
inline auto operator<= (const std::wstring& str,Action&& c)
    -> action_parser<literal_str_p<wchar_t>,Action>
{
    return _action_parser(_literal(str),std::forward<Action>(c));
}

template <typename Action>
inline auto operator<= (std::wstring&& str,Action&& c)
    -> action_parser<literal_str_p<wchar_t>,Action>
{
    return _action_parser(_literal(std::move(str)),std::forward<Action>(c));
}

template <typename Action>
inline auto operator<= (wchar_t ch,Action&& c)
    -> action_parser<literal_ch_p<wchar_t>,Action>
{
    return _action_parser(_literal(ch),std::forward<Action>(c));
}
}//end namespace ops

} // end namespace
#endif
