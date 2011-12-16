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
#include "../utility/basic_parser.h"
#include "literal_p.h"

template <typename Parser1,typename Parser2>
class difference_p:
    public basic_parser<typename std::remove_reference<Parser1>::type::iterator,
                        difference_p<Parser1,Parser2>>
{
public:
    typedef typename std::remove_reference<Parser1>::type::iterator Iterator;

    difference_p(Parser1&& p1,Parser2&& p2):
                parser1(std::forward<Parser1>(p1)),
                parser2(std::forward<Parser2>(p2)) {}
    ~difference_p() {}
public:
    bool do_parse(Iterator& first,Iterator last)
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
auto _difference(Parser1&& p1,Parser2&& p2) 
    -> difference_p<Parser1,Parser2>
{
    return difference_p<Parser1,Parser2>(std::forward<Parser1>(p1),std::forward<Parser2>(p2));
}

template <typename Parser1,typename Parser2>
auto operator- (Parser1&& p1,Parser2&& p2) 
    -> difference_p<Parser1,Parser2>
{
    return difference_p<Parser1,Parser2>(std::forward<Parser1>(p1),std::forward<Parser2>(p2));
}

template <typename Parser1>
auto operator- (Parser1&& p1,char ch) 
    -> decltype(_difference(std::forward<Parser1>(p1),_literal<typename std::remove_reference<Parser1>::type::iterator>(ch)))
{
    return _difference(std::forward<Parser1>(p1),
                       _literal<typename std::remove_reference<Parser1>::type::iterator>(ch));
}

template <typename Parser1>
auto operator- (Parser1&& p1,const char* str) 
    -> decltype(_difference(std::forward<Parser1>(p1),_literal<typename std::remove_reference<Parser1>::type::iterator>(str)))
{
    return _difference(std::forward<Parser1>(p1),
                       _literal<typename std::remove_reference<Parser1>::type::iterator>(str));
}

template <typename Parser1>
auto operator- (Parser1&& p1,const std::string& str) 
    -> decltype(_difference(std::forward<Parser1>(p1),_literal<typename std::remove_reference<Parser1>::type::iterator>(str)))
{
    return _difference(std::forward<Parser1>(p1),
                       _literal<typename std::remove_reference<Parser1>::type::iterator>(str));
}
#endif

