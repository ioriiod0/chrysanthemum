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

#include "type_tags.h"
#include "basic_parsers.h"
#include "context_parser.h"
#include "action_parser.h"
#include "../compound/literal_p.h"

template <typename Parser,typename AorC>
inline auto operator<= (Parser&& p,AorC&& ac)
    -> decltype(do_compose(std::forward<Parser>(p),
                           std::forward<AorC>(ac),
                           typename std::remove_reference<Parser>::type::tag_type() ))
{
    typedef typename std::remove_reference<Parser>::type::tag_type tag_type;
    return do_compose(std::forward<Parser>(p),std::forward<AorC>(ac),tag_type());
}

template <typename Converter>
inline auto operator<= (const char* str,Converter&& c)
    -> context_parser<literal_str_p,Converter>
{
    return _context_parser(_literal(str),std::forward<Converter>(c));
}

template <typename Converter>
inline auto operator<= (const std::string& str,Converter&& c)
    -> context_parser<literal_str_p,Converter>
{
    return _context_parser(_literal(str),std::forward<Converter>(c));
}

template <typename Converter>
inline auto operator<= (std::string&& str,Converter&& c)
    -> context_parser<literal_str_p,Converter>
{
    return _context_parser(_literal(std::move(str)),std::forward<Converter>(c));
}

template <typename Converter>
inline auto operator<= (char ch,Converter&& c)
    -> context_parser<literal_ch_p<char>,Converter>
{
    return _context_parser(_literal(ch),std::forward<Converter>(c));
}
#endif
