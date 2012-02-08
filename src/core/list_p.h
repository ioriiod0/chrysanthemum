// ======================================================================================
// File         : list_p.h
// Author       : Lei Gao 
// Last Change  : 12/07/2011 | 15:42:17 PM | Wednesday,December
// Description  : 
// ======================================================================================
#ifndef __LIST_P_H__
#define __LIST_P_H__

#include <type_traits>
#include <tuple>
#include "../utility/meta_fuctions.h"
#include "literal_p.h"
#include "parser_base.h"

namespace chrysanthemum {


template <typename Parser1,typename Parser2>
class list_p:public parser_base<list_p<Parser1,Parser2>>
{

public:

    list_p(Parser1&& p1,Parser2&& p2):
            parser1_(std::forward<Parser1>(p1)),
            parser2_(std::forward<Parser2>(p2)) {}
public:
    template <typename Scanner>
    bool operator()(Scanner& scan)
    {
        if(!parser1_(scan))
            return false;
        typename Scanner::iterator it;
        for(;;)
        {
            it = scan.save();
            if(!parser2_(scan) || !parser1_(scan))
            {
                scan.load(it);
                break;
            } 
        }
        return true;
    }

   private:
    Parser1 parser1_;
    Parser2 parser2_;

};


template <typename P1,typename P2>
inline auto _list(P1&& p1,P2&& p2) -> list_p<P1,P2>
{
    return list_p<P1,P2>(std::forward<P1>(p1),std::forward<P2>(p2));
}

namespace ops {

/////////////////////////////////////////////////////////////////
template <typename T1,typename T2>
inline auto  operator% (parser_base<T1>&& t1,parser_base<T2>&& t2)
    -> list_p<T1,T2> 
{
    return _list(std::move(t1.derived()),std::move(t2.derived()));
}

template <typename T1,typename T2>
inline auto  operator% (parser_base<T1>& t1,parser_base<T2>& t2) 
    -> list_p<T1&,T2&> 
{
    return _list(t1.derived(),t2.derived());
}

template <typename T1,typename T2>
inline auto  operator% (parser_base<T1>&& t1,parser_base<T2>& t2) 
    -> list_p<T1,T2&> 
{
    return _list(std::move(t1.derived()),t2.derived());
}

template <typename T1,typename T2>
inline auto  operator% (parser_base<T1>& t1,parser_base<T2>&& t2) 
    -> list_p<T1&,T2> 
{
    return _list(t1.derived(),std::move(t2.derived()));
}
///////////////////////////////////char right////////////////////////////////////////////
template <typename T1>
inline auto  operator% (parser_base<T1>&& t1,const char* str) 
    -> list_p<T1,literal_str_p<char>> 
{
    return _list(std::move(t1.derived()),_literal(str));
}

template <typename T1>
inline auto  operator% (const char* str,parser_base<T1>&& t1) 
     -> list_p<literal_str_p<char>,T1> 

{
    return _list(_literal(str),std::move(t1.derived()));
}

template <typename T1>
inline auto  operator% (parser_base<T1>&& t1,const std::string& str) 
     -> list_p<T1,literal_str_p<char>>
{
    return _list(std::move(t1.derived()),_literal(str));
}


template <typename T1>
inline auto  operator% (parser_base<T1>&& t1,std::string&& str) 
     -> list_p<T1,literal_str_p<char>>
{
    return _list(std::move(t1.derived()),_literal(std::move(str)));
}

template <typename T1>
inline auto  operator% (const std::string& str,parser_base<T1>&& t1) 
     -> list_p<literal_str_p<char>,T1> 
{
    return _list(_literal(str),std::move(t1.derived()));
}

template <typename T1>
inline auto  operator% (std::string&& str,parser_base<T1>&& t1) 
     -> list_p<literal_str_p<char>,T1> 
{
    return _list(_literal(std::move(str)),std::move(t1.derived()));
}

template <typename T1>
inline auto  operator% (parser_base<T1>&& t1,char ch) 
    ->list_p<T1,literal_ch_p<char>>
{
    return _list(std::move(t1.derived()),_literal(ch));
}

template <typename T1>
inline auto  operator% (char ch,parser_base<T1>&& t1) 
      -> list_p<literal_ch_p<char>,T1>
{
    return _list(_literal(ch),std::move(t1.derived()));
}
///////////////////////////////////char left////////////////////////////////////
template <typename T1>
inline auto  operator% (parser_base<T1>& t1,const char* str) 
    -> list_p<T1&,literal_str_p<char>> 
{
    return _list(t1.derived(),_literal(str));
}
template <typename T1>
inline auto  operator% (const char* str,parser_base<T1>& t1) 
     -> list_p<literal_str_p<char>,T1&> 

{
    return _list(_literal(str),t1.derived());
}

template <typename T1>
inline auto  operator% (parser_base<T1>& t1,const std::string& str) 
     -> list_p<T1&,literal_str_p<char>>
{
    return _list(t1.derived(),_literal(str));
}

template <typename T1>
inline auto  operator% (parser_base<T1>& t1,std::string&& str) 
     -> list_p<T1&,literal_str_p<char>>
{
    return _list(t1.derived(),_literal(std::move(str)));
}

template <typename T1>
inline auto  operator% (const std::string& str,parser_base<T1>& t1) 
     -> list_p<literal_str_p<char>,T1&> 
{
    return _list(_literal(str),t1.derived());
}
template <typename T1>
inline auto  operator% (std::string&& str,parser_base<T1>& t1) 
     -> list_p<literal_str_p<char>,T1&> 
{
    return _list(_literal(std::move(str)),t1.derived());
}
template <typename T1>
inline auto  operator% (parser_base<T1>& t1,char ch) 
    ->list_p<T1&,literal_ch_p<char>>
{
    return _list(t1.derived(),_literal(ch));
}
template <typename T1>
inline auto  operator% (char ch,parser_base<T1>& t1) 
      -> list_p<literal_ch_p<char>,T1&>
{
    return _list(_literal(ch),t1.derived());
}

///////////////////////////////////wchar_t right////////////////////////////////////////////

template <typename T1>
inline auto  operator% (parser_base<T1>&& t1,const wchar_t* str) 
    -> list_p<T1,literal_str_p<wchar_t>> 
{
    return _list(std::move(t1.derived()),_literal(str));
}

template <typename T1>
inline auto  operator% (const wchar_t* str,parser_base<T1>&& t1) 
     -> list_p<literal_str_p<wchar_t>,T1> 

{
    return _list(_literal(str),std::move(t1.derived()));
}

template <typename T1>
inline auto  operator% (parser_base<T1>&& t1,const std::wstring& str) 
     -> list_p<T1,literal_str_p<wchar_t>>
{
    return _list(std::move(t1.derived()),_literal(str));
}


template <typename T1>
inline auto  operator% (parser_base<T1>&& t1,std::wstring&& str) 
     -> list_p<T1,literal_str_p<wchar_t>>
{
    return _list(std::move(t1.derived()),_literal(std::move(str)));
}

template <typename T1>
inline auto  operator% (const std::wstring& str,parser_base<T1>&& t1) 
     -> list_p<literal_str_p<wchar_t>,T1> 
{
    return _list(_literal(str),std::move(t1.derived()));
}

template <typename T1>
inline auto  operator% (std::wstring&& str,parser_base<T1>&& t1) 
     -> list_p<literal_str_p<wchar_t>,T1> 
{
    return _list(_literal(std::move(str)),std::move(t1.derived()));
}

template <typename T1>
inline auto  operator% (parser_base<T1>&& t1,wchar_t ch) 
    ->list_p<T1,literal_ch_p<wchar_t>>
{
    return _list(std::move(t1.derived()),_literal(ch));
}

template <typename T1>
inline auto  operator% (wchar_t ch,parser_base<T1>&& t1) 
      -> list_p<literal_ch_p<wchar_t>,T1>
{
    return _list(_literal(ch),std::move(t1.derived()));
}
///////////////////////////////////wwchar_t_t left////////////////////////////////////
template <typename T1>
inline auto  operator% (parser_base<T1>& t1,const wchar_t* str) 
    -> list_p<T1&,literal_str_p<wchar_t>> 
{
    return _list(t1.derived(),_literal(str));
}
template <typename T1>
inline auto  operator% (const wchar_t* str,parser_base<T1>& t1) 
     -> list_p<literal_str_p<wchar_t>,T1&> 

{
    return _list(_literal(str),t1.derived());
}

template <typename T1>
inline auto  operator% (parser_base<T1>& t1,const std::wstring& str) 
     -> list_p<T1&,literal_str_p<wchar_t>>
{
    return _list(t1.derived(),_literal(str));
}

template <typename T1>
inline auto  operator% (parser_base<T1>& t1,std::wstring&& str) 
     -> list_p<T1&,literal_str_p<wchar_t>>
{
    return _list(t1.derived(),_literal(std::move(str)));
}

template <typename T1>
inline auto  operator% (const std::wstring& str,parser_base<T1>& t1) 
     -> list_p<literal_str_p<wchar_t>,T1&> 
{
    return _list(_literal(str),t1.derived());
}
template <typename T1>
inline auto  operator% (std::wstring&& str,parser_base<T1>& t1) 
     -> list_p<literal_str_p<wchar_t>,T1&> 
{
    return _list(_literal(std::move(str)),t1.derived());
}
template <typename T1>
inline auto  operator% (parser_base<T1>& t1,wchar_t ch) 
    ->list_p<T1&,literal_ch_p<wchar_t>>
{
    return _list(t1.derived(),_literal(ch));
}
template <typename T1>
inline auto  operator% (wchar_t ch,parser_base<T1>& t1) 
      -> list_p<literal_ch_p<wchar_t>,T1&>
{
    return _list(_literal(ch),t1.derived());
}


} //end namespace op


} //end namespace

#endif

