// ======================================================================================
// File         : and_p.h
// Author       : Gao Lei , Qianhong Wang
// Last Change  : 12/17/2011 | 21:30:22 PM | Saturday,December
// Description  : 
// ======================================================================================

#ifndef __and_P_H__
#define __and_P_H__


#include <type_traits>
#include <tuple>
#include "../utility/meta_fuctions.h"
#include "literal_p.h"
#include "parser_base.h"

namespace chrysanthemum{


template <typename... Args>
class and_p:public parser_base<and_p<Args...>> 
{
public:

    template <typename Tuple,typename Scan,std::size_t N>
    struct helper
    {
        inline static bool do_parse(Tuple& t,Scan& scan)
        {
            const static std::size_t Idx = std::tuple_size<Tuple>::value-N;
            if(!std::get<Idx>(t)(scan))
                return false;
            return helper<Tuple,Scan,N-1>::do_parse(t,scan);
        }
    };

    template <typename Tuple,typename Scan>
    struct helper<Tuple,Scan,1>
    {
        inline static bool do_parse(Tuple& t,Scan& scan)
        {
            const static std::size_t Idx = std::tuple_size<Tuple>::value-1;  
            if(!std::get<Idx>(t)(scan))
                return false;
            return true;
        }
    };

    typedef std::tuple<Args...> tuple_type;

public:
    and_p(Args&&... args):tuple_(std::forward<Args>(args)...) {}
public:
    template <typename Scanner>
    bool operator()(Scanner& scan) 
    {
       if(!helper<tuple_type,Scanner,
               std::tuple_size<tuple_type>::value>::do_parse(tuple_,scan))
           return false;
       return true;
    }
private:
    tuple_type tuple_;
};


////////////////////////////////////////////////////////////////////////////
template <typename... Args>
inline auto _and(Args&&... args) -> and_p<Args...> 
{
    return and_p<Args...>(std::forward<Args>(args)...);
}


namespace ops {
////////////////////////////////////////////////////////////////////////////
template <typename T1,typename T2>
inline auto  operator& (parser_base<T1>&& t1,parser_base<T2>&& t2)
    -> and_p<T1,T2> 
{
    return _and(std::move(t1.derived()),std::move(t2.derived()));
}

template <typename T1,typename T2>
inline auto  operator& (parser_base<T1>& t1,parser_base<T2>& t2) 
    -> and_p<T1&,T2&> 
{
    return _and(t1.derived(),t2.derived());
}

template <typename T1,typename T2>
inline auto  operator& (parser_base<T1>&& t1,parser_base<T2>& t2) 
    -> and_p<T1,T2&> 
{
    return _and(std::move(t1.derived()),t2.derived());
}

template <typename T1,typename T2>
inline auto  operator& (parser_base<T1>& t1,parser_base<T2>&& t2) 
    -> and_p<T1&,T2> 
{
    return _and(t1.derived(),std::move(t2.derived()));
}

///////////////////////////////////char right////////////////////////////////////////////
template <typename T1>
inline auto  operator& (parser_base<T1>&& t1,const char* str) 
    -> and_p<T1,literal_str_p<char>> 
{
    return _and(std::move(t1.derived()),_literal(str));
}

template <typename T1>
inline auto  operator& (const char* str,parser_base<T1>&& t1) 
     -> and_p<literal_str_p<char>,T1> 

{
    return _and(_literal(str),std::move(t1.derived()));
}

template <typename T1>
inline auto  operator& (parser_base<T1>&& t1,const std::string& str) 
     -> and_p<T1,literal_str_p<char>>
{
    return _and(std::move(t1.derived()),_literal(str));
}


template <typename T1>
inline auto  operator& (parser_base<T1>&& t1,std::string&& str) 
     -> and_p<T1,literal_str_p<char>>
{
    return _and(std::move(t1.derived()),_literal(std::move(str)));
}

template <typename T1>
inline auto  operator& (const std::string& str,parser_base<T1>&& t1) 
     -> and_p<literal_str_p<char>,T1> 
{
    return _and(_literal(str),std::move(t1.derived()));
}

template <typename T1>
inline auto  operator& (std::string&& str,parser_base<T1>&& t1) 
     -> and_p<literal_str_p<char>,T1> 
{
    return _and(_literal(std::move(str)),std::move(t1.derived()));
}

template <typename T1>
inline auto  operator& (parser_base<T1>&& t1,char ch) 
    ->and_p<T1,literal_ch_p<char>>
{
    return _and(std::move(t1.derived()),_literal(ch));
}

template <typename T1>
inline auto  operator& (char ch,parser_base<T1>&& t1) 
      -> and_p<literal_ch_p<char>,T1>
{
    return _and(_literal(ch),std::move(t1.derived()));
}
///////////////////////////////////char left////////////////////////////////////
template <typename T1>
inline auto  operator& (parser_base<T1>& t1,const char* str) 
    -> and_p<T1&,literal_str_p<char>> 
{
    return _and(t1.derived(),_literal(str));
}
template <typename T1>
inline auto  operator& (const char* str,parser_base<T1>& t1) 
     -> and_p<literal_str_p<char>,T1&> 

{
    return _and(_literal(str),t1.derived());
}

template <typename T1>
inline auto  operator& (parser_base<T1>& t1,const std::string& str) 
     -> and_p<T1&,literal_str_p<char>>
{
    return _and(t1.derived(),_literal(str));
}

template <typename T1>
inline auto  operator& (parser_base<T1>& t1,std::string&& str) 
     -> and_p<T1&,literal_str_p<char>>
{
    return _and(t1.derived(),_literal(std::move(str)));
}

template <typename T1>
inline auto  operator& (const std::string& str,parser_base<T1>& t1) 
     -> and_p<literal_str_p<char>,T1&> 
{
    return _and(_literal(str),t1.derived());
}
template <typename T1>
inline auto  operator& (std::string&& str,parser_base<T1>& t1) 
     -> and_p<literal_str_p<char>,T1&> 
{
    return _and(_literal(std::move(str)),t1.derived());
}
template <typename T1>
inline auto  operator& (parser_base<T1>& t1,char ch) 
    ->and_p<T1&,literal_ch_p<char>>
{
    return _and(t1.derived(),_literal(ch));
}
template <typename T1>
inline auto  operator& (char ch,parser_base<T1>& t1) 
      -> and_p<literal_ch_p<char>,T1&>
{
    return _and(_literal(ch),t1.derived());
}

///////////////////////////////////wchar_t right////////////////////////////////////////////

template <typename T1>
inline auto  operator& (parser_base<T1>&& t1,const wchar_t* str) 
    -> and_p<T1,literal_str_p<wchar_t>> 
{
    return _and(std::move(t1.derived()),_literal(str));
}

template <typename T1>
inline auto  operator& (const wchar_t* str,parser_base<T1>&& t1) 
     -> and_p<literal_str_p<wchar_t>,T1> 

{
    return _and(_literal(str),std::move(t1.derived()));
}

template <typename T1>
inline auto  operator& (parser_base<T1>&& t1,const std::wstring& str) 
     -> and_p<T1,literal_str_p<wchar_t>>
{
    return _and(std::move(t1.derived()),_literal(str));
}


template <typename T1>
inline auto  operator& (parser_base<T1>&& t1,std::wstring&& str) 
     -> and_p<T1,literal_str_p<wchar_t>>
{
    return _and(std::move(t1.derived()),_literal(std::move(str)));
}

template <typename T1>
inline auto  operator& (const std::wstring& str,parser_base<T1>&& t1) 
     -> and_p<literal_str_p<wchar_t>,T1> 
{
    return _and(_literal(str),std::move(t1.derived()));
}

template <typename T1>
inline auto  operator& (std::wstring&& str,parser_base<T1>&& t1) 
     -> and_p<literal_str_p<wchar_t>,T1> 
{
    return _and(_literal(std::move(str)),std::move(t1.derived()));
}

template <typename T1>
inline auto  operator& (parser_base<T1>&& t1,wchar_t ch) 
    ->and_p<T1,literal_ch_p<wchar_t>>
{
    return _and(std::move(t1.derived()),_literal(ch));
}

template <typename T1>
inline auto  operator& (wchar_t ch,parser_base<T1>&& t1) 
      -> and_p<literal_ch_p<wchar_t>,T1>
{
    return _and(_literal(ch),std::move(t1.derived()));
}
///////////////////////////////////wwchar_t_t left////////////////////////////////////
template <typename T1>
inline auto  operator& (parser_base<T1>& t1,const wchar_t* str) 
    -> and_p<T1&,literal_str_p<wchar_t>> 
{
    return _and(t1.derived(),_literal(str));
}
template <typename T1>
inline auto  operator& (const wchar_t* str,parser_base<T1>& t1) 
     -> and_p<literal_str_p<wchar_t>,T1&> 

{
    return _and(_literal(str),t1.derived());
}

template <typename T1>
inline auto  operator& (parser_base<T1>& t1,const std::wstring& str) 
     -> and_p<T1&,literal_str_p<wchar_t>>
{
    return _and(t1.derived(),_literal(str));
}

template <typename T1>
inline auto  operator& (parser_base<T1>& t1,std::wstring&& str) 
     -> and_p<T1&,literal_str_p<wchar_t>>
{
    return _and(t1.derived(),_literal(std::move(str)));
}

template <typename T1>
inline auto  operator& (const std::wstring& str,parser_base<T1>& t1) 
     -> and_p<literal_str_p<wchar_t>,T1&> 
{
    return _and(_literal(str),t1.derived());
}
template <typename T1>
inline auto  operator& (std::wstring&& str,parser_base<T1>& t1) 
     -> and_p<literal_str_p<wchar_t>,T1&> 
{
    return _and(_literal(std::move(str)),t1.derived());
}
template <typename T1>
inline auto  operator& (parser_base<T1>& t1,wchar_t ch) 
    ->and_p<T1&,literal_ch_p<wchar_t>>
{
    return _and(t1.derived(),_literal(ch));
}
template <typename T1>
inline auto  operator& (wchar_t ch,parser_base<T1>& t1) 
      -> and_p<literal_ch_p<wchar_t>,T1&>
{
    return _and(_literal(ch),t1.derived());
}



} //end namespace ops

} //end namespace
#endif
