// ======================================================================================
// File         : context_parser.h
// Author       : Lei Gao 
// Last Change  : 12/22/2011 | 16:39:34 PM | Thursday,December
// Description  : 
// ======================================================================================

#ifndef __CONTEXT_PARSER_H__
#define __CONTEXT_PARSER_H__
#include <type_traits>
#include <string>
#include "../compound/literal_p.h"
#include "type_tags.h"



template <typename Parser,typename Converter>
class context_parser:public context_parser_base
{
public:
    typedef typename Converter::ctx_type ctx_type;

    context_parser(Parser&& p,Converter&& c):
                    p_(std::forward<Parser>(p)),
                    c_(std::forward<Converter>(c)) {}
public:
    template <typename Iterator>
    bool operator() (Iterator& first,Iterator last)
    {
        Iterator it = first;
        if(p_(first,last))
            return c_(it,first);
        return false;
    }
    
    ctx_type& ctx()
    {
        return c_.ctx();
    }

    const ctx_type& ctx() const
    {
        return c_.ctx();
    }

 private:
    Parser p_;
    Converter c_;
};



template <typename Parser,typename Converter>
inline auto _context_parser (Parser&& p,Converter&& c)
    -> context_parser<Parser,Converter>
{
    return context_parser<Parser,Converter>(std::forward<Parser>(p),std::forward<Converter>(c));
}


/////////////////////////////////////////////////////////////////////////////////////
template <typename Parser,typename Converter>
inline auto do_compose (Parser&& p,Converter&& c,const basic_parser_tag&)
    -> context_parser<Parser,Converter>
{
    return context_parser<Parser,Converter>(std::forward<Parser>(p),std::forward<Converter>(c));
}

// template <typename Converter>
// inline auto do_compose (const char* str,Converter&& c)
//     -> context_parser<literal_str_p,Converter>
// {
//     return _context_parser(_literal(str),std::forward<Converter>(c));
// }

// template <typename Converter>
// inline auto do_compose (const std::string& str,Converter&& c)
//     -> context_parser<literal_str_p,Converter>
// {
//     return _context_parser(_literal(str),std::forward<Converter>(c));
// }

// template <typename Converter>
// inline auto do_compose (std::string&& str,Converter&& c)
//     -> context_parser<literal_str_p,Converter>
// {
//     return _context_parser(_literal(std::move(str)),std::forward<Converter>(c));
// }

// template <typename Converter>
// inline auto do_compose (char ch,Converter&& c)
//     -> context_parser<literal_ch_p<char>,Converter>
// {
//     return _context_parser(_literal(ch),std::forward<Converter>(c));
// }

#endif


