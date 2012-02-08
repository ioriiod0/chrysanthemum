// ======================================================================================
// File         : diference_p.h
// Author       : Lei Gao 
// Last Change  : 12/07/2011 | 15:42:09 PM | Wednesday,December
// Description  : 
// ======================================================================================


#ifndef __DIFFERENCE_P_H__
#define __DIFFERENCE_P_H__


#include <type_traits>
#include <tuple>
#include "../utility/meta_fuctions.h"
#include "literal_p.h"
#include "parser_base.h"


namespace chrysanthemum{

template <typename Parser1,typename Parser2>
class difference_p:public parser_base<difference_p<Parser1,Parser2> >
{
public: 
    difference_p(Parser1&& p1,Parser2&& p2):
                parser1(std::forward<Parser1>(p1)),
                parser2(std::forward<Parser2>(p2)) {}
public:
    template <typename Scanner>
    bool operator()(Scanner& scan)
    {
        auto it=scan.save();
        if(!parser2(scan))
        {   
            scan.load(it);
            if(parser1(scan))
            {
                return true;
            }
        }
        return false;
    }
private:
    Parser1 parser1;
    Parser2 parser2;
};

template <typename Parser1,typename Parser2>
inline auto _difference(Parser1&& p1,Parser2&& p2) 
    -> difference_p<Parser1,Parser2>
{
    return difference_p<Parser1,Parser2>(std::forward<Parser1>(p1),std::forward<Parser2>(p2));
}

namespace ops {

//////////////////////////////////////////////////////////////////
template <typename T1,typename T2>
inline auto  operator- (parser_base<T1>&& t1,parser_base<T2>&& t2)
    -> difference_p<T1,T2> 
{
    return _difference(std::move(t1.derived()),std::move(t2.derived()));
}

template <typename T1,typename T2>
inline auto  operator- (parser_base<T1>& t1,parser_base<T2>& t2) 
    -> difference_p<T1&,T2&> 
{
    return _difference(t1.derived(),t2.derived());
}

template <typename T1,typename T2>
inline auto  operator- (parser_base<T1>&& t1,parser_base<T2>& t2) 
    -> difference_p<T1,T2&> 
{
    return _difference(std::move(t1.derived()),t2.derived());
}

template <typename T1,typename T2>
inline auto  operator- (parser_base<T1>& t1,parser_base<T2>&& t2) 
    -> difference_p<T1&,T2> 
{
    return _difference(t1.derived(),std::move(t2.derived()));
}

///////////////////////////////////char right////////////////////////////////////////////
template <typename T1>
inline auto  operator- (parser_base<T1>&& t1,const char* str) 
    -> difference_p<T1,literal_str_p<char>> 
{
    return _difference(std::move(t1.derived()),_literal(str));
}

template <typename T1>
inline auto  operator- (parser_base<T1>&& t1,const std::string& str) 
     -> difference_p<T1,literal_str_p<char>>
{
    return _difference(std::move(t1.derived()),_literal(str));
}


template <typename T1>
inline auto  operator- (parser_base<T1>&& t1,std::string&& str) 
     -> difference_p<T1,literal_str_p<char>>
{
    return _difference(std::move(t1.derived()),_literal(std::move(str)));
}

template <typename T1>
inline auto  operator- (parser_base<T1>&& t1,char ch) 
    ->difference_p<T1,literal_ch_p<char>>
{
    return _difference(std::move(t1.derived()),_literal(ch));
}


///////////////////////////////////char left////////////////////////////////////
template <typename T1>
inline auto  operator- (parser_base<T1>& t1,const char* str) 
    -> difference_p<T1&,literal_str_p<char>> 
{
    return _difference(t1.derived(),_literal(str));
}

template <typename T1>
inline auto  operator- (parser_base<T1>& t1,const std::string& str) 
     -> difference_p<T1&,literal_str_p<char>>
{
    return _difference(t1.derived(),_literal(str));
}

template <typename T1>
inline auto  operator- (parser_base<T1>& t1,std::string&& str) 
     -> difference_p<T1&,literal_str_p<char>>
{
    return _difference(t1.derived(),_literal(std::move(str)));
}


template <typename T1>
inline auto  operator- (parser_base<T1>& t1,char ch) 
    ->difference_p<T1&,literal_ch_p<char>>
{
    return _difference(t1.derived(),_literal(ch));
}


///////////////////////////////////wchar_t right////////////////////////////////////////////

template <typename T1>
inline auto  operator- (parser_base<T1>&& t1,const wchar_t* str) 
    -> difference_p<T1,literal_str_p<wchar_t>> 
{
    return _difference(std::move(t1.derived()),_literal(str));
}


template <typename T1>
inline auto  operator- (parser_base<T1>&& t1,const std::wstring& str) 
     -> difference_p<T1,literal_str_p<wchar_t>>
{
    return _difference(std::move(t1.derived()),_literal(str));
}


template <typename T1>
inline auto  operator- (parser_base<T1>&& t1,std::wstring&& str) 
     -> difference_p<T1,literal_str_p<wchar_t>>
{
    return _difference(std::move(t1.derived()),_literal(std::move(str)));
}

template <typename T1>
inline auto  operator- (parser_base<T1>&& t1,wchar_t ch) 
    ->difference_p<T1,literal_ch_p<wchar_t>>
{
    return _difference(std::move(t1.derived()),_literal(ch));
}


///////////////////////////////////wwchar_t_t left////////////////////////////////////
template <typename T1>
inline auto  operator- (parser_base<T1>& t1,const wchar_t* str) 
    -> difference_p<T1&,literal_str_p<wchar_t>> 
{
    return _difference(t1.derived(),_literal(str));
}

template <typename T1>
inline auto  operator- (parser_base<T1>& t1,const std::wstring& str) 
     -> difference_p<T1&,literal_str_p<wchar_t>>
{
    return _difference(t1.derived(),_literal(str));
}

template <typename T1>
inline auto  operator- (parser_base<T1>& t1,std::wstring&& str) 
     -> difference_p<T1&,literal_str_p<wchar_t>>
{
    return _difference(t1.derived(),_literal(std::move(str)));
}


template <typename T1>
inline auto  operator- (parser_base<T1>& t1,wchar_t ch) 
    ->difference_p<T1&,literal_ch_p<wchar_t>>
{
    return _difference(t1.derived(),_literal(ch));
}


} //end op

} //end namespace
#endif

