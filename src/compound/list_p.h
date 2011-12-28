// ======================================================================================
// File         : list_p.h
// Author       : Lei Gao 
// Last Change  : 12/07/2011 | 15:42:17 PM | Wednesday,December
// Description  : 
// ======================================================================================
#ifndef __LIST_P_H__
#define __LIST_P_H__

#include <type_traits>
#include <string>
#include "../utility/meta_fuctions.h"
#include "literal_p.h"


template <typename Parser1,typename Parser2>
class list_p
{

public:

    list_p(Parser1&& p1,Parser2&& p2):
            parser1_(std::forward<Parser1>(p1)),
            parser2_(std::forward<Parser2>(p2)) {}
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        if(!parser1_(first,last))
            return false;
        Iterator it;
        for(;;)
        {
            it = first;
            if(!parser2_(first,last) || !parser1_(first,last))
            {
                first = it;
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

template <typename P1,typename P2>
inline auto operator% (P1&& p1,P2&& p2) -> list_p<P1,P2>
{
    return list_p<P1,P2>(std::forward<P1>(p1),std::forward<P2>(p2));
}

template <typename T>
inline auto operator% (T&& t,char ch)
    -> list_p<T,literal_ch_p<char>>
{
    return _list(std::forward<T>(t),_literal(ch));
}

template <typename T>
inline auto operator% (T&& t,const char* str)
    //-> decltype(_list(std::forward<T>(t),_literal(str)))
    -> list_p<T,literal_str_p>
{
    return _list(std::forward<T>(t),_literal(str));
}

template <typename T>
inline auto operator% (T&& t,const std::string& str)
    //-> decltype(_list(std::forward<T>(t),_literal(str)))
    -> list_p<T,literal_str_p>
{
    return _list(std::forward<T>(t),_literal(str));
}

template <typename T>
inline auto operator% (T&& t,std::string&& str)
    //-> decltype(_list(std::forward<T>(t),_literal(str)))
    -> list_p<T,literal_str_p>
{
    return _list(std::forward<T>(t),_literal(std::move(str)));
}


#endif

