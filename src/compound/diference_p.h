// ======================================================================================
// File         : diference_p.h
// Author       : Lei Gao 
// Last Change  : 12/07/2011 | 15:42:09 PM | Wednesday,December
// Description  : 
// ======================================================================================


#ifndef __DIFFERENCE_P_H__
#define __DIFFERENCE_P_H__

#include <string>
#include <type_traits>
#include "literal_p.h"

namespace chrysanthemum{

template <typename Parser1,typename Parser2>
class difference_p
{
public: 
    difference_p(Parser1&& p1,Parser2&& p2):
                parser1(std::forward<Parser1>(p1)),
                parser2(std::forward<Parser2>(p2)) {}
public:
    template <typename Iterator>
    bool operator()(Iterator& first,Iterator last)
    {
        Iterator it=first;
        if(!parser2(first,last))
        {   
            first = it;
            if(parser1(first,last))
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


template <typename Parser1,typename Parser2>
inline auto operator- (Parser1&& p1,Parser2&& p2) 
    -> difference_p<Parser1,Parser2>
{
    return difference_p<Parser1,Parser2>(std::forward<Parser1>(p1),std::forward<Parser2>(p2));
}

template <typename Parser1>
inline auto operator- (Parser1&& p1,char ch) 
    //-> decltype(_difference(std::forward<Parser1>(p1),_literal(ch)))
    -> difference_p<Parser1,literal_ch_p<char>>
{
    return _difference(std::forward<Parser1>(p1),
                       _literal(ch));
}

template <typename Parser1>
inline auto operator- (Parser1&& p1,const char* str) 
    //-> decltype(_difference(std::forward<Parser1>(p1),_literal(str)))
    -> difference_p<Parser1,literal_str_p>
{
    return _difference(std::forward<Parser1>(p1),
                       _literal(str));
}

template <typename Parser1>
inline auto operator- (Parser1&& p1,const std::string& str) 
    //-> decltype(_difference(std::forward<Parser1>(p1),_literal(str)))
    -> difference_p<Parser1,literal_str_p>
{
    return _difference(std::forward<Parser1>(p1),
                       _literal(str));
}

template <typename Parser1>
inline auto operator- (Parser1&& p1,std::string&& str) 
    //-> decltype(_difference(std::forward<Parser1>(p1),_literal(str)))
    -> difference_p<Parser1,literal_str_p>
{
    return _difference(std::forward<Parser1>(p1),
                       _literal(std::move(str)));
}

} //end op

} //end namespace
#endif

